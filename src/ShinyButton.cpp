#include <ShinyButton.h>


void ShinyButton::setPixel(int x, int y, color_t col) {
    if (x < 0 || y < 0 || x >= _width || y >= _height) return;
    uint32_t offset = y * _width + x;
    _buffer[offset] = col;
}

color_t ShinyButton::colorAt(int x, int y) {
    if (x < 0 || y < 0 || x >= _width || y >= _height) return Color::Black;
    uint32_t offset = y * _width + x;
    return _buffer[offset];
}

void ShinyButton::draw(Cariad *dev, int x, int y) {

    color_t buf[_width * _height];
    _buffer = buf;

    int hi = _value > 0 ? _lightHi : _light;
    int lo = _value > 0 ? _darkHi : _dark;
                
    color_t midpoint = dev->mix(hi, lo, 128);
    openWindow(0, 0, _width, _height);
    for (int y = 0; y < _height; y++) {
        int rowcol = 0;
        if (y < (_height/2)) {
            rowcol = dev->mix(hi, midpoint, (y*255 / (_height/2)));
        } else {
            rowcol = dev->mix(lo, midpoint, ((y - (_height/2)) * 255 / (_height/2)));
        }
        for (int x = 0; x < _width; x++) {
            if ((x == 0) && (y == 0)) windowData(Color::Black);
            else if ((x == 0) && (y == _height-1)) windowData(Color::Black);
            else if ((x == _width-1) && (y == 0)) windowData(Color::Black);
            else if ((x == _width-1) && (y == _height-1)) windowData(Color::Black);
            else if ((x == 0) || (y == 0)) windowData(hi);
            else if ((x == _width-1) || (y == _height-1)) windowData(lo);
            else windowData(rowcol);
        }
    }
    closeWindow();
    setFont(_font);
    int fw = stringWidth(_text);
    int fh = stringHeight(_text);
    setTextColor(lo, lo);
    setCursor(_width / 2 - fw / 2 + 1, _height / 2 - fh / 2 + 1 + _offset);
    print(_text);
    setTextColor(_fontColor, _fontColor);
    setCursor(_width / 2 - fw / 2 - 1, _height / 2 - fh / 2 - 1 + _offset);
    print(_text);
    dev->openWindow(x, y, _width, _height);
    dev->windowData(buf, _width * _height);
    dev->closeWindow();
}

void ShinyButton::setText(const char *t) {
    _text = t;
    _redraw = true;
}

void ShinyButton::setBackground(color_t h, color_t l) {
    _light = h;
    _dark = l;
    _redraw = true;
}

void ShinyButton::setHighlight(color_t h, color_t l) {
    _lightHi = h;
    _darkHi = l;
    _redraw = true;
}

void ShinyButton::setColor(color_t c) {
    _fontColor = c;
    _redraw = true;
}

