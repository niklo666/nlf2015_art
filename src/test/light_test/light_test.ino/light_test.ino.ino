void setup() 
{
   Serial.begin(9600);     // opens serial port, sets data rate to 9600 bps
   Serial1.begin(115200);     // opens serial port, sets data rate to 9600 bps
}

char buffer[128];
int buffer_counter = 0;
void loop() 
{
  if (Serial1.available() > 0) 
  {
    // read the incoming byte:
    incomingByte = Serial1.read();

    if (incomingByte != '0')
    {
      buffer[buffer_counter++] = incomingByte;
    }
    else
    {
      buffer[buffer_counter++] = '0';
      Serial.print("I received: ");
    }
  
    // say what you got:
    Serial.print("I received: ");
    Serial.print(incomingByte);
    Serial1.print("I received: ");
    String s = incomingByte;
    Serial1.print(s);
   }
}
