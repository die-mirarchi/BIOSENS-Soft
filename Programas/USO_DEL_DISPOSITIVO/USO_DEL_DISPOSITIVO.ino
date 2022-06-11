#include <Data.h>
#include <Block.h>
#include <SMSend.h>
#include <RTCuse.h>
#include <LCDuse.h>
#include <Environment.h>

#define MODULOS {5, 6, 7}
const uint8_t Modulos[] = MODULOS;
#define RST 8
#define TIME_HOLD_RST 15000

/***************************************************************************************************************
   Objects instantiation.
 ***************************************************************************************************************/
SMSend sms(&Serial2);   //Object in charge of the SIM800L for SMS send and recieve. Default with 9600 bd.
LCDuse lcd;             //Object in charge of the LCD 16x2 manage.
RTCuse rtc;             //Object in charge of the RTC manage (Time and EEPROM)
Block b;                //Object in charge of the blocks of data, we will use only one.
//Data Structures to save on EEPROM, every Data object is in charge of the Data manage on RTC EEPROM
Data estructuraDeDatos[] = {  *(new Data("PHONE1",  0)),        //Master phone, offset 0
                              *(new Data("PHONE2", 20)),        //Secondary phone, offset 20
                              *(new Data("PHONE3", 40)),        //Third phone, offset 40
                              *(new Data("ALERTS", 60)),        //Alerts time, offset 60
                              *(new Data("DATE1" , 70)),        //Date 1, offset 70
                              *(new Data("DATE2" , 100)),       //Date 2, offset 100
                              *(new Data("DATE3" , 130))        //Date 3, offset 130
                           };
Environment env(&b, &rtc);  //Object in charge of provide facility to the program menu and operations.

/***************************************************************************************************************
   Global flags and counters variables.
 ***************************************************************************************************************/
////For LCD screen
unsigned long timeCount = millis();      //Time counter on miliseconds for the LCD, reseteable.
int vecesCount = 0;                      //Count the times that the timeCount passed a certain time for selecting what information to show.
////For Alert time count
unsigned long timeCountAlert[] = {millis(), millis(), millis()};  //Time counter on miliseconds for the alerts, reseteable.
bool flagCurrent[] = {true, true, true};                  //Flag that determines if the current is working or not. Save the value when a change is captured.
////For RST Button
unsigned long timeCountRST;
bool flagRST = false;


/***************************************************************************************************************
   Setup and Loop. Main program.
 ***************************************************************************************************************/
void setup() {
  b.init(estructuraDeDatos, 1000);    //Initialize the block of information in the byte 1000 with the data provided and its features.
  lcd.init();                         //Initialize the LCD for its use.
  randomSeed(analogRead(0));
  String randCode = String(random(111, 999));
  for (int i = 0; i < 3; i++) {
    pinMode(Modulo[i], INPUT); //Setup the module that sense current as an input pin.
  }
  pinMode(RST, INPUT);
}

void loop() {
  showInScreen(timeCount, 10); //Show different info in LCD each 10 seconds using timeCount for counting time.

  verifyCurrent();              //Verify electric current, if not send messages each alertTime minutes to every phone configured.
  manageSMSRecieve();           //Verify received messages and answer them if exists.
}

/***************************************************************************************************************
   Receive of messages and send its answers functions.
 ***************************************************************************************************************/
void manageSMSRecieve() {
  String mensaje = sms.receiveSMS();                        //Receive the whole SMS with all info.
  if (sms.isSMS(mensaje)) {
    String code = sms.getMessageSMS(mensaje);
    if (code == randCode)
    {
      if (!Environment::isAPhoneNumber(env.getPhoneString(0))) {
        b.getDataObject("PHONE1").setData(sms.getMessageInfo(PHONE_NUMBER, mensaje));
      }
      else if (!Environment::isAPhoneNumber(env.getPhoneString(1))) {
        b.getDataObject("PHONE2").setData(sms.getMessageInfo(PHONE_NUMBER, mensaje));
      }
      else if (!Environment::isAPhoneNumber(env.getPhoneString(2))) {
        b.getDataObject("PHONE3").setData(sms.getMessageInfo(PHONE_NUMBER, mensaje));
      }
    }
  }

}
if (sms.isSMS(mensaje) && isFromAdmitedPhone(mensaje)) {  //Make sure what we receive is a message and if it was sent by an admited phone number.
  String message = sms.getMessageSMS(mensaje);            //Storage the message on the SMS received.
  String arg = "";
  if (message.startsWith("C") || message.startsWith("c")) { //Every command who have an argument starts with the 'C' or 'c' character.
    //Cut the argument on the message and storage it in another variable.
    int spacesCont = 0, argStart;
    for (int i = 0; i < message.length(); i++) {
      if (spacesCont == 2) arg += message[i];             //Argument is in the 3rd word, 2 spaces.
      if (message[i] == ' ') {                            //Count the spaces.
        spacesCont++;
        if (spacesCont < 3) argStart = i + 1;             //Save the offset of the argument in String.
      }
    }
    message = message.substring(0, argStart - 1) + "  ";  //Change the message cuting the argument.
  }
  arg.remove(arg.length() - 2);                           //Remove two unnecessary characters at the end of the argument.
  //Send an SMS to the number who sent the message answering his/her request.
  sms.sendSMS(sms.getMessageInfo(PHONE_NUMBER, mensaje), env.runMenuOption(Environment::keywordToOption(message), arg));
}
}

