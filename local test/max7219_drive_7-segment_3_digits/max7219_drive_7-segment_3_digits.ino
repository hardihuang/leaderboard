#include "LedControl.h" //  need the library
LedControl lc=LedControl(12,11,10,1); // lc is our object
int num1 = 0;
int num2 = 0;
int counts = 0;

void setup() {
  // put your setup code here, to run once:
  lc.shutdown(0,false);// turn off power saving, enables display
  lc.setIntensity(0,15);// sets brightness (0~15 possible values)
  lc.clearDisplay(0);// clear screen

  lc.setDigit(0,1,(byte)0,true);  //tenth
}

void loop() {
  // put your main code here, to run repeatedly:
  //lc.setDigit(0,2,(byte)2,false);
  //lc.setDigit(0,1,(byte)7,false);
  //lc.setDigit(0,0,(byte)1,false);
  
  
  lc.setDigit(0,0,(byte)num1,false); //ones
  num1 = num1+1;
  
  if(num1 == 10){
    num1 = 0;
    lc.setDigit(0,0,(byte)num1,false); //ones
    num2 = num2 + 1;
    lc.setDigit(0,1,(byte)num2,true);  //tenth
    if(num2 == 9){
      num2 = 0;  
    }
  }
  
  delay(300);
  
}
