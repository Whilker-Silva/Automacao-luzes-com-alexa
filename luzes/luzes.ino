#include <Espalexa.h>

#ifdef ARDUINO_ARCH_ESP32
#include <WiFi.h>
#else
#include <ESP8266WiFi.h>
#endif

#define led 2

const char *ssid = "Cristina ";
const char *password = "07192123";

Espalexa espalexa;

void setup()
{

    Serial.begin(115200);
    pinMode(led, OUTPUT);

    if (connectWifi() == true)
    {
        Serial.println("Conectado");
        digitalWrite(led, LOW);

        espalexa.addDevice("LED", firstLightChanged);
        espalexa.begin();
    }

    else
    {
        while (1)
        {
            Serial.println("Erro de conexão.");
            digitalWrite(led, LOW);
            delay(200);
            digitalWrite(led, HIGH);
            delay(200);
        }
    }
}

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