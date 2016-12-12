// This #include statement was automatically added by the Particle IDE.
#include "RFID.h"

/* FILE:    RC522_RFID_Module_Example
   DATE:    23/03/14
   VERSION: 0.2.1 Spark
REVISIONS:
29/08/16    Version 0.2.1, modified by ScruffR: corrected Software SPI sample
23/03/14    Version 0.2, modified by Paul Kourany to run on Spark Core
            with added support for Software SPI
24/07/13    Created version 0.1
This is an example of how to use the RC522 RFID module. The module allows reading
and writing to various types of RFID devices and can be found in our MFRC-522 
(HCMODU0016) and Ultimate RFID (HCARDU0068) kits. This example Arduino sketch uses
the RFID library written by Miguel Balboa to read the pre-programmed serial number 
from RFID cards and tags supplied with our RFID kits. Snapshots and links to the 
library are available on our support forum.
PINOUT:
RC522 MODULE    SPARK HARD SPI  SPARK SOFT SPI
SS                  A2              ANY
SCK                 A3              ANY
MOSI                A5              ANY
MISO                A4              ANY
IRQ                 N/A             N/A
GND                 GND             GND
RST                 D9              ANY
3.3V                3.3V            3.3V
You may copy, alter and reuse this code in any way you like, but please leave
reference to HobbyComponents.com in your comments if you redistribute this code.
This software may not be used directly for the purpose of selling products that
directly compete with Hobby Components Ltd's own range of products.
THIS SOFTWARE IS PROVIDED "AS IS". HOBBY COMPONENTS MAKES NO WARRANTIES, WHETHER
EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE, ACCURACY OR LACK OF NEGLIGENCE.
HOBBY COMPONENTS SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR ANY DAMAGES,
INCLUDING, BUT NOT LIMITED TO, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY
REASON WHATSOEVER.
*/
#include "application.h"

/* Include the RFID library */
/* SEE RFID.h for selecting Hardware or Software SPI modes */
#include "RFID.h"

/* Define the pins used for the SS (SDA) and RST (reset) pins for BOTH hardware and software SPI */
/* Change as required */
#define SS_PIN      A2      // Same pin used as hardware SPI (SS)
#define RST_PIN     D2

/* Define the pins used for the DATA OUT (MOSI), DATA IN (MISO) and CLOCK (SCK) pins for SOFTWARE SPI ONLY */
/* Change as required and may be same as hardware SPI as listed in comments */
#define MOSI_PIN    A5      // hardware SPI: A5
#define MISO_PIN    A4      //     "     " : A4
#define SCK_PIN     A3      //     "     " : A3

/* Create an instance of the RFID library */
#if defined(_USE_SOFT_SPI_)
    RFID RC522(SS_PIN, RST_PIN, MOSI_PIN, MISO_PIN, SCK_PIN);    // Software SPI
#else
    RFID RC522(SS_PIN, RST_PIN);                                 // Hardware SPI
#endif




//type:1 Dairy; 2 Meat; 3 Produce;  4:Bread.
//State variables
int present[]={0,0,0,0};
int date[]={0,0,0,0};
int month[]={0,0,0,0};
int expired[]={0,0,0,0};

//Card variables
int t[]={1,4,2,1,3,4,2,1,2,3};
int d[]={20,9,12,9,13,21,10,26,18,29};
int m[]={12,12,12,12,12,12,12,12,12,12};


int readCard(uint8_t x[])
{
    uint8_t a[10][5]={{125,43,242,197,97},{65,251,238,197,145},{186,92,238,197,205},{234,229,238,197,36},{21,207,241,197,238},{182,71,241,197,197},{106,211,238,197,146},{164,228,238,197,107},{28,111,238,197,88},{165,139,238,197,5}};
    int temp=-1;
    for(int i=0;i<10;i++)
    {
        for(int j=0;j<5;j++)
        {
            if(a[i][j]!=x[j])
                break;
            temp=i;
        }
    }
    Serial.println(temp+1);
    return (temp);
}

