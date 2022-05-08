

/////////////////////////////////////////////
//** Board Used: Arduino UNO             **//
//** App Used: Arduino Bluetooth Control **//
//** Power Source: 9V Battery            **//
/////////////////////////////////////////////


// Black Line Follower 
int IR1=6;      //Right sensor
int IR2=7;    //left Sensor
// motor one
int MotorAip1=2;
int MotorAip2=3; //analogue
// motor two
int MotorBip1=4;
int MotorBip2=5; //analogue
int spd= 100; //linear speed
int turnspd= 70; //turning speed

char bt;
char mode; 

#define echoPin 8 
#define trigPin 9
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement

void setup() 
{
  // put your setup code here, to run once:
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  pinMode(IR1,INPUT);
  pinMode(IR2,INPUT);
  pinMode(MotorAip1,OUTPUT);
  pinMode(MotorAip2,OUTPUT);
  pinMode(MotorBip1,OUTPUT);
  pinMode(MotorBip2,OUTPUT);
  
  Serial.begin(9600);
  Serial.print("Line Follower: 1 | Obstacle Avioder 2 | BT Control 3 | Stop 's' ");
}
void loop() 
{

// Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor

 if(Serial.available()>0)
 {     
      bt= Serial.read(); // reading the data received from the bluetooth module
      Serial.println(bt);
      delay(50);
 if(bt=='1' || bt=='2' || bt=='3' || bt=='s')
 { 
  mode=bt;
  switch(mode)
   {
        case '1': Serial.println("Switching to: Line Follower"); break; // when 1 is pressed on the app on your smart phone
        case '2': Serial.println("Switching to: Obstacle Avoider");  break; // when 2 is pressed on the app on your smart phone
        case '3': Serial.println("Switching to: Bluetooth Control"); break; // when 3 is pressed on the app on your smart phone
        case 's': Serial.println("Clearing all Modes: "); break; // when s is pressed on the app on your smart phone
   }
 }}
 if(mode == '1') 
      {  lineFollower(); }
      
 if(mode == '2') 
      {  obsAvoider(); }

 if(mode == '3') 
      {  BTControl(); }
      
 if(mode == 's') 
      {  Stop(); }        
}

void FW()
{//Move both the Motors
    digitalWrite(MotorAip1,LOW);
    analogWrite(MotorAip2,spd);
    digitalWrite(MotorBip1,LOW);
    analogWrite(MotorBip2,spd); 
    Serial.println(" Moving Forward "); }

void BK()
{//Move both the Motors
    digitalWrite(MotorAip1,HIGH);
    digitalWrite(MotorAip2,LOW);
    digitalWrite(MotorBip1,HIGH);
    digitalWrite(MotorBip2,LOW);
    Serial.println(" Moving Backward ");}

  
void Stop()
{//Stop both the motors
    digitalWrite(MotorAip1,LOW);
    analogWrite(MotorAip2,LOW);
    digitalWrite(MotorBip1,LOW);
    analogWrite(MotorBip2,LOW); 
    Serial.println(" Bot Stopped ");}
  
void RW()
{//Tilt robot towards right by stopping the right wheel and moving the left one
     digitalWrite(MotorAip1,LOW);
    analogWrite(MotorAip2,LOW);
    digitalWrite(MotorBip1,LOW);
    analogWrite(MotorBip2,turnspd);
    Serial.println(" Turnling Right ");
   delay(100);  }

void LW()
{
    //Tilt robot towards left by stopping the left wheel and moving the right one
    digitalWrite(MotorAip1,LOW);     
    analogWrite(MotorAip2,turnspd);
    digitalWrite(MotorBip1,LOW);
    analogWrite(MotorBip2,LOW);
    Serial.println(" Turnling Left ");
   delay(100);  }

void lineFollower()
{
  Serial.print("Line Follower Mode |");
  if(digitalRead(IR1)==LOW && digitalRead(IR2)==LOW)  //IR not on black line
  {  FW();  }

  else if(digitalRead(IR1)==LOW && digitalRead(IR2)==HIGH)
  {  LW();   }

  else if(digitalRead(IR1)==HIGH && digitalRead(IR2)==LOW)
  {  RW();  }
  
  else if(digitalRead(IR1)==HIGH && digitalRead(IR2)==HIGH) //IR will not glow on black line
  {  Stop(); }

  else
  {  Stop();  }
}

void obsAvoider()
{ 
  Serial.print("Obstacle Avoider Mode |");
if(distance <= 10)
  {
    Stop();
  }
    else
  {  FW();  
  }
Serial.print(" Distance: ");  
  Serial.print(distance);
  Serial.println(" cm");
}

void BTControl()
{
Serial.print("BT Mode: ");
        if (bt == 'f') {FW();}
        else if (bt == 'b') {BK();}
        else if (bt == 'l') {LW();}
        else if (bt == 'r') {RW();}
        else Stop();
}
