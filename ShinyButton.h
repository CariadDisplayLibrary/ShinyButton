#ifndef _SHINY_BUTTON_H
#define _SHINY_BUTTON_H

#include <DisplayCore.h>

class ShinyButton : public Widget {

    private:
        color_t _light;
        color_t _dark;

        color_t *_buffer;
        const char *_text;
        int _offset;
        const uint8_t *_font;
        color_t _fontColor;
        
    public:

        ShinyButton(Touch &t, DisplayCore &d, int x, int y, int w, int h, color_t light, color_t dark, const char *text, int offset, color_t tcol, const uint8_t *f) : Widget(t, d, x, y) {
            _width = w;
            _height = h;
            _sense_x = 0;
            _sense_y = 0;
            _sense_w = w;
            _sense_h = h;
            _text = text;
            _touch = true;
            _light = light;
            _dark = dark;
            _offset = offset;
            _font = f;
            _fontColor = tcol;
        }

        void setPixel(int x, int y, color_t col);
        color_t colorAt(int x, int y);
        void draw(DisplayCore *dev, int x, int y);
        void setText(const char *t);
        void setBackground(color_t h, color_t l);
        void setColor(color_t c);
};

#endif
