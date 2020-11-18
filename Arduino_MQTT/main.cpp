#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Servo.h>

//Red WiFi
#define SSID "franco"
#define PASS "franco6886"

// Servo
Servo servoMotor;

// GPIO
// #define Spark 5

//Publish and Subscribe
const char *MQTT_Server = {"broker.hivemq.com"};
int Port = 1883;
const char *publish_topic = "Dev/ESP32/Curso/";
const char *subscribe_topic = "Dev/ESP32/Test/";

int i = 0;

WiFiClient wificlient;
PubSubClient MQTTClient(wificlient);

void setup_wifi() // Conecta al wemos a la red wifi
{
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(SSID);

  WiFi.begin(SSID, PASS);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  //randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect() // Conecta o se reconecta al broker
{
  if (!MQTTClient.connected()) // si no esta conectado nos conectamos
  {
    String clientId = "ESP8266Client-";      // cada vez que nos reconectamos el nombre
    clientId += String(random(0xffff), HEX); // del cliente debe cambiar

    if (MQTTClient.connect(clientId.c_str())) // nos conectamos
    {
      Serial.println("conexion exitosa a broker");
      MQTTClient.subscribe(subscribe_topic); // nos subscribimos
    }
    else
    {
      Serial.println("No se pudo conectar al broker");
    }
  }
  MQTTClient.loop();
}

void callback(char *topic, byte *payload, unsigned int length) // Se encarga de recibir el mensaje
{
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++)
  {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  // Con el primer caracter del mensaje toma una accion
  if ((char)payload[0] == '1')
  {
    servoMotor.write(90);
    // digitalWrite(Spark, HIGH); // Activa el relay
    // Serial.println("ON");
  }
  else
  {
    servoMotor.write(0);
    // digitalWrite(Spark, LOW); // Desactiva el relay
    // Serial.println("OFF");
  }
}

void setup()
{
  servoMotor.attach(5);
  servoMotor.write(0);
  //pinMode(Spark, OUTPUT); // Definicion del
  Serial.begin(115200);
  setup_wifi();
  MQTTClient.setServer(MQTT_Server, Port); // Conexion al server , puerto por defecto 1883 usado en mqtt
  MQTTClient.setCallback(callback);        //
}

void loop()
{
  reconnect();

  // if (i > 5)
  // {
  //     i = 0;
  // }

  // Serial.println(i);
  // MQTTClient.publish(publish_topic, String(i).c_str());

  // i++;
  // delay(1000);
}
