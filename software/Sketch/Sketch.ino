#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_TSL2561_U.h>

// initialize motor pins
int motorA = 3;
int brakeA = 9;
int motorB = 11;
int brakeB = 8;
int dirA = 12;
int dirB = 13;

boolean bit3state;

int speaker = 5;

Adafruit_TSL2561_Unified tsl = Adafruit_TSL2561_Unified(TSL2561_ADDR_FLOAT, 12345);

void displaySensorDetails(void)
{
  sensor_t sensor;
  tsl.getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" lux");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" lux");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" lux");  
  Serial.println("------------------------------------");
  Serial.println("");
  delay(500);
}

void configureSensor(void)
{
  /* You can also manually set the gain or enable auto-gain support */
  // tsl.setGain(TSL2561_GAIN_1X);      /* No gain ... use in bright light to avoid sensor saturation */
  // tsl.setGain(TSL2561_GAIN_16X);     /* 16x gain ... use in low light to boost sensitivity */
  tsl.enableAutoRange(true);            /* Auto-gain ... switches automatically between 1x and 16x */
  
  /* Changing the integration time gives you better sensor resolution (402ms = 16-bit data) */
  tsl.setIntegrationTime(TSL2561_INTEGRATIONTIME_13MS);      /* fast but low resolution */
  // tsl.setIntegrationTime(TSL2561_INTEGRATIONTIME_101MS);  /* medium resolution and speed   */
  // tsl.setIntegrationTime(TSL2561_INTEGRATIONTIME_402MS);  /* 16-bit data but slowest conversions */

  /* Update these values depending on what you've set above! */  
  Serial.println("------------------------------------");
  Serial.print  ("Gain:         "); Serial.println("Auto");
  Serial.print  ("Timing:       "); Serial.println("13 ms");
  Serial.println("------------------------------------");
}

void setup() {
  Serial.begin(9600);
  Serial.println("Line Following Music Player");
  
  if(!tsl.begin()){
    Serial.print("no sensor detected");
    while(1);
  }

  for (int i=0;i<8;i++){
    pinMode(i,OUTPUT);
  }

  pinMode(10, OUTPUT);

  Serial.println("starting up...");

  // display sensor information to serial
  displaySensorDetails();

  // configure the sensor
  configureSensor();

  // configure motor pin modes
  pinMode(motorA, OUTPUT);
  pinMode(brakeA, OUTPUT);
  pinMode(brakeB, OUTPUT);
  pinMode(motorB, OUTPUT);
  pinMode(12, OUTPUT);

}

void loop() {

  // set up sensor event
  sensors_event_t event;
  int result;

  tsl.getEvent(&event);

  result = event.light*20;

  if(event.light > 255)
    result = 255*20;

  if(event.light){
     Serial.print(result); // print out the value of light intensity
     Serial.println(" lux"); // in lux
  } else {
    Serial.println("Unable to read sensor...");
  }

  int a = 30000/(2*result);

  digitalWrite(13, HIGH);
  digitalWrite(brakeB, LOW);
  digitalWrite(brakeA, LOW);
  analogWrite(motorA, 0);
  analogWrite(motorB, 0);

  for(int j = 0; j < 30; j++){
    for(int i = 0; i < a; i++){
      PORTD = 255;
      delayMicroseconds(result);
      PORTD = B00001000;
      delayMicroseconds(result);
    }
  }

  // pin 3 always HIGH but
  // good enough
  
}
