#include <due_can.h>
#include "variant.h"
#include "vesc.h"
#include "config.h"
#include "Arduino.h"

extern vesc_t* vesc;
int vescCount = 0;

void printFrame(CAN_FRAME *frame) {
   Serial.print("ID: 0x");
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

int getArrayLoc(CAN_FRAME *frame){
  for(int i = 0; i<NUM_VESC; i++){
    if(vesc[i].getEid() == (frame->id&0x000000FF)){
      return i;
    }
  }
  if(DEBUG){Serial.println("We ran into an error and could find vesc based of EID");}
  return 0;
}


void gotFrame(CAN_FRAME *frame) 
{
  vesc[getArrayLoc(frame)].setData(frame);
  printFrame(frame);
}

void gotUnknown(CAN_FRAME *frame) 
{
  printFrame(frame);
}

void gotPong(CAN_FRAME *frame){
  
  vesc[vescCount++] = vesc_t(frame->data.s0);
  if(DEBUG){
    Serial.print("Found Vesc of ID: ");
    Serial.println(vesc[vescCount-1].getEid());
    Serial.println("Found in frame:");
    printFrame(frame);
  }
  if(vescCount>=NUM_VESC){vescCount=0;}
}

void scanBus()
{
  CAN_FRAME outgoing;
  outgoing.extended = true;
  outgoing.priority = 1; //0-15 lower is higher priority
  outgoing.length = 1;
  uint32_t cmd = CAN_PACKET_PING<<8;
  for(int i = 0; i< 0xFF; i++){
    outgoing.id = cmd+i;
    Can0.sendFrame(outgoing);
  }
}

void watchForRangeSpecific(uint8_t mailbox, uint32_t id1, uint32_t id2, bool extended)
{
  uint32_t id = 0;
  uint32_t mask = 0;
  uint32_t temp;

  if (id1 > id2) 
  { 
    id1 = id1 ^ id2;
    id2 = id1 ^ id2; 
    id1 = id1 ^ id2;
  }

  id = id1;

  if (id2 <= 0x7FF) mask = 0x7FF;
  else mask = 0x1FFFFFFF;

  for (uint32_t c = id1; c <= id2; c++)
  {
    id &= c;
    temp = (~(id1 ^ c)) & 0x1FFFFFFF;
    mask &= temp;
  }
  Can0.setRXFilter(mailbox, id, mask, extended);
}

bool can_init(){
  bool good = true;
  good = Can0.begin(CAN_BPS_500K);
  if(!good){ //hit an oops, check your wiring
    return good;
  }
  
  int filter;
  //extended for monitoring vesc's status *needs can status 1_2_3_4_5*
  uint16_t temp = CAN_PACKET_STATUS<<8;
  watchForRangeSpecific(0, temp, temp+0xFF, true);
  temp = CAN_PACKET_STATUS_2<<8;
  watchForRangeSpecific(1, temp, temp+0xFF, true);
  temp = CAN_PACKET_STATUS_3<<8;
  watchForRangeSpecific(2, temp, temp+0xFF, true);
  temp = CAN_PACKET_STATUS_4<<8;
  watchForRangeSpecific(3, temp, temp+0xFF, true);
  temp = CAN_PACKET_STATUS_5<<8;
  watchForRangeSpecific(4, temp, temp+0xFF, true);
  temp = CAN_PACKET_PONG<<8;
  watchForRangeSpecific(5, temp, temp+0xFF, true);  //pong mailbox
  Can0.setRXFilter(6, 0, 0, true); //catch all extended mailbox
  
  Can0.attachCANInterrupt(5, gotPong);
  Can0.attachCANInterrupt(6, gotUnknown);
  Can0.attachCANInterrupt(gotFrame);

  scanBus();
    
  return good; 
}
