#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);  // GANTI 0x3F Ke 0x27 kalau LCD ga muncul
#include <DHT.h>
DHT dht(2, DHT11); //Pin, Jenis DHT

int dht5v = 3;    // untuk pengganti VCC/5vOLT
int relay5v = 13;
int buzzer = 12;
int blowerA = 11;
int blowerB = 10;
 
void setup(){
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight(); 
  // jadikan pin power sebagai output
  pinMode(dht5v, OUTPUT);
  pinMode(relay5v, OUTPUT);
  pinMode(blowerA, OUTPUT);
  pinMode(blowerB, OUTPUT);
  // default bernilai LOW
  digitalWrite(dht5v, LOW);
  Serial.begin(9600);
  dht.begin();
}
 
void loop(){
  digitalWrite(dht5v, HIGH);
    
  float humi = dht.readHumidity();
  float temp = dht.readTemperature();
    
  if(isnan(humi) && isnan(temp)) {
    lcd.setCursor(5,0);
    lcd.print("GROUP1");
    lcd.setCursor(1,1);
    lcd.print("EGGS INCUBATOR");
    tone(buzzer, 500);
    delay(200);
    tone(buzzer, 1000);
    delay(200);
    tone(buzzer, 2000);
    delay(200);
    tone(buzzer, 4000);
    delay(200);
    noTone(buzzer);
    delay(500);
  } else {
    Serial.print("Humi: ");
    Serial.print(humi);
    Serial.print(" ");
    Serial.print("Temp: ");
    Serial.println(temp);
    
    if (humi < 35) {
      digitalWrite(blowerA, HIGH);
      digitalWrite(blowerB, LOW);
      tone(buzzer, 1000);
      delay(250);
      noTone(buzzer);
      delay(250);
    } else if (humi > 60) {
      digitalWrite(blowerA, LOW);
      digitalWrite(blowerB, HIGH);
      tone(buzzer, 2000);
      delay(250);
      noTone(buzzer);
      delay(250);
    } else {
      digitalWrite(blowerA, HIGH);
      digitalWrite(blowerB, LOW);
      noTone(buzzer);
      delay(500);
    }
    
    if (temp < 35) {
      tone(buzzer, 500);
      delay(500);
      noTone(buzzer);
      delay(500);
    } else if (temp > 40) {
      tone(buzzer, 4000);
      delay(500);
      noTone(buzzer);
      delay(500);
    } else {
      noTone(buzzer);
      delay(500);
    }
    
    if (temp < 40) {
      digitalWrite(relay5v, HIGH);
    } else {
      digitalWrite(relay5v, LOW);
    }
    
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Humi: ");
    lcd.setCursor(5,0);
    lcd.print(humi);
    lcd.setCursor(10,0);
    lcd.print("%");
    
    lcd.setCursor(0,1);
    lcd.print("Temp: ");
    lcd.setCursor(5,1);
    lcd.print(temp);
    lcd.setCursor(10,1);
    // lcd.print((char)223);
    lcd.print("C");
  }
  delay(1000);
}
