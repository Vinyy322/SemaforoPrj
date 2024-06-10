//bibliotecas para ultilizar o wifi
#include <WiFi.h>
#include <WiFiClient.h>

//biblioteca para criar servidor html
#include <WebServer.h>
#include <string.h>

//cria uma instancia da biblioteca webServer passando a 
//porta de funcionamento(80)
WebServer server(80);

const char *ssid = "wifi-vasco";
const char *password = "12345678";

//definindo a configuração de rede
IPAddress local_IP(192,168,0,100);
IPAddress gateway(19,168,0,1);
IPAddress subnet(255,255,255,0);

//variaveis da porta do led
const int led_v1 = 15;
const int led_a1 = 2;
const int led_vm1 =4 ;

const int led_v2 = 5;
const int led_a2 = 18;
const int led_vm2 = 19;

float temp = 2;


void setup() {
  //configurando o Acess Point com o ESP
  Serial.begin(115200);
  Serial.print("configurando wifi...");
  Serial.println(WiFi.softAPConfig(local_IP, gateway, subnet)? "ok" : "erro na configuração" );
  Serial.print("iniciando wifi....");
  Serial.println(WiFi.softAP(ssid,password)? "ok": "erro na inicialização");
  Serial.print("IP do AP");
  Serial.println(WiFi.softAPIP());

  pinMode(led_v1, OUTPUT);//semaforo 1
  pinMode(led_a1, OUTPUT);//semaforo 1
  pinMode(led_vm1, OUTPUT);//semaforo 1

  pinMode(led_v2, OUTPUT);//semaforo 2
  pinMode(led_a2, OUTPUT);//semaforo 2
  pinMode(led_vm2, OUTPUT);//semaforo 2
}

void loop() {
  Ligado();
}

void Ligado(){
  apagarLed(led_vm1);//semaforo 1(apagar vermelho)
  acenderLed(led_v1);//semaforo 1
  acenderLed(led_vm2);//semaforo 2(acender vermelho)
  tempo(temp);
  apagarLed(led_v1);//semaforo 1
  acenderLed(led_a1);//semaforo 1
  tempo(temp);
  apagarLed(led_vm2);//semaforo 2
  apagarLed(led_a1);//semaforo 1
  acenderLed(led_vm1);//semaforo 1
  acenderLed(led_v2);//semaforo 2
  tempo(temp);
  apagarLed(led_v2);//semaforo 2
  acenderLed(led_a2);//semaforo 2
  tempo(temp);
  apagarLed(led_a2);//semaforo 2
  apagarLed(led_v2);//semaforo 2
}


void acenderLed(int led){
  digitalWrite(led, HIGH);
}

void apagarLed(int led){
  digitalWrite(led,LOW);
}

void tempo(int t){
  delay(t*1000);
}