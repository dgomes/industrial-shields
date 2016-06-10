#include <relaybox.h>

void callback(uint8_t relay_number, bool value) {
  Serial.print(relay_number); Serial.print(" - "); Serial.println(value?"ON":"OFF");
}

RelayBox mduino(callback);

void setup() {
  Serial.begin(9600);
}

void loop() {
  mduino.loop();
  String relay_name;
  if (Serial.available() > 0) {
    relay_name = Serial.readString();
    int relay_number = atoi(relay_name.c_str());

    mduino.switchRelay(relay_number, 5000);
  }

}
