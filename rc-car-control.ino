#include <Servo.h>    //library needed for servo control

Servo servo1;
Servo servo2;

//pins
int M1 = 3;   // motor 1 speed - PWM
int M2 = 11;   // motor 2 speed - PWM
int E1 = 12;   // motor 1 direction - digital
int E2 = 13;   // motor 2 direction - digital
int servopin1 = 5;  //servo pin1 - PWM
int servopin2 = 6;  //servo pin2 - PWM
int brake1 = 9; //stops the motor with a high output
int brake2 = 8;   //stops the motor with a high output
int I1 = 14;  //read the current draw of the motor 1
int I2 = 15;  //read the current draw of motor 2

//variables
char val;
boolean reverseFlag;
int speedy = 80; //255 is maximum speed and minimum which is stop, is 0


void setup()
{
  //setup pins
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);
  pinMode(E1, OUTPUT);
  pinMode(E2, OUTPUT);
  pinMode(brake1, OUTPUT);
  pinMode(brake2, OUTPUT);
  pinMode(I1, INPUT);
  pinMode(I2, INPUT);

  //setup servos
  servo1.attach(servopin1);
  servo2.attach(servopin2);
  servo1.write(90);
  servo2.write(90);

  //setup bluetooth
  Serial.begin(9600);
}

void loop()
{
  //int power = (I1*12)+(I2*12);    //send the power draw every time the program loops 
  //Serial.write(power);
  
  val = '!';    //resets the value read from the app so that it doesn't just loop
  if (Serial.available() > 0)   //checks for serial input
  {
    val = Serial.read();       // this will read and save the value as String (easier to convert into int)
    delay(20); 
    servoReset();
    delay(20);
    switch (val) // Perform an action depending on the command (will look through to see what was sent)
    {
      case 'w'://Move Forward
      case 'W':
        reverseFlag = false;
        forward (speedy);  // this will make the car go forward with the speed of each motor the parameters
        break;
      case 's'://Move Backwards
      case 'S':
        reverseFlag = true;
        reverse (speedy);  // this will make the car go backwards with the speed of each motor the parameters
        break;
      case 'a'://Turn Left
      case 'A':
        left();
        break;
      case 'd'://Turn Right
      case 'D':
        right();
        break;
      case 'q': //stop
      case 'Q':
        brake();
        break;
      case 'z':   //speedup
      case 'Z':
        speedup();
        if(reverseFlag)
        {
          reverse(speedy);
        }
        else
        {
          forward(speedy);
        }
        break;   
      case 'x':   //slowdown
      case 'X':
        slowdown();
        if(reverseFlag)
        {
          reverse(speedy);
        }
        else
        {
          forward(speedy);
        }
        break;   
      default:
        break;
    }
  }
}

/*
 * stops the motors using the 'brake' pins of the driver board
 */
void brake(void) 
{
  digitalWrite(brake1, HIGH); // the low here is to set the voltage for E1 to low, as in 0V cause it's the LOW value.
  digitalWrite(brake2, HIGH); // the low here is to set the voltage for E2 to low, as in 0V cause it's the LOW value.
  speedy = 80;
}

/*
 * sets motors in forward direction (low)
 * inputs the desired speed of the motors (0 to 255)
 */
void forward(int a)
{
  digitalWrite(brake1, LOW);  //ensures the brake is disabled
  digitalWrite(brake2, LOW);

  digitalWrite(E1, LOW);    // low => forward
  analogWrite(M1, a);  // sets motor1 to speed A
  digitalWrite(E2, LOW);    // low => forward
  analogWrite(M2, a);  // sets motor2 to speed B
}

/*
 * sets motors in reverse direction (high)
 * inputs the desired speed of the motors (0 to 255)
 */
void reverse(int a)
{
  digitalWrite(brake1, LOW);  //ensures the brake is disabled
  digitalWrite(brake2, LOW);

  digitalWrite(E1, HIGH);    // high => reverse
  analogWrite(M1, a);  // sets motor1 to speed A
  digitalWrite(E2, HIGH);    // high => reverse
  analogWrite(M2, a);  // sets motor2 to speed B
}


/*
 * increases the speed of the motors
 * speed in synchronous
 * increments the variable representing the speed by a set value
 */
void speedup(void)
{
    if(speedy < 250)    //255 is max speed, want to keep it in multiples of 10
    {
      speedy += 10; 
    }
    else{}
}

/*
 * decreases the speed of the motors
 * speed in synchronous
 * decriments the variable representing the speed by a set value
 */
void slowdown(void)
{
    if(speedy > 20)   //motors stall under 20
    {
      speedy -= 10; 
    }
    else{}
}


  /*
 * resets the servos to 90 degrees
 */
  void servoReset(void)
  {
    servo1.write(90);
    delay(20);
    servo2.write(90);
    delay(20);
  }

    /*
 * this will turn the car to the right using servos with PWM
 * uses the Arduino Servo library
  */
  void right(void)
  {
     servo1.write(135);
     delay(20);
     servo2.write(45);
     delay(20);
  }
  
  /*
   * this will turn the car to the left using servos with PWM
   * uses the Arduino Servo library
   * the inverse of the right(void) function
   */
  void left(void)
  {
     servo1.write(45);
     delay(20);
     servo2.write(135);
     delay(20);
  }




