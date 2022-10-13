#ifndef TRANSMITWIFI_H
#define TRANSMITWIFI_H

#include "defs.h"
#include "functions.h"

void mqttCallback(char *topic, byte *message, unsigned int length);

void setup_wifi();

void reconnect();

<<<<<<< HEAD:N3-AvionicsFlightSoftware/include/transmitwifi.h
void sendTelemetryWiFi(Data sv);

void handleWiFi(Data sv);
=======
  // If a message is received on the topic esp32/output, you check if the message is either "on" or "off".
  // Changes the output state according to the message
  if (String(topic) == "esp32/ejection")
  {
    debug("Changing output to ");
    if (messageTemp == "on")
    {
      debugln("on");
      digitalWrite(EJECTION_PIN, HIGH);
    }
    else if (messageTemp == "off")
    {
      debugln("off");
      digitalWrite(EJECTION_PIN, LOW);
    }
  }
}
void create_Accesspoint()
{
  debugln();
  debug("creating access point ");
  debugln("ssid: ");
  debugln(ssid);
  debugln("password: ");
  debugln(password);
  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();
  debugln("Access point successully created ");
  debugln("IP address: ");
  debugln(IP);

  client.setServer(mqtt_server, MQQT_PORT);
  client.setCallback(mqttCallback);
}

void setup_wifi()
{
  // Connect to a WiFi network
  debugln();
  debug("Connecting to ");
  debugln(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    debug(".");
  }

  debugln("");
  debugln("WiFi connected");
  debugln("IP address: ");
  debugln(WiFi.localIP());

  client.setServer(mqtt_server, MQQT_PORT);
  client.setCallback(mqttCallback);
}

void reconnect()
{
  // Loop until we're reconnected
  while (!client.connected())
  {
    debugln("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8266Client"))
    {
      debugln("connected");
      // Subscribe
      client.subscribe("esp32/ejection");
    }
    else
    {
      debug("failed, rc=");
      debug(client.state());
      debugln(" try again in 50 milliseconds");
      // Wait 5 seconds before retrying
      delay(50);
    }
  }
}

void sendTelemetryWiFi(Data sv)
{

  // for (int i = 0; i < 5; i++)
  // {
  // publish whole message i json
  char mqttMessage[300];
  sprintf(mqttMessage, "{\"timestamp\":%lld,\"altitude\":%.3f,\"temperature\":%.3f,\"ax\":%.3f,\"ay\":%.3f,\"az\":%.3f,\"gx\":%.3f,\"gy\":%.3f,\"gz\":%.3f,\"filtered_s\":%.3f,\"filtered_v\":%.3f,\"filtered_a\":%.3f,\"state\":%d,\"longitude\":%.8f,\"latitude\":%.8f}", sv.timeStamp, sv.altitude, sv.temperature, sv.ax, sv.ay, sv.az, sv.gx, sv.gy, sv.gz, sv.filtered_s, sv.filtered_v, sv.filtered_a, sv.state, sv.longitude, sv.latitude);
  client.publish("esp32/message", mqttMessage);
  // char mqttMessage[200];
  // sprintf(mqttMessage, "{\"timestamp\":%lld,\"altitude\":%.3f,\"state\":%d,\"longitude\":%.8f,\"latitude\":%.8f}",sv.timeStamp, sv.altitude, sv.state, sv.longitude, sv.latitude);
  // client.publish("esp32/message", mqttMessage);
  debugln(mqttMessage);
  // }
}

void handleWiFi(Data sv)
{
  if (!client.connected())
  {
    reconnect();
  }
  client.loop();
  sendTelemetryWiFi(sv);
}
>>>>>>> dff4c80b2ca2dcd13d97aa8500f23a521ff3e5b9:include/transmitwifi.h

#endif