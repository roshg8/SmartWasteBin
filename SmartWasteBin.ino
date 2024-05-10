#define BLYNK_TEMPLATE_ID "TMPL2Gt19yO_u"
#define BLYNK_TEMPLATE_NAME "Arduino mkr 1010"

#include <WiFiNINA.h>
#include <BlynkSimpleWiFiNINA.h>

char auth[] = "DpqEZk3mbGcuqcESILDDrmYd13K_b5y0";

char ssid[] = "SETUP-D345";
char pass[] = "collar4484bring";

const int trigPin = 9;  //Ultrasonic sensor trigger pin
const int echoPin = 10; //Ultrasonic sensor echo pin
const float binFullThreshold = 20.0; //Distance threshold in centimeters to determine bin fullness

void setup() {
  Serial.begin(9600);

  //Ultrasonic sensor pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Connect to the WiFi
  Blynk.begin(auth, ssid, pass);
}

void loop() {
  Blynk.run();  //Run Blynk application
  float distance = getDistance();

  //Check if the distance indicates bin fullness
  if (distance <= binFullThreshold) {
    //Bin is considered full
    Blynk.virtualWrite(V1, 1); //Send bin full signal to Blynk app
  } else {
    //Bin is not full
    Blynk.virtualWrite(V1, 0); //Send bin not full signal to Blynk app
  }

  delay(1000); //Adjust delay based on required measurement frequency
}

//Function to get distance
float getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  unsigned long duration = pulseIn(echoPin, HIGH);
  float distance = (duration * 0.034) / 2;

  return distance;
}