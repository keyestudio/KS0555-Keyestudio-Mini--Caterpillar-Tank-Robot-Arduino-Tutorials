/*
  Keyestudio Mini Tank Robot V3 (Popular Edition)
  lesson 18
  Fire extinguishing tank
  http://www.keyestudio.com
*/

int flame_L = A1; //Define the flame interface on the left as the analog pin A1
int flame_R = A2; //Define the flame interface on the right as the analog pin A2
//The wiring of line tracking sensor
#define L_pin  11  //left
#define M_pin  7  //middle
#define R_pin  8  //right
//The pin of the servo 130
int INA = 12;
int INB = 13;
#define ML_Ctrl 4  //Define the direction control pin of the left motor
#define ML_PWM 6   //Define the PWM control pin of the left motor
#define MR_Ctrl 2  //Define the direction control pin of the right motor
#define MR_PWM 5   //Define the PWM control pin of the right motor
int L_val, M_val, R_val, flame_valL, flame_valR;

void setup()
{
  Serial.begin(9600);
  //Set all pins of the line tracking sensor as input mode
  pinMode(L_pin, INPUT);
  pinMode(M_pin, INPUT);
  pinMode(R_pin, INPUT);
  //Define the flame as INPUT
  pinMode(flame_L, INPUT);
  pinMode(flame_R, INPUT);
  //Define the motor as OUTPUT
  pinMode(ML_Ctrl, OUTPUT);
  pinMode(ML_PWM, OUTPUT);
  pinMode(MR_Ctrl, OUTPUT);
  pinMode(MR_PWM, OUTPUT);
  pinMode(INA, OUTPUT);//Set digital port INA as OUTPUT
  pinMode(INB, OUTPUT);//Set digital port INB as OUTPUT
}

void loop () {
  //Read the analog value of the flame sensors
  flame_valL = analogRead(flame_L);
  flame_valR = analogRead(flame_R);
  Serial.print(flame_valL);
  Serial.print("  ");
  Serial.print(flame_valR);
  Serial.println("  ");
//  delay(500);
  if (flame_valL <= 700 || flame_valR <= 700) {
    Car_Stop();
    fan_begin();
  } else {
    fan_stop();
    L_val = digitalRead(L_pin); //Read the value of the left sensor
    M_val = digitalRead(M_pin); //Read the value of the middle sensor
    R_val = digitalRead(R_pin); //Read the value of the right sensor
    
    if (M_val == 1) { //the middle one detects black lines
      if (L_val == 1 && R_val == 0) { //If a black line is detected on the left, but not on the right, turn left
        Car_left();
      }
      else if (L_val == 0 && R_val == 1) { //If a black line is detected on the right, not on the left, turn right
        Car_right();
      }
      else { //otherwise, go front
        Car_front();
      }
    }
    else { //The middle one doesn't detect black lines
      if (L_val == 1 && R_val == 0) { //If a black line is detected on the left, but not on the right, turn left
        Car_left();
      }
      else if (L_val == 0 && R_val == 1) { //If a black line is detected on the right, not on the left, turn right
        Car_right();
      }
      else { //otherwise, stop
        Car_Stop();
      }
    }
  }

}


void fan_stop() {
  //stop rotating
  digitalWrite(INA, LOW);
  digitalWrite(INB, LOW);
}

void fan_begin() {
  //fan rotates
  digitalWrite(INA, LOW);
  digitalWrite(INB, HIGH);
}

void Car_front()
{
  digitalWrite(MR_Ctrl, HIGH);
  analogWrite(MR_PWM, 150);
  digitalWrite(ML_Ctrl, HIGH);
  analogWrite(ML_PWM, 150);
}
void Car_back()
{
  digitalWrite(MR_Ctrl, LOW);
  analogWrite(MR_PWM, 100);
  digitalWrite(ML_Ctrl, LOW);
  analogWrite(ML_PWM, 100);
}
void Car_left()
{
  digitalWrite(MR_Ctrl, HIGH);
  analogWrite(MR_PWM, 150);
  digitalWrite(ML_Ctrl, LOW);
  analogWrite(ML_PWM, 100);
}
void Car_right()
{
  digitalWrite(MR_Ctrl, LOW);
  analogWrite(MR_PWM, 100);
  digitalWrite(ML_Ctrl, HIGH);
  analogWrite(ML_PWM, 150);
}
void Car_Stop()
{
  digitalWrite(MR_Ctrl, LOW);
  analogWrite(MR_PWM, 100);
  digitalWrite(ML_Ctrl, LOW);
  analogWrite(ML_PWM, 100);
  
  digitalWrite(MR_Ctrl, LOW);
  analogWrite(MR_PWM, 0);
  digitalWrite(ML_Ctrl, LOW);
  analogWrite(ML_PWM, 0);
}
 //****************************************************************
