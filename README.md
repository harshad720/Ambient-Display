# Ambient-Display
## Introduction
How many times have you opened the fridge, taken out the milk, peeked at the expiration date and then realized that it expired a day before or few days ago? You end up wasting food and money by throwing out spoiled food. The perishable food items in the fridge expires soon if you forget to use it. There needs to be some way that helps to reduce the food wastage by indicating that the item will expire soon and it needs to be used. 
## About The Project
Most of us have probably thrown out food due to spoilage, but regularly doing this is terribly wasteful and expensive. That’s why we decided to build a smart display that indicates the freshness of food items like vegetables, fruits, milk, meat, bread, bakery item etc.
We have indicated the items by display the best thing that depict the products in the fridge.
For eg:	
Tree depicts produce items like vegetables and fruits
Chicken depicts Meat and eggs
Cow depicts milk and other dairy products
Wheat depicts bakery goods like bread, cakes etc
## Materials
Clear Acrylic
Particle Photon (x2)
Soft wood for base of display and enclosure of Photon
RFID Reader and Tags
Neopixel LED strips(4 strips)
LED
Wires
![img_0986](https://cloud.githubusercontent.com/assets/21200411/21118606/a4fe7e58-c08c-11e6-8295-c4b9d3912255.jpg)

## Tools
Laser Cutter for engraving and cutting
Glue Gun
Soldering Iron

## Data Description
Type 1: Dairy (Blue)
Type 2: Meat (White)
Type 3: Produce (Green)
Type 4: Wheat (Yellow)

## Input Connections
SDA-A2
SCK-A3
MOSI-A5
MISO-A4
RST-D2
LED-D7(to show that the card was scanned)

## Output Connections
The output code displays the data received from the input photon onto the neopixel LED strips.
The connections are shown below:
Neopixel LED strips - D1,D2,D3,D4.

## Libraries used:
• Neopixel.h
• rfid.h

## References
RFID.h from pkourany(https://github.com/pkourany/RC522_RFID)

## Image and Video

![whatsapp image 2016-12-12 at 3 36 49 pm](https://cloud.githubusercontent.com/assets/21200411/21118546/523ce722-c08c-11e6-8bc8-ead186e66326.jpeg)


https://youtu.be/1rxCyY9-Ofo

