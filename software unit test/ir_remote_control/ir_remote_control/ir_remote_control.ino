#include "IRremote.h"

int receiver = 9; // Signal Pin of IR receiver to Arduino Digital Pin 11

/*-----( Declare objects )-----*/
IRrecv irrecv(receiver);     // create instance of 'irrecv'
decode_results results;      // create instance of 'decode_results'
int key = 0;  //what key is pressed

void setup()   /*----( SETUP: RUNS ONCE )----*/
{
  Serial.begin(9600);
  Serial.println("IR Receiver Button Decode"); 
  irrecv.enableIRIn(); // Start the receiver

}/*--(end setup )---*/


void loop()   /*----( LOOP: RUNS CONSTANTLY )----*/
{
  getKeys();
    if(key){
      Serial.println(key);
      key = 0;
    }

}/* --(end main loop )-- */

/*-----( Function )-----*/
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
        key = 0;//other button
    }
    
    irrecv.resume(); // receive the next value
  } 
}
