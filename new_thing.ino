#include <SPI.h>
#include <MFRC522.h> //RFID reader
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include "LILMAN.h.h" // icons location

//TFT screen pins
#define TFT_CS   5
#define TFT_RST  6
#define TFT_DC   7
#define TFT_MOSI  11
#define TFT_SCLK  13

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST); //initialise the TFT display

//RFID pins
#define RST_PIN  9
#define SDA_PIN   10

MFRC522 mfrc522(SDA_PIN, RST_PIN);  // initialize the RC522 module (RFID reader)

//colours
#define BLACK 0x0000
#define BLUE 0x001F
#define RED 0xF800
#define GREEN 0x07E0
#define CYAN 0x07FF
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define WHITE 0xFFFF


bool tag_scanned = false; //set the RFID reader as naturally not being scanned

void setup() {
  Serial.begin(9600);
    Serial.println("Starting up");
  SPI.begin(); // Start SPI communication
  mfrc522.PCD_Init(); // Initialize RFID module
  tft.begin(); // Initialize TFT screen

  
  // clear the screen with a black background
tft.fillScreen(BLACK);

}

void loop() {
  // Generate a random image
 // for (int y = 0; y < 160; y++) {
  //  for (int x = 0; x < 128; x++) {
    //  // Generate a random color
     // uint16_t color = (rand() % 0xFFFF);
     // tft.drawPixel(x, y, color);
int screen_width = 240;
int screen_height = 320;
int image_width = 128;
int image_height = 160;
   


int x = (screen_width - image_width); // 2
int y = (screen_height - image_height); // 2

if (!tag_scanned) {


tft.drawBitmap(x, 10, panda, 128, 160, ILI9341_WHITE);}

  // Look for new cards
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
 
    // Show UID on serial monitor
    Serial.print("UID tag :");
    String content = "";
    byte letter;
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
      Serial.print(mfrc522.uid.uidByte[i], HEX);
      content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
      content.concat(String(mfrc522.uid.uidByte[i], HEX));
       
    }
    Serial.println();
    Serial.print("Message : ");
    content.toUpperCase();
    tag_scanned = true; 
    Serial.println("tag scanned");
    if (content.substring(1) == "AA 27 0A 86") {
    
      Serial.println("Red heart");
      Serial.println();
      //draw heart on screen
 tft.drawBitmap(35, 80, heart, 64, 64, ILI9341_RED);

      // Draw a green circle on the screen
     // tft.fillCircle(100, 50, 20, GREEN);

    }
     
     
     else {
      Serial.println("Yellow heart");
       // Draw a red circle on the screen
      //draw yellow
      tft.drawBitmap(35, 80, heart, 64, 64, ILI9341_YELLOW);
    }
  }
}
