#include <elapsedMillis.h>

int rly0 = 9;
int rly1 = 10;
int rly2 = 11;
int rly3 = 12;
void setup()
{
  Serial.begin(115200);
  Serial1.begin(115200);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(8, OUTPUT);
  digitalWrite(5, HIGH);
  digitalWrite(4, LOW);
  digitalWrite(8, HIGH);
  delay(3000);
  digitalWrite(8, LOW);
  Serial.println("A7 Power ON!");
  pinMode(rly0, OUTPUT);
  pinMode(rly1, OUTPUT);
  pinMode(rly2, OUTPUT);
  pinMode(rly3, OUTPUT);
  digitalWrite(rly0, 1);
  digitalWrite(rly1, 1);
  digitalWrite(rly2, 1);
  digitalWrite(rly3, 1);

  //  delay(8000);
  Serial1.println("AT+CMGF=1");
  delay(1000);
}
String details = "";
bool readSMS = false;
elapsedMillis timer;
void loop()
{
  char dat;


  while (Serial1.available()) {
    dat = Serial1.read();
    details += String(dat);
    if (!readSMS) {
      timer = 0;
      readSMS = !readSMS;
    }
  }
  if (details != "" && timer > 1000 && readSMS) {
    details.trim();
    int x = details.indexOf("+CMT:");
    int y = details.indexOf("\n");
    int len = details.length();
    if ( x > y && len > 68) {
      String phone = details.substring(x + 11, x + 20);
      String message = details.substring(69);
      Serial.println("phone number = " + String(phone));
      Serial.println("message = " + String(message));
      sendSMS("SMS RECEIVED :" + message + "\nReply :We will check on you soon", phone);
    }
    readSMS = !readSMS;
    details = "";
  }

}
void sendSMS(String sms, String number) {
  delay(700);
  Serial1.println("AT+CMGS=\"+255" + number + "\""); //change ZZ with country code and xxxxxxxxxxx with phone number to sms
  delay(700);
  Serial1.print(sms); //text content
  delay(700);
  Serial1.write(26);
  delay(700);
}
