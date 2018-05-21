#include "LedControl.h"
#include <EEPROM.h>

LedControl lc=LedControl(12,11,10,3);
int scores[2][8]{
  //{12,15,42,63,45,0,0,0},
  //{2,4,1,3,5,0,0,0}  
};

void setup() {
  Serial.begin(9600);
  for(int index=0; index<lc.getDeviceCount();index++){
    lc.shutdown(index, false);
    lc.setIntensity(index, 15);
  }
  clearDigits();
  delay(100);
  fetchData();
  sort(scores,8);
}

void loop() {
  //clearDigits();
	
	for(int index=0; index<8; index++){
    Display(index+1, scores[1][index], scores[0][index]);
  }
  
  delay(1000);
}


int Display(int row, int group, int score){
  int addr1;
  int addr2;
  int addr3;
  int digit1;
  int digit2;
  int digit3;
  int value1;
  int value2;
  int value3;
  boolean dp2;
  
  if(group == 0){
    group = 0XFF;  
    score = 0XFF;
  }
  
	switch(row){

		case 1:	
			addr1 = 0;	
			digit1 = 0;	
			addr2 = 0;
			digit2 = 1;
			addr3 = 0;
			digit3 = 2;
			break;
			
		case 2:
			addr1 = 0;
			digit1 = 3;
			addr2 = 0;
			digit2 = 4;
			addr3 = 0;
			digit3 = 5;
			break;
     
		case 3:
			addr1 = 1;
			digit1 = 0;
			addr2 = 0;
			digit2 = 6;
			addr3 = 0;
			digit3 = 7;
			break;
      
		case 4:
			addr1 = 1;
			digit1 = 1;
			addr2 = 1;
			digit2 = 2;
			addr3 = 1;
			digit3 = 3;
			break;
      
		case 5:
			addr1 = 1;
			digit1 = 4;
			addr2 = 1;
			digit2 = 5;
			addr3 = 1;
			digit3 = 6;
			break;
      
		case 6:
			addr1 = 1;
			digit1 = 7;
			addr2 = 2;
			digit2 = 0;
			addr3 = 2;
			digit3 = 1;
			break;
      
		case 7:
			addr1 = 2;
			digit1 = 2;
			addr2 = 2;
			digit2 = 3;
			addr3 = 2;
			digit3 = 4;
			break;
      
		case 8:
			addr1 = 2;
			digit1 = 5;
			addr2 = 2;
			digit2 = 6;
			addr3 = 2;
			digit3 = 7;
			break;
		
	}
	
	value1 = group;	
	value3 = GetNumber(score,0);
	value2 = GetNumber(score,1);
	dp2 = GetNumber(score,2);
	
	lc.setDigit(addr1, digit1, (byte)value1, 0);	//group digit
	lc.setDigit(addr2, digit2, (byte)value2, dp2);	//score tens and hundreds digit
	lc.setDigit(addr3, digit3, (byte)value3, 0);	//score ones digit
  /*
  Serial.print("Group: ");s
  Serial.print(value1);
  Serial.print(" Score: ");
  Serial.print(score);
  Serial.println();*/
}

//places: 0=ones 1=tens 2=hundreds
int GetNumber(int v, int places){
	int ones;  
  int tens;  
  boolean hundreds; 

  if(v <= 0 || v > 198){
		return v;  
	}
    ones=v%10;  
    v=v/10;  
    tens=v%10;  
    v=v/10; 
    hundreds=v;  
	
	if(places == 0){
	    return ones;
	}else if(places == 1){
	    return tens;
	}else if(places == 2){
	    return hundreds;
	}else{
	    return;  
	}
}

void clearDigits(){
  for(int index=0; index<lc.getDeviceCount();index++){
    lc.clearDisplay(index);
  }
}

void sort(int a[2][8], int size) {
    for(int i=0; i<(size-1); i++) {
        for(int o=0; o<(size-(i+1)); o++) {
                if(a[0][o] < a[0][o+1]) {
                    int t = a[0][o];
                    int u = a[1][o];
                    a[0][o] = a[0][o+1];
                    a[1][o] = a[1][o+1];
                    a[0][o+1] = t;
                    a[1][o+1] = u;
                }
        }
    }
}

void fetchData(){
  for(int i=0;i<8;i++){
    scores[0][i]= EEPROM.read(i);
    scores[1][i]= EEPROM.read(i+8);
  }  
}


