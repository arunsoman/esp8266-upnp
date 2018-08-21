#include <Arduino.h>
#include "tfwifi.h"

const char* ssid     = "<<YOUR SID>>";
const char* password = "<<YOUR PASSWORD>>";

bool setup_wifi() {
    Serial.printf("Connecting to %s",ssid);
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    IPAddress ip = WiFi.localIP();
    Serial.printf("WiFi connected IP address: %u.%u.%u.%u", ip[0], ip[1], ip[2], ip[3]);
    return true;
}

DateTime* getDateTime(){
  DateTime* dateTime = new DateTime();
	dateTime->setUpdateCallback([]()
	{
		HttpRequest request(WiFi.gatewayIP(), 80, "/");
		HttpResponse response;
		HttpClient().openUrl(&request, &response);

		String result;
		if (response.hasHeader("Date"))
		{
			HttpHeader* dateHeader = response.getHeader("Date");
			result = dateHeader->Value;
			Serial.printf("Date: %s\n", result.c_str());
		}
		return result;
	});

	dateTime->update();
	dateTime->begin();
  return dateTime;
}
