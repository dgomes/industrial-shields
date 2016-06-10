#include "relaybox.h"

RelayBox::RelayBox() {
    this->callback = NULL;
}

void RelayBox::setup(RELAYBOX_CALLBACK_SIGNATURE) {
    this->callback = callback;
}

void RelayBox::switchRelay(int i, bool mode) {  //true = HIGH, false = LOW
    if(mode) {
        DEBUG_PRINTLN(String("Relay(")+String(i)+String(") ... ON"));
    } else {
        DEBUG_PRINTLN(String("Relay(")+String(i)+String(") ... OFF"));
    }
    digitalWrite(relay[i],mode?HIGH:LOW);
    if(this->callback)
        this->callback(i, mode);
}

// Turn relay ON and program relay to turn OFF in the future
void RelayBox::switchRelay(int i, int period) {
    switchRelay(i,true);
    
    relay_sleep[i] = period;
}

//Switch AFTER after period
void RelayBox::loop() {
    unsigned long now = millis();

    //keep track of time of last loop
    unsigned long elapsed_time = now - relay_sleep[0];
    
    for(int i=1; i< sizeof(relay)/sizeof(int); i++) {
        if(relay_sleep[i] != 0) {
            if((long) (relay_sleep[i] - elapsed_time) <= 0) {
                switchRelay(i,false);
                relay_sleep[i] = 0;
            } else {
                relay_sleep[i] -= elapsed_time;
            }
        }
    }

    relay_sleep[0] = now;
}
