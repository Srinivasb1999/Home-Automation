const int led = 9;
int brightness = 0;   
int fadeAmount = 5;
int a,x,b;
int state = 0;

void setup() 
{
  Serial.begin(9600);
  pinMode(led , OUTPUT);
  pinMode(A0,INPUT);
  pinMode(12,INPUT);
}

void loop() 
{
      a=digitalRead(12); 
     
    while(a==0)  
   {
    int c = analogRead(A0);
    Serial.print(c);
    Serial.print("\n");
    delay(50);
    if (c<300)
   {
     analogWrite(led,brightness);
     delay(100);
     brightness=brightness+fadeAmount;
    }

    else if (c >300)
   {
    //fadeAmount = -fadeAmount;
    //brightness = brightness - fadeAmount;
    analogWrite(led,brightness);    
    int fade=-6;
    brightness=brightness+fade;
       if(brightness<5)
     {
      brightness=0;
     }
    }
    delay(80);
    if(Serial.available() > 0)
    break;
   }
   state = Serial.read();
    if (state == 'f') 
    {
    digitalWrite(led, LOW); // Turn LED OFF
    Serial.println("LED: OFF"); // Send back, to the phone, the String "LED: ON"
    state = 0;
    }
   else if (state == 'o')
   {
    digitalWrite(led, HIGH);
    Serial.println("LED: ON");
    state =0;
   }
}
 

  
