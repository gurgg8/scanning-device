#include <Servo.h>
#include <math.h>

// Initialize servo objects and variables
Servo serch; 
Servo laser_1;
int x = 0;
int i = 0;
bool j;

// Initialize distance measurement variables
float duration, distance;

void setup()
{
  // Set pin modes and initialize servo positions
  pinMode(6, OUTPUT);
  pinMode(5, INPUT);
  pinMode(2, OUTPUT);
  pinMode(13, OUTPUT);
  serch.attach(9);
  laser_1.attach(10);
  pinMode(9, OUTPUT);
  Serial.begin(9600);
  serch.write(90);
}

void loop() 
{
  // Perform servo scan and laser measurement
  while (i <= 140)
  {
    scanAndMeasure();
    serch.write(x);
    delay(50);
    x++;
    i++;
  }
  
  while (i >= 30)
  {
    scanAndMeasure();
    serch.write(x);
    delay(50);
    x--;
    i--;
  }
}

void scanAndMeasure()
{
  distance = getDistance();
  
  // Check if distance is within range of laser
  if (distance > 0 && distance < 50)
  {
    // Turn on laser
    digitalWrite(13, HIGH);

    // Calculate laser angle based on distance and servo angle
    float angle = getLaserAngle(distance, x);
    laser_1.write((int)angle);
    Serial.println((int)angle);

    j = true;
  }
  else
  {
    // Turn off laser if distance is out of range
    digitalWrite(13, LOW);
    j = false;
  }
}

float getDistance()
{
  // Send ultrasonic pulse and measure duration of echo
  digitalWrite(6, LOW);
  digitalWrite(6, HIGH);
  digitalWrite(6, LOW);
  duration = pulseIn(5, HIGH);

  // Convert duration to distance in cm and return
  return (duration * 0.0343) / 2;
}

float getLaserAngle(float distance, int servoAngle)
{
  // Calculate laser angle based on distance and servo angle
  float laserAngle = atan((distance * sin(servoAngle / 180.0 * PI)) / (13.5 - (distance * cos(servoAngle / 180.0 * PI)))) / PI * 180.0 + 90;

  return laserAngle;
}























































  /*#include <Servo.h>
  #include <math.h>


  Servo serch; 
  Servo laser_1;
  Servo laser_2;

  int x = 0;
  int i = 0;  
  bool j;

  float duration, distance;


  void setup()
  {

    pinMode(6, OUTPUT);
    pinMode(5, INPUT);
    pinMode(2, OUTPUT);
    pinMode(13, OUTPUT);
    
    serch.attach(9);
    laser_1.attach(10);

    pinMode(9, OUTPUT);
    
    Serial.begin(9600);

    serch.write(90);

  }

  void loop() 
  {

    //Serial.println(dist());

    while (i <= 140)
    {
      scangal();     
      //Serial.print("distance is: ");
      //Serial.println(dist());
      serch.write(x);
      delay(50);     
      //Serial.print("Servo Position: ");
      //Serial.println(i);
      x++;
      i++;
    }
   
    while (i >= 30)
    {
      scangal();
      //Serial.print("distance is: ");
      //Serial.println(dist());
        serch.write(x);
        delay(50);
      //Serial.print("Servo Position: ");
      //Serial.println(i);
      x--;
      i--;
      
    }
  
     
  }
  
  
  void scangal()
  {

    if (dist() < 50)
      {
        //Serial.print("good\n");

        digitalWrite(13, HIGH);

        //Serial.print("Distance: ");
        //Serial.println(distance);

        laser_1.write((int)b());

        
        Serial.println((int)b());

       j = true;

 
      }
      else
      {

        //Serial.print("bad\n");

        digitalWrite(13, LOW);

        j = false;
     
      }  
  }
  int dist()
  {

    digitalWrite(6, LOW);
    digitalWrite(6, HIGH);
    digitalWrite(6, LOW);

    duration = pulseIn(5, HIGH);
    distance = (duration*.0343)/2;
    return(distance);
  }
  float b()
{
  float t;
  float d = dist();
  
  if (d > 0 && d < 50) { // make sure the distance is within range
    t = atan((d * sin(x / 180.0 * PI)) / (13.5 - (d * cos(x / 180.0 * PI)))) / PI * 180.0 + 90;
  } else {
    t = 0; // return 0 if the distance is out of range
  }

  return t;
}

*/