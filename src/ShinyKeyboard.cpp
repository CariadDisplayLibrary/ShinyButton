#include <ShinyButton.h>

const struct KeyboardCode ShinyKeyboard::UK[4*62] = {
    
        {"`", '`'}, {"1", '1'}, {"2", '2'}, {"3", '3'}, {"4", '4'}, {"5", '5'}, {"6", '6'}, {"7", '7'}, {"8", '8'}, {"9", '9'}, {"0", '0'}, {"-", '-'}, {"=", '='}, {"<=", 8},
        {"=>", 11}, {"q", 'q'}, {"w", 'w'}, {"e", 'e'}, {"r", 'r'}, {"t", 't'}, {"y", 'y'}, {"u", 'u'}, {"i", 'i'}, {"o", 'o'}, {"p", 'p'}, {"[", '['}, {"]", ']'}, {"", 0},
        {"Caps", 0x101}, {"a", 'a'}, {"s", 's'}, {"d", 'd'}, {"f", 'f'}, {"g", 'g'}, {"h", 'h'}, {"j", 'j'}, {"k", 'k'}, {"l", 'l'}, {";", ';'}, {"'", '\''}, {"#", '#'}, {"Ret", 13},
        {"^", 0x102}, {"\\", '\\'}, {"z", 'z'}, {"x", 'x'}, {"c", 'c'}, {"v", 'v'}, {"b", 'b'}, {"n", 'n'}, {"m", 'm'}, {",", ','}, {".", '.'}, {"/", '/'}, {"^", 0x103},
        {"Ctrl", 0x104}, {"Gui", 0x105}, {"Alt", 0x106}, {"", ' '}, {"Alt", 0x107}, {"Menu", 0x108}, {"Ctrl", 0x109},
   
  
        {"`", '`'}, {"!", '!'}, {"\"", '"'}, {"#", '#'}, {"$", '$'}, {"%", '%'}, {"^", '^'}, {"&", '&'}, {"*", '*'}, {"(", '('}, {")", ')'}, {"_", '_'}, {"+", '+'}, {"<=", 8},
        {"=>", 11}, {"Q", 'Q'}, {"W", 'W'}, {"E", 'E'}, {"R", 'R'}, {"T", 'T'}, {"Y", 'Y'}, {"U", 'U'}, {"I", 'I'}, {"O", 'O'}, {"P", 'P'}, {"{", '{'}, {"}", '}'}, {"", 0},
        {"Caps", 0x101}, {"A", 'A'}, {"S", 'S'}, {"D", 'D'}, {"F", 'F'}, {"G", 'G'}, {"H", 'H'}, {"J", 'J'}, {"K", 'K'}, {"L", 'L'}, {":", ':'}, {"@", '@'}, {"~", '~'}, {"Ret", 13},
        {"^", 0x102}, {"|", '|'}, {"Z", 'Z'}, {"X", 'X'}, {"C", 'C'}, {"V", 'V'}, {"B", 'B'}, {"N", 'N'}, {"M", 'M'}, {"<", '<'}, {">", '>'}, {"?", '?'}, {"^", 0x103},
        {"Ctrl", 0x104}, {"Gui", 0x105}, {"Alt", 0x106}, {"", ' '}, {"Alt", 0x107}, {"Menu", 0x108}, {"Ctrl", 0x109},
 

        {"", 0}, {"", 0}, {"", 0}, {"", 0}, {"", 0}, {"", 0}, {"", 0}, {"", 0}, {"", 0}, {"", 0}, {"", 0}, {"", 0}, {"", 0}, {"<=", 8},
        {"=>", 11}, {"", 0}, {"", 0}, {"", 0}, {"", 0}, {"", 0}, {"", 0}, {"", 0}, {"", 0}, {"", 0}, {"", 0}, {"", 0}, {"", 0}, {"", 0},
        {"Caps", 0x101}, {"", 0}, {"", 0}, {"", 0}, {"", 0}, {"", 0}, {"", 0}, {"", 0}, {"", 0}, {"", 0}, {"", 0}, {"", 0}, {"", 0}, {"Ret", 13},
        {"^", 0x102}, {"", 0}, {"", 0}, {"", 0}, {"", 0}, {"", 0}, {"", 0}, {"", 0}, {"", 0}, {"", 0}, {"", 0}, {"", 0}, {"^", 0x103},
        {"Ctrl", 0x104}, {"Gui", 0x105}, {"Alt", 0x106}, {"", ' '}, {"Alt", 0x107}, {"Menu", 0x108}, {"Ctrl", 0x109},


        {"", 0}, {"", 0}, {"", 0}, {"", 0}, {"", 0}, {"", 0}, {"", 0}, {"", 0}, {"", 0}, {"", 0}, {"", 0}, {"", 0}, {"", 0}, {"<=", 8},
        {"=>", 11}, {"", 0}, {"", 0}, {"", 0}, {"", 0}, {"", 0}, {"", 0}, {"", 0}, {"", 0}, {"", 0}, {"", 0}, {"", 0}, {"", 0}, {"", 0},
        {"Caps", 0x101}, {"", 0}, {"", 0}, {"", 0}, {"", 0}, {"", 0}, {"", 0}, {"", 0}, {"", 0}, {"", 0}, {"", 0}, {"", 0}, {"", 0}, {"Ret", 13},
        {"^", 0x102}, {"", 0}, {"", 0}, {"", 0}, {"", 0}, {"", 0}, {"", 0}, {"", 0}, {"", 0}, {"", 0}, {"", 0}, {"", 0}, {"^", 0x103},
        {"Ctrl", 0x104}, {"Gui", 0x105}, {"Alt", 0x106}, {"", ' '}, {"Alt", 0x107}, {"Menu", 0x108}, {"Ctrl", 0x109}
};


