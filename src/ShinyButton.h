#ifndef _SHINY_BUTTON_H
#define _SHINY_BUTTON_H

#include <DisplayCore.h>

class ShinyButton : public Widget {

    private:
        color_t _light;
        color_t _dark;
        color_t _lightHi;
        color_t _darkHi;

        color_t *_buffer;
        const char *_text;
        int _offset;
        const uint8_t *_font;
        color_t _fontColor;
        
    public:

        ShinyButton(Touch &t, DisplayCore &d, int x, int y, int w, int h, color_t light, color_t dark, color_t lightHi, color_t darkHi, const char *text, int offset, color_t tcol, const uint8_t *f) : Widget(t, d, x, y) {
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
            _lightHi = lightHi;
            _darkHi = darkHi;
            _offset = offset;
            _font = f;
            _fontColor = tcol;
        }

        void setPixel(int x, int y, color_t col);
        color_t colorAt(int x, int y);
        void draw(DisplayCore *dev, int x, int y);
        void setText(const char *t);
        void setBackground(color_t h, color_t l);
        void setHighlight(color_t h, color_t l);
        void setColor(color_t c);
};

#define KEYSIZE(X, Y) (scale * (X)), (scale * (Y))
#define KEYPOS(X, Y) (x + scale * (X)), (y + scale * (Y))

struct KeyboardCode {
    const char *keycap;
    int keycode;
};


// A super-class which combines many ShinyButtons to make a keyboard
class ShinyKeyboard : public Widget {
    private:
        ShinyButton btn_backtick;
        ShinyButton btn_1;
        ShinyButton btn_2;
        ShinyButton btn_3;
        ShinyButton btn_4;
        ShinyButton btn_5;
        ShinyButton btn_6;
        ShinyButton btn_7;
        ShinyButton btn_8;
        ShinyButton btn_9;
        ShinyButton btn_0;
        ShinyButton btn_minus;
        ShinyButton btn_equals;
        ShinyButton btn_backspace;
        ShinyButton btn_tab;
        ShinyButton btn_q;
        ShinyButton btn_w;
        ShinyButton btn_e;
        ShinyButton btn_r;
        ShinyButton btn_t;
        ShinyButton btn_y;
        ShinyButton btn_u;
        ShinyButton btn_i;
        ShinyButton btn_o;
        ShinyButton btn_p;
        ShinyButton btn_bktopn;
        ShinyButton btn_bktcls;
        ShinyButton btn_blank;
        ShinyButton btn_caps;
        ShinyButton btn_a;
        ShinyButton btn_s;
        ShinyButton btn_d;
        ShinyButton btn_f;
        ShinyButton btn_g;
        ShinyButton btn_h;
        ShinyButton btn_j;
        ShinyButton btn_k;
        ShinyButton btn_l;
        ShinyButton btn_semi;
        ShinyButton btn_apos;
        ShinyButton btn_hash;
        ShinyButton btn_return;
        ShinyButton btn_lshift;
        ShinyButton btn_bslash;
        ShinyButton btn_z;
        ShinyButton btn_x;
        ShinyButton btn_c;
        ShinyButton btn_v;
        ShinyButton btn_b;
        ShinyButton btn_n;
        ShinyButton btn_m;
        ShinyButton btn_comma;
        ShinyButton btn_stop;
        ShinyButton btn_slash;
        ShinyButton btn_rshift;
        ShinyButton btn_lctrl;
        ShinyButton btn_win;
        ShinyButton btn_lalt;
        ShinyButton btn_space;
        ShinyButton btn_ralt;
        ShinyButton btn_menu;
        ShinyButton btn_rctrl;

        int _scale;
        const uint8_t *_font;

        color_t _colHi;
        color_t _colLo;
        color_t _colPressHi;
        color_t _colPressLo;

        void setupKeyboardData();

        const struct KeyboardCode *_keycaps;
        int _mode;
        bool _modeLock;

        ShinyButton *buttons[62];

        void (*_onKeypress)(int);

    public:
        static const struct KeyboardCode UK[4*62];

        // Object based event handing (NEW)
        void handleTap(Event *e);
        void handlePress(Event *e);
        void handleRelease(Event *e);
//        void handleRepeat(Event *e);
//        void handleDrag(Event *e);

        ShinyKeyboard(Touch &ts, DisplayCore &dev, int x, int y, int scale, color_t colHi, color_t colLo, color_t colPressHi, color_t colPressLo, color_t colFont, const uint8_t *font);

        void draw(DisplayCore *dev, int x, int y);
        void render();
        void redraw();
        void setLocation(int x, int y);

        void setKeyData(const struct KeyboardCode *data) {
            _keycaps = data;
            setupKeyboardData();
            _redraw = true;
        }

        void setMode(int mode);

        void onKeypress(void (*func)(int)) {
            _onKeypress = func;
        }
};

class ShinyKeypad : public Widget {
    private:
        ShinyButton btn_1;
        ShinyButton btn_2;
        ShinyButton btn_3;
        ShinyButton btn_4;
        ShinyButton btn_5;
        ShinyButton btn_6;
        ShinyButton btn_7;
        ShinyButton btn_8;
        ShinyButton btn_9;
        ShinyButton btn_star;
        ShinyButton btn_0;
        ShinyButton btn_hash;

        int _scale;
        const uint8_t *_font;

        color_t _colHi;
        color_t _colLo;
        color_t _colPressHi;
        color_t _colPressLo;

        void setupKeyboardData();

        const struct KeyboardCode *_keycaps;
        int _mode;
        bool _modeLock;

        ShinyButton *buttons[12];

        void (*_onKeypress)(int);

    public:
        static const struct KeyboardCode Phone[12];
        static const struct KeyboardCode Decimal[12];

        // Object based event handing (NEW)
        void handleTap(Event *e);
        void handlePress(Event *e);
        void handleRelease(Event *e);
//        void handleRepeat(Event *e);
//        void handleDrag(Event *e);

        ShinyKeypad(Touch &ts, DisplayCore &dev, int x, int y, int scale, color_t colHi, color_t colLo, color_t colPressHi, color_t colPressLo, color_t colFont, const uint8_t *font);

        void draw(DisplayCore *dev, int x, int y);
        void render();
        void redraw();
        void setLocation(int x, int y);

        void setKeyData(const struct KeyboardCode *data) {
            _keycaps = data;
            setupKeyboardData();
            _redraw = true;
        }

        void setMode(int mode);

        void onKeypress(void (*func)(int)) {
            _onKeypress = func;
        }
};


#endif
