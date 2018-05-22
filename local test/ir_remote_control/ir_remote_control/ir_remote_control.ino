#include "IRremote.h"

int receiver = 9; // Signal Pin of IR receiver to Arduino Digital Pin 11

/*-----( Declare objects )-----*/
IRrecv irrecv(receiver);     // create instance of 'irrecv'
decode_results results;      // create instance of 'decode_results'

void setup()   /*----( SETUP: RUNS ONCE )----*/
{
  Serial.begin(9600);
  Serial.println("IR Receiver Button Decode"); 
  irrecv.enableIRIn(); // Start the receiver

}/*--(end setup )---*/


void loop()   /*----( LOOP: RUNS CONSTANTLY )----*/
{
  if (irrecv.decode(&results)) // have we received an IR signal?

  {
     int command = translateIR();
    if(command == '1'){
        scores[0][0]++;
        for(int index=0; index<8; index++){
          Display(index+1, scores[1][index], scores[0][index]);
        }
    }
    irrecv.resume(); // receive the next value
  }  
}/* --(end main loop )-- */

/*-----( Function )-----*/

int translateIR(){ // takes action based on IR code received
  char btn=0;
  switch(results.value){
    case 0xFF629D: btn = "add"; break;
    case 0xFF22DD: btn = "left";    break;
    case 0xFF02FD: btn = "ok";    break;
    case 0xFFC23D: btn = "right";   break;
    case 0xFFA857: btn = "minus"; break;
    case 0xFF6897: btn = 1;    break;
    case 0xFF9867: btn = 2;    break;
    /*
    case 0xFFB04F: Serial.println(" 3");    break;
    case 0xFF30CF: Serial.println(" 4");    break;
    case 0xFF18E7: Serial.println(" 5");    break;
    case 0xFF7A85: Serial.println(" 6");    break;
    case 0xFF10EF: Serial.println(" 7");    break;
    case 0xFF38C7: Serial.println(" 8");    break;
    case 0xFF5AA5: Serial.println(" 9");    break;
    case 0xFF42BD: Serial.println(" *");    break;
    case 0xFF4AB5: Serial.println(" 0");    break;
    case 0xFF52AD: Serial.println(" #");    break;
    case 0xFFFFFFFF: Serial.println(" REPEAT");break;  
  */
    default: 
      btn = "other button";
  }
  return btn;
  delay(500); // Do not get immediate repeat
} 
