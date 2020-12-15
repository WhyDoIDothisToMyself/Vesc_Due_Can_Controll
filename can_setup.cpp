#include <due_can.h>
#include "variant.h"
#include "vesc.h"

void printFrame(CAN_FRAME &frame) {
   Serial.print("ID: 0x");
   Serial.print(frame.id, HEX);
   Serial.print(" Len: ");
   Serial.print(frame.length);
   Serial.print(" Data: 0x");
   for (int count = 0; count < frame.length; count++) {
       Serial.print(frame.data.bytes[count], HEX);
       Serial.print(" ");
   }
   Serial.print("\r\n");
}

void printFrame(CAN_FRAME *frame, int filter) {
   Serial.print("Fltr: ");
   if (filter > -1) Serial.print(filter);
   else Serial.print("???");
   Serial.print(" ID: 0x");
   Serial.print(frame->id, HEX);
   Serial.print(" Len: ");
   Serial.print(frame->length);
   Serial.print(" Data: 0x");
   for (int count = 0; count < frame->length; count++) {
       Serial.print(frame->data.bytes[count], HEX);
       Serial.print(" ");
   }
   Serial.print("\r\n");
}

//TODO: real stuff with this, will pull vals into vesc structs for live updates, refresh rate in vesc tool.
void gotFrameMB0(CAN_FRAME *frame) 
{
  printFrame(frame, 0);
}

void gotFrameMB1(CAN_FRAME *frame) 
{
  printFrame(frame, 1);
}

void gotFrameMB2(CAN_FRAME *frame) 
{
  printFrame(frame, 2);
}

void gotFrameMB3(CAN_FRAME *frame) 
{
  printFrame(frame, 3);
}

void gotFrameMB6(CAN_FRAME *frame) 
{
  printFrame(frame, 6);
}

void gotFrame(CAN_FRAME *frame) 
{
  printFrame(frame, -1);
}

bool can_init(){
  bool good = true;
  good = Can0.begin(CAN_BPS_500K);
  if(!good){ //hit an oops, check your wiring
    return good;
  }
  
  int filter;
  //extended for monitoring vesc's status *needs can status 1_2_3_4_5*
  Can0.setRXFilter(0, 0x00000500, 0x000005FF, true);
  Can0.setRXFilter(1, 0x00000500, 0x000005FF, true);
  Can0.setRXFilter(2, 0x00000500, 0x000005FF, true);
  Can0.setRXFilter(3, 0x00000500, 0x000005FF, true);
  Can0.setRXFilter(4, 0, 0, true); //catch all extended mailbox
  Can0.setRXFilter(5, 0, 0, true); //catch all extended mailbox

  Can0.attachCANInterrupt(0, gotFrameMB0);
  Can0.attachCANInterrupt(1, gotFrameMB1);
  Can0.attachCANInterrupt(2, gotFrameMB2);
  Can0.attachCANInterrupt(3, gotFrameMB3);
  
  //standard on box 6, shouldn't get any, but still
  Can0.setRXFilter(6, 0, 0, false);
  Can0.attachCANInterrupt(6, gotFrameMB6);
  // extended catchall interupt
  Can0.attachCANInterrupt(gotFrame);
    
  return good; 
}
