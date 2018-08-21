#ifndef __TFWIFI_H
#define __TFWIFI_H

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include "..\util\DateTime.h"

bool setup_wifi();
DateTime* getDateTime();
#endif
