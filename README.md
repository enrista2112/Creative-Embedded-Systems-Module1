# Creative Embedded Systems Module 1: Generative Art

Link to Blog Post: https://flashy-tellurium-248.notion.site/Module-1-Generative-Art-11469c3732868043beb4c3fa4378121f

In my Creative Embedded Systems class, for our first module, each student wrote a single ESP32 program that visualized a design of their choice on the screen of an ESP32. The theme of this module was ‘Fall’. The goal of this is to create a generative art installation in the fifth floor Milstein. 

For this project, the design of my choice was a jack o'lantern with leaves falling in the background. The pumpkin's face is drawn progressively with each zoom, starting with the pumpkin shape, then adding the eyes, nose, and mouth. As the zoom reaches its maximum, the eyes, nose, and mouth appear "lit" by filling them with a lighter orange color. Randomly positioned leaves of different fall colors (red, green, orange, yellow) are drawn on the background each time the zoom progresses.


Required Libraries:
* Adafruit_GFX.h
* Adafruit_ST7789.h
* SPI.h

Hardware:
* ESP32 TTGO T-display
* Lipo battery
* USB-C

Components:
Setup: The TFT display is initialized in the setup() function. The screen is cleared to black (tft.fillScreen(ST77XX_BLACK)), and the display rotation is set.
Pumpkin Shape: The pumpkin is drawn as a rounded rectangle (tft.fillRoundRect()) with adjustable width and height to give it a more realistic appearance. The pumpkin is drawn during the first call to  drawJackOLantern(), i.e. the first zoom.
Eyes: The eyes are triangles, drawn symmetrically on the pumpkin. The pumpkin and its eyes are drawn during the second call to  drawJackOLantern(), i.e. the second zoom.
Nose: The nose is a triangle that appears during the third zoom level. The pumpkin and its eyes and nose are drawn during the third call to  drawJackOLantern(), i.e. the third zoom.
Mouth: The mouth is a rectangle with two fangs on the top. The pumpkin and its eyes, nose, and mouth are drawn during the fourth call to drawJackOLantern(), i.e. the fourth zoom.
Lighting Effect: At the maximum zoom, the inside of the eyes, nose, and mouth are filled with a lighter orange to simulate a "lit" Jack-o'-lantern. The carved pumpkin is lit up during the fifth and final call to drawJackOLantern(), i.e. the fourth zoom.

Random Falling Leaves: Randomly positioned leaves in fall colors are drawn on the background each time the zoom level changes. Each time the zoom level changes, the drawRandomLeaves() function is called to draw a set of random leaves in different colors across the screen.

Zooming: The zoomFactor controls how much of the pumpkin's features are revealed at each step. At each zoom level, the code checks which features should be drawn and whether the "lit" effect should be applied.

