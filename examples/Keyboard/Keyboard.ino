#include <HX8347D.h>
#include <XPT2046.h>
#include <LiberationSans.h>
#include <ShinyButton.h>
#include <Roboto.h>

DSPI1 spi;
HX8347D tft(spi, 7, 10); // D/C and CS pins
XPT2046 ts(spi, 4, 240, 320);  // 4 = touch chip select

USBFS usbDevice;
USBManager USB(usbDevice, 0xf055, 0xf002, "Majenko Technologies", "USB TFT Keyboard");
CDCACM uSerial;

#define TEXTSIZE 30
char input[TEXTSIZE] = {'|', 0};
int ipos = 0;
bool textUpdate = true;

// We can use a ShinyButton for displaying text if we like - they are versatile.
ShinyButton textArea(ts, tft, 
    10, 96,                         // Top left coordinates 
    300, 32,                        // Dimensions
    Color::White, Color::Gray80,    // Normal colour gradient
    Color::White, Color::Gray80,    // Highlight colour gradient
    input,                          // Text to display (if it's in RAM you can modify it)
    0,                              // Vertical font offset
    Color::Black,                   // Text colour
    Fonts::Roboto);                 // Font to use

// The keyboard widget. It's actually a compound widget made up of 62 ShinyButtons.
ShinyKeyboard keyboard(ts, tft, 
    10, 128,                             // Top left coordinates
    5,                                  // Scale 
    Color::Gray70, Color::Gray30,       // Normal colours
    Color::DarkOrange, Color::Gray30,   // Pressed colours
    Color::White,                       // Font colour
    Fonts::LiberationSans12);

// This is what we do when a key is pressed.
void handleKeypress(int keycode) {
    // 8 is backspace (^H)
    if (keycode == 8) {
        if (ipos > 0) {
            ipos--;
            input[ipos] = '|';
            input[ipos+1] = 0;
        }
    }

    // 13 is return (^M)
    if (keycode == 13) {
        input[0] = '|';
        input[1] = 0;
        ipos = 0;
    }

    // Everything between 32 (space) and 127 (house) is printable.
    if (keycode >= 32 && keycode <= 127) {
        if (ipos < TEXTSIZE-2) {
            input[ipos++] = keycode;
            input[ipos] = '|';
            input[ipos+1] = 0;
        }
    }

    textArea.redraw();
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

    // Attach the handler that gets called when a key is pressed.
    keyboard.onKeypress(handleKeypress);

}

// The loop is as simple as sampling the touch screen and rendering 
// the widgets. Nothing more.
void loop() {
    ts.sample();
    keyboard.render();
    textArea.render();
}
