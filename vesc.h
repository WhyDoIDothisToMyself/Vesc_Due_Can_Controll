
#include <due_can.h>
#include "variant.h"

#define EID_MASK 0x000000FF 

// CAN commands
typedef enum {
  CAN_PACKET_SET_DUTY = 0,  
  CAN_PACKET_SET_CURRENT,               //1 
  CAN_PACKET_SET_CURRENT_BRAKE,         //2
  CAN_PACKET_SET_RPM,                   //3 
  CAN_PACKET_SET_POS,                   //4
  CAN_PACKET_FILL_RX_BUFFER,            //5   
  CAN_PACKET_FILL_RX_BUFFER_LONG,       //6
  CAN_PACKET_PROCESS_RX_BUFFER,         //7
  CAN_PACKET_PROCESS_SHORT_BUFFER,      //8
  CAN_PACKET_STATUS,                    //9
  CAN_PACKET_SET_CURRENT_REL,           //10
  CAN_PACKET_SET_CURRENT_BRAKE_REL,     //11
  CAN_PACKET_SET_CURRENT_HANDBRAKE,     //12
  CAN_PACKET_SET_CURRENT_HANDBRAKE_REL, //13
  CAN_PACKET_STATUS_2,                  //14
  CAN_PACKET_STATUS_3,                  //15
  CAN_PACKET_STATUS_4,                  //16
  CAN_PACKET_PING,                      //17
  CAN_PACKET_PONG,                      //18
  CAN_PACKET_DETECT_APPLY_ALL_FOC,      //19
  CAN_PACKET_DETECT_APPLY_ALL_FOC_RES,  //20
  CAN_PACKET_CONF_CURRENT_LIMITS,       //21
  CAN_PACKET_CONF_STORE_CURRENT_LIMITS, //22
  CAN_PACKET_CONF_CURRENT_LIMITS_IN,    //23
  CAN_PACKET_CONF_STORE_CURRENT_LIMITS_IN,//24
  CAN_PACKET_CONF_FOC_ERPMS,            //25
  CAN_PACKET_CONF_STORE_FOC_ERPMS,      //26
  CAN_PACKET_STATUS_5,                  //27
  CAN_PACKET_POLL_TS5700N8501_STATUS,   //28
  CAN_PACKET_CONF_BATTERY_CUT,          //29
  CAN_PACKET_CONF_STORE_BATTERY_CUT,    //30
  CAN_PACKET_SHUTDOWN                   //31
} CAN_PACKET_ID;

#ifndef VESC_T_H
#define VESC_T_H

class vesc_t
{
    uint32_t eid;
    
  public:
    float duty;
    float current;
    float currentBrake;
    float rpm;
    float pos;
    float fettemp;
    float tempmotor;
    float avg_motor_current;
    float avg_input_current;
    float voltage;
    float amp_hours_consumed;
    float amp_hours_charged;
    float watt_hours_consumed;
    float watt_hours_charged;
    float tachometer;
    float batcurrent;
    float PIDpos;
    uint8_t fault;

    vesc_t(uint32_t c_eid){
      this->eid = c_eid;
      }
    
    uint32_t getEid(){return eid;}
    void setData(CAN_FRAME *frame);
    void printVals();
    void setDuty(float duty);
    void setCurrent(float current);
    void setCurrentBrake(float currentBrake);
    void setrpm(float rpm);
    void setpos(float pos);
    void sendData(CAN_PACKET_ID cpid, uint64_t data, uint8_t priority, int dLength);
};
#endif

int16_t extract16(uint16_t data);
int32_t extract32(uint32_t data);
int64_t extract64(uint64_t data);
                     

   
