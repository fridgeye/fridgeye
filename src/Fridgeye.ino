bool currentDoorState = false;

bool isDoorOpen()
{
  int lightLevel = analogRead(A0);
  if (lightLevel > 10)
  {
    return true;
  }
  else
  {
    return false;
  }
}

void setup()
{
  // Configure the pin connected to thte photocell as an analog input
  pinMode(A0, INPUT);

  // Open the USB serial port
  Serial.begin(9600);

  // Initialize the door state. true is open and false indicates closed
  currentDoorState = isDoorOpen();
}

void loop()
{
  // Query the state of the door right now
  bool newDoorState = isDoorOpen();

  // If the new state is different than the stored state then we need to
  // fire an event
  if (newDoorState != currentDoorState)
  {
    currentDoorState = newDoorState;
    if(currentDoorState)
    {
      Serial.println("Door Open");
      Particle.publish("fridge-door-open", PRIVATE);
    }
    else
    {
      Serial.println("Door Closed");
      Particle.publish("fridge-door-closed", PRIVATE);
    }
  }

  delay(1000);
}
