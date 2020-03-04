const int led=6;
int a,count=0;


void setup() {
  Serial.begin(9600);
  pinMode(led,OUTPUT);
  pinMode(A0,INPUT);
  
}

void loop()
{
  a=analogRead(A0);
  Serial.print(a);
  Serial.print("\n");
  
  if(a>4)
   { digitalWrite(6,HIGH);
     //for(int i=0;;i++)
     //delay(1000+i);
   }
  else
    digitalWrite(6,LOW);

   

}
