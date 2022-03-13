/**
 * @file  header.h
 * @date  14.03.2022
 * @author Daze
 */
/* Pin layout
        _________
  RST - |       | - SCL
  D2  - |       | - SDA
  D3~ - |       | -  A1
  VCC - |       | -  A0
  GND - |       | - D13 (LED)
  D5~ - |       | - D12
  D6~ - |       | - D11
  D7  - |       | - ~D9
  GND - |       | - GND
  RAW - |_______| - VCC

  - 2 input for limmit switch motor_1
  - 2 input for limmit switch motor_2
  - 2 output for motor_1
  - 2 output for motor_2
  - 1 out pur for led
 */
#include <Arduino.h>

#ifndef HEADER_FILE
#define HEADER_FILE

#define X_DIRECT D3    // x -axis control
#define X_STEP D2      // x -axis direction
#define X_HOME D12     // x -axis control
#define X_LIMIT D5     // x -axis direction
#define Y_DIRECT D6    // y -axis control
#define Y_STEP D7      // y -axis direction
#define Y_HOME D11     // x -axis control
#define Y_LIMIT D9     // x -axis direction

void GPIO_Init(void);
void Serial_Handle(void);

void Turn_On_LED(void);
void Turn_Off_LED(void);
void Led_blink(int times, int period);

void Motor_Operate(void);
void Origin_search(void);
void Return_Home_X(void);
void Return_Home_Y(void);
void Drive_X(int step, int direct);
void Drive_Y(int step, int direct);

void Calculate_Timer(void);
char Calculate_Checsum(char *data, int8_t size);

extern bool motor_X_sleep;
extern bool motor_Y_sleep;
extern bool motor_X_wakeup;
extern bool motor_Y_wakeup;
extern int motor_X_ontime;
extern int motor_Y_ontime;
extern int motor_X_hold;
extern int motor_Y_hold;

extern char receiveByte;
extern char receiveBuffer[4];

#endif
