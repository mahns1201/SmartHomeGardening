char data;

void setup()
{
  Serial.begin(115200);
  pinMode(13, OUTPUT);
}

void loop()
{
  if (Serial.available())
  {
    data = Serial.read();
  }
  
  
  if (data == "A")
  {
    digitalWrite(13, 1);
  }
  else if (data == "B")
  {
    digitalWrite(13, 0);
  }
}
