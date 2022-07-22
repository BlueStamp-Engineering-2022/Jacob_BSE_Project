#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>
#include <Adafruit_NeoPixel.h>




#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#define LED_PIN A0
#define LED_COUNT 40
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB +NEO_KHZ800);
uint32_t white = strip.Color(150, 150, 200);
uint32_t red = strip.Color(255, 0, 0);
uint32_t pink = strip.Color(175, 25, 35);
uint32_t blue = strip.Color(0, 100, 255);
//uint32_t gold = strip.Color(120, 125, 25);
//uint32_t numbers = strip.Color(/*whatever I wanna use*/);
const int buttonPin = A1;
int button = 0;


/* Assign a unique ID to this sensor at the same time */
Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);

void displaySensorDetails(void)
{
  sensor_t sensor;
  mag.getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" uT");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" uT");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" uT");  
  Serial.println("------------------------------------");
  Serial.println("");
  delay(500);
}

void setup(void) 
{
  strip.begin();
  strip.show();
  strip.clear();
  strip.setBrightness(10); //modified from 225
  pinMode (buttonPin, INPUT_PULLUP);
  Serial.begin(9600);
  Serial.println("HMC5883 Magnetometer Test"); Serial.println("");
  Wire.begin();
  /* Initialise the sensor */
  if(!mag.begin())
  {
    /* There was a problem detecting the HMC5883 ... check your connections */
    Serial.println("Ooops, no HMC5883 detected ... Check your wiring!");
    while(1);
  }
  /* Display some basic information on this sensor */
  displaySensorDetails();


   
}

