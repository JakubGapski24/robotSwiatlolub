#include <Arduino.h>

class Robot {
  private:
          int L_direction;
          int L_speed;
          int R_speed;
          int R_direction;

  public:
          Robot() {
            L_direction = 4;
            L_speed = 5;
            R_speed = 6;
            R_direction = 9;
          }


          int getL_direction() {
            return L_direction;
          }
          int getL_speed() {
            return L_speed;
          }
          int getR_speed() {
            return R_speed;
          }
          int getR_direction() {
            return R_direction;
          }

          void leftMotor (int speed) {
            if (speed > 0) { //jedź do przodu

              speed = map(speed, 0, 100, 0, 165); //165 to maksymalna prędkość
              digitalWrite(L_direction, 0); //lewy silnik - obrót w prawo
              analogWrite(L_speed, speed); //prędkość lewego silnika PWM
            }
            else if (speed < 0) { //jedź do tyłu
              speed = abs(speed); //zamień na liczbę dodatnią
              speed = map(speed, 0, 100, 0, 165); //165 to maksymalna prędkość
              digitalWrite(L_direction, 1); //lewy silnik - obrót w lewo
              analogWrite(L_speed, speed); //prędkość lewego silnika w PWM
            }
            else {
              analogWrite(L_speed, 0);
            }
          }

          void rightMotor (int speed) {
            if (speed > 0) { //jedź do przodu
              speed = map(speed, 0, 100, 0, 165); //165 to maksymalna prędkość
              digitalWrite(R_direction, 0); //prawy silnik - obrót w prawo
              analogWrite(R_speed, speed); //prędkość prawego silnika PWM
            }
            else if (speed < 0) { //jedź do tyłu
              speed = abs(speed); //zamień na liczbę dodatnią
              speed = map(speed, 0, 100, 0, 165); //165 to maksymalna prędkość
              digitalWrite(R_direction, 1); //lewy silnik - obrót w lewo
              analogWrite(R_speed, speed); //prędkość lewego silnika w procentach
            }
            else {
              analogWrite(R_speed, 0);
            }
          }

          void stopRobot() {
            analogWrite(L_speed, 0);
            analogWrite(R_speed, 0);
          }
};

class LightFollower : public Robot {
  private:
          int L_light;
          int R_light;
          int LIGHT_MIN;
          int LIGHT_MAX;

  public:
          LightFollower() {
            L_light = 15;
            R_light = 14;
            LIGHT_MIN = -300;
            LIGHT_MAX = 300;
          }

          int following() {
            int roznica = analogRead(L_light) - analogRead(R_light);
            if (roznica < LIGHT_MIN) {
              roznica = LIGHT_MIN;
            }
            else if (roznica > LIGHT_MAX) {
              roznica = LIGHT_MAX;
            }
            return map(roznica, LIGHT_MIN, LIGHT_MAX, -50, 50);
          }
};

LightFollower robot;

void setup() {
  pinMode(robot.getL_direction(), OUTPUT);
  pinMode(robot.getL_speed(), OUTPUT);
  pinMode(robot.getR_speed(), OUTPUT);
  pinMode(robot.getR_direction(), OUTPUT);
}

void loop() {
  int roznica = robot.following();  
  robot.leftMotor(40 + roznica);
  robot.rightMotor(40 - roznica);
}