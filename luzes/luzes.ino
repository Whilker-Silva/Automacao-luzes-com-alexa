// incluido blibliotecas para uso do ESP8266
#ifdef ARDUINO_ARCH_ESP32
#include <WiFi.h>
#else
#include <ESP8266WiFi.h>
#endif
#include <Espalexa.h> //incluindo bibliteca para comunicação com alexa

#define led 2 // Definindo pino do led

// Criando vetor para led RGB
int led_rgb[]{5, 4, 0};

// Declarando nome da rede e senha do wifi
const char *ssid = "Cristina ";
const char *password = "07192123";

Espalexa espalexa; // criando objeto espalexa

//=============================================================================

void setup()
{
    Serial.begin(115200); // iniciando comunicação serial

    pinMode(led, OUTPUT);        // declarando modo do pino do led como OUTPUT
    pinMode(led_rgb[0], OUTPUT); // declarando modo dos pino RGB como OUTPUT
    pinMode(led_rgb[1], OUTPUT); // declarando modo dos pino RGB como OUTPUT
    pinMode(led_rgb[2], OUTPUT); // declarando modo dos pino RGB como OUTPUT

    if (connectWifi() == true) // se a conexão com wifi for concluida
    {
        // sinalizar no serial
        Serial.println("Conectado");

        // adicionando dispositivos led e informando qual função realizar
        espalexa.addDevice("LUZ QUARTO", luz_quarto);
        espalexa.addDevice("LUZ RGB", controla_led_RGB);

        espalexa.begin(); // iniciando comunicação com alexa
    }

    else // falha na conexão com o wifi
    {
        // mostra mensagem de erro no serial e piscar led para sinalização
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
    // Realizando verificar de comando da alexa
    espalexa.loop();
    delay(1);
}

//=============================================================================

// Função para controle da luz RGB
void controla_led_RGB(uint8_t brightness, uint32_t rgb)
{
    // Delcarando variáveis para RGB
    byte R = (rgb >> 16) & 0xFF;
    byte G = (rgb >> 8) & 0xFF;
    byte B = rgb & 0xFF;
    
    // Realizando cálculo para brilho da luz
    R = R * brightness / 255;
    G = G * brightness / 255;
    B = B * brightness / 255;

    // Ligando led RGB de acordo com os valores fornecido pela alexa
    analogWrite(led_rgb[0], R);
    analogWrite(led_rgb[1], G);
    analogWrite(led_rgb[2], B);

    // mostrando no serial valores RGB
    Serial.print("LUZ_RGB | ");
    Serial.print("Cor: ");
    Serial.print(R);
    Serial.print(", ");
    Serial.print(G);
    Serial.print(", ");
    Serial.println(B);
}

// Função para controle da luz Quarto
void luz_quarto(uint8_t brightness)
{
    /*OBS: O módulo Wemos D1 R2 mini trabalha com nivel lógico invertido
    por esse motivo ao informa HIGH o led desliga e ao informar LOW o led liga
    Sendo caso for usar o código com um sistema de nivel lógioco convencional deve-se
    modifar código conforme o projeto*/

    byte x = 255 - brightness; // cálculo para conversão do nivel lógico conforme OBS

    analogWrite(led, x); // ligar luz com valor pwm cálculado

    // mostrar valor pwm no serial
    Serial.print("LUZ_QUARTO | ");
    Serial.print("Brilho: ");
    Serial.println(brightness);
}

// Função para realizar a conxão com wifi
boolean connectWifi()
{

    // declarando variáveis de estado e contagem
    boolean state = true;
    int i = 0;

    WiFi.mode(WIFI_STA);        // Modo de conexão wifi
    WiFi.begin(ssid, password); // rede e senha do wifi

    // tentando realizar conexão
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);

        // Caso a conexão falhe 20x mudar estado para false e dar brake no while
        if (i > 20)
        {
            state = false;
            break;
        }
        i++;
    }

    // finaliza função retorno valor de estado
    // caso tenha sucesso na conexão estado permanece true
    return state;
}