void loop(void) 
{
  strip.fill(white, 0);
  /* Get a new sensor event */ 
  sensors_event_t event; 
  mag.getEvent(&event);
 
  /* Display the results (magnetic vector values are in micro-Tesla (uT)) */
  Serial.print("X: "); Serial.print(event.magnetic.x); Serial.print("  ");
  Serial.print("Y: "); Serial.print(event.magnetic.y); Serial.print("  ");
  Serial.print("Z: "); Serial.print(event.magnetic.z); Serial.print("  ");Serial.println("uT");

  // Hold the module so that Z is pointing 'up' and you can measure the heading with x&y
  // Calculate heading when the magnetometer is level, then correct for signs of axis.
  float heading = atan2(event.magnetic.y, event.magnetic.x);
  
  // Once you have your heading, you must then add your 'Declination Angle', which is the 'Error' of the magnetic field in your location.
  // Find yours here: http://www.magnetic-declination.com/
  // Mine is: -13* 2' W, which is ~13 Degrees, or (which we need) 0.22 radians
  // If you cannot find your Declination, comment out these two lines, your compass will be slightly off.
  //declination at home is .244 radians, blue stamp is .22
  float declinationAngle = 0.22;
  heading += declinationAngle;
  
  // Correct for when signs are reversed.
  if (heading < 0) heading += 2*PI;
    
  // Check for wrap due to addition of declination.
  if (heading > 2*PI) heading -= 2*PI;
   
  // Convert radians to degrees for readability.
  float headingDegrees = 360 - (heading * 180/M_PI); 

  
  Serial.print("Heading (degrees): "); Serial.println(headingDegrees);
  
    
  if (headingDegrees>0 && headingDegrees<15) {
    strip.setPixelColor(17, red);
    strip.setPixelColor(18, pink);
    strip.setPixelColor(16, pink);
  }
  
  if (headingDegrees>15 && headingDegrees<30) {
    strip.setPixelColor(18, red);
     strip.setPixelColor(17, pink);
     strip.setPixelColor(19, pink);
  }
  
  if (headingDegrees>30 && headingDegrees<45) {
    strip.setPixelColor(19, red);
    strip.setPixelColor(18, pink);
    strip.setPixelColor(20, pink);
  }
  if (headingDegrees>45 && headingDegrees<60) {
    strip.setPixelColor(20, red);
    strip.setPixelColor(19, pink);
    strip.setPixelColor(21, pink);
  }
  if (headingDegrees>60 && headingDegrees<75) {
    strip.setPixelColor(21, red);
    strip.setPixelColor(20, pink);
    strip.setPixelColor(22, pink);
  }
  if (headingDegrees>75 && headingDegrees<90) {
    strip.setPixelColor(22, red);
    strip.setPixelColor(21, pink);
    strip.setPixelColor(23, pink);
  }
    if (headingDegrees>90 && headingDegrees<105) {
    strip.setPixelColor(23, red);
    strip.setPixelColor(22, pink);
    strip.setPixelColor(0, pink);
  }
  if (headingDegrees>105 && headingDegrees<120) {
    strip.setPixelColor(0, red);
    strip.setPixelColor(23, pink);
    strip.setPixelColor(1, pink);
  }
  if (headingDegrees>120 && headingDegrees<135) {
    strip.setPixelColor(1, red);
    strip.setPixelColor(0, pink);
    strip.setPixelColor(2, pink);
  }
    if (headingDegrees>135 && headingDegrees<150) {
    strip.setPixelColor(2, red);
    strip.setPixelColor(1, pink);
    strip.setPixelColor(3, pink);
  }
    if (headingDegrees>150 && headingDegrees<165) {
    strip.setPixelColor(3, red);
    strip.setPixelColor(2, pink);
    strip.setPixelColor(4, pink);
  }
    if (headingDegrees>165 && headingDegrees<180) {
    strip.setPixelColor(4, red);
    strip.setPixelColor(3, pink);
    strip.setPixelColor(5, pink);
  }
    if (headingDegrees>180 && headingDegrees<195) {
    strip.setPixelColor(5, red);
    strip.setPixelColor(4, pink);
    strip.setPixelColor(6, pink);
  }
    if (headingDegrees>195 && headingDegrees<210) {
    strip.setPixelColor(6, red);
    strip.setPixelColor(5, pink);
    strip.setPixelColor(7, pink);
  }
    if (headingDegrees>210 && headingDegrees<225) {
    strip.setPixelColor(7, red);
    strip.setPixelColor(6, pink);
    strip.setPixelColor(8, pink);
  }
    if (headingDegrees>225 && headingDegrees<240) {
    strip.setPixelColor(8, red);
    strip.setPixelColor(7, pink);
    strip.setPixelColor(9, pink);
     }
      if (headingDegrees>240 && headingDegrees<255) {
    strip.setPixelColor(9, red);
    strip.setPixelColor(8, pink);
    strip.setPixelColor(10, pink);
  }
    if (headingDegrees>255 && headingDegrees<270) {
    strip.setPixelColor(10, red);
    strip.setPixelColor(9, pink);
    strip.setPixelColor(11, pink);
  }
    if (headingDegrees>270 && headingDegrees<285) {
    strip.setPixelColor(11, red);
    strip.setPixelColor(10, pink);
    strip.setPixelColor(12, pink);
  }
    if (headingDegrees>285 && headingDegrees<300) {
    strip.setPixelColor(12, red);
    strip.setPixelColor(11, pink);
    strip.setPixelColor(13, pink);
  }
    if (headingDegrees>300 && headingDegrees<315) {
    strip.setPixelColor(13, red);
    strip.setPixelColor(12, pink);
    strip.setPixelColor(14, pink);
  }
    if (headingDegrees>315 && headingDegrees<330) {
    strip.setPixelColor(14, red);
    strip.setPixelColor(13, pink);
    strip.setPixelColor(15, pink);
  }
    if (headingDegrees>330 && headingDegrees<345) {
    strip.setPixelColor(15, red);
    strip.setPixelColor(14, pink);
    strip.setPixelColor(16, pink);
  }
  if (headingDegrees>345 && headingDegrees<360) {
    strip.setPixelColor(16, red);
    strip.setPixelColor(15, pink);
    strip.setPixelColor(17, pink);
  }
  

//strip.setPixelColor(24, red);
//strip.setPixelColor(25, red);
  
  float z=event.magnetic.z;
  float x=event.magnetic.x;
  float y=event.magnetic.y;  

 
  
 
 float inclination = calcInclination(event.magnetic.x,event.magnetic.y,event.magnetic.z);
 float inclinationDegrees = (inclination * (180/M_PI));


  // Check if negative, and if so put at correct positive angle
  if (inclinationDegrees < 0){
    inclinationDegrees += 360;
  }

  // Do azimuth switching if necessary
  if (headingDegrees > 180){
    inclinationDegrees = 180 - inclinationDegrees ;
  }

  // Make sure we are under 360
  if (inclinationDegrees > 360){
    inclinationDegrees -= 360;
  }

  // Make sure we are over zero
  if (inclinationDegrees < 0){
    inclinationDegrees += 360;
  }
  Serial.println ("inclinationDegrees: ");
  Serial.print (inclinationDegrees);  


if (inclinationDegrees>0 && inclinationDegrees<22.5) {
    strip.setPixelColor(24, red);
    strip.setPixelColor(39, pink);
    strip.setPixelColor(25, pink);
}
if (inclinationDegrees>22.5 && inclinationDegrees<45) {
    strip.setPixelColor(25, red);
    strip.setPixelColor(24, pink);
    strip.setPixelColor(26, pink);
}
if (inclinationDegrees>45 && inclinationDegrees<67.5) {
    strip.setPixelColor(26, red);
    strip.setPixelColor(25, pink);
    strip.setPixelColor(27, pink);
}
if (inclinationDegrees>67.5 && inclinationDegrees<90) {
    strip.setPixelColor(27, red);
    strip.setPixelColor(26, pink);
    strip.setPixelColor(28, pink);
}
if (inclinationDegrees>90 && inclinationDegrees<112.5) {
    strip.setPixelColor(28, red);
    strip.setPixelColor(27, pink);
    strip.setPixelColor(29, pink);
}
if (inclinationDegrees>112.5 && inclinationDegrees<135) {
    strip.setPixelColor(29, red);
    strip.setPixelColor(28, pink);
    strip.setPixelColor(30, pink);
}
if (inclinationDegrees>135 && inclinationDegrees<157.5) {
    strip.setPixelColor(30, red);
    strip.setPixelColor(29, pink);
    strip.setPixelColor(31, pink);
}
if (inclinationDegrees>157.5 && inclinationDegrees<180) {
    strip.setPixelColor(31, red);
    strip.setPixelColor(30, pink);
    strip.setPixelColor(32, pink);
}
if (inclinationDegrees>180 && inclinationDegrees<202.5) {
    strip.setPixelColor(32, red);
    strip.setPixelColor(31, pink);
    strip.setPixelColor(33, pink);
}
if (inclinationDegrees>202.5 && inclinationDegrees<225) {
    strip.setPixelColor(33, red);
    strip.setPixelColor(32, pink);
    strip.setPixelColor(34, pink);
}
if (inclinationDegrees>225 && inclinationDegrees<247.5) {
    strip.setPixelColor(34, red);
    strip.setPixelColor(33, pink);
    strip.setPixelColor(35, pink);
}
if (inclinationDegrees>247.5 && inclinationDegrees<270) {
    strip.setPixelColor(35, red);
    strip.setPixelColor(34, pink);
    strip.setPixelColor(36, pink);
}
if (inclinationDegrees>270 && inclinationDegrees<292.5) {
    strip.setPixelColor(36, red);
    strip.setPixelColor(35, pink);
    strip.setPixelColor(37, pink);
}
if (inclinationDegrees>292.5 && inclinationDegrees<315) {
    strip.setPixelColor(37, red);
    strip.setPixelColor(38, pink);
    strip.setPixelColor(36, pink);
}
if (inclinationDegrees>315 && inclinationDegrees<337.5) {
    strip.setPixelColor(38, red);
    strip.setPixelColor(37, pink);
    strip.setPixelColor(39, pink);
}
if (inclinationDegrees>337.5 && inclinationDegrees<360) {
    strip.setPixelColor(39, red);
    strip.setPixelColor(38, pink);
    strip.setPixelColor(24, pink);
}

  strip.show();
}   

float calcInclination(float x, float y, float z)
{
  /* Given x,y,z componets of a field, return the
     inclination angle w.r.t horizontal in radians. */
     
  return atan2(z,sqrt(x*x + y*y));
}
