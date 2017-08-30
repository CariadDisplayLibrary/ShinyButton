#include <HX8347D.h>
#include <XPT2046.h>
#include <LiberationSans.h>
#include <ShinyButton.h>

DSPI1 spi;
HX8347D tft(spi, 7, 10); // D/C and CS pins
XPT2046 ts(spi, 4, 240, 320);  // 4 = touch chip select

USBFS usbDevice;
USBManager USB(usbDevice, 0xf055, 0xf002, "Majenko Technologies", "USB TFT Keyboard");
CDCACM uSerial;

#define TEXTSIZE 30
char input[TEXTSIZE] = {0};
int ipos = 0;
bool textUpdate = true;

ShinyKeyboard keyboard(ts, tft, 
    8, 128,                             // Top left coordinates
    5,                                  // Scale 
    Color::Gray70, Color::Gray30,       // Normal colours
    Color::DarkOrange, Color::Gray30,   // Pressed colours
    Color::White,                       // Font colour
    Fonts::LiberationSans12);

void handleKeypress(int keycode) {
    if (keycode == 8) {
        if (ipos > 0) {
            ipos--;
            input[ipos] = 0;
        }
    }

    if (keycode == 13) {
        input[0] = 0;
        ipos = 0;
    }

    if (keycode >= 32 && keycode <= 127) {
        if (ipos < TEXTSIZE-1) {
            input[ipos++] = keycode;
            input[ipos] = 0;
        }
    }

    textUpdate = true;
}

void setup() {
    USB.addDevice(uSerial);
    USB.begin();

    // Backlight on the WaveShare 2.8" TFT
    pinMode(9, OUTPUT);
    digitalWrite(9, HIGH);

    // Enable the TFT
    tft.initializeDevice();
    tft.setRotation(1);

    // Set up the touch (on the WaveShare the touch is rotated 180 degrees
    ts.initializeDevice();
    ts.setRotation(3);

    // Offsets are *pre* rotation
    ts.scaleX(1.15);
    ts.offsetX(-20);
    ts.scaleY(1.15);
    ts.offsetY(-30);
    
    tft.fillScreen(Color::Black);

    keyboard.onKeypress(handleKeypress);

    tft.setFont(Fonts::LiberationSans26);
    int h = tft.stringHeight(" ");
    tft.fillRectangle(0, 0, 320, h + 20, Color::White);
}

void loop() {
    ts.sample();
    keyboard.render();
    if  (textUpdate) {
        textUpdate = false;
        tft.setCursor(10, 10);
        tft.setTextColor(Color::Black, Color::White);
        tft.setFont(Fonts::LiberationSans26);
        int h = tft.stringHeight(input);
        int w = tft.stringWidth(input);
        tft.print(input);
        tft.fillRectangle(10 + w, 10, 300 - w, h, Color::White);
        tft.print("|");
    }
}
