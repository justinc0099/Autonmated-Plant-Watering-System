#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

//buttons
int incButton = 8;
int decButton = 9;
boolean buttonState1 = false;
boolean buttonState2 = false;
boolean currentButtonState1;
boolean currentButtonState2;
boolean prevState1;
boolean prevState2;

//valve pin
int valvePin = 6;

//timer varaibles
unsigned long startTime1 = millis();
unsigned long endTime1;
long interval1 = 60000;
unsigned long startTime2 = millis();
unsigned long endTime2;
long interval2 = 100;
int minutes = -1;
int hours = 6;
int timeInt = 1;
int newTimeInt;
int aNum = hours;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(16, 2);

  pinMode(incButton, INPUT);
  pinMode(decButton, INPUT);
  pinMode(valvePin, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  // timer1 to calculate time until next watering
  endTime1 = millis();
  if (endTime1 - startTime1 >= interval1) {
    minutes -= 1;
    startTime1 = millis();
  }

//timer boundaries
  if (minutes <= -1 ) {
      hours -= 1;
      minutes = 59;
    }
    if (hours <= -1) {
      //put code here to make valve let water go through
      digitalWrite(valvePin, HIGH);
      Serial.println("open");
      delay(3000);
      digitalWrite(valvePin, LOW);
      Serial.println("close");
      hours = newTimeInt;
      minutes = 0;
    }

  //timer 2 to display lcd screen without delay
  endTime2 = millis();
  if (endTime2 - startTime2 >= interval2) {
    lcd.clear();
    lcd.print("hours " + String(hours));
    lcd.setCursor(0, 1);
    lcd.print("minutes " + String(minutes));
    startTime2 = millis();
  }

  // button states with debounce
  currentButtonState1 = debounce(incButton, prevState1);
  if (currentButtonState1 == true && prevState1 == false) {
    hours += timeInt;
    newTimeInt = hours;
    aNum = hours;
  }
  else {newTimeInt = aNum;}
  prevState1 = currentButtonState1;

  currentButtonState2 = debounce(decButton, prevState2);
  if (currentButtonState2 == true && prevState2 == false) {
    hours -= timeInt;
    newTimeInt = hours;
    aNum = hours;
  }
  else {newTimeInt = aNum;}
  prevState2 = currentButtonState2;

}



//debounce function
boolean debounce(int aButton, boolean aPrevState) {
  boolean aCurrentButtonState = digitalRead(aButton);
  if (aCurrentButtonState != aPrevState) {
    delay(50);
  }
  return aCurrentButtonState;
}
