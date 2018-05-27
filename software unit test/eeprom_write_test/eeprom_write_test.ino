#include <EEPROM.h>
int addr = 0;
int scores[2][8]{
  {128,15,42,63,45,0,0,0},
  {1,2,3,4,5,0,0,0}  
};

void setup() {
  Serial.begin(9600);
  for(int i=0;i<8;i++){
    EEPROM.write(i, scores[0][i]);
    EEPROM.write(i+8, scores[1][i]);
  }
  for(int i=0;i<16;i++){
    Serial.println(EEPROM.read(i));
  }
  
}

void loop() {



}
