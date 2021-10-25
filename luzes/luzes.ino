//incluido blibliotecas

#ifdef ARDUINO_ARCH_ESP32
#include <WiFi.h>
#else
#include <ESP8266WiFi.h>
#endif

#include <Espalexa.h>

//Definindo pino do led
#define led 2

//Declarando nome da rede e senha do wifi
const char *ssid = "Cristina ";
const char *password = "07192123";

//criando objeto espalexa
Espalexa espalexa;

void setup()
{ //inicio do setup

    Serial.begin(115200); //iniciando comunicação serial
    pinMode(led, OUTPUT); //declarando modo do pino do led como OUTPUT

    //se a conexão com wifi for concluida
    if (connectWifi() == true)
    {
        //sinalizar no serial e desligar led por padrão
        Serial.println("Conectado");
        digitalWrite(led, LOW);

        espalexa.addDevice("LED", firstLightChanged); // adicionar componente led na rede para conexão com a alexa
        espalexa.begin();                             //inicindo alexa
    }

    //caso falhe a conexão com o wifi
    else
    {
        //mostra mensagem de erro no serial e piscar led para sinalização
        while (1)
        {
            Serial.println("Erro de conexão.");
            digitalWrite(led, LOW);
            delay(200);
            digitalWrite(led, HIGH);
            delay(200);
        }
    }
} //fim do setup

void loop()
{
    espalexa.loop();
    delay(1);
}

//--------------------------------------------------------------------------

void firstLightChanged(uint8_t brightness)
{

    if (brightness == 0)
    {
        digitalWrite(led, HIGH);
        Serial.println(brightness);
    }

    else
    {
        digitalWrite(led, LOW);
        Serial.println(brightness);
    }
}

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