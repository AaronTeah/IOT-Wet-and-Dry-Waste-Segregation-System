#define BLYNK_TEMPLATE_ID "TMPL6NTOkCWF1"
#define BLYNK_TEMPLATE_NAME "Smart Dustbin"
#define BLYNK_AUTH_TOKEN "NcFPQDtFQVmhLJE2XiJszo_7N6G1GCCS"

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "yourwifiname"; //Change the wifi name here
char pass[] = "yourpassword"; //Change the wifi password here

BlynkTimer timer;

#define echoPin D5
#define trigPin D6
#define echoPin1 D7
#define trigPin1 D8
long duration;
long duration1;
int distance1; 
int distance; 
int binLevel=0;
int binLevel1=0;

void SMESensor()
{
  ultrasonic(); 
  delay(100);
}

void ultrasonic()
{
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = duration * 0.034 / 2; //formula to calculate the distance for ultrasonic sensor
    binLevel=map(distance, 20, 0, 0,100); // ADJUST BIN HEIGHT HERE
    Blynk.virtualWrite(V0, distance);
    Blynk.virtualWrite(V1, binLevel);

    digitalWrite(trigPin1, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin1, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin1, LOW);
    duration1 = pulseIn(echoPin1, HIGH);
    distance1 = duration1 * 0.034 / 2; //formula to calculate the distance for ultrasonic sensor
    binLevel1=map(distance1, 20, 0, 0,100); // ADJUST BIN HEIGHT HERE
    Blynk.virtualWrite(V3, distance1);
    Blynk.virtualWrite(V4, binLevel1);

    if (binLevel > 80){
      Blynk.logEvent("dustbin_level_wet","Wet Dustbin is FULL!");
    }
    if (binLevel1 > 80){
      Blynk.logEvent("dustbin_level_dry","Dry Dustbin is FULL!");
    }
}
void setup()
{
  Serial.begin(9600);
  // pinMode(D7, INPUT);
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  pinMode(trigPin1, OUTPUT); 
  pinMode(echoPin1, INPUT); 
   Blynk.begin(auth, ssid, pass);
  delay(2000);
  timer.setInterval(1000L, SMESensor);
}

void loop() 
{
  Blynk.run();
  timer.run(); 
}
