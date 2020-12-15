
#include <due_can.h>
#include "variant.h"

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
  CAN_PACKET_PONG,                      //17
  CAN_PACKET_DETECT_APPLY_ALL_FOC,      //18
  CAN_PACKET_DETECT_APPLY_ALL_FOC_RES,  //19
  CAN_PACKET_CONF_CURRENT_LIMITS,       //20
  CAN_PACKET_CONF_STORE_CURRENT_LIMITS, //21
  CAN_PACKET_CONF_CURRENT_LIMITS_IN,    //22
  CAN_PACKET_CONF_STORE_CURRENT_LIMITS_IN,//23
  CAN_PACKET_CONF_FOC_ERPMS,            //24
  CAN_PACKET_CONF_STORE_FOC_ERPMS,      //25
  CAN_PACKET_STATUS_5,                  //26
  CAN_PACKET_POLL_TS5700N8501_STATUS,   //27
  CAN_PACKET_CONF_BATTERY_CUT,          //28
  CAN_PACKET_CONF_STORE_BATTERY_CUT,    //29
  CAN_PACKET_SHUTDOWN                   //30
} CAN_PACKET_ID;                        
