/**
 * @file  motor_control.cpp
 * @date  14.03.2022
 * @author Daze
 */
#include <header.h>

void Return_Home_X(void)
{
  digitalWrite(X_STEP,HIGH);
  delay(200);
  digitalWrite(X_DIRECT,LOW);
  delay(100);

  while (digitalRead(X_HOME) == LOW)
  {
    digitalWrite(X_STEP,LOW);
    delay(50);
    digitalWrite(X_STEP,HIGH);
    delay(50);
  }
}

void Return_Home_Y(void)
{
  digitalWrite(Y_STEP,HIGH);
  delay(200);
  digitalWrite(Y_DIRECT,LOW);
  delay(100);

  while (digitalRead(Y_HOME) == LOW)
  {
    digitalWrite(Y_STEP,LOW);
    delay(50);
    digitalWrite(Y_STEP,HIGH);
    delay(50);
  }
}

void Drive_X(int step, int direct)
{
  int i = 0;
  digitalWrite(X_STEP,HIGH);
  delay(200);
  digitalWrite(X_DIRECT,direct);
  delay(100);
  
  for (i=0; i < step; i++)
  {
    digitalWrite(X_STEP,LOW);
    delay(50);
    digitalWrite(X_STEP,HIGH);
    delay(50);
    if(digitalRead(X_HOME) == LOW || digitalRead(X_LIMIT) == LOW){
      Serial.println("X limit switch was pressed");
    }
  }
  Serial.println("X moved");
}

void Drive_Y(int step, int direct)
{
  int i = 0;
  digitalWrite(Y_STEP,HIGH);
  delay(200);
  digitalWrite(Y_DIRECT,direct);
  delay(100);
  
  for (i=0; i < step; i++)
  {
    digitalWrite(Y_STEP,LOW);
    delay(50);
    digitalWrite(Y_STEP,HIGH);
    delay(50);
    if(digitalRead(Y_HOME) == LOW || digitalRead(Y_LIMIT) == LOW){
      Serial.println("Y limit switch was pressed");
    }
  }
  Serial.println("Y moved");
}

void Origin_search(void)
{
  // Return_Home_X();  
  Drive_X(20,HIGH);
  // Return_Home_Y();  
  Drive_Y(20,HIGH);
}
