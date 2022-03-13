/**
 * @file  main.cpp
 * @date  14.03.2022
 * @author Daze
 */
#include <header.h>
char receiveByte;
char receiveBuffer[4];
int8_t receiveCnt;

void setup()
{
  GPIO_Init();
  Led_blink(20, 100);
  Serial.begin(9600);
  Serial.println("Starting");
  Origin_search();
}

void loop()
{
  Calculate_Timer();
  Serial_Handle();
  Motor_Operate();
}

void GPIO_Init(void)
{
  pinMode(X_DIRECT, OUTPUT);
  pinMode(Y_DIRECT, OUTPUT);
  pinMode(X_STEP, OUTPUT);
  pinMode(Y_STEP, OUTPUT);

  pinMode(X_HOME, INPUT);
  pinMode(Y_HOME, INPUT);
  pinMode(X_LIMIT, INPUT);
  pinMode(Y_LIMIT, INPUT);

  pinMode(LED_BUILTIN, OUTPUT);
}

void Serial_Handle(void)
{
  if (Serial.available() > 0)
  {
    Turn_On_LED();
    receiveByte = Serial.read();
    receiveBuffer[receiveCnt] = receiveByte;
    receiveCnt++;
    if(receiveCnt > 3)
    {
      receiveCnt = 0;
    }

    Serial.print("Received: ");
    Serial.println(receiveByte);
  }
}

void Calculate_Timer()
{
  static uint32_t start = micros();
  yield();
  if ((micros() - start) >= 1000)
  {

    // start += 1000;
  }
}

void Motor_Operate()
{
  char cmd = receiveBuffer[0];
  int16_t data = (receiveBuffer[1] << 8) | receiveBuffer[2];
  char checksum = receiveBuffer[3];

  if (Calculate_Checsum(&receiveBuffer[0], 3) != checksum)
  {
    return;
  }
  else
  {
    Serial.println(data);
  }

  switch (cmd)
  {
  case '1':
    Drive_X(5, 0);
    break;
  case '2':
    Drive_X(5, 1);
    break;
  case '3':
    Drive_Y(5, 0);
    break;
  case '4':
    Drive_Y(5, 1);
    break;
  default:
    break;
  }
}

char Calculate_Checsum(char *data, int8_t size)
{
  char checksum = 0;
  for (int8_t i = 0; i < size; i++)
  {
    checksum = checksum ^ *data;
    data++;
  }
  return checksum;
}
