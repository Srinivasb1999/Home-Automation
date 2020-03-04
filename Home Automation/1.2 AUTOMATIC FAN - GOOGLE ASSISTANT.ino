#include "DHT.h"           // Including DHT22 library
#include "LiquidCrystal.h" // Including LCD library
#include <SoftwareSerial.h>
SoftwareSerial ArduinoUno(3,2);

#define DHTPIN 6      // Declaring pin 6 for communicating to DHT22 sensor
#define DHTTYPE DHT11 // Declaring the type of DHT sensor we are using (DHT22 or DHT11)

DHT dht(DHTPIN, DHTTYPE);          // Declaring DHT connection and type
LiquidCrystal lcd(12,11,10,9,8,7); // Declaring LCD connections

int Motor_Pin1 = 4;  // pin 2 on L293D
int Motor_Pin2 = 13;  // pin 7 on L293D
int Enable = 5;  
int i=1;// pin 1 on L293D
//float val=0;
void setup() {
  pinMode(Motor_Pin1, OUTPUT);  
  pinMode(Motor_Pin2, OUTPUT);
  pinMode(Enable, OUTPUT);
  lcd.begin(16,2); // Initializes the 16x2 LCD
  dht.begin();     // Initializes DHT sensor
  Serial.begin(115200);
  ArduinoUno.begin(4800);
}

void loop() {
 //lcd.clear();
 
 // Clear LCD
while(i)
{
  
  
  int temp = dht.readTemperature(); // Reading the temperature in Celsius

  if (isnan(temp)) {                  // Validating received data
    Serial.print("Failed to read");
    delay(1000);
    return;
  }

  lcd.setCursor(0,0);
  lcd.print("Temp.: "); 
  lcd.print(temp);      // Writing temperature in the first row
  lcd.print(" C");
  lcd.setCursor(0,1);
  // Setting the position to display fan speed

  if(temp <25 ) {                 // If the temperature less than 25
    analogWrite(Enable,0);        // 0% PWM duty cycle
    lcd.print("Fan OFF ");      
    delay(500);
  }
  else if(temp>=25 & temp<30) {      // If the temperature is between 25 & 30
    analogWrite(Enable,77);         // 30% of maximum duty cycle value (255). 
    lcd.print("Fan Speed: 30% ");
    //delay(500);
  }
  else if(temp>=30 & temp<35) {      // If the temperature is between 30 & 35
    analogWrite(Enable, 153);        // 60% of maximum duty cycle value (255).
    lcd.print("Fan Speed: 60% ");
    //delay(500);
  }
  if(temp>=35) {                // If the temperature is above 35
    analogWrite(Enable, 255);        // 100% duty cycle
    lcd.print("Fan Speed: 100%   ");
    //delay(500);
  }

  digitalWrite(Motor_Pin1, HIGH);  // To drive the motor in a particular direction
 digitalWrite(Motor_Pin2, LOW);     // To drive the motor in a particular direction
  
  if(ArduinoUno.available()>0)
   break;
}
 float val = ArduinoUno.parseFloat();
  if(ArduinoUno.read()== '\n')
  {
  Serial.println(val);
  }
  if(val == 49)
  { Serial.println("SUCCESS");
   digitalWrite(Motor_Pin1, LOW);  // To drive the motor in a particular direction
 digitalWrite(Motor_Pin2, LOW);
 lcd.clear();
   lcd.print("Fan is switched");
   lcd.setCursor(0,1);
   lcd.print("off through wifi!"); 
   
   i=0;// To drive the motor in a particular direction
  }
  else if (val == 48)
 {
    digitalWrite(Motor_Pin1, HIGH);  // To drive the motor in a particular direction
 digitalWrite(Motor_Pin2, LOW);
 lcd.clear();
 
 i=1; 
    }
  
}

  //delay(500); // 2 seconds delay