ShinyKeyboard::ShinyKeyboard(Touch &ts, DisplayCore &dev, int x, int y, int scale, color_t colHi, color_t colLo, color_t colPressHi, color_t colPressLo, color_t colFont, const uint8_t *font)  : Widget(ts, dev, x, y),
            btn_backtick         (ts, dev, KEYPOS(0, 0),     KEYSIZE(4, 4),      colHi, colLo, colPressHi, colPressLo, "`", 0, colFont, font),
            btn_1                (ts, dev, KEYPOS(4, 0),     KEYSIZE(4, 4),      colHi, colLo, colPressHi, colPressLo, "1", 0, colFont, font),
            btn_2                (ts, dev, KEYPOS(8, 0),     KEYSIZE(4, 4),      colHi, colLo, colPressHi, colPressLo, "2", 0, colFont, font),
            btn_3                (ts, dev, KEYPOS(12, 0),    KEYSIZE(4, 4),      colHi, colLo, colPressHi, colPressLo, "3", 0, colFont, font),
            btn_4                (ts, dev, KEYPOS(16, 0),    KEYSIZE(4, 4),      colHi, colLo, colPressHi, colPressLo, "4", 0, colFont, font),
            btn_5                (ts, dev, KEYPOS(20, 0),    KEYSIZE(4, 4),      colHi, colLo, colPressHi, colPressLo, "5", 0, colFont, font),
            btn_6                (ts, dev, KEYPOS(24, 0),    KEYSIZE(4, 4),      colHi, colLo, colPressHi, colPressLo, "6", 0, colFont, font),
            btn_7                (ts, dev, KEYPOS(28, 0),    KEYSIZE(4, 4),      colHi, colLo, colPressHi, colPressLo, "7", 0, colFont, font),
            btn_8                (ts, dev, KEYPOS(32, 0),    KEYSIZE(4, 4),      colHi, colLo, colPressHi, colPressLo, "8", 0, colFont, font),
            btn_9                (ts, dev, KEYPOS(36, 0),    KEYSIZE(4, 4),      colHi, colLo, colPressHi, colPressLo, "9", 0, colFont, font),
            btn_0                (ts, dev, KEYPOS(40, 0),    KEYSIZE(4, 4),      colHi, colLo, colPressHi, colPressLo, "0", 0, colFont, font),
            btn_minus            (ts, dev, KEYPOS(44, 0),    KEYSIZE(4, 4),      colHi, colLo, colPressHi, colPressLo, "-", 0, colFont, font),
            btn_equals           (ts, dev, KEYPOS(48, 0),    KEYSIZE(4, 4),      colHi, colLo, colPressHi, colPressLo, "=", 0, colFont, font),
            btn_backspace        (ts, dev, KEYPOS(52, 0),    KEYSIZE(8, 4),      colHi, colLo, colPressHi, colPressLo, "<=", 0, colFont, font),
            btn_tab              (ts, dev, KEYPOS(0, 4),     KEYSIZE(6, 4),      colHi, colLo, colPressHi, colPressLo, "=>", 0, colFont, font),
            btn_q                (ts, dev, KEYPOS(6, 4),     KEYSIZE(4, 4),      colHi, colLo, colPressHi, colPressLo, "Q", 0, colFont, font),
            btn_w                (ts, dev, KEYPOS(10, 4),    KEYSIZE(4, 4),      colHi, colLo, colPressHi, colPressLo, "W", 0, colFont, font),
            btn_e                (ts, dev, KEYPOS(14, 4),    KEYSIZE(4, 4),      colHi, colLo, colPressHi, colPressLo, "E", 0, colFont, font),
            btn_r                (ts, dev, KEYPOS(18, 4),    KEYSIZE(4, 4),      colHi, colLo, colPressHi, colPressLo, "R", 0, colFont, font),
            btn_t                (ts, dev, KEYPOS(22, 4),    KEYSIZE(4, 4),      colHi, colLo, colPressHi, colPressLo, "T", 0, colFont, font),
            btn_y                (ts, dev, KEYPOS(26, 4),    KEYSIZE(4, 4),      colHi, colLo, colPressHi, colPressLo, "Y", 0, colFont, font),
            btn_u                (ts, dev, KEYPOS(30, 4),    KEYSIZE(4, 4),      colHi, colLo, colPressHi, colPressLo, "U", 0, colFont, font),
            btn_i                (ts, dev, KEYPOS(34, 4),    KEYSIZE(4, 4),      colHi, colLo, colPressHi, colPressLo, "I", 0, colFont, font),
            btn_o                (ts, dev, KEYPOS(38, 4),    KEYSIZE(4, 4),      colHi, colLo, colPressHi, colPressLo, "O", 0, colFont, font),
            btn_p                (ts, dev, KEYPOS(42, 4),    KEYSIZE(4, 4),      colHi, colLo, colPressHi, colPressLo, "P", 0, colFont, font),
            btn_bktopn           (ts, dev, KEYPOS(46, 4),    KEYSIZE(4, 4),      colHi, colLo, colPressHi, colPressLo, "[", 0, colFont, font),
            btn_bktcls           (ts, dev, KEYPOS(50, 4),    KEYSIZE(4, 4),      colHi, colLo, colPressHi, colPressLo, "]", 0, colFont, font),
            btn_blank            (ts, dev, KEYPOS(54, 4),    KEYSIZE(1, 4),      colHi, colLo, colPressHi, colPressLo, "", 0, colFont, font),
            btn_caps             (ts, dev, KEYPOS(0, 8),     KEYSIZE(7, 4),      colHi, colLo, colPressHi, colPressLo, "Caps", 0, colFont, font),
            btn_a                (ts, dev, KEYPOS(7, 8),     KEYSIZE(4, 4),      colHi, colLo, colPressHi, colPressLo, "A", 0, colFont, font),
            btn_s                (ts, dev, KEYPOS(11, 8),    KEYSIZE(4, 4),      colHi, colLo, colPressHi, colPressLo, "S", 0, colFont, font),
            btn_d                (ts, dev, KEYPOS(15, 8),    KEYSIZE(4, 4),      colHi, colLo, colPressHi, colPressLo, "D", 0, colFont, font),
            btn_f                (ts, dev, KEYPOS(19, 8),    KEYSIZE(4, 4),      colHi, colLo, colPressHi, colPressLo, "F", 0, colFont, font),
            btn_g                (ts, dev, KEYPOS(23, 8),    KEYSIZE(4, 4),      colHi, colLo, colPressHi, colPressLo, "G", 0, colFont, font),
            btn_h                (ts, dev, KEYPOS(27, 8),    KEYSIZE(4, 4),      colHi, colLo, colPressHi, colPressLo, "H", 0, colFont, font),
            btn_j                (ts, dev, KEYPOS(31, 8),    KEYSIZE(4, 4),      colHi, colLo, colPressHi, colPressLo, "J", 0, colFont, font),
            btn_k                (ts, dev, KEYPOS(35, 8),    KEYSIZE(4, 4),      colHi, colLo, colPressHi, colPressLo, "K", 0, colFont, font),
            btn_l                (ts, dev, KEYPOS(39, 8),    KEYSIZE(4, 4),      colHi, colLo, colPressHi, colPressLo, "L", 0, colFont, font),
            btn_semi             (ts, dev, KEYPOS(43, 8),    KEYSIZE(4, 4),      colHi, colLo, colPressHi, colPressLo, ";", 0, colFont, font),
            btn_apos             (ts, dev, KEYPOS(47, 8),    KEYSIZE(4, 4),      colHi, colLo, colPressHi, colPressLo, "'", 0, colFont, font),
            btn_hash             (ts, dev, KEYPOS(51, 8),    KEYSIZE(4, 4),      colHi, colLo, colPressHi, colPressLo, "#", 0, colFont, font),
            btn_return           (ts, dev, KEYPOS(55, 4),    KEYSIZE(5, 8),      colHi, colLo, colPressHi, colPressLo, "Ret", 0, colFont, font),
            btn_lshift           (ts, dev, KEYPOS(0, 12),    KEYSIZE(5, 4),      colHi, colLo, colPressHi, colPressLo, "^", 0, colFont, font),
            btn_bslash           (ts, dev, KEYPOS(5, 12),    KEYSIZE(4, 4),      colHi, colLo, colPressHi, colPressLo, "\\", 0, colFont, font),
            btn_z                (ts, dev, KEYPOS(9, 12),    KEYSIZE(4, 4),      colHi, colLo, colPressHi, colPressLo, "Z", 0, colFont, font),
            btn_x                (ts, dev, KEYPOS(13, 12),   KEYSIZE(4, 4),      colHi, colLo, colPressHi, colPressLo, "X", 0, colFont, font),
            btn_c                (ts, dev, KEYPOS(17, 12),   KEYSIZE(4, 4),      colHi, colLo, colPressHi, colPressLo, "C", 0, colFont, font),
            btn_v                (ts, dev, KEYPOS(21, 12),   KEYSIZE(4, 4),      colHi, colLo, colPressHi, colPressLo, "V", 0, colFont, font),
            btn_b                (ts, dev, KEYPOS(25, 12),   KEYSIZE(4, 4),      colHi, colLo, colPressHi, colPressLo, "B", 0, colFont, font),
            btn_n                (ts, dev, KEYPOS(29, 12),   KEYSIZE(4, 4),      colHi, colLo, colPressHi, colPressLo, "N", 0, colFont, font),
            btn_m                (ts, dev, KEYPOS(33, 12),   KEYSIZE(4, 4),      colHi, colLo, colPressHi, colPressLo, "M", 0, colFont, font),
            btn_comma            (ts, dev, KEYPOS(37, 12),   KEYSIZE(4, 4),      colHi, colLo, colPressHi, colPressLo, ",", 0, colFont, font),
            btn_stop             (ts, dev, KEYPOS(41, 12),   KEYSIZE(4, 4),      colHi, colLo, colPressHi, colPressLo, ".", 0, colFont, font),
            btn_slash            (ts, dev, KEYPOS(45, 12),   KEYSIZE(4, 4),      colHi, colLo, colPressHi, colPressLo, "/", 0, colFont, font),
            btn_rshift           (ts, dev, KEYPOS(49, 12),   KEYSIZE(11, 4),     colHi, colLo, colPressHi, colPressLo, "^", 0, colFont, font),
            btn_lctrl            (ts, dev, KEYPOS(0, 16),    KEYSIZE(6, 4),      colHi, colLo, colPressHi, colPressLo, "Ctrl", 0, colFont, font),
            btn_win              (ts, dev, KEYPOS(6, 16),    KEYSIZE(5, 4),      colHi, colLo, colPressHi, colPressLo, "Win", 0, colFont, font),
            btn_lalt             (ts, dev, KEYPOS(11, 16),   KEYSIZE(5, 4),      colHi, colLo, colPressHi, colPressLo, "Alt", 0, colFont, font),
            btn_space            (ts, dev, KEYPOS(16, 16),   KEYSIZE(24,4),      colHi, colLo, colPressHi, colPressLo, "", 0, colFont, font),
            btn_ralt             (ts, dev, KEYPOS(40, 16),   KEYSIZE(5, 4),      colHi, colLo, colPressHi, colPressLo, "Alt", 0, colFont, font),
            btn_menu             (ts, dev, KEYPOS(45, 16),   KEYSIZE(7, 4),      colHi, colLo, colPressHi, colPressLo, "Menu", 0, colFont, font),
            btn_rctrl            (ts, dev, KEYPOS(52, 16),   KEYSIZE(8, 4),      colHi, colLo, colPressHi, colPressLo, "Ctrl", 0, colFont, font) {
    _scale = scale;
    _font = font;
    _colHi = colHi;
    _colLo = colLo;
    _colPressHi = colPressHi;
    _colPressLo = colPressLo;

    int i = 0;

    buttons[i++] = &btn_backtick;
    buttons[i++] = &btn_1;
    buttons[i++] = &btn_2;
    buttons[i++] = &btn_3;
    buttons[i++] = &btn_4;
    buttons[i++] = &btn_5;
    buttons[i++] = &btn_6;
    buttons[i++] = &btn_7;
    buttons[i++] = &btn_8;
    buttons[i++] = &btn_9;
    buttons[i++] = &btn_0;
    buttons[i++] = &btn_minus;
    buttons[i++] = &btn_equals;
    buttons[i++] = &btn_backspace;

    buttons[i++] = &btn_tab;
    buttons[i++] = &btn_q;
    buttons[i++] = &btn_w;
    buttons[i++] = &btn_e;
    buttons[i++] = &btn_r;
    buttons[i++] = &btn_t;
    buttons[i++] = &btn_y;
    buttons[i++] = &btn_u;
    buttons[i++] = &btn_i;
    buttons[i++] = &btn_o;
    buttons[i++] = &btn_p;
    buttons[i++] = &btn_bktopn;
    buttons[i++] = &btn_bktcls;
    buttons[i++] = &btn_blank;

    buttons[i++] = &btn_caps;
    buttons[i++] = &btn_a;
    buttons[i++] = &btn_s;
    buttons[i++] = &btn_d;
    buttons[i++] = &btn_f;
    buttons[i++] = &btn_g;
    buttons[i++] = &btn_h;
    buttons[i++] = &btn_j;
    buttons[i++] = &btn_k;
    buttons[i++] = &btn_l;
    buttons[i++] = &btn_semi;
    buttons[i++] = &btn_apos;
    buttons[i++] = &btn_hash;

    buttons[i++] = &btn_return;

    buttons[i++] = &btn_lshift;
    buttons[i++] = &btn_bslash;
    buttons[i++] = &btn_z;
    buttons[i++] = &btn_x;
    buttons[i++] = &btn_c;
    buttons[i++] = &btn_v;
    buttons[i++] = &btn_b;
    buttons[i++] = &btn_n;
    buttons[i++] = &btn_m;
    buttons[i++] = &btn_comma;
    buttons[i++] = &btn_stop;
    buttons[i++] = &btn_slash;
    buttons[i++] = &btn_rshift;
    buttons[i++] = &btn_lctrl;
    buttons[i++] = &btn_win;
    buttons[i++] = &btn_lalt;
    buttons[i++] = &btn_space;
    buttons[i++] = &btn_ralt;
    buttons[i++] = &btn_menu;
    buttons[i++] = &btn_rctrl;

    _keycaps = UK;

    _mode = 0;
    _modeLock = false;

    for (i = 0; i < 62; i++) {
        buttons[i]->setEventObject(this);
    }

    _onKeypress = NULL;

    setMode(0);

}


