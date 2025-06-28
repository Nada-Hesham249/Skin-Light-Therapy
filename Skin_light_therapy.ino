#include <Key.h>
#include <Keypad.h>
#include <LiquidCrystal_I2C.h>

const byte ROWS = 4; // Number of rows in the keypad
const byte COLS = 4; // Number of columns in the keypad

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {13, 5, 11, 12}; // Connect to the row pinouts of the 
byte colPins[COLS] = {2,3,4, 7}; // Connect to the column pinouts of the keypad

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

LiquidCrystal_I2C lcd(0x27,16,2);
#define trigPin 8
#define echoPin A1 
#define red_IR 9
#define blue 6
#define UV 10
#define buzzer A2
char c, I ;
int led;
int x=0, t,i=0;
float distance=15 , duration;
void setup() {
pinMode(trigPin, OUTPUT);
 pinMode(echoPin, INPUT);
 pinMode(red_IR, OUTPUT);
 pinMode(UV, OUTPUT);
 pinMode(blue, OUTPUT);
 pinMode(buzzer, OUTPUT);
lcd.init();
lcd.backlight();
lcd.setCursor(0,0);
lcd.print("CHOOSE THE CASE");
delay(1500);
 lcd.clear();
lcd.setCursor(0,0);
lcd.print("A)INFLAMMATION");
lcd.setCursor(0,1);
lcd.print("B)ACNE C)ECZEMA ");
digitalWrite(red_IR, LOW);
digitalWrite(blue, LOW);
digitalWrite(UV, LOW);
}

void loop() {
     c= keypad.getKey() ; 
     if (c != NO_KEY) {
     if(c=='A' || c=='B' || c=='C' )
      { 
       lcd.clear();
       lcd.print("CHOOSE INTENSITY");
        delay(1500);
      lcd.clear();
      lcd.print("1)LOW  2)MEDIUM");
      lcd.setCursor(0,1);
      lcd.print("3)HIGH");
       
    while (x==0) {
        I = keypad.getKey();
        if(I=='1' ||I=='2'  ||I=='3' ){
          x=1;
          lcd.clear();
           lcd.print("    PUT THE");
           lcd.setCursor(0,1);
           lcd.print("  INJURED PART");
           dist1();
          lcd.print("  STARTING NOW!");
          delay(2000);
          lcd.clear();
        }
        else
        {
          x=0;
        }
      } 
    
  if(c=='A'&& x==1)
  {led=map(I,'0','3',0,255);

   Serial.println(led);
   analogWrite(red_IR,led);
    Serial.println("red");
    time();
   }
  
  else if(c=='B'&& x==1)
  {led=map(I,'0','3',0,255);
   analogWrite(blue,led);
         Serial.println("blue");
    time();
}
  
  else if(c=='C'&& x==1)
  {led=map(I,'0','3',0,255);
   analogWrite(UV,led);
         Serial.println("UV");
    time();
}}} 
  }

 void reset (){
    x=0;
    digitalWrite(red_IR, LOW);
    digitalWrite(blue, LOW);
    digitalWrite(UV, LOW);
    do{
      i++;
    tone(buzzer,300,800);
     lcd.print("    THE END!");
   delay(1000);
   noTone(buzzer);
    }while(i<2);
   lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("CHOOSE THE CASE");
    delay(2000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("A)IFLAMMATION");
    lcd.setCursor(0,1);
    lcd.print("B)ACNE C)ECZEMA ");
  }

void time(){
  for( t = 10 ;t>=0;t--){
    
    lcd.print("time is:");
    if(t<10){
         lcd.print("0");
    }
    lcd.print(t);
    if(t!=0)
   { dist2();}
    Serial.println(distance);
   delay(1000);
        lcd.clear();
  }
    reset();
}

void dist1(){
   digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
 distance = duration * 0.034 / 2;
 
 for(;distance>=15;){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
   duration = pulseIn(echoPin, HIGH);
 distance = duration * 0.034 / 2;
  digitalWrite(red_IR, LOW);
    digitalWrite(blue, LOW);
    digitalWrite(UV, LOW);
 }
}
void dist2(){
   digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
 distance = duration * 0.034 / 2;
 
 for(;distance>=15;){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
   duration = pulseIn(echoPin, HIGH);
 distance = duration * 0.034 / 2;
  digitalWrite(red_IR, LOW);
    digitalWrite(blue, LOW);
    digitalWrite(UV, LOW);
    tone(buzzer,300,400);
   delay(1000);
 }
 if(c=='A')
 {
analogWrite(red_IR,led);
 }
  if(c=='B')
 {
analogWrite(blue,led);
 }
  if(c=='C')
 {
analogWrite(UV,led);
 }
}
