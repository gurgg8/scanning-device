#include <Servo.h>
#include <math.h>

// Initialize servo objects and variables
Servo serch; 
Servo laser_1;
int x = 30;
int i = 30;
bool j;

// Initialize distance measurement variables
float duration, distance;

void setup()
{
  // Set pin modes and initialize servo positions
  pinMode(6, OUTPUT);
  pinMode(5, INPUT);
  pinMode(2, OUTPUT);
  pinMode(12, OUTPUT);
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
    

    // Calculate laser angle based on distance and servo angle
    float angle = getLaserAngle(distance, x);
    laser_1.write((int)angle);
    Serial.println((int)angle);

    shoot();
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

void shoot()
{
    Serial.println("target has been detected");
  // Turn on laser
    digitalWrite(12, HIGH);
    delay(2000);
    // Turn off laser 
    digitalWrite(12, LOW);
    delay(1000);
    Serial.println("target has been eliminated");

}