void ShinyKeyboard::draw(DisplayCore *dev, int x, int y) {
}

void ShinyKeyboard::render() {
    for (int i = 0; i < 62; i++) {
        buttons[i]->render();
    }
}

void ShinyKeyboard::redraw() {
    for (int i = 0; i < 62; i++) {
        buttons[i]->redraw();
    }
}

void ShinyKeyboard::setLocation(int x, int y) {
    int scale = _scale; // Needed for the KEYPOS macro
    Widget::setLocation(x, y);

    btn_backtick.setLocation(KEYPOS(0, 0));
    btn_1.setLocation(KEYPOS(4, 0));
    btn_2.setLocation(KEYPOS(8, 0));
    btn_3.setLocation(KEYPOS(12, 0));
    btn_4.setLocation(KEYPOS(16, 0));
    btn_5.setLocation(KEYPOS(20, 0));
    btn_6.setLocation(KEYPOS(24, 0));
    btn_7.setLocation(KEYPOS(28, 0));
    btn_8.setLocation(KEYPOS(32, 0));
    btn_9.setLocation(KEYPOS(36, 0));
    btn_0.setLocation(KEYPOS(40, 0));
    btn_minus.setLocation(KEYPOS(44, 0));
    btn_equals.setLocation(KEYPOS(48, 0));
    btn_backspace.setLocation(KEYPOS(52, 0));

    btn_tab.setLocation(KEYPOS(0, 4));
    btn_q.setLocation(KEYPOS(6, 4));
    btn_w.setLocation(KEYPOS(10, 4));
    btn_e.setLocation(KEYPOS(14, 4));
    btn_r.setLocation(KEYPOS(18, 4));
    btn_t.setLocation(KEYPOS(22, 4));
    btn_y.setLocation(KEYPOS(26, 4));
    btn_u.setLocation(KEYPOS(30, 4));
    btn_i.setLocation(KEYPOS(34, 4));
    btn_o.setLocation(KEYPOS(38, 4));
    btn_p.setLocation(KEYPOS(42, 4));
    btn_bktopn.setLocation(KEYPOS(46, 4));
    btn_bktcls.setLocation(KEYPOS(50, 4));
    btn_blank.setLocation(KEYPOS(54, 4));

    btn_caps.setLocation(KEYPOS(0, 8));
    btn_a.setLocation(KEYPOS(7, 8));
    btn_s.setLocation(KEYPOS(11, 8));
    btn_d.setLocation(KEYPOS(15, 8));
    btn_f.setLocation(KEYPOS(19, 8));
    btn_g.setLocation(KEYPOS(23, 8));
    btn_h.setLocation(KEYPOS(27, 8));
    btn_j.setLocation(KEYPOS(31, 8));
    btn_k.setLocation(KEYPOS(35, 8));
    btn_l.setLocation(KEYPOS(39, 8));
    btn_semi.setLocation(KEYPOS(43, 8));
    btn_apos.setLocation(KEYPOS(47, 8));
    btn_hash.setLocation(KEYPOS(51, 8));

    btn_return.setLocation(KEYPOS(55, 4));

    btn_lshift.setLocation(KEYPOS(0, 12));
    btn_bslash.setLocation(KEYPOS(5, 12));
    btn_z.setLocation(KEYPOS(9, 12));
    btn_x.setLocation(KEYPOS(13, 12));
    btn_c.setLocation(KEYPOS(17, 12));
    btn_v.setLocation(KEYPOS(21, 12));
    btn_b.setLocation(KEYPOS(25, 12));
    btn_n.setLocation(KEYPOS(29, 12));
    btn_m.setLocation(KEYPOS(33, 12));
    btn_comma.setLocation(KEYPOS(37, 12));
    btn_stop.setLocation(KEYPOS(41, 12));
    btn_slash.setLocation(KEYPOS(45, 12));
    btn_rshift.setLocation(KEYPOS(49, 12));

    btn_lctrl.setLocation(KEYPOS(0, 16));
    btn_win.setLocation(KEYPOS(6, 12));
    btn_lalt.setLocation(KEYPOS(11, 16));
    btn_space.setLocation(KEYPOS(16, 16));
    btn_ralt.setLocation(KEYPOS(40, 16));
    btn_menu.setLocation(KEYPOS(45, 16));
    btn_rctrl.setLocation(KEYPOS(52, 16));
}

void ShinyKeyboard::handlePress(Event *e) {
    ShinyButton *w = (ShinyButton *)e->source;
    w->setValue(1);
}

void ShinyKeyboard::handleRelease(Event *e) {
    ShinyButton *w = (ShinyButton *)e->source;
    w->setValue(0);
}

void ShinyKeyboard::handleTap(Event *e) {
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

void ShinyKeyboard::setupKeyboardData() {
    int offset = _mode * 62;
    for (int i = 0; i < 62; i++) {
        buttons[i]->setUserValue(_keycaps[offset + i].keycode);
        buttons[i]->setText(_keycaps[offset + i].keycap);
    }
}


void ShinyKeyboard::setMode(int mode) {
    _mode = mode;
    setupKeyboardData();
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
}
