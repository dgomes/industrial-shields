/*
 * Author: Diogo Gomes <diogogomes@gmail.com>
 * 
 * This works with an M-DUINO PLC Arduino 38R http://www.industrialshields.com/m-duino-plc-arduino-34R-i-os-relay_analog-digital
 * and an EmonTX V3.4 (http://openenergymonitor.org/emon/modules/emonTxV3) connected through the Serial1 port
 * 
 * Relays are numbered:
 * 1 - R0.1       9  - R1.1
 * 2 - R0.2       10 - R1.2
 * 3 - R0.3       11 - R1.3
 * 4 - R0.4       12 - R1.4
 * 5 - R0.5       13 - R1.5
 * 6 - R0.6       14 - R1.6
 * 7 - R0.7       15 - R1.7
 * 8 - R0.8       16 - R1.8
 * 
 * Default configuration will listen for events on MQTT path /mduino/# where # is the number of the relay
 * Events can be a delay (in miliseconds) or the strings ON or OFF
 */
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

#define RELAYBOX_CALLBACK_SIGNATURE void (*callback)(uint8_t, bool)

class RelayBox {
    private:
        //Configuration Relay OUT (220Vac - 8A max)
        int relay[17] = {-1, 23,22,25,24,40,39,38,37,28,27,30,29,45,44,43,42}; //m-duino-plc-arduino-34R
        unsigned long relay_sleep[17] = {1, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; //index 0 hold last loop millis() 
        RELAYBOX_CALLBACK_SIGNATURE;

    public:
        RelayBox(); //TODO box model/version as a enum parameter
        void setup(RELAYBOX_CALLBACK_SIGNATURE); 

        void switchRelay(int i, bool mode); //true = HIGH, false = LOW
        void switchRelay(int i, int period); // Program relay to turn off in the future - milliseconds
        void loop(); //must be called in the loop()
};

#endif
