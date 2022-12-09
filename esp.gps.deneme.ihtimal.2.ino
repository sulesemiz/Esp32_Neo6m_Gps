/*some obs:
 *  * There are three serial ports on the ESP known as U0UXD, U1UXD and U2UXD.
 * 
 * U0UXD is used to communicate with the ESP32 for programming and during reset/boot.
 * U1UXD is unused and can be used for your projects. Some boards use this port for SPI Flash access though
 * U2UXD is unused and can be used for your projects.
 * on the code, i use the u2uxd. Dont forget to invert the rx/tx with the sensor ;)
 */

#include <HardwareSerial.h>
#include <TinyGPS++.h>

#define RXD2 16
#define TXD2 17

TinyGPSPlus gps;

void setup() {
 Serial.begin(115200);
 Serial1.begin(9600, SERIAL_8N1, RXD2, TXD2); //gps baud
}

void loop() {
 bool recebido = false;
  while (Serial1.available()) {
     char cIn = Serial1.read();
     recebido = gps.encode(cIn);
  }
   if (gps.location.isUpdated() && gps.altitude.isUpdated())
  {
    Serial.print("D/M/A: ");
Serial.print(gps.date.value());
Serial.print(" | alt: ");
Serial.print(gps.altitude.feet());
Serial.print(" | lat: ");
Serial.print(gps.location.lat(), 6);
Serial.print(" | lng: ");
Serial.print(gps.location.lng(), 6);
Serial.print(" | satellites: ");
Serial.println(gps.satellites.value());
delay(500);
  }
}