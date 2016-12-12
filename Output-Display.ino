// This #include statement was automatically added by the Particle IDE.
#include "neopixel/neopixel.h"
#include "application.h"

// IMPORTANT: Set pixel COUNT, PIN and TYPE
#define PIXEL_PIN D2
#define PIXEL_COUNT 8
#define PIXEL_TYPE WS2812B

Adafruit_NeoPixel strip1 = Adafruit_NeoPixel(PIXEL_COUNT, D1, PIXEL_TYPE);
Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(PIXEL_COUNT, D2, PIXEL_TYPE);
Adafruit_NeoPixel strip3 = Adafruit_NeoPixel(PIXEL_COUNT, D3, PIXEL_TYPE);
Adafruit_NeoPixel strip4 = Adafruit_NeoPixel(PIXEL_COUNT, D4, PIXEL_TYPE);

int m[32];
int state[]={0,0,0,0};

void rainbow(uint8_t wait);
uint32_t Wheel(byte WheelPos);

void plau(const char *data)
{
    for(int i=0;i<4;i++)
    {
        //for(int j=0;j<8;j++)
        //{
            if(data[i]=='1')
            {
                switch(i)
                {
                    case 0: strip1.setBrightness(0); break;
                    case 1: strip2.setBrightness(0); break;
                    case 2: strip3.setBrightness(0); break;
                    case 3: strip4.setBrightness(0); break;
                }
            }
            else if(data[i]=='2')
            {
                switch(i)
                {
                    case 0: strip1.setBrightness(100); break;
                    case 1: strip2.setBrightness(100); break;
                    case 2: strip3.setBrightness(100); break;
                    case 3: strip4.setBrightness(100); break;
                }
            }
            else if(data[i]=='3')
            {
                switch(i)
                {
                    case 0: strip1.setBrightness(255); break;
                    case 1: strip2.setBrightness(255); break;
                    case 2: strip3.setBrightness(255); break;
                    case 3: strip4.setBrightness(255); break;
                }
            }
        //}
    }
}

void setup() {
    Serial.begin(9600);
    strip1.begin();
    strip1.show(); // Initialize all pixels to 'off'
    strip1.setBrightness(255);
    strip2.begin();
    strip2.show(); // Initialize all pixels to 'off'
    strip2.setBrightness(255);
    strip3.begin();
    strip3.show(); // Initialize all pixels to 'off'
    strip3.setBrightness(255);
    strip4.begin();
    strip4.show(); // Initialize all pixels to 'off'
    strip4.setBrightness(255);
    Particle.subscribe("dataqwertyuiop",myHandler);
    
}

void myHandler (const char *event, const char *data)    //handles the data coming from the cloud and sends it to the different functions 
{
    Serial.print("\n\n\n DATA:::");
    Serial.println(data);
    for(int i=0;i<4;i++)
    {
        Serial.println(data[i]);
    }
    plau(data);
    
}

void loop() {
    for(int i=0;i<8;i++)
    {
        strip1.setPixelColor(i,strip1.Color(255,255,0));
        strip2.setPixelColor(i,strip2.Color(255,255,255));
        strip3.setPixelColor(i,strip3.Color(0,255,0));
        strip4.setPixelColor(i,strip4.Color(0,0,255));
    }
    /*for(int i=8;i<16;i++)
    {
        strip.setPixelColor(i,strip.Color(255,0,0));
    }
    for(int i=16;i<24;i++)
    {
        strip.setPixelColor(i,strip.Color(0,255,0));
    }
    for(int i=24;i<32;i++)
    {
        strip.setPixelColor(i,strip.Color(0,0,255));
    }*/
    strip1.show();
    strip2.show();
    strip3.show();
    strip4.show();
    delay(50);
}