//Return if the message received is froma an admited phone number on the system.
bool isFromAdmitedPhone(String _mensaje) {
  String nro = sms.getMessageInfo(PHONE_NUMBER, _mensaje);   //Drill down the message to get the phone number who sent it.
  for (int i = 0; i < 3; i++) {
    if (nro == env.getPhoneString(i)) return true;
  }     //If some storaged number on EEPROM concides with the phone who sent the message return true.
  return false;                                         //Else return false.
}

/***************************************************************************************************************
   Current state information, action functions and reset button.
 ***************************************************************************************************************/
void verifyCurrent() {
  for (int i = 0; i < 3; i++) {
    if ( (isCurrentActive(i) != flagCurrent[i])    //If the actual current state is different from the previous value
         || ( !flagCurrent[i] && (millis() - timeCountAlert[i]) / 1000 > env.getAlertTime().getData().toInt() * 60)) { //Or the current is not working and the alert time has passed.
      flagCurrent[i] = isCurrentActive(i);                            //The flag will change or mantain its value depending on the current state.
      for (int j = 0; j < 3; j++) {
        if (Environment::isAPhoneNumber(env.getPhoneString(i))) { //If the number getted in the EEPROM is configured send him the alert.
          sms.sendSMS(env.getPhoneString(j), String("Estado de la luz: " + currentState(Modulos[i]) + "."));
          delay(5000);
        }
      }
      timeCountAlert[i] = millis();                                  //Reset the alerts timer.
    }
  }
}


void checkRST() {
  if (isRSTActive() != flagRST && isRSTActive()) {
    timeCountRST = millis();
    flagRST = isRSTActive();
  }
  if (isRSTActive() != flagRST && !isRSTActive()) {
    timeCountRST = millis();
    flagRST = isRSTActive();
  }
  if (isRSTActive() && flagRST == isRSTActive() && (millis() - timeCountRST) > TIME_HOLD_RST) {
    b.getDataObject("PHONE1").setData("-NO DEFINIDO-");
    b.getDataObject("PHONE2").setData("-NO DEFINIDO-");
    b.getDataObject("PHONE3").setData("-NO DEFINIDO-");
  }
}

//Get if the current is working or not.
bool isCurrentActive(int index) {
  return digitalRead(Modulos[index]);  //Program this with Fabio module.
}
bool isRSTActive() {
  return digitalRead(RST);
}

//Get if the current is working or not as a String.
String currentState(int _pin) {
  if (digitalRead(_pin)) return "En funcionamiento";
  else return "Cortada";
}


/***************************************************************************************************************
   LCD information showing functions.
 ***************************************************************************************************************/
//Return true if the time on argument is between two another times.
bool isTimeBetween(unsigned long timePassed, int seg1, int seg2) {
  return timePassed >= seg1 && timePassed < seg2;
}

void showInScreen(unsigned long _tim, int _period) {
  if (Environment::isAPhoneNumber(env.getPhoneString(0))) {
    _tim = (millis() - _tim) / 1000;          //Convert tim to seconds
    if (_tim < _period * vecesCount) return; //Verify if it would change the text, otherwise stop function execution.
    vecesCount++;                            //Increment counter for print another info on screen.
    //Choose what information we're gonna print on screen according to the time that has passed.
    if     (isTimeBetween(_tim,    0    , _period  ))  lcd.print("TELEFONO MASTER:", env.getPhone(0));    //Show master phone number
    else if (isTimeBetween(_tim, _period  , _period * 2))  lcd.print("TELEFONO 2:"     , env.getPhone(1)); //Show second phone number
    else if (isTimeBetween(_tim, _period * 2, _period * 3))  lcd.print("TELEFONO 3:"     , env.getPhone(2)); //Show third phone number
    else if (isTimeBetween(_tim, _period * 3, _period * 4))  lcd.print("TIEMPO ALERTAS:" , String(env.getAlertTime().getData() + " minutos.")); //Show configured Alert time.
    else {
      timeCount = millis();  //Reset all values for start showing info from the beginning.
      vecesCount = 0;
    }
  }
  else {
    lcd.print("CODIGO: ", randCode);
  }
}
