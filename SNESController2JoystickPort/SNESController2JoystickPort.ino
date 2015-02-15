#include <digitalWriteFast.h> // https://code.google.com/p/digitalwritefast/

// Cable colors from the SNES Controller Extension Cable
// green = 5V
// yellow = latch
// blue = clock
// red =  serial
// black = ground

int latch = 2; 
int clock = 3;
int datin = 4;

int controller_data = 0;

int up = 9;
int down = 10;
int left = 11;
int right = 12;
int fire = 13;

int lastState;

void setup() 
{
  //SNES Controller
  pinMode(latch,OUTPUT);
  pinMode(clock,OUTPUT);
  pinMode(datin,INPUT);

  digitalWriteFast(latch,HIGH);
  digitalWriteFast(clock,HIGH);

  // C64/Amiga/Atari Port
  pinMode(up, INPUT);
  pinMode(down, INPUT);
  pinMode(left, INPUT);
  pinMode(right, INPUT);
  pinMode(fire, INPUT);
  
  digitalWrite(up,LOW);
  digitalWrite(down,LOW);
  digitalWrite(left,LOW);
  digitalWrite(right,LOW);
  digitalWrite(fire,LOW);
}

void setPin(int pin, boolean mode)
{
   if(mode)
       pinMode(pin, OUTPUT);
   else
       pinMode(pin, INPUT);
}

void controllerRead() 
{
  digitalWriteFast(latch,LOW);
  digitalWriteFast(clock,HIGH);
  
  digitalWriteFast(latch,HIGH);
  delayMicroseconds(12);

  digitalWriteFast(latch,LOW);
  delayMicroseconds(6);

  controller_data = 0;
  
  for (int i = 0; i < 16; i ++) 
  {
    delayMicroseconds(2);
    controller_data |= (1-digitalReadFast(datin)) << i;
    delayMicroseconds(4);
    digitalWriteFast(clock,LOW);
    delayMicroseconds(6);
    digitalWriteFast(clock,HIGH);
  }
}

void loop() 
{ 
  controllerRead();

  for(int i=0 ; i < 16; i++)
  {
      if((controller_data & 1 << i) != (lastState & 1 << i)) 
      {

        switch (i)
        {
          case 0: // B
            setPin(fire, (controller_data & 1 << i) ? true : false);
            break;
          case 1: // Y
            setPin(up, (controller_data & 1 << i) ? true : false);
            break;
          case 2: // Select
            break;
          case 3: // Start
            break;
           case 4: // Up
            setPin(up, (controller_data & 1 << i) ? true : false);
            break;
           case 5: // Down
            setPin(down, (controller_data & 1 << i) ? true : false);
            break;
           case 6: // Left
            setPin(left, (controller_data & 1 << i) ? true : false);
            break;
           case 7: // Right
            setPin(right, (controller_data & 1 << i) ? true : false);
            break;
           case 8: // A
            setPin(fire, (controller_data & 1 << i) ? true : false);                                                                                                                                                                                                                                                     
            break;
           case 9: // X
            setPin(up, (controller_data & 1 << i) ? true : false);
            break;
           case 10: // Left Trigger 
            break;    
           case 11: // Right Trigger
            break;       
        }
     }
  }
  lastState = controller_data;
}
  
  

