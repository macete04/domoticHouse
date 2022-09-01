#ifndef NET_H
#define NET_H

#include <WiFi.h>
#include <PubSubClient.h>

WiFiClient espClient;
PubSubClient client(espClient);

void wifi(const char *ssid, const char *password);
void callback(char* topic, byte* payload, unsigned int length);
void reconnect(const char *mqtt_id, const char *mqtt_us, const char *mqtt_pass);

#endif
