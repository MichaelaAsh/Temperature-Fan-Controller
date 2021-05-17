// C++ code
/**
 Project 1
 Team: 3, Tinkering 
 Name: Temperature base Fan Controller 
 Purpose: Control the speed of the motor which will be attached to a fan
          based on temperature.
 @author  Michaela Hibbert(team lead), Jean Marc Yapo, Asher Abbas, 
         Yvan Philippe Kengne Ponka 
 @version 1.0 May 05 2021
*/ 
#include <LiquidCrystal.h>

// initializing 
const int RELAY_PIN = 8, FAN =  9, TEMP_PIN = A1; 
const int TOO_COLD =  14, HOT = 15;

const int rs = 12, en = 11, db1 = 5, db2 = 4, db3 = 3, db4 = 2;
LiquidCrystal lcd(rs, en, db1, db2, db3, db4);

typedef struct Display {
  
  String tempC;
  String tempF;
  String fanStatus;
  String fanSpeed;
  int speedOfFan;
  
}Display;

// Global Variables
Display display; 
typedef int (*Function) (const unsigned char);
Function Switch = digitalRead;


// Function prototype 
/**
  Initialize the the columns and rows for LCD 
  and write Introduction message to LCD
*/ 
void initLCD ();

/**
	Determine whether to turn on/off the relay(based 
    on the status of the fan)and 
    speed of the motor. 
*/ 
void powerFan(); 

/** 
@param toDisplay
*/ 
void displayToLCD (String toDisplay);

/**
Converts voltage to temperature in C
@param voltage 
*/ 
double getTempInC (double voltage);
/**
Converts temperature in C to F  
@param temp (in C)
*/ 
double  getTempInF(double temp);

////////////////////////////////////////////////////  
void setup()
{
  pinMode(FAN, OUTPUT);
  pinMode (RELAY_PIN, OUTPUT);
  pinMode(13, OUTPUT); 
  
  // initialize number of columns and rows 
  initLCD();
  
}

void loop()
{
  if (Switch(13) == LOW) { 
     display.speedOfFan = 0;
     powerFan();
  } else {
    
    
    //Read the temp
    double temp = analogRead(TEMP_PIN); 

    double voltage = temp * 5.0; 
    voltage /= 1024.0;  

    // calculate the temperature in C
    double temperature =  getTempInC (voltage);

    // print temperature in F
    getTempInF(temperature);

    //set the display.speedOfFan and 
    // display.fanStatus based on the temperature
    
    if(temperature >= HOT)
    { 
      display.speedOfFan = 325;
    }
    else if(temperature <= TOO_COLD)
    {
      	display.speedOfFan = 0;
        display.fanStatus = "Fan: OFF"; 
     }

    if(temperature >= 20 && temperature < 25)
    {
      display.speedOfFan = 402;
      display.fanStatus = "Fan speed: 20%";
    }
     else if(temperature >= 25 && temperature < 30)
    {
       display.speedOfFan = 469;
       display.fanStatus  = "Fan speed: 40%";
    }
     else if(temperature >= 30 && temperature < 35)
    {
       display.speedOfFan = 536;
       display.fanStatus  = "Fan speed: 60%";
    }
     else if(temperature >= 35 && temperature < 40)
    {
        display.speedOfFan = 603;
        display.fanStatus  = "Fan speed: 80%";
    }
     else if(temperature >= 40)
    {
        display.speedOfFan = 670;
        display.fanStatus  = "Fan speed: 100%";
    }
      displayToLCD(display.tempC); 
      displayToLCD(display.tempF);
      displayToLCD(display.fanStatus);
      powerFan();
    
  }
  
  
  
}
////////////////////////////////////////////////////
void initLCD () {
  lcd.begin(16, 2);
  lcd.setCursor(0,0);
  lcd.print("Temperature");
  lcd.setCursor(0,1);
  lcd.print("Control");
  delay(1000);
  lcd.clear();
}
////////////////////////////////////////////////////
void powerFan() {
  if (display.fanStatus != "Fan: OFF") {
     digitalWrite(RELAY_PIN, HIGH);
     analogWrite(FAN,display.speedOfFan);
     delay(1000); 
  } else {
     analogWrite(FAN,display.speedOfFan);
     digitalWrite(RELAY_PIN, LOW);
  }
  
}
  
//////////////////////////////////////////////////// 
void displayToLCD (String toDisplay) {
  lcd.print(toDisplay); 
  delay(3000);
  lcd.clear();  
}
//////////////////////////////////////////////////// 
double getTempInC (double voltage){
  double temp = (voltage - 0.5) * 100.0; 
  display.tempC = "Temp in C " + String(temp);
  return temp;
}
////////////////////////////////////////////////////
double  getTempInF(double temp){
  double tempF = (temp * 9/5) + 32.0;
  display.tempF = "Temp in F " + String(tempF);
  return tempF;
}
//////////////////////////////////////////////////// 
