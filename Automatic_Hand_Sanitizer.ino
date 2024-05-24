#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27,16,2); //Set alamat LCD I2C dan besar karakter pada LCD
Servo servo1, servo2; //Mendefinisikan kedua servo
const int trigPin = 6;
const int echoPin = 5;
long duration, distance; //Mendefinisikan durasi dan jarak

void setup() 
{
  lcd.init(); //Inisialisasi LCD
  lcd.backlight(); //Menyalakan backlight
  servo1.attach(9);
  servo2.attach(10);
  pinMode(trigPin, OUTPUT); //trigPin sebagai Output
  pinMode(echoPin, INPUT); //echoPin sebagai Input
  Serial.begin(9600); //Kecepatan bit rate dalam pengiriman
}

void loop() 
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); //Membaca echoPin sebagai durasi
  distance= duration*0.034/2; //Perhitungan jarak

  if (distance <= 10)
  {
    servo1.write(55),servo2.write(55);
    delay(100);    
    Serial.println("Handsanitizer Keluar"); //Tampilan Serial Monitor ketika tangan berada<=10cm didepan sensor
    Serial.print (distance);  // Tampilan jarak tangan pada Serial Monitor
    Serial.println (" cm"); //Tampilan satuan pada serial monitor
  }
  else 
  {
    servo1.write(0),servo2.write(0);
    delay(100);
    Serial.println("Handsanitizer Stop"); //Tampilan Serial Monitor ketika tangan berada<=10cm didepan sensor 
  }
  lcd.setCursor(0,0); //Peletakan kalimat pada kolom 0 dan baris 0
  lcd.print("Dekatkan Tanganmu"); //Menampilkan pada LCD
  lcd.scrollDisplayLeft(); //Running text kalimat dari kiri ke kanan
  delay(500);

  lcd.setCursor(1,1); //Peletakan kalimat pada kolom 1 dan baris 1
  lcd.print("Terima Kasih :)"); //Menampilkan pada LCD
  delay(500);
}