/*int itemDate(int card)
{
    int d[]={};
    return d[card];
}

int itemMonth(int card)
{
    int m[]={};
    return m[card];
}
int itemType(int card)
{
    int t[]={};
    return t[card];
}*/


void changeState(int card)
{
    Serial.println(card+1);
    int type=t[card]-1;
    if(present[type]==0)
    {
        present[type]=1;
        date[type]=d[card];
        month[type]=m[card];
        int i=type;
        /*Serial.print("Type ");
        Serial.println(i);
        Serial.print("Present ");
        Serial.println(present[i]);
        Serial.print("Date ");
        Serial.println(date[i]);
        Serial.print("Month ");
        Serial.println(month[i]);*/
    }
    else
    {
        present[type]=0;
        expired[type]=0;
        month[type]=0;
        date[type]=0;
    }
    /*int type = itemType(card);
    numbers[type++];
    if(numbers[type]==0)
    {
        day[type]=itemDate(card);
        month[type]=itemMonth(card);
    }
    else if(itemMonth(card)month[type])
    {
        
    }*/
    
    
}

void printState()
{
    Serial.print("Type  ");
    Serial.print("Present  ");
    Serial.print("Date  ");
    Serial.print("Month  ");
    Serial.println("Expired  ");
    for(int i=0;i<4;i++)
    {
        
        Serial.print(i+1);
        Serial.print("      ");
        Serial.print(present[i]);
        Serial.print("      ");
        Serial.print(date[i]);
        Serial.print("      ");
        Serial.print(month[i]);
        Serial.print("      ");
        Serial.println(expired[i]);
    }
}


void setup()
{ 
  Serial.begin(9600);
  pinMode(D7,OUTPUT);
#if !defined(_USE_SOFT_SPI_)
  /* Enable the HW SPI interface */
  SPI.setDataMode(SPI_MODE0);
  SPI.setBitOrder(MSBFIRST);
  SPI.setClockDivider(SPI_CLOCK_DIV8);
  SPI.begin();
#endif

  /* Initialise the RFID reader */
  RC522.init();
}


void loop()
{
    int data[]={9,9,9,9};
  /* Temporary loop counter */
  uint8_t i;
    digitalWrite(D7,LOW);
  /* Has a card been detected? */
  if (RC522.isCard())
  {
    /* If so then get its serial number */
    RC522.readCardSerial();

    Serial.println("Card detected:");
    digitalWrite(D7,HIGH);
    
    /* Output the serial number to the UART */
    /*for(i = 0; i <= 4; i++)
    {
      Serial.print(RC522.serNum[i]);
      Serial.print(" ");
      
    }*/
    int card = readCard(RC522.serNum);
    changeState(card);
    
    Serial.println();
    
    /*for(int i=0;i<4;i++)
    {
        Serial.print("Type ");
        Serial.println(i);
        Serial.print("Present ");
        Serial.println(present[i]);
        Serial.print("Date ");
        Serial.println(date[i]);
        Serial.print("Month ");
        Serial.println(month[i]);
    }*/
  }
  else
      Serial.println("Card NOT detected:");
      
  delay(1000);
  printState();
  for(int i=0;i<4;i++)
  {
      
      if(Time.day()>=date[i]&&Time.month()>=month[i]&&present[i]==1)
      {
          expired[i]=1;
      }
      else
      {
          expired[i]=0;
          
      }
      //Serial.println(expired[i]);
  }
  for(int i=0;i<4;i++)
  {
      if(present[i]==0)
      {
          Serial.print("1");
          data[i]=1;
      }
      else if(expired[i]==0)
      {
          Serial.print("2");
          data[i]=2;
      }
      else
      {
          Serial.print("3");
          data[i]=3;
      }
      /*Serial.print(present[i]);
      Serial.print(expired[i]);*/
      Serial.print(" ");
  }
  Serial.println();
  String s="";
  
  for(int i=0;i<=3;i++)
  {
      s+=data[i];
      //Serial.print(x[i]);
  }
  Serial.println("Data: "+s);
  Particle.publish("dataqwertyuiop",s);
}
