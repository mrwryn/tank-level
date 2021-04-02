

#include <LiquidCrystal_I2C.h>

#define trigPin 25
#define echoPin 26
#define buzzer 5
#define pump 3
#define redLED 4
#define yellowLED 6
#define greenLED 2

#include <SoftwareSerial.h>
int sound = 500; // variable for buzzer sound
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);


SoftwareSerial DebugSerial(2, 3); // RX, TX

void main_setup()
{
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(pump, OUTPUT);
  pinMode (redLED, OUTPUT);
  pinMode (yellowLED, OUTPUT);
  pinMode (greenLED, OUTPUT);

  lcd.init();
  lcd.backlight();

}

void main_loop()
{

  // controlling the ultrasonic sensor

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration;
  int distance;

  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);

  // Calculating the distance
  distance = duration * 0.034 / 2; //reads the distance of the water level

  //controlling the buzzer
  if (distance < 15)
  { noTone(buzzer); // buzzer off
  }
  else
  {
    tone(buzzer, sound); // buzzer on
    digitalWrite(redLED, HIGH);
    digitalWrite(yellowLED, LOW);
    digitalWrite(greenLED, LOW);
  }

  // controlling the lcd display
  if (distance > 15)
  {
    lcd.setCursor(2, 0);
    lcd.print("Water Empty ");
    lcd.setCursor(2, 1);
    lcd.print("Level: ");
    lcd.print (distance);
    lcd.print (" cm");


  }
  else if (distance > 15 || distance < 5)  ////if the distance is between 5 and 15cm
  {
    lcd.init();
    lcd.backlight();
    lcd.setCursor(2, 0);
    lcd.print("Water Low ");
    lcd.setCursor(2, 1);
    lcd.print("Level: ");
    lcd.print(distance);
    lcd.print( " cm");
    digitalWrite(redLED, LOW);
    digitalWrite(yellowLED, HIGH);
    digitalWrite(greenLED, LOW);

  }
  if (distance <= 5)
  {
    lcd.init();
    lcd.backlight();
    lcd.setCursor(2, 0);
    lcd.print("Water Full ");
    lcd.setCursor(2, 1);
    lcd.print("Level: ");
    lcd.print(distance);
    lcd.print( " cm");
    digitalWrite(redLED, LOW);
    digitalWrite(yellowLED, LOW);
    digitalWrite(greenLED, HIGH);
  }
  delay(1000);
}
const int tempPin = A0;    // pin that the sensor is attached to
const int heatPin = 3;       // pin that the LED is attached to
const int threshold = 40;   // an arbitrary threshold level that's in the range of the analog input

void temp_setup() {

  pinMode(heatPin, OUTPUT);
  // initialize serial communications:
  Serial.begin(9600);
}

void temp_loop() {
  // read the value of the potentiometer:
  int analogValue = analogRead(heatPin);

  // if the analog value is high enough, turn on the LED:
  if (analogValue > threshold) {
    digitalWrite(heatPin, HIGH);
  } else {
    digitalWrite(heatPin, LOW);
  }

  // print the analog value:
  Serial.println(analogValue);
  delay(1);        // delay in between reads for stability
}
