// Include Libraries
#include "Arduino.h"
#include "LiquidCrystal.h"

#include <IRremote.h>


// Pin Definitions
#define LCD_PIN_RS	7
#define LCD_PIN_E	6
#define LCD_PIN_DB4	2
#define LCD_PIN_DB5	3
#define LCD_PIN_DB6	4
#define LCD_PIN_DB7	5

#define MOTOR_1 8
#define MOTOR_2 9



// Global variables and defines

// object initialization
LiquidCrystal lcd(LCD_PIN_RS,LCD_PIN_E,LCD_PIN_DB4,LCD_PIN_DB5,LCD_PIN_DB6,LCD_PIN_DB7);



// define vars for testing menu
int a = 1;
int RECV_PIN = 11;

IRrecv irrecv(RECV_PIN);

decode_results results;
// Setup the essentials for your circuit to work. It runs first every time your circuit is powered with electricity.
void setup() 
{
    pinMode(MOTOR_1, OUTPUT);
    pinMode(MOTOR_2, OUTPUT);
    Serial.begin(9600);
    irrecv.enableIRIn();
    lcd.begin(16, 2);  
}

// Main logic of your circuit. It defines the interaction between the components you selected. After setup, it runs over and over again, in an eternal loop.
void loop() 
{
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
      digitalWrite(MOTOR_2, HIGH);
        
        //writes on the LCD
      lcd.setCursor(0, 0);
      lcd.print("I dreamt I was");
      lcd.setCursor(0, 1);
      lcd.print("a butterfly");
      // Turn on the display:
      lcd.display();
    
      delay(8000);
      a = 2;
    }
    if(a==2){
        //stops the motors
      digitalWrite(MOTOR_1, LOW);
      digitalWrite(MOTOR_2, LOW);
       //writes on the LCD
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("STOP");
      a = 3;
    }
}

