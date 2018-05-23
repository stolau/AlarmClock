// Include Libraries
#include "Arduino.h"
#include "LiquidCrystal.h"
#include "MPU6050.h"
#include "Wire.h"
#include "I2Cdev.h"
#include "IR.h"
#include "IRremote.h"
#include "IRremoteInt.h"
#include "TimeAlarms.h"
#include "Time.h"


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

int timeSetup();

// Global variables and defines
int16_t mpu6050Ax, mpu6050Ay, mpu6050Az;
int16_t mpu6050Gx, mpu6050Gy, mpu6050Gz;

// Global variables for loop
bool alarmFlag = false;
int timeHours = 12;
int timeMins = 12;
int alarmHours = -1;
int alarmMins = -1;
int alarmTime = 0;
int number;
int maxNum;

// object initialization
LiquidCrystal lcd(LCD_PIN_RS,LCD_PIN_E,LCD_PIN_DB4,LCD_PIN_DB5,LCD_PIN_DB6,LCD_PIN_DB7);
MPU6050 mpu6050;


// define vars for testing menu
int a = 1;
int RECV_PIN = 11;

IRrecv irrecv(RECV_PIN);

decode_results results;
int giveNumber(int maxNum, int IRresult);
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
    setTime(timeHours, timeMins, 53, 0, 0, 0);
    lcd.begin(16, 2);  
}

void AlarmOn()
{
  int wait = 300;
  int shake_count = 0;
  int shake_tr = 10;
  int treshold = 1200;
  int fl = 1;
  //digitalWrite(MOTOR_1, HIGH);
  while(shake_tr > shake_count)
  {
    if(irrecv.decode(&results))
    {
      if(results.value == 0xA857)
      {
        break;
      }
    }
    mpu6050.getMotion6(&mpu6050Ax, &mpu6050Ay, &mpu6050Az, &mpu6050Gx, &mpu6050Gy, &mpu6050Gz);
    int gx1 = mpu6050Gx;
    int gy1 = mpu6050Gy;
    int gz1 = mpu6050Gz;
    analogWrite(SPEAKER, 12);
    digitalWrite(LED_1, HIGH);
    delay(wait);
    analogWrite(SPEAKER, 0);
    delay(wait);
    irrecv.resume();
    mpu6050.getMotion6(&mpu6050Ax, &mpu6050Ay, &mpu6050Az, &mpu6050Gx, &mpu6050Gy, &mpu6050Gz);
    int gx2 = mpu6050Gx;
    int gy2 = mpu6050Gy;
    int gz2 = mpu6050Gz;
    if((abs(gx2 - gx1) >= treshold) or (abs(gy2 - gy1) >= treshold) or (abs(gz2-gz1) >= treshold))
	{
      shake_count += 1;
    }
    if(shake_count >= shake_tr)
      {
       analogWrite(SPEAKER, 0);
      break;
      }    
   }
  //digitalWrite(MOTOR_1, LOW);
 }


