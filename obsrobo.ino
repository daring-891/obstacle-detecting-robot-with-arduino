#include <Servo.h>

#include <NewPing.h>      

Servo myservo;

//define the pins to be connected to ultrasonic sensorw

#define trigPin A0

#define echoPin A1

//define the pins to be connected to ultrasonic sensor

#define LeftMotor1  4

#define LeftMotor2  5

#define RightMotor1 2

#define RightMotor2 3

#define maxdist 300

#define objdist 23

NewPing sonar(trigPin, echoPin, maxdist); 

int leftDistance, rightDistance;

//setup function to define the pinmodes

void setup() 

{

  pinMode(LeftMotor1,  OUTPUT);

  pinMode(LeftMotor2,  OUTPUT);

  pinMode(RightMotor1, OUTPUT);

  pinMode(RightMotor2, OUTPUT);


  pinMode(trigPin, OUTPUT);

  pinMode(echoPin, INPUT);

  myservo.attach(11);   

  myservo.write(90);


  delay(1000);

}

//Loop infinite function

void loop()

{

   int read_dist;

  //Make servo to turn 90 degree

   myservo.write(90);

  

   delay(90);

   //calling read sensor function to read the sensor data

   read_dist = readsensors();

   //checking the distance that is measured with the predefined value

    if(read_dist < objdist)

   {

    //if low calling the decide path function

    decide_path();

   }

   //calling the move forward function to move the robot forward

   moveforward();


   delay(500);

} 

//Function to read the sensor value

int readsensors()

{

  int distance;


  delay(70);   

  //using the newping.h library function to measure the distance

  unsigned int uS = sonar.ping();

  distance = uS/US_ROUNDTRIP_CM;

  return distance;

}

void decide_path()

{

  robostop();

  //rotating the servo to 3 degree to right side

  myservo.write(3);  

  delay(500);

  //calling read sensor function to measure the distance on right side

  rightDistance = readsensors(); 

  delay(500);

  myservo.write(180);  

  delay(700);

  leftDistance = readsensors(); 

  delay(500);

  myservo.write(90); 

  delay(100);

  check_distance(); 

}

//function to compare the distances

void check_distance()

{

  //checking whether left measured distance is lesser that right

  if (leftDistance < rightDistance) 

  {

    turnright();

  }

  //checking whether left measured distance is greater that right

  else if (leftDistance > rightDistance)

  {

    turnleft();

  }

  else

  {

    turnaround(); 

  }

}

void moveforward()

{

  digitalWrite(LeftMotor1, HIGH);

  digitalWrite(LeftMotor2, LOW);

  digitalWrite(RightMotor1, HIGH);

  digitalWrite(RightMotor2, LOW);

}

void turnleft()

{

  digitalWrite(LeftMotor1, LOW);

  digitalWrite(LeftMotor2, LOW);

  digitalWrite(RightMotor1, HIGH);

  digitalWrite(RightMotor2, LOW);

  delay(350);

  moveforward();

}

void turnright()

{

  digitalWrite(LeftMotor1, HIGH);

  digitalWrite(LeftMotor2, LOW);

  digitalWrite(RightMotor1, LOW);

  digitalWrite(RightMotor2, LOW);

  delay(350);

  moveforward();

}

void turnaround()

{

  digitalWrite(LeftMotor1, LOW);

  digitalWrite(LeftMotor2, HIGH);

  digitalWrite(RightMotor1, HIGH);

  digitalWrite(RightMotor2, LOW);

  delay(700);

  moveforward();

}

void robostop()

{

  digitalWrite(LeftMotor1, LOW);

  digitalWrite(LeftMotor2, LOW);

  digitalWrite(RightMotor1, LOW);

  digitalWrite(RightMotor2, LOW);
}

