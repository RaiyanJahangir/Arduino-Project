#include<TimerOne.h>
#include <SoftwareSerial.h>
#include "pitches.h"
SoftwareSerial mySerial (9, 10) ;//RX-9, TX-10
// notes in the melody:
int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};
#define ledPin 7

String input;
int i;
String my_name;


#define USE_ARDUINO_INTERRUPTS true
// Set-up low-level interrupts for most acurate BPM math.
#include <PulseSensorPlayground.h>
// Includes the PulseSensorPlayground Library.
// Variables
const int PulseWire = 0;

// PulseSensor PURPLE WIRE connected to ANALOG PIN D
const int LED13 = 13;
//The on-board Arduino LED, close to PIN 13.
int Threshold = 550;
//determine which Signal to "count as a beat" and which to ignore.
//(/ Use the "Getting Started Project" to fine-tune Threshold Value beyond default setting.
// Otherwise leave the default "550" value.
PulseSensorPlayground pulseSensor; // Creates an instance of the PulseSensorPlayground object called "pulseSensor"

void setup (){

  pinMode(ledPin,OUTPUT);
  //pinMode(buzzer_Pin,OUTPUT);
//85%-> 96 (normal) 
//70%-> 48 (low)
//77%->63  (normal)
mySerial . begin (9600) ; 
Serial.begin(9600) ;
// For Serial Monitor
// Configure the PulseSensor object, by assigning our variables to it.
pulseSensor. analogInput (PulseWire) ;

pulseSensor. blinkOnPulse (LED13) ;
pulseSensor . setThreshold (Threshold) ;
// Double-check the "pulseSensor" object was created and "began" seeing a signal.
if (pulseSensor.begin () ) {
Serial.println("We created a pulseSensor Object !"); //This prints one time at Arduino power-up, or on Arduino reset.
}
}



void loop () {
  int noteDuration;
  Serial.print("Enter your Name:");
  //analogWrite(ledPin,0);
  while(Serial.available()==0){}
        
        my_name = Serial.readStringUntil('\n');
         Serial.println();
         Serial.println();
        Serial.println("Nice to meet you, " + my_name + "!");
   
int myBPM = pulseSensor.getBeatsPerMinute();


if (pulseSensor.sawStartOfBeat() ) {
Serial.println ("A HeartBeat Happened ! ");
Serial.print("BPM: ");
Serial.println (myBPM);
if( myBPM < 60){
  Serial.println();
  
  Serial.println(my_name+", Your Heart Rate is Low and you are suffering from BRADYCARDIA");
  analogWrite(ledPin,255);
  int noteDuration = 2000;
    tone(6, melody[0], noteDuration);
    mySerial.println();
    mySerial.println();
  
     mySerial.println("AT+CMGF=1");
   delay(1000);
    mySerial.println("OK");
   delay(1000);
   mySerial.println("AT+CMGS=\"+8801757403666\"\r"); // leplace s with Mobile mader
   delay(1000);
    mySerial.print(my_name+"'s heart Rate is Low and suffering from BRADYCARDIA\n");
    mySerial.println();
    mySerial.println();
    mySerial.println("---------------------------------------------------------------------");
    //int pauseBetweenNotes = noteDuration * 1.30;
    //delay(pauseBetweenNotes);
    //tone(6, 0, noteDuration);
}
else if( myBPM > 100){
  Serial.println();
  Serial.println();
  Serial.println(my_name+", Your Heart Rate is High and you are suffering from TACHYCARDIA");
  analogWrite(ledPin,255);
   noteDuration = 2000;
    tone(6, melody[0], noteDuration);
     mySerial.println();
     
     mySerial.println("AT+CMGF=1");
   delay(1000);
    mySerial.println("OK");
   delay(1000);
   mySerial.println("AT+CMGS=\"+8801757403666\"\r"); // leplace s with Mobile mader
   delay(1000);
     mySerial.println(my_name+"'s Heart Rate is High and suffering from TACHYCARDIA");
     mySerial.println();
     mySerial.println();
     mySerial.println("----------------------------------------------------------------------");
    //int pauseBetweenNotes = noteDuration * 1.30;
    //delay(pauseBetweenNotes);
    //tone(6, 0, noteDuration);
}
else{
  Serial.println();
  Serial.println(my_name+", Your Heart rate is normal");
  analogWrite(ledPin,0);
  mySerial.println();
  mySerial.println();
  
   mySerial.println("AT+CMGF=1");
   delay(1000);
   mySerial.println("OK");
   delay(1000);
   mySerial.println("AT+CMGS=\"+8801757403666\"\r"); // leplace s with Mobile mader
   delay(1000);
  mySerial.println(my_name+"'s Heart rate is normal");
  mySerial.println();
  mySerial.println();
  mySerial.println("---------------------------------------------------------------------------");
}
}
//tone(6, 0, noteDuration);
// Print the value inside of myBEK.
Serial.println();
Serial.println();
delay (20);
  
// considered best practice in a simple sketch.
}
