#include <Arduino.h>
#include "net\tfwifi.h"
#include "upnp\Ssdp.h"
#include "util\DateTime.h"
#include "util\emulator\WeMoEmulator.h"
#define TREE_PIN 2
#define GARL_PIN 12

DateTime *dateTime;
Ssdp *ssdp;

void setup() {
  setup_wifi();
  dateTime= getDateTime();
  ssdp = new Ssdp(WiFi.localIP());
	ssdp->setDateTime(dateTime);
	ssdp->setUdpSendCount(1);
  ssdp->addDevice(new WeMoEmulator("Christmas Tree", TREE_PIN, 8080U));
  ssdp->begin();

}

void loop() {
  ssdp->loop();
}
