#include <WiFi.h>                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        
#include <PubSubClient.h>

const char* ssid = "";
const char* password =  "";
const char* mqttServer = "";  // broker
const int mqttPort = ;
const char* mqttUser = "";
const char* mqttPassword = "";
const int ledPin = 5;

WiFiClient espClient;
PubSubClient client(espClient);

int contador = 1;
char mensagem[30];

void setup()
{
  pinMode (ledPin, OUTPUT);
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.println("Iniciando conexao com a rede WiFi..");
  }

  Serial.println("Conectado na rede WiFi!");
}

void loop()
{
  //Faz a conexao com o broker MQTT
  reconectabroker();
  sprintf(mensagem, "%d%dC05", contador, contador);
  Serial.print("Mensagem enviada: ");
  Serial.println(mensagem);

  //Envia a mensagem ao broker
  client.publish("test1", mensagem); // topic
  Serial.println("Mensagem enviada com sucesso...");
 // Serial.println(mqttServer);
  digitalWrite (ledPin, HIGH);  // turn on the LED
  delay(500); // wait for half a second or 500 milliseconds
  digitalWrite (ledPin, LOW); 
  
  //Incrementa o contador
  contador++;
  
  //Aguarda 30 segundos para enviar uma nova mensagem
  delay(30000);
}

void reconectabroker()
{
  //Conexao ao broker MQTT
  client.setServer(mqttServer, mqttPort);
  while (!client.connected())
  {
    Serial.println("Conectando ao broker MQTT...");
    if (client.connect("IFtesting",mqttUser,mqttPassword ))
    {
      Serial.println("Conectado ao broker!");
    }
    else
    {
      Serial.print("Falha na conexao ao broker - Estado: ");
      Serial.print(client.state());
      delay(2000);
    }
  }
}
