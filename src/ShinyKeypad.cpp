#include <ShinyButton.h>

const struct KeyboardCode ShinyKeypad::Phone[4*3] = {
        {"1", '1'}, {"2", '2'}, {"3", '3'}, 
        {"4", '4'}, {"5", '5'}, {"6", '6'},
        {"7", '7'}, {"8", '8'}, {"9", '9'},
        {"*", '*'}, {"0", '0'}, {"#", '#'},
};

const struct KeyboardCode ShinyKeypad::Decimal[4*3] = {
        {"1", '1'}, {"2", '2'}, {"3", '3'}, 
        {"4", '4'}, {"5", '5'}, {"6", '6'},
        {"7", '7'}, {"8", '8'}, {"9", '9'},
        {"<", 8}, {"0", '0'}, {".", '.'},
};


ShinyKeypad::ShinyKeypad(Touch &ts, Cariad &dev, int x, int y, int scale, color_t colHi, color_t colLo, color_t colPressHi, color_t colPressLo, color_t colFont, const uint8_t *font)  : Widget(ts, dev, x, y),
            btn_1                (ts, dev, KEYPOS(0, 0),     KEYSIZE(4, 4),      colHi, colLo, colPressHi, colPressLo, "1", 0, colFont, font),
            btn_2                (ts, dev, KEYPOS(4, 0),     KEYSIZE(4, 4),      colHi, colLo, colPressHi, colPressLo, "2", 0, colFont, font),
            btn_3                (ts, dev, KEYPOS(8, 0),     KEYSIZE(4, 4),      colHi, colLo, colPressHi, colPressLo, "3", 0, colFont, font),
            btn_4                (ts, dev, KEYPOS(0, 4),    KEYSIZE(4, 4),      colHi, colLo, colPressHi, colPressLo, "4", 0, colFont, font),
            btn_5                (ts, dev, KEYPOS(4, 4),    KEYSIZE(4, 4),      colHi, colLo, colPressHi, colPressLo, "5", 0, colFont, font),
            btn_6                (ts, dev, KEYPOS(8, 4),    KEYSIZE(4, 4),      colHi, colLo, colPressHi, colPressLo, "6", 0, colFont, font),
            btn_7                (ts, dev, KEYPOS(0, 8),    KEYSIZE(4, 4),      colHi, colLo, colPressHi, colPressLo, "7", 0, colFont, font),
            btn_8                (ts, dev, KEYPOS(4, 8),    KEYSIZE(4, 4),      colHi, colLo, colPressHi, colPressLo, "8", 0, colFont, font),
            btn_9                (ts, dev, KEYPOS(8, 8),    KEYSIZE(4, 4),      colHi, colLo, colPressHi, colPressLo, "9", 0, colFont, font),
            btn_star             (ts, dev, KEYPOS(0, 12),    KEYSIZE(4, 4),      colHi, colLo, colPressHi, colPressLo, "*", 0, colFont, font),
            btn_0                (ts, dev, KEYPOS(4, 12),    KEYSIZE(4, 4),      colHi, colLo, colPressHi, colPressLo, "0", 0, colFont, font),
            btn_hash             (ts, dev, KEYPOS(8, 12),    KEYSIZE(4, 4),      colHi, colLo, colPressHi, colPressLo, "#", 0, colFont, font)
    {
    _scale = scale;
    _font = font;
    _colHi = colHi;
    _colLo = colLo;
    _colPressHi = colPressHi;
    _colPressLo = colPressLo;

    int i = 0;

    buttons[i++] = &btn_1;
    buttons[i++] = &btn_2;
    buttons[i++] = &btn_3;
    buttons[i++] = &btn_4;
    buttons[i++] = &btn_5;
    buttons[i++] = &btn_6;
    buttons[i++] = &btn_7;
    buttons[i++] = &btn_8;
    buttons[i++] = &btn_9;
    buttons[i++] = &btn_star;
    buttons[i++] = &btn_0;
    buttons[i++] = &btn_hash;

    _keycaps = Phone;

    _mode = 0;
    _modeLock = false;

    for (i = 0; i < 12; i++) {
        buttons[i]->setEventObject(this);
    }

    _onKeypress = NULL;

    setMode(0);

}

void ShinyKeypad::draw(Cariad *dev, int x, int y) {
}

void ShinyKeypad::render() {
    for (int i = 0; i < 12; i++) {
        buttons[i]->render();
    }
}

void ShinyKeypad::redraw() {
    for (int i = 0; i < 12; i++) {
        buttons[i]->redraw();
    }
}

void ShinyKeypad::setLocation(int x, int y) {
    int scale = _scale; // Needed for the KEYPOS macro
    Widget::setLocation(x, y);

    btn_1.setLocation(KEYPOS(0, 0));
    btn_2.setLocation(KEYPOS(4, 0));
    btn_3.setLocation(KEYPOS(8, 0));
    btn_4.setLocation(KEYPOS(0, 4));
    btn_5.setLocation(KEYPOS(4, 4));
    btn_6.setLocation(KEYPOS(8, 4));
    btn_7.setLocation(KEYPOS(0, 8));
    btn_8.setLocation(KEYPOS(4, 8));
    btn_9.setLocation(KEYPOS(8, 8));
    btn_star.setLocation(KEYPOS(0, 12));
    btn_0.setLocation(KEYPOS(4, 12));
    btn_hash.setLocation(KEYPOS(8, 12));
}

