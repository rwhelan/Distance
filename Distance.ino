
// Output Pins, IN ORDER from LSB to MSB (hard coded currently to 10 pins)
int Pins[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 16};
// Which Analog pin is the sensor on
int SensorPin = 0;


// Number of samples to keep
const int numSamples = 10;
int Samples[numSamples];
int idx = 0;
// delay between readings
const int loopDelay = 100;

// Serial output of the values?
const bool withSerial = false;

void WriteOutInt(int num){
// This function takes an int and writes it out over the 
// output pins.  LOW is HIGH and HIGH is LOW after the 
// logic shift in the IC connected to the output pins

  for (int i = 0; i < 10; i++){
    if ( (num >> i) & 1 ){
      digitalWrite(Pins[i], LOW);
    } else {
      digitalWrite(Pins[i], HIGH);
    }
  }
}

int sampleAvg(){
// Returns a floored avg of all the values in the Samples[] Array

  int total = 0;
  for (int i = 0; i < numSamples; i++) {
    total += Samples[i];
  }
  return total / numSamples;
}

void setup() {
  if (withSerial) { Serial.begin(9600); }

// Set all Pins[] as output pins and set them all HIGH
// which is wired to be LOW
  for (int i = 0; i < 10; i++){
    pinMode(Pins[i], OUTPUT);
    digitalWrite(Pins[i], HIGH);
  }
}

void loop() {
  if (idx >= numSamples) { idx = 0; }

  Samples[idx] = analogRead(SensorPin);
  idx += 1;

  if (withSerial) {  
    for (int i = 0; i < numSamples; i++) {
      Serial.print(Samples[i]);
      Serial.print(" ");
    }
    Serial.print("- ");
    Serial.print(sampleAvg());
    Serial.print("\n");
  }
  
  WriteOutInt(sampleAvg());
  delay(loopDelay); 
}
