#include "relaybox.h"

RelayBox::RelayBox(RELAYBOX_CALLBACK_SIGNATURE) {
    this->callback = callback;
}

void RelayBox::switchRelay(int i, bool mode) {  //true = HIGH, false = LOW
    if(mode) {
        DEBUG_PRINTLN(String("Relay(")+String(i)+String(") ... ON"));
    } else {
        DEBUG_PRINTLN(String("Relay(")+String(i)+String(") ... OFF"));
    }
    digitalWrite(relay[i],mode?HIGH:LOW);
    this->callback(i, mode);
}

// Program relay to turn off in the future
void RelayBox::switchRelay(int i, int period) {
    unsigned long now = millis();
    
    switchRelay(i,true);
    
    relay_sleep[i] = now + period;
}

//Switch off after period
void RelayBox::loop() {
    unsigned long now = millis();

    //keep track of time of last loop
    if(now < relay_sleep[0]) {
        relay_sleep[0] = now;
    }

    for(int i=1; i<= MAX_RELAY; i++) {
        if (relay_sleep[i] != 0 && now >= relay_sleep[i]) {
            switchRelay(i,false);
            relay_sleep[i] = 0;
        }
    }
}