// Main Loop, waits for command and keeps the clock ticking
void loop() 
{
  // Screen is only refreshed if seconds are over 58-02
  if(second(now()) > 59 or second(now()) < 1)
  {
    lcd.clear();
    lcd.setCursor(5,0);
    lcd.print(hour(now()));
    lcd.setCursor(8,0);
    lcd.print(":");
    lcd.setCursor(9,0);
    lcd.print(minute(now()));
    if(alarmFlag == true)
    {
      lcd.setCursor(0, 1);
      lcd.print("** ");
      lcd.setCursor(5, 1);
      lcd.print(alarmHours);
      lcd.setCursor(8, 1);
      lcd.print(":");
      lcd.setCursor(9, 1);
      lcd.print(alarmMins);
      if(hour(now())==alarmHours && minute(now())==alarmMins)
      {
        AlarmOn();
        alarmFlag = false;
      }
    }
    }
  if (irrecv.decode(&results))
  {
    // To setup new time for clock
    // Mark CH
    if(results.value == 0xFF629D)
    {
    
    // uses setupTime function to determine time
      lcd.clear();
      lcd.setCursor(5,0);
      lcd.print(hour(now()));
      lcd.setCursor(8,0);
      lcd.print(":");
      lcd.setCursor(9,0);
      lcd.print(minute(now()));
      lcd.setCursor(0,1);
      lcd.print("Setup Time: ");
	    timeHours = hourSetup();
      timeMins = minsSetup();
      setTime(timeHours, timeMins, 53, 0, 0, 0);
    }
      // Activates Alarm (Turns alarm and LED)
      // Mark EQ
    if(results.value == 0xFF906F)
    {
      if(alarmFlag == true)
      {
      // Deactivates alarm time here
      // Turns alarmFlag off
      // 
        digitalWrite(LED_1, LOW);
        alarmFlag = false;
      }
     else
      {
          // Checks if there is already alarmTime, if not asks for user input
        if(alarmHours == -1 && alarmMins == -1)
        {
          lcd.clear();
          lcd.setCursor(5,0);
          lcd.print(hour(now()));
          lcd.setCursor(8,0);
          lcd.print(":");
          lcd.setCursor(9,0);
          lcd.print(minute(now()));
          lcd.setCursor(0,1);
          lcd.print("Set Alarm: ");
          alarmHours = hourSetup();
	        alarmMins = minsSetup();
        }
        digitalWrite(LED_1, HIGH);
        alarmFlag = true;
        lcd.setCursor(0, 1);
        lcd.print("** ");
        lcd.setCursor(5, 1);
        lcd.print(alarmHours);
        lcd.setCursor(8, 1);
        lcd.print(":");
        lcd.setCursor(9, 1);
        lcd.print(alarmMins);
      // Turns LED on
      }
    }
    // Setups new ALARMtime
    // Mark CH+
    if(results.value == 0xFFE21D)
    {
      lcd.clear();
      lcd.setCursor(5,0);
      lcd.print(hour(now()));
      lcd.setCursor(8,0);
      lcd.print(":");
      lcd.setCursor(9,0);
      lcd.print(minute(now()));
      lcd.setCursor(0,1);
      lcd.print("Set Alarm: ");
	  alarmHours = hourSetup();
	  alarmMins = minsSetup();
    }
    irrecv.resume();
    }
    delay(100);

}
int hourSetup()
{
	int hourNum = 2;
	int maxNum = 0;
	int setHour = 0;
	// Loops here until 2 digits to indicate hours are marked
    while(hourNum > 0)
    {
      int number = -1;
      if(irrecv.decode(&results))
      {
        // Checks if its first digit
        if(hourNum == 2)
        {
          maxNum = 2;
          number = giveNumber(maxNum, results.value);
          irrecv.resume();
          if(number >= 0)
          {
            number = number * 10;
            setHour = setHour + number;
            hourNum = hourNum - 1;
            lcd.setCursor(11, 1);
            lcd.print(setHour);
          }
        }
        // If not its second digit
        else
        {
          // lcd.clear();
          // lcd.print("Dadaa22");
          if(setHour < 20)
          {
            maxNum = 9;
            number = giveNumber(maxNum, results.value);
            irrecv.resume();
            if(number >= 0)
            {
              setHour = setHour + number;
              hourNum = hourNum - 1;
              lcd.setCursor(11, 1);
              lcd.print(setHour);
            }
           }
           else
           {
             maxNum = 3;
             number = giveNumber(maxNum, results.value);
             irrecv.resume();
             if(number >= 0)
             {
               setHour = setHour + number;
               hourNum = hourNum - 1;
               lcd.setCursor(11, 1);
               lcd.print(setHour);
             }
            } 
          }
		}
    }
	return setHour;
}
int minsSetup()
{
	int minsNum = 2;
	int maxNum = 0;
	int setMin = 0;
	
    while(minsNum > 0)
    {
      // lcd.clear();
      // lcd.print("Dadaa");
      if(irrecv.decode(&results))
      {
        // Checks if its first digit
        if(minsNum == 2)
        {
          maxNum = 5;
          number = giveNumber(maxNum, results.value);
          irrecv.resume();
          if(number > 0)
          {
            number = number * 10;
            setMin = setMin + number;
            minsNum = minsNum - 1;
            lcd.setCursor(13, 1);
            lcd.print(":");
            lcd.setCursor(14, 1);
            lcd.print(setMin);
          }
        }
        // If not its second digit
        else
        {
            maxNum = 9;
            number = giveNumber(maxNum, results.value);
            irrecv.resume();
            if(number >= 0)
            {
              setMin = setMin + number;
              minsNum = minsNum - 1;
              lcd.setCursor(13, 1);
              lcd.print(":");
              lcd.setCursor(14, 1);
              lcd.print(setMin);
            }
         }
      }
    }

  return setMin;
}

// Function transferms hexdigit from receiver to number
// Also checks out if there is limitations to 00:00-23:59 clocksystem
int giveNumber(int maxNum, int IRresult)
{
  //lcd.print(IRresult, HEX);
  // Mark 0
  if(IRresult == 0x6897)
  {
    return 0;
  }
  // Mark 1
  if(IRresult == 0x30CF)
  {
    return 1;
  }
  if(IRresult == 0x18E7)
  {
    return 2;
  }
  //  Mark 3
  if(IRresult == 0x7A85)
  {
    if(maxNum >= 3)
    {
      return 3;
    }
    else
    {
      // Aborted mission
      lcd.print("1");
      return -1;
    }
  }
  //  Mark 4
  if(IRresult == 0x10EF)
  {
    if(maxNum >= 4)
    {
      return 4;
    }
    else
    {
      // Aborted mission
      lcd.print("2");
      return -1;
    }
  }
  //  Mark 5
  if(IRresult == 0x38C7)
  {
    if(maxNum >= 5)
    {
      return 5;
    }
    else
    {
      // Aborted mission
      return -1;
    }
  }
  //  Mark 6
  if(IRresult == 0x5AA5)
  {
    if(maxNum >= 6)
    {
      return 6;
    }
    else
    {
      // Aborted mission
      return -1;
    }
  }
  //  Mark 7
  if(IRresult == 0x42BD)
  {
    if(maxNum >= 7)
    {
      return 7;
    }
    else
    {
      // Aborted mission
      return -1;
    }
  }
  //  Mark 8
  if(IRresult == 0x4AB5)
  {
    if(maxNum >= 8)
    {
      return 8;
    }
    else
    {
      // Aborted mission
      return -1;
    }
  }
  //  Mark 9
  if(IRresult == 0x52AD)
  {
    if(maxNum >= 9)
    {
      return 9;
    }
    else
    {
      // Aborted mission
      return -1;
    }
  }
  else
  {
    return -1;
  }
  
  
}
