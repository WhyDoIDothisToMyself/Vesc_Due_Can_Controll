
#include <due_can.h>
#include "variant.h"
#include "vesc.h"
//Todo: write these commands
class vesc_t
{ 
  private:
    uint32_t eid;
    
  public:
    float duty;
    float current;
    float currentBrake;
    float rpm;
    float pos;
    float mostemp[6];
    float temppcb;
    float avg_motor_current;
    float avg_input_current;
    float voltage;
    float amp_hours_consumed;
    float amp_hours_charged;
    float watt_hours_consumed;
    float watt_hours_charged;
    float odometer;
    float odometer_abs;
    uint8_t fault;
    
    uint32_t getEid(){
      return eid;
    }

    void setDuty(vesc_t vesc, float duty){
      
    }
    void setCurrent(vesc_t vesc, float current){
      
    }
    void setCurrentBrake(vesc_t vesc, float currentBrake){
      
    }
    void setrpm(vesc_t vesc, float rpm){
      
    }
    void setpos(vesc_t vesc, float pos){
      
    }
    void getValues(vesc_t vesc, uint32_t eid){
      
    }
    void scanBus(){
      for(int i = 0; i< 0xFF; i++){
        //Todo ping pong to get eids by checking the whole bus
      }
    }
    
    void sendData(CAN_PACKET_ID cpid, uint8_t data, byte priority){
      
      CAN_FRAME outgoing;
      
      outgoing.id = eid + (cpid<<8);//Attaches command to eid
      
      outgoing.extended = true;
      
      outgoing.priority = priority; //0-15 lower is higher priority
      
      outgoing.length = 1;
      
      outgoing.data.byte[0] = data;
      
      Can0.sendFrame(outgoing);
      
    }
    
    void sendData(CAN_PACKET_ID cpid, uint16_t data, uint8_t priority){
      
      CAN_FRAME outgoing;
      
      outgoing.id = eid + (cpid<<8);//Attaches command to eid
      
      outgoing.extended = true;
      
      outgoing.priority = priority; //0-15 lower is higher priority
      
      outgoing.length = 2;
      //TODO: look into why data is read backwards
      outgoing.data.s0 = data;
      
      Can0.sendFrame(outgoing);
    }
    
    void sendData(CAN_PACKET_ID cpid, uint32_t data, uint8_t priority){
      
      CAN_FRAME outgoing;
      
      outgoing.id = eid + (cpid<<8);//Attaches command to eid
      
      outgoing.extended = true;
      
      outgoing.priority = priority; //0-15 lower is higher priority
      
      outgoing.length = 4;
      //TODO: look into why data is read backwards
      outgoing.data.low = data;
      
      Can0.sendFrame(outgoing);
    }
    
    void sendData(CAN_PACKET_ID cpid, uint64_t data, uint8_t priority){
      CAN_FRAME outgoing;
      
      outgoing.id = eid + (cpid<<8);//Attaches command to eid
      
      outgoing.extended = true;
      
      outgoing.priority = priority; //0-15 lower is higher priority
      
      outgoing.length = 8;
      //TODO: look into why data is read backwards
      outgoing.data.value = data;
      
      Can0.sendFrame(outgoing);
    }
};