void ShinyKeypad::handlePress(Event *e) {
    ShinyButton *w = (ShinyButton *)e->source;
    w->setValue(1);
}

void ShinyKeypad::handleRelease(Event *e) {
    ShinyButton *w = (ShinyButton *)e->source;
    w->setValue(0);
}

void ShinyKeypad::handleTap(Event *e) {
    ShinyButton *w = (ShinyButton *)e->source;
    int keycode = w->getUserValue();
    switch (keycode) {

        // Mode changing keys

        case 0x101: // Caps lock
            if (_mode == 1) {
                setMode(0);
                _modeLock = false;
            } else {
                setMode(1);
                _modeLock = true;
            }
            break;
        case 0x102: // Left Shift
        case 0x103: // Right Shift
            if (_mode == 1) {
                setMode(0);
            } else {
                setMode(1);
            }
            _modeLock = false;
            break;
        case 0x104: // Left Ctrl
        case 0x109: // Right Ctrl
            if (_mode == 2) {
                setMode(0);
            } else {
                setMode(2);
            }
            _modeLock = false;
            break;
        case 0x106: // Left Alt
        case 0x107: // Right Alt
            if (_mode == 3) {
                setMode(0);
            } else {
                setMode(3);
            }
            _modeLock = false;
            break;

        // Special keys

        case 8: // Backspace
            break;
        case 11: // Tab
            break;
        case 13: // Return
            break;
        case 0x105: // Gui
            break;
        case 0x108: // Menu
            break;

        // Standard character keys

        default:
            if (!_modeLock) setMode(0);
            break;

    }

    if (_onKeypress) _onKeypress(keycode);
}

void ShinyKeypad::setupKeyboardData() {
    int offset = 0; // We don't do modes yet on keypads. _mode * 12;
    for (int i = 0; i < 12; i++) {
        buttons[i]->setUserValue(_keycaps[offset + i].keycode);
        buttons[i]->setText(_keycaps[offset + i].keycap);
    }
}


void ShinyKeypad::setMode(int mode) {
// Again - no modes.
    _mode = mode;
    setupKeyboardData();
#if 0
    switch (mode) {
        case 0: // Normal
            btn_caps.setBackground(Color::Gray70, Color::Gray30);
            btn_lshift.setBackground(Color::Gray70, Color::Gray30);
            btn_rshift.setBackground(Color::Gray70, Color::Gray30);
            btn_lctrl.setBackground(Color::Gray70, Color::Gray30);
            btn_win.setBackground(Color::Gray70, Color::Gray30);
            btn_lalt.setBackground(Color::Gray70, Color::Gray30);
            btn_ralt.setBackground(Color::Gray70, Color::Gray30);
            btn_menu.setBackground(Color::Gray70, Color::Gray30);
            btn_rctrl.setBackground(Color::Gray70, Color::Gray30);
            break;
        case 1: // Shift
            btn_caps.setBackground(Color::Gray30, Color::Gray70);
            btn_lshift.setBackground(Color::Gray30, Color::Gray70);
            btn_rshift.setBackground(Color::Gray30, Color::Gray70);
            btn_lctrl.setBackground(Color::Gray70, Color::Gray30);
            btn_win.setBackground(Color::Gray70, Color::Gray30);
            btn_lalt.setBackground(Color::Gray70, Color::Gray30);
            btn_ralt.setBackground(Color::Gray70, Color::Gray30);
            btn_menu.setBackground(Color::Gray70, Color::Gray30);
            btn_rctrl.setBackground(Color::Gray70, Color::Gray30);
            break;
        case 2: // Ctrl
            btn_caps.setBackground(Color::Gray70, Color::Gray30);
            btn_lshift.setBackground(Color::Gray70, Color::Gray30);
            btn_rshift.setBackground(Color::Gray70, Color::Gray30);
            btn_lctrl.setBackground(Color::Gray30, Color::Gray70);
            btn_win.setBackground(Color::Gray70, Color::Gray30);
            btn_lalt.setBackground(Color::Gray70, Color::Gray30);
            btn_ralt.setBackground(Color::Gray70, Color::Gray30);
            btn_menu.setBackground(Color::Gray70, Color::Gray30);
            btn_rctrl.setBackground(Color::Gray30, Color::Gray70);
            break;
        case 3: // Alt
            btn_caps.setBackground(Color::Gray70, Color::Gray30);
            btn_lshift.setBackground(Color::Gray70, Color::Gray30);
            btn_rshift.setBackground(Color::Gray70, Color::Gray30);
            btn_lctrl.setBackground(Color::Gray70, Color::Gray30);
            btn_win.setBackground(Color::Gray70, Color::Gray30);
            btn_lalt.setBackground(Color::Gray30, Color::Gray70);
            btn_ralt.setBackground(Color::Gray30, Color::Gray70);
            btn_menu.setBackground(Color::Gray70, Color::Gray30);
            btn_rctrl.setBackground(Color::Gray70, Color::Gray30);
            break;
    }
#endif
}
