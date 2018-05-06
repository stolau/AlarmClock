// Include Libraries
#include "Arduino.h"
#include "LiquidCrystal.h"
#include "Arduino.h"
#include "MPU6050.h"
#include "Wire.h"
#include "I2Cdev.h"
#include "IR.h"
#include "IRremote.h"
#include "IRremoteInt.h"



// Pin Definitions
#define LCD_PIN_RS  7
#define LCD_PIN_E 6
#define LCD_PIN_DB4 2
#define LCD_PIN_DB5 3
#define LCD_PIN_DB6 4
#define LCD_PIN_DB7 5

#define SPEAKER 10

#define MOTOR_1 8
#define LED_1 9



// Global variables and defines
int16_t mpu6050Ax, mpu6050Ay, mpu6050Az;
int16_t mpu6050Gx, mpu6050Gy, mpu6050Gz;


// object initialization
LiquidCrystal lcd(LCD_PIN_RS,LCD_PIN_E,LCD_PIN_DB4,LCD_PIN_DB5,LCD_PIN_DB6,LCD_PIN_DB7);
MPU6050 mpu6050;


// define vars for testing menu
int a = 1;
int RECV_PIN = 11;

IRrecv irrecv(RECV_PIN);

decode_results results;
// Setup the essentials for your circuit to work. It runs first every time your circuit is powered with electricity.
void setup() 
{
    pinMode(MOTOR_1, OUTPUT);
    pinMode(LED_1, OUTPUT);
    pinMode(SPEAKER, OUTPUT);
    Serial.begin(9600);
    Wire.begin();
    mpu6050.initialize();
    irrecv.enableIRIn();
    lcd.begin(16, 2);  
}

void Alarm()
{
  int wait = 100;
  int shake_count = 0;
  int shake_tr = 5;
  int treshold = 1000;
  //digitalWrite(MOTOR_1, HIGH);
  while(wait > 1)
  {
    analogWrite(SPEAKER, 12);
    digitalWrite(LED_1, HIGH);
    delay(wait);
    analogWrite(SPEAKER, 0);
    digitalWrite(LED_1, LOW);
    delay(wait);
    mpu6050.getMotion6(&mpu6050Ax, &mpu6050Ay, &mpu6050Az, &mpu6050Gx, &mpu6050Gy, &mpu6050Gz);
    if(&mpu6050Ax > treshold){
      shake_count += 1;
    }
    if(shake_count >= shake_tr)
      {
      break;
      }    
   }
  //digitalWrite(MOTOR_1, LOW);
  }


// PLACEHOLDER, TEST LOOP
void loop() 
{
    mpu6050.getMotion6(&mpu6050Ax, &mpu6050Ay, &mpu6050Az, &mpu6050Gx, &mpu6050Gy, &mpu6050Gz);
    /*Serial.print(mpu6050Ax); Serial.print("\t");
    Serial.print(mpu6050Ay); Serial.print("\t");
    Serial.print(mpu6050Az); Serial.print("\t");
    Serial.print(mpu6050Gx); Serial.print("\t");
    Serial.print(mpu6050Gy); Serial.print("\t");
    Serial.print(mpu6050Gz); Serial.print("\t");*/
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(mpu6050Ax);
    lcd.setCursor(0,1);
    lcd.print(mpu6050Ay);
    if (irrecv.decode(&results)) {
      if((results.value, HEX) != 0xFFFFFFF){
          // if IR value other than FFFFFF, print the value on the LCD
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(results.value, HEX);
      delay(100);
      }
      irrecv.resume();
    }
    if(a==1){
        //starts the motors
      digitalWrite(MOTOR_1, HIGH);
      digitalWrite(LED_1, HIGH);
        
        //writes on the LCD
      lcd.setCursor(3, 0);
      lcd.print("X   X");
      lcd.setCursor(2, 1);
      lcd.print("-------");
      // Turn on the display:
      lcd.display();
      analogWrite(SPEAKER, 12);
      delay(500);
      analogWrite(SPEAKER, 96);
      delay(500);
      a = 2;
    }
    if(a==2){
        //stops the motors
       //writes on the LCD
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("STOP");
      a = 3;
      analogWrite(SPEAKER, 0);
    }
    delay(100);
}

