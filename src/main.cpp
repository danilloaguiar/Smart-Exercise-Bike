#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display



 volatile byte quarter_revolutions;
 int period4;
 int speed;
 unsigned int voltas;
 int distancia;
 unsigned long timeold;
 float aux;
 int cursor;
 int aro = 4.14;

void detect()//This function is called whenever a magnet/interrupt is detected by the arduino
 {
   quarter_revolutions++;
   period4 = (millis() - timeold);
   timeold = millis();
   aux = 0.25 * aro * 3600 * 1000 / period4;
   speed = aux;
   lcd.setCursor(0,0);
   lcd.print("                ");
   lcd.setCursor(0,0);
   lcd.print("Speed:");
   lcd.setCursor(7,0);
   lcd.print(speed,DEC);
   lcd.setCursor(13,0);
   lcd.print("m/h");
   Serial.print("Speed: ");
   Serial.print(speed, DEC);
   Serial.print(" m/h \n");
 }

 void setup()
 {
  Serial.begin(9600);
  lcd.init();                      // initialize the lcd 
  lcd.backlight();
  lcd.setCursor(1,0);
  lcd.clear();
  attachInterrupt(PB4, detect, RISING); //Initialize the intterrupt pin 
  quarter_revolutions = 0;
  speed = 0;
  period4 = 0;
  voltas = 0;
  distancia = 0;
  timeold = 0; 
  cursor = 10;
  lcd.setCursor(0,1);
  lcd.print("Distance:");
  lcd.setCursor(0,0);
  lcd.print("Speed:"); 
   }


void loop()//Measure RPM
 {

   if(distancia >= 10){
     cursor = 11;
   }
   if(distancia >= 100){
     cursor = 12;
   }
   if (quarter_revolutions >= 4) { 
     quarter_revolutions = 0;
     voltas++;
     distancia = voltas * aro;
     lcd.setCursor(0,1);
     lcd.print("                ");
     lcd.setCursor(0,1);
     lcd.print("Distance:");
     lcd.setCursor(9,1);
     lcd.print(distancia,DEC);
     lcd.setCursor(cursor,1);
     lcd.print("metros");
     Serial.print("Distance: ");
     Serial.print(distancia, DEC);
     Serial.print(" m \n ");
   }
 }