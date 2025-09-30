#include <LiquidCrystal.h>
const int ldrPin=A0;
long startTime;
long elapsedTime;
int lapNum=1;

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(28, 2);
}

void loop() {
  int ldrValue = analogRead(ldrPin);

  lcd.setCursor(0, 1);
  lcd.print("#" + String(lapNum) + " Time: " );

  if (ldrValue>700) {
    printTime(ldrValue);
  }
  
}

void printTime(int ldrValue) {
  startTime = millis();
  int lcdLog = 0;

  while (ldrValue>700) {
    elapsedTime = millis()-startTime;
    Serial.println(elapsedTime);

    if (lcdLog%10==0) {
      long totalSeconds = elapsedTime/1000;
      long totalMinutes = totalSeconds/60;
      long remainingSeconds = totalSeconds%60;
      long remainingMS = elapsedTime%1000;
      lcd.setCursor(9, 1);

      lcd.print(String(totalMinutes) + ":" + String(remainingSeconds) + ":" + remainingMS);
      ldrValue = analogRead(ldrPin);

      for (int i = 0; i < 7; i++) {
        lcd.print(" ");
      }
      
    }

    lcdLog++;
  }


  long totalSeconds = elapsedTime/1000;
  long totalMinutes = totalSeconds/60;
  long remainingSeconds = totalSeconds%60;
  long remainingMS = elapsedTime%1000;

  lcd.setCursor(0, 0);
  Serial.println("Lap Number " + String(lapNum) + " Time: " + String(totalMinutes) + ":" + String(remainingSeconds) + ":" + String(remainingMS));
  lcd.print("#" + String(lapNum) + " Time: " + String(totalMinutes) + ":" + String(remainingSeconds) + ":" + String(remainingMS));

  lcd.setCursor(0, 1);
  for (int i = 0; i < 16; i++) {
    lcd.print(" ");
  }

  elapsedTime=0;
  lapNum++;

}