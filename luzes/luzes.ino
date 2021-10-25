//incluido blibliotecas para uso do ESP8266
#ifdef ARDUINO_ARCH_ESP32
#include <WiFi.h>
#else
#include <ESP8266WiFi.h>
#endif
#include <Espalexa.h>

#include <Espalexa.h> //incluindo bibliteca para comunicação com alexa

#define led 2 //Definindo pino do led

//Declarando nome da rede e senha do wifi
const char *ssid = "Cristina ";
const char *password = "07192123";

Espalexa espalexa; //criando objeto espalexa

//=============================================================================

void setup()
{
    Serial.begin(115200); //iniciando comunicação serial

    pinMode(led, OUTPUT); //declarando modo do pino do led como OUTPUT

    if (connectWifi() == true) //se a conexão com wifi for concluida
    {
        //sinalizar no serial e desligar led por padrão
        Serial.println("Conectado");

        espalexa.addDevice("LED", controla_led); //adicionando dispositivo led e informando qual função realizar
        espalexa.begin();                        //iniciando comunicação com alexa
    }

    else //falha na conexão com o wifi
    {
        //mostra mensagem de erro no serial e piscar led para sinalização
        while (1)
        {
            Serial.println("Erro de conexão.");
            digitalWrite(led, LOW);
            delay(2000);
            digitalWrite(led, HIGH);
            delay(2000);
        }
    }
}

//=============================================================================

void loop()
{
    espalexa.loop();
    delay(1);
}

//=============================================================================

//Função para controle do led quando alexa for acionada
void controla_led(uint8_t brightness)
{
    /*OBS: O módulo Wemos D1 R2 mini trabalha com nivel lógico invertido
    por esse motivo ao informa HIGH o led desliga e ao informar LOW o led liga
    Sendo caso for usar o código com um sistema de nivel lógioco convencional deve-se 
    modifar código conforme o projeto*/

    //se brilho for igual a 0 (desligado)
    if (brightness == 0)
    {
        digitalWrite(led, HIGH);// desligar led conforme observação no inicio da função
        Serial.println(brightness);// mostrar valor pwm no serial
    }

    //se brilho for diferente de 0 (ligado)
    else
    {
        digitalWrite(led, LOW);// ligar led conforme observação no inicio da função
        Serial.println(brightness);// mostrar valor pwm no serial
    }
    
}

//Função para realizar a conxão com wifi
boolean connectWifi()
{
    boolean state = true;
    int i = 0;

    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        if (i > 20)
        {
            state = false;
            break;
        }
        i++;
    }

    return state;
}