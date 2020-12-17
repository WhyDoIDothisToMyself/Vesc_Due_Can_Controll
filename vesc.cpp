#include "Arduino.h"
#include <due_can.h>
#include "variant.h"
#include "vesc.h"
#include "config.h"

//Todo: write these commands

void vesc_t::setData(CAN_FRAME *frame){
  
  uint8_t dataInfo = frame->id>>8;
  switch (dataInfo){
    case CAN_PACKET_STATUS:
      rpm = extract32(frame->data.low);
      current = extract16(frame->data.s2)*1e-1;
      duty = extract16(frame->data.s3)*1e-3;
      break;
    case CAN_PACKET_STATUS_2:
      amp_hours_consumed = extract32(frame->data.low);
      amp_hours_charged = extract32(frame->data.high)*1e-4;
      break;
    case CAN_PACKET_STATUS_3:
      watt_hours_consumed = extract32(frame->data.low)*1e-4;
      watt_hours_charged = extract32(frame->data.high)*1e-4;
      break;
    case CAN_PACKET_STATUS_4:
      fettemp = extract16(frame->data.s0)*1e-1;
      tempmotor = extract16(frame->data.s1)*1e-1;
      batcurrent = extract16(frame->data.s2)*1e-1;
      PIDpos = extract16(frame->data.s3)/50;
      break;
    case CAN_PACKET_STATUS_5:
      tachometer = extract32(frame->data.low);
      voltage = extract16(frame->data.s2)*1e-1;
      if(DEBUG){
        printVals();
      }
      break;
  }
}

void vesc_t::printVals(){
  Serial.println(eid);
  Serial.print("Duty: ");
  Serial.println(duty);
  Serial.print("RPM: ");
  Serial.println(rpm);
  Serial.print("Current: ");
  Serial.println(current);
  Serial.print("amp_hours_consumed: ");
  Serial.println(amp_hours_consumed);
  Serial.print("amp_hours_charged: ");
  Serial.println(amp_hours_charged);
  Serial.print("watt_hours_consumed: ");
  Serial.println(watt_hours_consumed);
  Serial.print("watt_hours_charged: ");
  Serial.println(watt_hours_charged);
  Serial.print("fettemp: ");
  Serial.println(fettemp);
  Serial.print("tempmotor: ");
  Serial.println(tempmotor);
  Serial.print("batcurrent: ");
  Serial.println(batcurrent);
  Serial.print("PIDpos: ");
  Serial.println(PIDpos);
  Serial.print("tachometer: ");
  Serial.println(tachometer);
  Serial.print("voltage: ");
  Serial.println(voltage); 
}
void vesc_t::setDuty(float duty){
  this->sendData(CAN_PACKET_SET_DUTY, (uint64_t)(duty*1000), 3, 4);
}
void vesc_t::setCurrent(float current){
  this->sendData(CAN_PACKET_SET_CURRENT,(current*1e1),3,4);
}
void vesc_t::setCurrentBrake(float currentBrake){
  this->sendData(CAN_PACKET_SET_CURRENT_BRAKE,(currentBrake*1e1),3,4);
}
void vesc_t::setrpm(float rpm){
  this->sendData(CAN_PACKET_SET_RPM,rpm,3,8);
}


void vesc_t::sendData(CAN_PACKET_ID cpid, uint64_t data, uint8_t priority, int dLength){
  CAN_FRAME outgoing;
  
  outgoing.id = eid | (cpid<<8);//Attaches command to eid
  
  outgoing.extended = true;
  
  outgoing.priority = priority; //0-15 lower is higher priority
  
  outgoing.length = dLength;
  
  outgoing.data.value = data<<((8-dLength)*4);
  
  Can0.sendFrame(outgoing);
}

int16_t extract16(uint16_t data){
  uint8_t t1 = data>>8;
  uint8_t t2 = data;
  return ((uint16_t)t2)<<8 | t1;
}

int32_t extract32(uint32_t data){
  uint16_t t1 = (data>>16);
  uint16_t t2 = data;
  return ((uint32_t)extract16(t2))<<16 | extract16(t1);
}

int64_t extract64(uint64_t data){
  uint32_t t1 = (data>>32);
  uint32_t t2 = data;
  return ((uint64_t)extract32(t2))<<32 | extract32(t1);
}
