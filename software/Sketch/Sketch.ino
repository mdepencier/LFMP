#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_TSL2561_U.h>

// initialize motor pins
int motorA = 12;
int brakeA = 9;

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

  Serial.println("starting up...");

  // display sensor information to serial
  displaySensorDetails();

  // configure the sensor
  configureSensor();

  // configure motor pin modes
  pinMode(motorA, OUTPUT);
  pinMode(brakeA, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  // set up sensor event
  sensors_event_t event;

  // get event data
  tsl.getEvent(&event);

  // if the event contains a value for light
  if(event.light){
    // Serial.print(event.light); // print out the value of light intensity
    // Serial.println(" lux"); // in lux
  } else {
    Serial.println("Unable to read sensor...");
  }
  
//  digitalWrite(motorA, HIGH);
//  digitalWrite(brakeA, LOW);
  
  int result = event.light + 5;
  result -= result % 10;

  Serial.println(event.light);

//  for (int a=0;a<256;a++){
//    PORTD = a;//send out ramp to digital pins 0-7
//    Serial.println(a);
//    delay(10);//wait 5ms
//  }

  PORTD = event.light;
  
  delay(40);
}
