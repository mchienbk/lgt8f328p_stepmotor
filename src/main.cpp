#include <Arduino.h>
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
RAW - |_______| - VCC     */


// 2 input for limmit switch (1)
// 2 input for limmit switch (2)
// 2 output for limmit motor (1)
// 2 output for limmit motor (2)
// 1 out pur for led

#define X_DIR    D3  // x -axis control
#define X_STP    D2  // x -axis direction 
#define X_HOME   D12 // x -axis control
#define X_LIMIT  D5  // x -axis direction 

#define Y_DIR    D6  // y -axis control
#define Y_STP    D7  // y -axis direction
#define Y_HOME   D11 // x -axis control
#define Y_LIMIT  D9  // x -axis direction 

void GPIO_Init(void);
void Led_ON(void);
void Led_OFF(void);
void Led_blink(int times, int period);
void Origin_search(void);
void X_return(void);
void Y_return(void);
void X_move(int step, int direct);
void Y_move(int step, int direct);
char incomingByte;

void setup() {
  GPIO_Init();
  Led_blink(20,100);
  Serial.begin(9600);
  Serial.println("Starting");
  Origin_search();
}

void loop() {
  Led_OFF();
  if (Serial.available() > 0)
  { 
    Led_ON();
    incomingByte = Serial.read();
    Serial.print("Received: ");
    Serial.println(incomingByte);

    // if (incomingByte == 0x01)
    // {
    //   Serial.println("Done");
    // }
    // else{
    //   Serial.println(incomingByte);
    // }

    switch(incomingByte){
      case '1':
        X_move(5,0);
        break;
      case '2':
        X_move(5,1);
        break;
      case '3':
        Y_move(5,0);
        break;
      case '4':
        Y_move(5,1);
        break;        
      default:
        break;
    }
  }
  delay(10);
}


void GPIO_Init(void){
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);
  pinMode(D13,OUTPUT);
  pinMode(D5, INPUT); 
  pinMode(D9, INPUT); 
  pinMode(D11,INPUT); 
  pinMode(D12,INPUT); 

}


void Led_ON(){
  digitalWrite(LED_BUILTIN,HIGH);
} 
void Led_OFF(){
  digitalWrite(LED_BUILTIN,LOW);
}

void Led_blink(int times, int period){
  int i = 0;
  for (i=0; i < times; i++){
    Led_ON();
    delay(period);
    Led_OFF();
    delay(period);
  }
}

void X_return(void)
{
  digitalWrite(X_STP,HIGH); delay(200);
  digitalWrite(X_DIR,LOW);  delay(100);

  while (digitalRead(X_HOME)==LOW){
    digitalWrite(X_STP,LOW);
    delay(50);
    digitalWrite(X_STP,HIGH);
    delay(50);
  }
}

void Y_return(void){
  digitalWrite(Y_STP,HIGH); delay(200);
  digitalWrite(Y_DIR,LOW);  delay(100);

  while (digitalRead(Y_HOME)==LOW){
    digitalWrite(Y_STP,LOW);
    delay(50);
    digitalWrite(Y_STP,HIGH);
    delay(50);
  }
}

void X_move(int step, int direct)
{
  int i = 0;
  digitalWrite(X_STP,HIGH);   delay(200);
  digitalWrite(X_DIR,direct); delay(100);
  
  for (i=0; i < step; i++){
    digitalWrite(X_STP,LOW);
    delay(50);
    digitalWrite(X_STP,HIGH);
    delay(50);
    if(digitalRead(X_HOME)==LOW || digitalRead(X_LIMIT)==LOW){
      Serial.println("X limit switch was pressed");
    }
  }
  Serial.println("X moved");
}

void Y_move(int step, int direct)
{
  int i = 0;
  digitalWrite(Y_STP,HIGH);   delay(200);
  digitalWrite(Y_DIR,direct); delay(100);
  
  for (i=0; i < step; i++){
    digitalWrite(Y_STP,LOW);
    delay(50);
    digitalWrite(Y_STP,HIGH);
    delay(50);
    if(digitalRead(Y_HOME)==LOW || digitalRead(Y_LIMIT)==LOW){
      Serial.println("Y limit switch was pressed");
    }
  }
  Serial.println("Y moved");
}

void Origin_search(void)
{
  // X_return();  
  X_move(20,HIGH);
  // Y_return();  
  Y_move(20,HIGH);
}



