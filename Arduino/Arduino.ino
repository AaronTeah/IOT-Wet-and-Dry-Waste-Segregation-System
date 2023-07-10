#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

Servo myservo;
Servo myservo1; 

int irsensor = 2;
int pos = 0;
int value = A0;
int state = 0;

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2); // Changed the number of rows from 4 to 2

void setup() { 
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("TRASH IN");
  lcd.setCursor(0, 1);
  lcd.print("CASH OUT");
  delay(3000);
  lcd.clear();
  Serial.begin(9600);
  myservo.attach(9); //front
  myservo1.attach(10); //back
  myservo.write(100);
  myservo1.write(100);
  delay(1000);
  pinMode(irsensor, INPUT);
  pinMode(value, INPUT);
  //analogWrite(value, LOW);
}

void loop() {
  value = analogRead(A0);
  if (digitalRead(irsensor) == LOW){
    state = 1; 
    delay(2000); 
    for(int i = 0; i < 10; i++){
      value = analogRead(A0);
      if (value > 950) { // Corrected the usage of irsensor pin
        myservo.write(30); 
        myservo1.write(170); //left
        delay(2000);
        myservo.write(100); 
        myservo1.write(100); 
        delay(1000); 
        lcd.setCursor(0, 0); 
        lcd.print("DRY Waste"); 
        lcd.setCursor(0, 1); 
        lcd.print("materials"); 
        delay(1000); 
        state = 0; 
        break; 
      } 
    }
    if(state == 1){
      Serial.println(value); // Changed Serial.printIn to Serial.println
      myservo.write(170);
      myservo1.write(30);
      delay(500);
      myservo.write(100); 
      myservo1.write(100);
      delay(500); 
      myservo.write(170); 
      myservo1.write(30); 
      delay(2000);
      myservo.write(100);
      myservo1.write(100);
      delay(1000);
      lcd.setCursor(0, 0);
      lcd.print("WET Waste");
      lcd.setCursor(0, 1);
      lcd.print("materials");
      delay(1000);
      state = 0; 
    }
  }
  //value = analogRead(A0);
  //if (value < 900) {
  

  lcd.clear();
  Serial.println(value);
}
