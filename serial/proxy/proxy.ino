void setup() {
  Serial1.begin(115200, SERIAL_8N1);
  Serial.println("Up\n");
}

void loop()
{
  if (Serial1.available() > 0)
  {
    Serial.write(Serial1.read());
  }
  
  if(Serial.available() > 0)
  {
    Serial1.write(Serial.read());
  }
}
