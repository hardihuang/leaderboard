int scores[2][8]{
  {12,15,42,63,45,76,21,93},
  {2,8,3,7,4,6,5,1}  
};
int sortValues[13] = { 2, 7, 4, 6, 5, 3, 8, 10, 9, 11, 14, 12, 13 }; 

void setup(){
  Serial.begin(9600);
}

void loop() {
    //Pass in the values and the size.

  Serial.println("Sorted Array: ");
  for(int i=0; i<8; i++) {
     Serial.print(scores[1][i]); 
     Serial.print(" score: ");
     Serial.println(scores[0][i]);
  }
  
  delay(100000); //Make sure we have enough time to see the output before starting the demo again.
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
