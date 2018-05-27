#include "LedControl.h" //  need the library
LedControl lc=LedControl(12,11,10,3); // lc is our object
int num = 0;

void setup() {
  // put your setup code here, to run once:
  lc.shutdown(0,false);// turn off power saving, enables display
  lc.shutdown(1,false);
  lc.shutdown(2,false);
  lc.setIntensity(0,15);// sets brightness (0~15 possible values)
  lc.setIntensity(1,15);
  lc.setIntensity(2,15);
  lc.clearDisplay(0);// clear screen
  lc.clearDisplay(1);// clear screen
  lc.clearDisplay(2);// clear screen

  //first group
  lc.setDigit(0,0,(byte)1,false);
  lc.setDigit(0,1,(byte)8,1);
  lc.setDigit(0,2,(byte)8,false);
  lc.setDigit(0,3,(byte)2,false);
  lc.setDigit(0,4,(byte)8,1);
  lc.setDigit(0,5,(byte)8,false);
  lc.setDigit(0,6,(byte)8,1);
  lc.setDigit(0,7,(byte)8,false);

  //second group
  lc.setDigit(1,0,(byte)1,false); //#3 1
  lc.setDigit(1,1,(byte)8,false); //#4 1
  lc.setDigit(1,2,(byte)8,1);     //#4 2
  lc.setDigit(1,3,(byte)2,false); //#4 3
  lc.setDigit(1,4,(byte)8,false); //#5 1
  lc.setDigit(1,5,(byte)8,1);     //#5 2
  lc.setDigit(1,6,(byte)8,false); //#5 3
  lc.setDigit(1,7,(byte)8,false); //$6 1

  //third group
  lc.setDigit(2,0,(byte)1,1); //#6 2
  lc.setDigit(2,1,(byte)8,0); //#6 3
  lc.setDigit(2,2,(byte)8,0);     //#7 1
  lc.setDigit(2,3,(byte)2,1); //#7 2
  lc.setDigit(2,4,(byte)8,0); //#7 3
  lc.setDigit(2,5,(byte)8,0);     //#8 1
  lc.setDigit(2,6,(byte)8,1); //#8 2
  lc.setDigit(2,7,(byte)8,0); //$8 3

  delay(2000);
  lc.clearDisplay(0);// clear screen
  lc.clearDisplay(1);// clear screen
  lc.clearDisplay(2);// clear screen
}

void loop() {
  lc.setDigit(0,0,(byte)1,false); //#1 1
  //lc.setDigit(0,1,(byte)8,1);   
  //lc.setDigit(0,2,(byte)8,false);
  lc.setDigit(0,3,(byte)2,false); //#2 1
  //lc.setDigit(0,4,(byte)8,1);
  //lc.setDigit(0,5,(byte)8,false);
  lc.setDigit(1,0,(byte)3,false);//#3 1
  lc.setDigit(1,1,(byte)4,false);//#4 1
  lc.setDigit(1,4,(byte)5,false);//#5 1
  lc.setDigit(1,7,(byte)6,false); //$6 1

  lc.setDigit(2,2,(byte)7,0);     //#7 1
  lc.setDigit(2,5,(byte)8,0);     //#8 1
  
  printNumber(num);
  num = num +1;
 delay(500);
  
}

void printNumber(int v) {  
    int ones;  
    int tens;  
    bool hundreds; 

    boolean negative=false;

    if(v < -9 || v > 198)  
        num = 0;
        //return;  
        
    if(v<0) {  
        negative=true; 
        v=v*-1;  
    }
    ones=v%10;  
    v=v/10;  
    tens=v%10;  
    v=v/10; 
    hundreds=v;  
    if(negative) {  
        //print character '-' in the leftmost column  
        //lc.setChar(0,3,'-',false);  
        } 
    else {
        //print a blank in the sign column  
        //lc.setChar(0,3,' ',false);  
    }  
    //Now print the number digit by digit 
    //lc.setDigit(0,2,(byte)hundreds,false);
    
    lc.setDigit(0,1,(byte)tens,hundreds); 
    lc.setDigit(0,2,(byte)ones,false); 
    lc.setDigit(0,4,(byte)tens,hundreds); 
    lc.setDigit(0,5,(byte)ones,false); 
    lc.setDigit(0,6,(byte)tens,hundreds); 
    lc.setDigit(0,7,(byte)ones,false); 

    lc.setDigit(1,2,(byte)tens,hundreds);     //#4 2
    lc.setDigit(1,3,(byte)ones,false); //#4 3
    lc.setDigit(1,5,(byte)tens,hundreds);     //#5 2
    lc.setDigit(1,6,(byte)ones,false); //#5 3

    lc.setDigit(2,0,(byte)tens,hundreds);
    lc.setDigit(2,1,(byte)ones,0);
    lc.setDigit(2,3,(byte)tens,hundreds);
    lc.setDigit(2,4,(byte)ones,0);
    lc.setDigit(2,6,(byte)tens,hundreds);
    lc.setDigit(2,7,(byte)ones,0);
} 
