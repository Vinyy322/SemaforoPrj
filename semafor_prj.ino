//bibliotecas para ultilizar o wifi
#include <WiFi.h>
#include <WiFiClient.h>

//biblioteca para criar servidor html
#include <WebServer.h>
#include <string.h>

//cria uma instancia da biblioteca webServer passando a 
//porta de funcionamento(80)
WebServer server(80);

const char *ssid = "wifi-VnGtMaAt";
const char *password = "12345678";

//definindo a configuração de rede
IPAddress local_IP(192,168,0,100);
IPAddress gateway(19,168,0,1);
IPAddress subnet(255,255,255,0);

int logado = 0;

//variaveis da porta do led
const int led_v1 = 15;
const int led_a1 = 2;
const int led_vm1 =4 ;

const int led_v2 = 5;
const int led_a2 = 18;
const int led_vm2 = 19;

int tempV1 = 20;
int tempA1 = 5;

int tempV2 = 20;
int tempA2 = 5;

unsigned long previousMillis = 0;  // Armazena o último tempo em que a transição ocorreu

enum SemaforoState {  // Estados da máquina de estados
  ACENDER_S1_VERD_S2_VERM,
  APAGAR_S1_VERD_ACENDER_S1_AMA_S2_VERM,
  APAGAR_AMA1_VERM2_ACENDER_VERM1_VERD2,
  APAGAR_VERD2_ACENDER_AMA2_VERM1,
  COMPLETO
};

SemaforoState currentState = ACENDER_S1_VERD_S2_VERM;

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

  server.on("/", handleLogin);// o "/" siguinifica a rota raiz  / apresenta a tela de login
  server.on("/pagPrincipal", handlePrin);// apresenta a tela tempo
  server.on("/validaLogin",validaLogin);
  server.on("/configSemaforo", configSemaforo);
  server.begin();

}

void loop() {
  server.handleClient();
  Ligado();
}

void Ligado(){
  // apagarLed(led_vm1);//semaforo 1(apagar vermelho)
  // acenderLed(led_v1);//semaforo 1(acende verde)
  // acenderLed(led_vm2);//semaforo 2(acender vermelho)
  // tempo(tempV1);
  // apagarLed(led_v1);//semaforo 1(apaga verde)
  // acenderLed(led_a1);//semaforo 1(acende amarelo)
  // tempo(tempA1);
  // apagarLed(led_vm2);//semaforo 2(apaga vermelho)
  // apagarLed(led_a1);//semaforo 1(apaga amarelo)
  // acenderLed(led_vm1);//semaforo 1(acende vermelho)
  // acenderLed(led_v2);//semaforo 2(acender verde)
  // tempo(tempV2);
  // apagarLed(led_v2);//semaforo 2(apaga verde)
  // acenderLed(led_a2);//semaforo 2(acende amarelo)
  // tempo(tempA2);
  // apagarLed(led_a2);//semaforo 2(apaga amarelo)
  // apagarLed(led_v2);//semaforo 2(apaga verde)

  unsigned long currentMillis = millis();  // Obtém o tempo atual

  switch (currentState) {
    case ACENDER_S1_VERD_S2_VERM:
      if (currentMillis - previousMillis >= tempA2*1000) {
        previousMillis = currentMillis;
        apagarLed(led_a2);
        apagarLed(led_vm1);
        acenderLed(led_v1);
        acenderLed(led_vm2);
        currentState = APAGAR_S1_VERD_ACENDER_S1_AMA_S2_VERM;
      }
      break;

    case APAGAR_S1_VERD_ACENDER_S1_AMA_S2_VERM:
      if (currentMillis - previousMillis >= tempV1*1000) {
        previousMillis = currentMillis;
        apagarLed(led_v1);
        acenderLed(led_vm2);
        acenderLed(led_a1);
        currentState = APAGAR_AMA1_VERM2_ACENDER_VERM1_VERD2;
      }
      break;

    case APAGAR_AMA1_VERM2_ACENDER_VERM1_VERD2:
      if (currentMillis - previousMillis >= tempA1*1000) {
        previousMillis = currentMillis;
        apagarLed(led_vm2);
        apagarLed(led_a1);
        acenderLed(led_vm1);
        acenderLed(led_v2);
        currentState = APAGAR_VERD2_ACENDER_AMA2_VERM1;
      }
      break;

    case APAGAR_VERD2_ACENDER_AMA2_VERM1:
      if (currentMillis - previousMillis >= tempV2*1000) {
        previousMillis = currentMillis;
        apagarLed(led_v2);
        acenderLed(led_a2);
        acenderLed(led_vm1);
        currentState = COMPLETO;
      }
      break;

    case COMPLETO:
      // O ciclo completo de acendeSemaforo() terminou. Pode reiniciar se necessário.
      currentState = ACENDER_S1_VERD_S2_VERM;
      //previousMillis=0; // Reinicia o ciclo
      break;
  }
}


void acenderLed(int led){
  digitalWrite(led, HIGH);
}

void apagarLed(int led){
  digitalWrite(led,LOW);
}

