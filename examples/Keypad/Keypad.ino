#include <ShinyButton.h>
#include <Roboto.h>
#include <Picadillo.h>

// You'll want to change this to match your screen
Picadillo tft;
AnalogTouch ts(LCD_XL, LCD_XR, LCD_YU, LCD_YD, 320, 480);

#define TEXTSIZE 30
char input[TEXTSIZE] = {'|', 0};
int ipos = 0;

int mode = 0;

// We can use a ShinyButton for displaying text if we like - they are versatile.
ShinyButton textArea(ts, tft,
                     40, 20,                         // Top left coordinates
                     240, 32,                        // Dimensions
                     Color::White, Color::Gray80,    // Normal colour gradient
                     Color::White, Color::Gray80,    // Highlight colour gradient
                     input,                          // Text to display (if it's in RAM you can modify it)
                     0,                              // Vertical font offset
                     Color::Black,                   // Text colour
                     Fonts::Roboto);                 // Font to use

// The keyboard widget. It's actually a compound widget made up of 62 ShinyButtons.
ShinyKeypad keyboard(ts, tft,
                     40, 68,                             // Top left coordinates
                     20,                                  // Scale
                     Color::Gray70, Color::Gray30,       // Normal colours
                     Color::DarkOrange, Color::Gray30,   // Pressed colours
                     Color::White,                       // Font colour
                     Fonts::Roboto);

ShinyButton cancel(ts, tft, 
                   0, 400, 
                   128, 64, 
                   Color::DarkRed, Color::Black, 
                   Color::Red, Color::Black, 
                   "Cancel", 0, 
                   Color::White, Fonts::Roboto);

ShinyButton ok(ts, tft, 
                   319-128, 400, 
                   128, 64, 
                   Color::DarkGreen, Color::Black, 
                   Color::Green, Color::Black, 
                   "OK", 0, 
                   Color::White, Fonts::Roboto);

// This is what we do when a key is pressed.
void handleKeypress(int keycode) {

	switch (keycode) {
          case 8: // Backspace
               if (ipos > 0) {
                    ipos--;
                    input[ipos] = '|';
                    input[ipos + 1] = 0;
               }
               break;
          case '.':
               if (strchr(input, '.') == NULL) {
                    if (ipos < TEXTSIZE - 2) {
                         input[ipos++] = '.';
                         input[ipos] = '|';
                         input[ipos + 1] = 0;
                    }
               }
               break;
           default:
               if (ipos < TEXTSIZE - 2) {
                    input[ipos++] = keycode;
                    input[ipos] = '|';
                    input[ipos + 1] = 0;
               }
	}

	textArea.redraw();
}

void doOk(Event *e) {
     mode = 1;
}

void doCancel(Event *e) {
     input[0] = '|';
     input[1] = 0;
     ipos = 0;
     textArea.redraw();
}

void highlight(Event *e) {
     e->source->setValue(1);
}

void lowlight(Event *e) {
     e->source->setValue(0);
}

void setup() {
	// Enable the TFT
	tft.initializeDevice();
	tft.setRotation(0);
	tft.setBacklight(255);
	// Set up the touch (on the WaveShare the touch is rotated 180 degrees
	ts.initializeDevice();
	ts.setRotation(0);
	// Offsets are *pre* rotation
	ts.scaleX(4.3);
	ts.scaleY(3.3);
	ts.offsetY(5);
	tft.fillScreen(Color::Black);
	// Attach the handler that gets called when a key is pressed.
	keyboard.onKeypress(handleKeypress);
	keyboard.setKeyData(ShinyKeypad::Decimal);

     cancel.onTap(doCancel);
     cancel.onPress(highlight);
     cancel.onRelease(lowlight);
     ok.onTap(doOk);
     ok.onPress(highlight);
     ok.onRelease(lowlight);
}

// The loop is as simple as sampling the touch screen and rendering
// the widgets. Nothing more.
void loop() {
	ts.sample();
     double enteredValue = 0;
     static uint32_t ts = 0;
     
     switch (mode) {
          case 0:
          	keyboard.render();
	          textArea.render();
               cancel.render();
               ok.render();
               break;
          case 1:
               tft.fillScreen(Color::Black);
               tft.setFont(Fonts::Roboto);
               tft.setCursor(0, 50);
               tft.setTextColor(Color::Yellow, Color::Black);
               tft.println("You entered: ");
               enteredValue = strtod(input, NULL);
               tft.println(enteredValue, 8);
               ts = millis();
               mode = 2;
               break;
           case 2:
               if (millis() - ts > 5000) {
                    tft.fillScreen(Color::Black);
                    input[0] = '|';
                    input[1] = 0;
                    ipos = 0;
                    keyboard.redraw();
                    textArea.redraw();
                    cancel.redraw();
                    ok.redraw();
                    mode = 0;
               }
     }
}
