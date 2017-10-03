int motorPin = 2; //Make sure this is an analog OUT pin
int opticalSensor = 3;//Make sure this is an analog IN pin
int speakerPin = 5; //Make sure this is an analog OUT pin
int startedPin = 7; //This can be digital in

void setup() {
  pinMode(motorPin, OUTPUT);
  pinMode(opticalSensor, INPUT);
  pinMode(speakerPin, OUTPUT);

  Serial.begin(9600);
  while (! Serial);
  Serial.println("Program Started");
}

int brightness () {
  //Get input of the opticalSensor
  //Return brightness value

}

void loop() {
  if (digitalRead (startedPin) == high) {
    int speed = 150;
    int tolerance = 0.1;
    analogWrite(motorPin, speed);


    if (brightness > tolerance) {

      //Output voltage to the speaker based on brightness value

    }


  }

}








