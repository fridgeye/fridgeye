bool currentDoorState;
double currentTemperature;

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

double getTemperatureInC()
{
  int tmp36Value = analogRead(A4);
  return (tmp36Value * 0.0008 - 0.5) / 0.010;
}

void setup()
{
  // Configure the pin connected to thte photocell as an analog input
  pinMode(A0, INPUT);

  // Configure the pin connected to the TMP36 as an anolog input
  pinMode(A4, INPUT);

  // Register currentTemperature with the Particle Cloud
  Particle.variable("fridge-temp", currentTemperature);

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

  // Report the temperature
  currentTemperature = getTemperatureInC();
  Serial.printlnf("Temperature: %.2f", currentTemperature);

  delay(1000);
}
