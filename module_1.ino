#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>  // Make sure this library is installed
#include <SPI.h>

// pinouts from https://github.com/Xinyuan-LilyGO/TTGO-T-Display
#define TFT_MOSI 19
#define TFT_SCLK 18
#define TFT_CS 5
#define TFT_DC 16
#define TFT_RST 23
#define TFT_BL 4

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

// Jack-o'-lantern face dimensions and zoom factor
int faceWidth = 40;   // wider pumpkin
int faceHeight = 30; 
int zoomFactor = 1;
int maxZoom = 5; 

uint16_t brown = tft.color565(165, 42, 42);

// Leaf colors
uint16_t leafColors[] = {ST77XX_RED, ST77XX_GREEN, ST77XX_ORANGE, ST77XX_YELLOW, brown};

void drawRandomLeaves() {
  int numLeaves = random(5, 15);  // Random number of leaves
  for (int i = 0; i < numLeaves; i++) {
    int x = random(0, tft.width());
    int y = random(0, tft.height());
    uint16_t color = leafColors[random(0, 5)];
    tft.fillCircle(x, y, random(3, 5), color);  // Random leaf size and color
  }
}

void setup() {
  // Initialize the display
  pinMode(TFT_BL, OUTPUT);
  digitalWrite(TFT_BL, HIGH); 

  tft.init(135, 240);  // Init ST7789 with 240x240 resolution
  tft.setRotation(1);  // Set rotation as needed
  tft.fillScreen(ST77XX_BLACK);  
  
}

void drawJackOLantern(int x, int y, int width, int height, int zoomLevel) {

  // adding basic pumpkin on first appearance
  // rounder rectangle for better pumpkin shape
  tft.fillRoundRect(x - width / 2, y - height / 2, width, height, height / 5, ST77XX_ORANGE);

  // brown stem
  int stemWidth = width / 6; // width of the stem as 1/6 of the pumpkin's width
  int stemHeight = height / 8; // height of the stem as 1/6 of the pumpkin's height
  tft.fillRect(x - stemWidth / 2, y - height / 2 - stemHeight / 2, stemWidth, stemHeight, brown);

  // variables for the eyes
  int eyeOffset = width / 6;  // horizontal distance between the eyes
  int eyeHeight = height / 4;  // height of the eyes
  int eyeWidth = eyeHeight;
  int eyeYPosition = y - height / 6;  // Y position for the eyes

  // variables for the nose
  int noseHeight = height / 6; // height of nose is 1/6 of the pumpkin's height

  // add features based on zoom level

  // adding eyes on zoom level 2
  if (zoomLevel >= 2) {
    // Left eye
    tft.fillTriangle(
      x - eyeOffset - eyeWidth / 2, eyeYPosition,
      x - eyeOffset + eyeWidth / 2, eyeYPosition,
      x - eyeOffset, eyeYPosition - eyeHeight, ST77XX_BLACK);

    // Right eye
    tft.fillTriangle(
      x + eyeOffset - eyeWidth / 2, eyeYPosition,
      x + eyeOffset + eyeWidth / 2, eyeYPosition,
      x + eyeOffset, eyeYPosition - eyeHeight, ST77XX_BLACK);
  }

  // add nose on zoom level 3
  if (zoomLevel >= 3) {
    // Nose (right-side-up triangle, moved higher)
    tft.fillTriangle(x, y - height / 10, x - noseHeight / 2, y - height / 10 + noseHeight, x + noseHeight / 2, y - height / 10 + noseHeight, ST77XX_BLACK);
  }

  // add mouth with vampire fangs on zoom level 4
  if (zoomLevel >= 4) {

    int mouthWidth = width / 2;
    int mouthHeight = height / 8;
    int mouthY = y + height / 4;
    tft.fillRect(x - mouthWidth / 2, mouthY, mouthWidth, mouthHeight, ST77XX_BLACK);

    int fangHeight = height / 6;
    int fangWidth = width / 5;

    tft.fillTriangle(
      x - mouthWidth / 4, mouthY + mouthHeight / 2,
      x - mouthWidth / 4 - fangWidth / 2, mouthY - fangHeight + mouthHeight / 2,
      x - mouthWidth / 4 + fangWidth / 2, mouthY - fangHeight + mouthHeight / 2, ST77XX_ORANGE);
    tft.fillTriangle(
      x + mouthWidth / 4, mouthY + mouthHeight / 2,
      x + mouthWidth / 4 - fangWidth / 2, mouthY - fangHeight + mouthHeight / 2,
      x + mouthWidth / 4 + fangWidth / 2, mouthY - fangHeight + mouthHeight / 2, ST77XX_ORANGE);

  }

  // light up pumpkin on final level
  if (zoomLevel == maxZoom) {
    // lighter shade of orange
    uint16_t lightOrange = tft.color565(255, 160, 0); 

    // eyes
    tft.fillTriangle(
      x - eyeOffset - eyeWidth / 2, eyeYPosition,
      x - eyeOffset + eyeWidth / 2, eyeYPosition,
      x - eyeOffset, eyeYPosition - eyeHeight, lightOrange);
    tft.fillTriangle(
      x + eyeOffset - eyeWidth / 2, eyeYPosition,
      x + eyeOffset + eyeWidth / 2, eyeYPosition,
      x + eyeOffset, eyeYPosition - eyeHeight, lightOrange);

    // nose
    tft.fillTriangle(x, y - height / 10, x - noseHeight / 2, y - height / 10 + noseHeight, x + noseHeight / 2, y - height / 10 + noseHeight, lightOrange);

    // mouth
    int mouthWidth = width / 2;
    int mouthHeight = height / 8;
    int mouthY = y + height / 4;
    tft.fillRect(x - mouthWidth / 2, mouthY, mouthWidth, mouthHeight, lightOrange);

    // need to redraw fangs
    int fangHeight = height / 6;
    int fangWidth = width / 5;

    tft.fillTriangle(
      x - mouthWidth / 4, mouthY + mouthHeight / 2,
      x - mouthWidth / 4 - fangWidth / 2, mouthY - fangHeight + mouthHeight / 2,
      x - mouthWidth / 4 + fangWidth / 2, mouthY - fangHeight + mouthHeight / 2, ST77XX_ORANGE);
    tft.fillTriangle(
      x + mouthWidth / 4, mouthY + mouthHeight / 2,
      x + mouthWidth / 4 - fangWidth / 2, mouthY - fangHeight + mouthHeight / 2,
      x + mouthWidth / 4 + fangWidth / 2, mouthY - fangHeight + mouthHeight / 2, ST77XX_ORANGE);
    
  }
}


void loop() {
  // Clear the display
  tft.fillScreen(ST77XX_BLACK);

  drawRandomLeaves();

  // Draw the Jack-o'-lantern in the center of the screen, adjusting the size with zoom
  int x = tft.width() / 2;
  int y = tft.height() / 2;
  drawJackOLantern(x, y, faceWidth * zoomFactor, faceHeight * zoomFactor, zoomFactor);

  // Increment zoom factor and loop back if it exceeds max zoom
  zoomFactor++;
  if (zoomFactor > maxZoom) {
    zoomFactor = 1;  // Reset zoom after reaching maximum
  }

  // Wait a couple of seconds before next zoom
  delay(1000);
}