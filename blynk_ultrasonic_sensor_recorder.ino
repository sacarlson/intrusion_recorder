/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Follow us:                  http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************

  This example shows how value can be pushed from Arduino to
  the Blynk App.

  WARNING :
  For this example you'll need Adafruit DHT sensor libraries:
    https://github.com/adafruit/Adafruit_Sensor
    https://github.com/adafruit/DHT-sensor-library

  App project setup:
    Value Display widget attached to V5
    Value Display widget attached to V6
 *************************************************************/

 // This project is to detect any intrution into a space and to record the time and distance from your object
 // this version uses the ultrasonic distance measurment device HCSR04
 // later planed to replace or add the HC-SR505 to mark instrution points
 // but that device only acts as on or off intrution without distance so might keep both as an option 
 // for this project I used an arduino uno with wifi.  later I would like to implement with a esp-32 
 // with the esp-32 we can run in sleep mode with very little power so would be able to run with a battery for long term remote monitoring with no power supply

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial


#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>
#include <SoftwareSerial.h>
#include <HCSR04.h>


// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "wifinetname";
char pass[] = "wifipassword";

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
//char auth[] = "--------hzoKa";

// for local auth you can go to admin http and click user
// copy token and paste here
//char auth[] = "-------ZLSl";
// funtracker token for ultrasonic_dis_count app
char auth[] = "--------9oYF ";

// Software Serial on Uno, Nano...
SoftwareSerial EspSerial(2, 3); // RX, TX

// Your ESP8266 baud rate:
#define ESP8266_BAUD 9600

ESP8266 wifi(&EspSerial);

//WidgetTerminal terminal(V0);

BlynkTimer timer;

// pins for HCSR04 were only chosen that were easy for me to see location.  you can use most any 2 pins from 4 - 13
// pins 2 and 3 on this project are jumped to esp8266 for wifi coms
HCSR04 hc(7,6);//initialisation class HCSR04 (trig pin , echo pin)

int count = 0;
int trig_distance = 10;
int min_distance = 4000;
//int val;
// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
void sendSensor()
{
  //Serial.println("start sendSensor");
  int distance = hc.dist();
  Blynk.virtualWrite(V5, 0);
  if (distance < trig_distance) {
    count++;
    Blynk.virtualWrite(V0, count);
    Blynk.virtualWrite(V5, 1.01/distance);
    digitalWrite(LED_BUILTIN, HIGH); 
    Serial.println(count);
  }else {
    digitalWrite(LED_BUILTIN, LOW); 
  }
   
  Serial.println("distance");
  Serial.println(distance);
  Blynk.virtualWrite(V1, distance);
 
  if (min_distance > distance){
    min_distance = distance;
    Blynk.virtualWrite(V4, min_distance);
  }
  Serial.println("end sendSensor");
}

void setup()
{
  // Debug console
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  //pinMode(11, INPUT_PULLUP);// tank level high
   
  // Set ESP8266 baud rate
  EspSerial.begin(ESP8266_BAUD);
  
  //Blynk.begin(auth, wifi, ssid, pass);
  Blynk.begin(auth, wifi, ssid, pass, "www.funtracker.site", 8080);  //scotty's privated blynk server
  // You can also specify server:
  //Blynk.begin(auth, wifi, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, wifi, ssid, pass, IPAddress(192,168,1,100), 8080);
  Blynk.virtualWrite(V3,trig_distance);
  Blynk.virtualWrite(V0,count);
  Blynk.virtualWrite(V4,min_distance);
  timer.setInterval(2000L, sendSensor);
}

BLYNK_WRITE(V3){
  // trig_distance parameter entry in cm
  trig_distance = param.asInt();
  Serial.println("trig_distance");
  Serial.println(trig_distance);
}

BLYNK_WRITE(V5){
  // reset count and other values to start positions
  count = 0;
  min_distance = 4000;
  trig_distance = 10;
  Blynk.virtualWrite(V3,trig_distance);
  Blynk.virtualWrite(V0,count);
  Blynk.virtualWrite(V4,min_distance);
}

void loop()
{
  Blynk.run();
  timer.run();
}
