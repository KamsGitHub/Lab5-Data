  const int ledPin = 9;       // pin that the LED is attached to
  const int TWOPI = 2*3.1415926;
  unsigned long currentTime = 0;
  unsigned long lastTime = 0;
  const unsigned long intervalBetweenData = 1000;
  int brightness;

  const int numReadings = 50;
  int readings[numReadings];  // the readings from the analog input
  int readIndex = 0;          // the index of the current reading
  int total = 0;              // the running total
  int average = 0;            // the average
  int inputPin = A0;

  void setup() {
    // initialize serial communication with computer:
    pinMode(ledPin, OUTPUT);
    Serial.begin(9600);
    // initialize all the readings to 0:
    for (int thisReading = 0; thisReading < numReadings; thisReading++) {
      readings[thisReading] = 0;
    }

  }

  void loop() {
    brightness = 100+5*sin(1.0*TWOPI*millis()/1000);
    analogWrite(ledPin,brightness);
      // subtract the last reading:
      total = total - readings[readIndex];
      // read from the sensor:
      readings[readIndex] = analogRead(inputPin);
      // add the reading to the total:
      total = total + readings[readIndex];
      // advance to the next position in the array:
      readIndex = readIndex + 1;
    
      // if we're at the end of the array...
      if (readIndex >= numReadings) {
        // ...wrap around to the beginning:
        readIndex = 0;
      }
    
      // calculate the average:
      average = total / numReadings;
      // send it to the computer as ASCII digits
      Serial.print(millis());
      Serial.print(',');
      Serial.println(average);
    delay(5);
  }
