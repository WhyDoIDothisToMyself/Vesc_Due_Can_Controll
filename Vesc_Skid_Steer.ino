
#include <due_can.h>
#include "variant.h"
#include "vesc.h"
#include "config.h"
#include "can_setup.h"
#include "Vesc_Skid_Steer.h"

vesc_t* vesc = (vesc_t*)malloc(sizeof(vesc_t) * NUM_VESC);

String cmd;

void setup() {
  if(DEBUG){
    Serial.begin(115200);
    Serial.println("Begin init");
    }
  if(!can_init())
  { 
    if(DEBUG){ 
      Serial.println("Can initialization failed");
      return;
    }
  }
  if(DEBUG){
    Serial.println("Finish Init");
  }
  Serial.println("Input Current");
}

void loop() {
  if(Serial.available()){
        cmd = Serial.read();
        Serial.print("You typed: " );
        Serial.println(cmd);
    }
  vesc[0].setCurrent(cmd.toInt());
  cmd = 0;
}
