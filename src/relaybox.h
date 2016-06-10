#ifndef RelayBox_h
#define RelayBox_h

#include <Arduino.h>

#ifdef DEBUG
#define DEBUG_PRINT(x)     Serial.print (x)
#define DEBUG_PRINTLN(x)  Serial.println (x)
#else
#define DEBUG_PRINT(x)
#define DEBUG_PRINTLN(x) 
#endif

//Configuration Relay OUT (220Vac - 8A max)
#define MAX_RELAY 16

#define RELAYBOX_CALLBACK_SIGNATURE void (*callback)(uint8_t, bool)

class RelayBox {
    private:
        int relay[17] = {-1, 23,22,25,24,40,39,38,37,28,27,30,29,45,44,43,42};
        unsigned long relay_sleep[17] = {1, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; //index 0 hold last loop millis() 
        RELAYBOX_CALLBACK_SIGNATURE;

    public:
        RelayBox(RELAYBOX_CALLBACK_SIGNATURE); //TODO box model/version as a enum parameter

        void switchRelay(int i, bool mode); //true = HIGH, false = LOW
        void switchRelay(int i, int period); // Program relay to turn off in the future - milliseconds
        void loop(); //must be called in the loop()
};

#endif
