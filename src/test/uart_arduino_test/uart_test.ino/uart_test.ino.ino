int led = 13;
int ledstate = LOW;

void setup() 
{
  pinMode(led, OUTPUT); 
  
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial1.begin(1000000, SERIAL_8N1);

  Serial.print("setup exit...");
  Serial1.print("setup exit...");
}

void loop() 
{
  // put your main code here, to run repeatedly:
  delay(1000);
  Serial.print("this is a test...");
  Serial1.print("this is a test...");
  digitalWrite(led, ledstate);
  ledstate = !ledstate;
}
