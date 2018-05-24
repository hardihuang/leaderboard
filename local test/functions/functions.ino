#include <EEPROM.h>

#include "LedControl.h"
LedControl lc=LedControl(12,11,10,3);

#include "IRremote.h"
int receiver = 9;
IRrecv irrecv(receiver);
decode_results results;

int state = 0; //0=display; 1=edit Group; 2=reset
int selectedGroup = 0;  //which group we are dealing with
int groupIndex = 10; //10 is a flag for nothing; 9 is group does not exist
int endIndex = 8; //which index should we put the new group
unsigned long blinkTimer = millis();
int blinkFlag = 0;
int scores[2][8]{};//score array saves the group number and the score, and the order
int key = 0;  //what key is pressed

void setup() {
  //inserting the dummy data to the eeprom
  int dummyData[2][8]{
     {0,0,0,0,0,0,0,0},
     {1,2,3,4,5,6,7,0}  
   };
  writeData(dummyData);

//initialize the program
  //IR receiver
  irrecv.enableIRIn();
   
  //display
  for(int index=0; index<lc.getDeviceCount();index++){
    lc.shutdown(index, false);  //wake up all the MAX7219 ICs
    lc.setIntensity(index, 15); //set the Intensity to the max value 0-15
  }
  clearDigits();
  
  //data
  fetchData();  //fetch the data from the eeprom
  sort(scores,8); //sort the data array
  drawScreen();
}

void loop() {

  if(state == 1){
    blinkGroup();
  }
  
  getKeys();
  if(key){
    if(key>48 and key<57 and state == 0){ //pressed 1-8 group number and in display mode
      state = 1;//edit group mode
      selectedGroup = key-48;//set the group number
    }
    if(state == 1){
      
      if(key == 97){//pressed up button
        //add one point to the selected group 
        addScore();
      }else if(key == 101){//pressed down button
        //minus one point to the selected group  
        minusScore();
      }else if(key == 42){//pressed * button
        //delete this selected group  
        deleteGroup();
        state = 0;
      }else if(key == 35){//pressed # button
        //add this selected group
        addGroup();
      }else if(key == 99){//pressed ok to exit the editing mode
        state = 0;
        selectedGroup = 0;
      }
    }
    
    key = 0;
    sort(scores,8);
    writeData(scores);
    drawScreen();
   
  }
}

void fetchData(){
  for(int i=0;i<8;i++){
    scores[0][i]= EEPROM.read(i);
    scores[1][i]= EEPROM.read(i+8);
  }  
}

void writeData(int data[2][8]){
  for(int i=0;i<8;i++){
    if(data[1][i] == 0){  //is the group is deactivited?
      data[0][i] = 0;     //clear the score data as well
    }
    EEPROM.write(i, data[0][i]);
    EEPROM.write(i+8, data[1][i]);
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

void drawScreen(){
  //clearDigits();
  for(int index=0; index<8; index++){  
    Display(index+1, scores[1][index], scores[0][index]);
  }
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

  //map each digit address to the value for each row
  //array order: addr1;digit1;addr2;digit2;addr3;digit3
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

  //group == 0 means this group is deactivited, so set send 0XFF to turn off this row
  if(group == 0){
    value1 = ' ';  
    value3 = ' ';
    value2 = ' ';
    dp2 = 0;
  }
  if(score == ' '){  
    value3 = ' ';
    value2 = ' ';
    dp2 = 0;
  }

  lc.setChar(addr1, digit1, value1, 0);  //group digit
  lc.setChar(addr2, digit2, value2, dp2);  //score tens and hundreds digit
  lc.setChar(addr3, digit3, value3, 0);  //score ones digit

}

void getKeys(){
  if(irrecv.decode(&results)){ // have we received an IR signal?

    switch(results.value){
      case 0xFF629D: key = 'a'; break;//add
      case 0xFF22DD: key = 'b'; break;//left
      case 0xFF02FD: key = 'c'; break;//ok
      case 0xFFC23D: key = 'd'; break;//right
      case 0xFFA857: key = 'e'; break;//minus
      case 0xFF6897: key = '1'; break;
      case 0xFF9867: key = '2'; break;
      case 0xFFB04F: key = '3'; break;
      case 0xFF30CF: key = '4'; break;
      case 0xFF18E7: key = '5'; break;
      case 0xFF7A85: key = '6'; break;
      case 0xFF10EF: key = '7'; break;
      case 0xFF38C7: key = '8'; break;
      case 0xFF5AA5: key = '9'; break;
      case 0xFF42BD: key = '*'; break;
      case 0xFF4AB5: key = '0'; break;
      case 0xFF52AD: key = '#'; break;
      default: 
        key = 0;//other button we don't care
    }
    
    irrecv.resume(); // receive the next value
  } 
}

void clearDigits(){
  for(int index=0; index<lc.getDeviceCount();index++){
    lc.clearDisplay(index);
  }
}

void addScore(){
  //find the selectedGroup index in the scores array  
  searchGroup();
  //add one to that group score
  scores[0][groupIndex]++;
  groupIndex = 10;
}

void minusScore(){
  searchGroup();
  //add one to that group score
  scores[0][groupIndex]--;
  groupIndex = 10;
}

void addGroup(){
  //if the group does not exist now
  searchGroup();
  if(groupIndex == 9){//group does not exist
    scores[1][endIndex] = selectedGroup;//add the group to the end of the array
    scores[0][endIndex] = 0;
  }
}

void deleteGroup(){
  searchGroup();
  if(groupIndex < 9){//is the group exist?
    //delete this group and move everything forward
    for(int i=groupIndex;i<7;i++){
      scores[1][i]=scores[1][i+1];
      scores[0][i]=scores[0][i+1];
    }
    
    selectedGroup = 0;
    groupIndex = 10;
  }

}

void searchGroup(){
  for(int i=0; i<8; i++){
    if(scores[1][i]==selectedGroup){
      groupIndex = i;  
    }
    if(scores[1][i]==0 and endIndex > 7){
      endIndex = i;
    }
    if(i==7 and groupIndex == 10){
      groupIndex = 9;//group does not exist , exit the for loop
    }
  }
}

void blinkGroup(){
  searchGroup();
  if(millis() - blinkTimer > 300){
     if(blinkFlag == 1){
        Display(groupIndex+1, selectedGroup, scores[0][groupIndex]);
        blinkFlag = 0;
     }else if(blinkFlag == 0){
        Display(groupIndex+1, ' ' , ' ');
        blinkFlag = 1;
     }  
     blinkTimer = millis();
     
  } 
  
}
