// incluido blibliotecas para uso do ESP8266
#ifdef ARDUINO_ARCH_ESP32
#include <WiFi.h>
#else
#include <ESP8266WiFi.h>
#endif
#include <Espalexa.h>  //incluindo bibliteca para comunicação com alexa

#define led 2  // Definindo pino do led

// Declarando nome da rede e senha do wifi
const char *ssid = "CRISTINA";
const char *password = "07192123";

Espalexa espalexa;  // criando objeto espalexa

//=============================================================================

void setup() {


  pinMode(led, OUTPUT);  // declarando modo do pino do led como OUTPUT
  digitalWrite(led, HIGH);

  /*if (connectWifi() == true)  // se a conexão com wifi for concluida
  {

    // adicionando dispositivos led e informando qual função realizar
    espalexa.addDevice("ESPELHO", luz_quarto);

    espalexa.begin();  // iniciando comunicação com alexa

    digitalWrite(led, LOW);
  }

  else  // falha na conexão com o wifi
  {
    // mostra mensagem de erro no serial e piscar led para sinalização
    while (1) {
      digitalWrite(led, LOW);
      delay(2000);
      digitalWrite(led, HIGH);
      delay(2000);
    }
  }*/
}

//=============================================================================

void loop() {
 /* espalexa.loop();
  delay(1);*/
}

//=============================================================================


// Função para controle da luz do espelho
void luz_quarto(uint8_t brightness) {
  /*OBS: O módulo Wemos D1 R2 mini trabalha com nivel lógico invertido
    por esse motivo ao informa HIGH o led desliga e ao informar LOW o led liga
    Sendo caso for usar o código com um sistema de nivel lógioco convencional deve-se
    modifar código conforme o projeto*/

  byte x = 255 - brightness;  // cálculo para conversão do nivel lógico conforme OBS

  analogWrite(led, x);  // ligar luz com valor pwm cálculado

  // mostrar valor pwm no serial
  Serial.print("ESPELHO | ");
  Serial.print("Brilho: ");
  Serial.println(brightness);
}

// Função para realizar a conxão com wifi
boolean connectWifi() {

  // declarando variáveis de estado e contagem
  boolean state = true;
  int i = 0;

  WiFi.mode(WIFI_STA);         // Modo de conexão wifi
  WiFi.begin(ssid, password);  // rede e senha do wifi

  // tentando realizar conexão
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);

    // Caso a conexão falhe 20x mudar estado para false e dar brake no while
    if (i > 20) {
      state = false;
      break;
    }
    i++;
  }

  // finaliza função retorno valor de estado
  // caso tenha sucesso na conexão estado permanece true
  return state;
}