
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
int phval = 0; // the pH meter Analog output is connected with the Arduino’s A0
unsigned long int avgval; //Store the average value of the sensor feedback
int buffer_arr[10],temp;
void setup() 
{
 Serial.begin(9600);
  lcd.init(); 
  lcd.begin(16, 2);
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("  WelCome To ");
  lcd.setCursor(0, 1);
  lcd.print(" Our Projects");
  delay(2000);
  lcd.clear();
}
void loop() {
 for(int i=0;i<10;i++) //Get 10 sample value from the sensor for smooth the value
 { 
 buffer_arr[i]=analogRead(A0);
 delay(30);
 }
 for(int i=0;i<9;i++) //sort the analog from small to large
 {
 for(int j=i+1;j<10;j++)
 {
 if(buffer_arr[i]>buffer_arr[j])
 {
 temp=buffer_arr[i];
 buffer_arr[i]=buffer_arr[j];
 buffer_arr[j]=temp;
 }
 }
 }
 avgval=0;
 for(int i=2;i<8;i++)   //take the average value of 6 center sample
 avgval+=buffer_arr[i];
 float volt=(float)avgval*5.0/1024/6; //convert the analog into millivolt
 float ph_act = 3.5*volt; //convert the millivolt into pH value
 lcd.setCursor(0, 0);
 lcd.print(" pH Val:");
 lcd.setCursor(10, 0);
 lcd.print(ph_act);
 delay(1000);
}
