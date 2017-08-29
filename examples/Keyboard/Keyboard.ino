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

bool tempShift = false;
bool textUpdate = true;

// Size and font to use for different parts
#define FONT_HUGE  Fonts::LiberationSans20
#define FONT_LARGE Fonts::LiberationSans14
#define FONT_SMALL Fonts::LiberationSans10

// Location on the screen of the keyboard
#define KBY 128
#define KBX 8

// The scale of the keyboard. Each key has a size (4x4 for a normal character key) and that
// size is multiplied by this scale factor to get the pixel size. The whole keyboard is 60x20 before scaling.
#define SCALE 5

// Macros to calculate key location and size from the keyboard position and scale
#define KEYSIZE(X, Y) (SCALE * (X)), (SCALE * (Y))
#define KEYPOS(X, Y) (KBX + SCALE * (X)), (KBY + SCALE * (Y))

// All the keyboard buttons
ShinyButton btn_backtick         (ts, tft, KEYPOS(0, 0),     KEYSIZE(4, 4),      Color::Gray70, Color::Gray30, "`", 0, Color::White, FONT_LARGE);
ShinyButton btn_1                (ts, tft, KEYPOS(4, 0),     KEYSIZE(4, 4),      Color::Gray70, Color::Gray30, "1", 0, Color::White, FONT_LARGE);
ShinyButton btn_2                (ts, tft, KEYPOS(8, 0),     KEYSIZE(4, 4),      Color::Gray70, Color::Gray30, "2", 0, Color::White, FONT_LARGE);
ShinyButton btn_3                (ts, tft, KEYPOS(12, 0),    KEYSIZE(4, 4),      Color::Gray70, Color::Gray30, "3", 0, Color::White, FONT_LARGE);
ShinyButton btn_4                (ts, tft, KEYPOS(16, 0),    KEYSIZE(4, 4),      Color::Gray70, Color::Gray30, "4", 0, Color::White, FONT_LARGE);
ShinyButton btn_5                (ts, tft, KEYPOS(20, 0),    KEYSIZE(4, 4),      Color::Gray70, Color::Gray30, "5", 0, Color::White, FONT_LARGE);
ShinyButton btn_6                (ts, tft, KEYPOS(24, 0),    KEYSIZE(4, 4),      Color::Gray70, Color::Gray30, "6", 0, Color::White, FONT_LARGE);
ShinyButton btn_7                (ts, tft, KEYPOS(28, 0),    KEYSIZE(4, 4),      Color::Gray70, Color::Gray30, "7", 0, Color::White, FONT_LARGE);
ShinyButton btn_8                (ts, tft, KEYPOS(32, 0),    KEYSIZE(4, 4),      Color::Gray70, Color::Gray30, "8", 0, Color::White, FONT_LARGE);
ShinyButton btn_9                (ts, tft, KEYPOS(36, 0),    KEYSIZE(4, 4),      Color::Gray70, Color::Gray30, "9", 0, Color::White, FONT_LARGE);
ShinyButton btn_0                (ts, tft, KEYPOS(40, 0),    KEYSIZE(4, 4),      Color::Gray70, Color::Gray30, "0", 0, Color::White, FONT_LARGE);
ShinyButton btn_minus            (ts, tft, KEYPOS(44, 0),    KEYSIZE(4, 4),      Color::Gray70, Color::Gray30, "-", 0, Color::White, FONT_LARGE);
ShinyButton btn_equals           (ts, tft, KEYPOS(48, 0),    KEYSIZE(4, 4),      Color::Gray70, Color::Gray30, "=", 0, Color::White, FONT_LARGE);
ShinyButton btn_backspace        (ts, tft, KEYPOS(52, 0),    KEYSIZE(8, 4),      Color::Gray70, Color::Gray30, "<=", 0, Color::White, FONT_LARGE);

ShinyButton btn_tab              (ts, tft, KEYPOS(0, 4),     KEYSIZE(6, 4),      Color::Gray70, Color::Gray30, "=>", 0, Color::White, FONT_LARGE);
ShinyButton btn_q                (ts, tft, KEYPOS(6, 4),     KEYSIZE(4, 4),      Color::Gray70, Color::Gray30, "Q", 0, Color::White, FONT_LARGE);
ShinyButton btn_w                (ts, tft, KEYPOS(10, 4),    KEYSIZE(4, 4),      Color::Gray70, Color::Gray30, "W", 0, Color::White, FONT_LARGE);
ShinyButton btn_e                (ts, tft, KEYPOS(14, 4),    KEYSIZE(4, 4),      Color::Gray70, Color::Gray30, "E", 0, Color::White, FONT_LARGE);
ShinyButton btn_r                (ts, tft, KEYPOS(18, 4),    KEYSIZE(4, 4),      Color::Gray70, Color::Gray30, "R", 0, Color::White, FONT_LARGE);
ShinyButton btn_t                (ts, tft, KEYPOS(22, 4),    KEYSIZE(4, 4),      Color::Gray70, Color::Gray30, "T", 0, Color::White, FONT_LARGE);
ShinyButton btn_y                (ts, tft, KEYPOS(26, 4),    KEYSIZE(4, 4),      Color::Gray70, Color::Gray30, "Y", 0, Color::White, FONT_LARGE);
ShinyButton btn_u                (ts, tft, KEYPOS(30, 4),    KEYSIZE(4, 4),      Color::Gray70, Color::Gray30, "U", 0, Color::White, FONT_LARGE);
ShinyButton btn_i                (ts, tft, KEYPOS(34, 4),    KEYSIZE(4, 4),      Color::Gray70, Color::Gray30, "I", 0, Color::White, FONT_LARGE);
ShinyButton btn_o                (ts, tft, KEYPOS(38, 4),    KEYSIZE(4, 4),      Color::Gray70, Color::Gray30, "O", 0, Color::White, FONT_LARGE);
ShinyButton btn_p                (ts, tft, KEYPOS(42, 4),    KEYSIZE(4, 4),      Color::Gray70, Color::Gray30, "P", 0, Color::White, FONT_LARGE);
ShinyButton btn_bktopn           (ts, tft, KEYPOS(46, 4),    KEYSIZE(4, 4),      Color::Gray70, Color::Gray30, "[", 0, Color::White, FONT_LARGE);
ShinyButton btn_bktcls           (ts, tft, KEYPOS(50, 4),    KEYSIZE(4, 4),      Color::Gray70, Color::Gray30, "]", 0, Color::White, FONT_LARGE);
ShinyButton btn_blank            (ts, tft, KEYPOS(54, 4),    KEYSIZE(1, 4),      Color::Gray70, Color::Gray30, "", 0, Color::White, FONT_LARGE);

ShinyButton btn_caps             (ts, tft, KEYPOS(0, 8),     KEYSIZE(7, 4),      Color::Gray70, Color::Gray30, "Caps", 0, Color::White, FONT_SMALL);
ShinyButton btn_a                (ts, tft, KEYPOS(7, 8),     KEYSIZE(4, 4),      Color::Gray70, Color::Gray30, "A", 0, Color::White, FONT_LARGE);
ShinyButton btn_s                (ts, tft, KEYPOS(11, 8),    KEYSIZE(4, 4),      Color::Gray70, Color::Gray30, "S", 0, Color::White, FONT_LARGE);
ShinyButton btn_d                (ts, tft, KEYPOS(15, 8),    KEYSIZE(4, 4),      Color::Gray70, Color::Gray30, "D", 0, Color::White, FONT_LARGE);
ShinyButton btn_f                (ts, tft, KEYPOS(19, 8),    KEYSIZE(4, 4),      Color::Gray70, Color::Gray30, "F", 0, Color::White, FONT_LARGE);
ShinyButton btn_g                (ts, tft, KEYPOS(23, 8),    KEYSIZE(4, 4),      Color::Gray70, Color::Gray30, "G", 0, Color::White, FONT_LARGE);
ShinyButton btn_h                (ts, tft, KEYPOS(27, 8),    KEYSIZE(4, 4),      Color::Gray70, Color::Gray30, "H", 0, Color::White, FONT_LARGE);
ShinyButton btn_j                (ts, tft, KEYPOS(31, 8),    KEYSIZE(4, 4),      Color::Gray70, Color::Gray30, "J", 0, Color::White, FONT_LARGE);
ShinyButton btn_k                (ts, tft, KEYPOS(35, 8),    KEYSIZE(4, 4),      Color::Gray70, Color::Gray30, "K", 0, Color::White, FONT_LARGE);
ShinyButton btn_l                (ts, tft, KEYPOS(39, 8),    KEYSIZE(4, 4),      Color::Gray70, Color::Gray30, "L", 0, Color::White, FONT_LARGE);
ShinyButton btn_semi             (ts, tft, KEYPOS(43, 8),    KEYSIZE(4, 4),      Color::Gray70, Color::Gray30, ";", 0, Color::White, FONT_LARGE);
ShinyButton btn_apos             (ts, tft, KEYPOS(47, 8),    KEYSIZE(4, 4),      Color::Gray70, Color::Gray30, "'", 0, Color::White, FONT_LARGE);
ShinyButton btn_hash             (ts, tft, KEYPOS(51, 8),    KEYSIZE(4, 4),      Color::Gray70, Color::Gray30, "#", 0, Color::White, FONT_LARGE);

ShinyButton btn_return           (ts, tft, KEYPOS(55, 4),    KEYSIZE(5, 8),      Color::Gray70, Color::Gray30, "Ret", 0, Color::White, FONT_SMALL);

ShinyButton btn_lshift           (ts, tft, KEYPOS(0, 12),    KEYSIZE(5, 4),      Color::Gray70, Color::Gray30, "^", 0, Color::White, FONT_LARGE);
ShinyButton btn_bslash           (ts, tft, KEYPOS(5, 12),    KEYSIZE(4, 4),      Color::Gray70, Color::Gray30, "\\", 0, Color::White, FONT_LARGE);
ShinyButton btn_z                (ts, tft, KEYPOS(9, 12),    KEYSIZE(4, 4),      Color::Gray70, Color::Gray30, "Z", 0, Color::White, FONT_LARGE);
ShinyButton btn_x                (ts, tft, KEYPOS(13, 12),   KEYSIZE(4, 4),      Color::Gray70, Color::Gray30, "X", 0, Color::White, FONT_LARGE);
ShinyButton btn_c                (ts, tft, KEYPOS(17, 12),   KEYSIZE(4, 4),      Color::Gray70, Color::Gray30, "C", 0, Color::White, FONT_LARGE);
ShinyButton btn_v                (ts, tft, KEYPOS(21, 12),   KEYSIZE(4, 4),      Color::Gray70, Color::Gray30, "V", 0, Color::White, FONT_LARGE);
ShinyButton btn_b                (ts, tft, KEYPOS(25, 12),   KEYSIZE(4, 4),      Color::Gray70, Color::Gray30, "B", 0, Color::White, FONT_LARGE);
ShinyButton btn_n                (ts, tft, KEYPOS(29, 12),   KEYSIZE(4, 4),      Color::Gray70, Color::Gray30, "N", 0, Color::White, FONT_LARGE);
ShinyButton btn_m                (ts, tft, KEYPOS(33, 12),   KEYSIZE(4, 4),      Color::Gray70, Color::Gray30, "M", 0, Color::White, FONT_LARGE);
ShinyButton btn_comma            (ts, tft, KEYPOS(37, 12),   KEYSIZE(4, 4),      Color::Gray70, Color::Gray30, ",", 0, Color::White, FONT_LARGE);
ShinyButton btn_stop             (ts, tft, KEYPOS(41, 12),   KEYSIZE(4, 4),      Color::Gray70, Color::Gray30, ".", 0, Color::White, FONT_LARGE);
ShinyButton btn_slash            (ts, tft, KEYPOS(45, 12),   KEYSIZE(4, 4),      Color::Gray70, Color::Gray30, "/", 0, Color::White, FONT_LARGE);
ShinyButton btn_rshift           (ts, tft, KEYPOS(49, 12),   KEYSIZE(11, 4),     Color::Gray70, Color::Gray30, "^", 0, Color::White, FONT_LARGE);

ShinyButton btn_lctrl            (ts, tft, KEYPOS(0, 16),    KEYSIZE(6, 4),      Color::Gray70, Color::Gray30, "Ctrl", 0, Color::White, FONT_SMALL);
ShinyButton btn_win              (ts, tft, KEYPOS(6, 16),    KEYSIZE(5, 4),      Color::Gray70, Color::Gray30, "Win", 0, Color::White, FONT_SMALL);
ShinyButton btn_lalt             (ts, tft, KEYPOS(11, 16),   KEYSIZE(5, 4),      Color::Gray70, Color::Gray30, "Alt", 0, Color::White, FONT_SMALL);
ShinyButton btn_space            (ts, tft, KEYPOS(16, 16),   KEYSIZE(24,4),      Color::Gray70, Color::Gray30, "", 0, Color::White, FONT_SMALL);
ShinyButton btn_ralt             (ts, tft, KEYPOS(40, 16),   KEYSIZE(5, 4),      Color::Gray70, Color::Gray30, "Alt", 0, Color::White, FONT_SMALL);
ShinyButton btn_menu             (ts, tft, KEYPOS(45, 16),   KEYSIZE(7, 4),      Color::Gray70, Color::Gray30, "Menu", 0, Color::White, FONT_SMALL);
ShinyButton btn_rctrl            (ts, tft, KEYPOS(52, 16),   KEYSIZE(8, 4),      Color::Gray70, Color::Gray30, "Ctrl", 0, Color::White, FONT_SMALL);

// A Form to group all the keyboard buttons together
Form keyboard(62,
    &btn_backtick, &btn_1, &btn_2, &btn_3, &btn_4, &btn_5, &btn_6, &btn_7, &btn_8, &btn_9, &btn_0, &btn_minus, &btn_equals, &btn_backspace,     // 14
    &btn_tab, &btn_q, &btn_w, &btn_e, &btn_r, &btn_t, &btn_y, &btn_u, &btn_i, &btn_o, &btn_p, &btn_bktopn, &btn_bktcls, &btn_blank,             // 14
    &btn_caps, &btn_a, &btn_s, &btn_d, &btn_f, &btn_g, &btn_h, &btn_j, &btn_k, &btn_l, &btn_semi, &btn_apos, &btn_hash, &btn_return,            // 14
    &btn_lshift, &btn_bslash, &btn_z, &btn_x, &btn_c, &btn_v, &btn_b, &btn_n, &btn_m, &btn_comma, &btn_stop, &btn_slash, &btn_rshift,           // 13
    &btn_lctrl, &btn_win, &btn_lalt, &btn_space, &btn_ralt, &btn_menu, &btn_rctrl                                                               //  7
);

// This function sets the keyboard into "normal" mode. It replaces all the user values and key-cap text.
// Some colours are also changed (for shift/caps).
void setupKeyboardDataNormal() {
    btn_backtick.setUserValue('`'); btn_backtick.setText("`");
    btn_1.setUserValue('1');        btn_1.setText("1");
    btn_2.setUserValue('2');        btn_2.setText("2");
    btn_3.setUserValue('3');        btn_3.setText("3");
    btn_4.setUserValue('4');        btn_4.setText("4");
    btn_5.setUserValue('5');        btn_5.setText("5");
    btn_6.setUserValue('6');        btn_6.setText("6");
    btn_7.setUserValue('7');        btn_7.setText("7");
    btn_8.setUserValue('8');        btn_8.setText("8");
    btn_9.setUserValue('9');        btn_9.setText("9");
    btn_0.setUserValue('0');        btn_0.setText("0");
    btn_minus.setUserValue('-');    btn_minus.setText("-");
    btn_equals.setUserValue('=');   btn_equals.setText("=");
    btn_backspace.setUserValue(8);  btn_backspace.setText("<=");
    btn_tab.setUserValue(11);       btn_tab.setText("=>");
    btn_q.setUserValue('q');        btn_q.setText("q");
    btn_w.setUserValue('w');        btn_w.setText("w");
    btn_e.setUserValue('e');        btn_e.setText("e");
    btn_r.setUserValue('r');        btn_r.setText("r");
    btn_t.setUserValue('t');        btn_t.setText("t");
    btn_y.setUserValue('y');        btn_y.setText("y");
    btn_u.setUserValue('u');        btn_u.setText("u");
    btn_i.setUserValue('i');        btn_i.setText("i");
    btn_o.setUserValue('o');        btn_o.setText("o");
    btn_p.setUserValue('p');        btn_p.setText("p");
    btn_bktopn.setUserValue('[');   btn_bktopn.setText("[");
    btn_bktcls.setUserValue(']');   btn_bktcls.setText("]");
    btn_blank.setUserValue(0);      btn_blank.setText("");
    btn_caps.setUserValue(0x101);   btn_caps.setText("Caps");
    btn_a.setUserValue('a');        btn_a.setText("a");
    btn_s.setUserValue('s');        btn_s.setText("s");
    btn_d.setUserValue('d');        btn_d.setText("d");
    btn_f.setUserValue('f');        btn_f.setText("f");
    btn_g.setUserValue('g');        btn_g.setText("g");
    btn_h.setUserValue('h');        btn_h.setText("h");
    btn_j.setUserValue('j');        btn_j.setText("j");
    btn_k.setUserValue('k');        btn_k.setText("k");
    btn_l.setUserValue('l');        btn_l.setText("l");
    btn_semi.setUserValue(';');     btn_semi.setText(";");
    btn_apos.setUserValue('\'');    btn_apos.setText("'");
    btn_hash.setUserValue('#');     btn_hash.setText("#");
    btn_return.setUserValue(13);    btn_return.setText("Ret");
    btn_lshift.setUserValue(0x102); btn_lshift.setText("^");
    btn_bslash.setUserValue('\\');  btn_bslash.setText("\\");
    btn_z.setUserValue('z');        btn_z.setText("z");
    btn_x.setUserValue('x');        btn_x.setText("x");
    btn_c.setUserValue('c');        btn_c.setText("c");
    btn_v.setUserValue('v');        btn_v.setText("v");
    btn_b.setUserValue('b');        btn_b.setText("b");
    btn_n.setUserValue('n');        btn_n.setText("n");
    btn_m.setUserValue('m');        btn_m.setText("m");
    btn_comma.setUserValue(',');    btn_comma.setText(",");
    btn_stop.setUserValue('.');     btn_stop.setText(".");
    btn_slash.setUserValue('/');    btn_slash.setText("/");
    btn_rshift.setUserValue(0x103); btn_rshift.setText("^");
    btn_lctrl.setUserValue(0x104);  btn_lctrl.setText("Ctrl");
    btn_win.setUserValue(0x105);    btn_win.setText("Win");
    btn_lalt.setUserValue(0x106);   btn_lalt.setText("Alt");
    btn_space.setUserValue(' ');    btn_space.setText("");
    btn_ralt.setUserValue(0x107);   btn_ralt.setText("Alt");
    btn_menu.setUserValue(0x108);   btn_menu.setText("Menu");
    btn_rctrl.setUserValue(0x109);  btn_rctrl.setText("Ctrl");

    btn_caps.setBackground(Color::Gray70, Color::Gray30);
    btn_lshift.setBackground(Color::Gray70, Color::Gray30);
    btn_rshift.setBackground(Color::Gray70, Color::Gray30);
}

// This function sets the keyboard into "shift" mode. It replaces all the user values and key-cap text.
// Some colours are also changed (for shift/caps).
void setupKeyboardDataShift() {
    btn_backtick.setUserValue('`'); btn_backtick.setText("`");
    btn_1.setUserValue('!');        btn_1.setText("!");
    btn_2.setUserValue('"');        btn_2.setText("\"");
    btn_3.setUserValue('#');        btn_3.setText("#");
    btn_4.setUserValue('$');        btn_4.setText("$");
    btn_5.setUserValue('%');        btn_5.setText("%");
    btn_6.setUserValue('^');        btn_6.setText("^");
    btn_7.setUserValue('&');        btn_7.setText("&");
    btn_8.setUserValue('*');        btn_8.setText("*");
    btn_9.setUserValue('(');        btn_9.setText("(");
    btn_0.setUserValue(')');        btn_0.setText(")");
    btn_minus.setUserValue('_');    btn_minus.setText("_");
    btn_equals.setUserValue('+');   btn_equals.setText("+");
    btn_backspace.setUserValue(8);  btn_backspace.setText("<=");
    btn_tab.setUserValue(11);       btn_tab.setText("=>");
    btn_q.setUserValue('Q');        btn_q.setText("Q");
    btn_w.setUserValue('W');        btn_w.setText("W");
    btn_e.setUserValue('E');        btn_e.setText("E");
    btn_r.setUserValue('R');        btn_r.setText("R");
    btn_t.setUserValue('T');        btn_t.setText("T");
    btn_y.setUserValue('Y');        btn_y.setText("Y");
    btn_u.setUserValue('U');        btn_u.setText("U");
    btn_i.setUserValue('I');        btn_i.setText("I");
    btn_o.setUserValue('O');        btn_o.setText("O");
    btn_p.setUserValue('P');        btn_p.setText("P");
    btn_bktopn.setUserValue('{');   btn_bktopn.setText("{");
    btn_bktcls.setUserValue('}');   btn_bktcls.setText("}");
    btn_blank.setUserValue(0);      btn_blank.setText("");
    btn_caps.setUserValue(0x201);   btn_caps.setText("Caps");
    btn_a.setUserValue('A');        btn_a.setText("A");
    btn_s.setUserValue('S');        btn_s.setText("S");
    btn_d.setUserValue('D');        btn_d.setText("D");
    btn_f.setUserValue('F');        btn_f.setText("F");
    btn_g.setUserValue('G');        btn_g.setText("G");
    btn_h.setUserValue('H');        btn_h.setText("H");
    btn_j.setUserValue('J');        btn_j.setText("J");
    btn_k.setUserValue('K');        btn_k.setText("K");
    btn_l.setUserValue('L');        btn_l.setText("L");
    btn_semi.setUserValue(':');     btn_semi.setText(":");
    btn_apos.setUserValue('@');    btn_apos.setText("@");
    btn_hash.setUserValue('~');     btn_hash.setText("~");
    btn_return.setUserValue(13);    btn_return.setText("Ret");
    btn_lshift.setUserValue(0x202); btn_lshift.setText("v");
    btn_bslash.setUserValue('|');  btn_bslash.setText("|");
    btn_z.setUserValue('Z');        btn_z.setText("Z");
    btn_x.setUserValue('X');        btn_x.setText("X");
    btn_c.setUserValue('C');        btn_c.setText("C");
    btn_v.setUserValue('V');        btn_v.setText("V");
    btn_b.setUserValue('B');        btn_b.setText("B");
    btn_n.setUserValue('N');        btn_n.setText("N");
    btn_m.setUserValue('M');        btn_m.setText("M");
    btn_comma.setUserValue('<');    btn_comma.setText("<");
    btn_stop.setUserValue('>');     btn_stop.setText(">");
    btn_slash.setUserValue('?');    btn_slash.setText("?");
    btn_rshift.setUserValue(0x203); btn_rshift.setText("v");
    btn_lctrl.setUserValue(0x104);  btn_lctrl.setText("Ctrl");
    btn_win.setUserValue(0x105);    btn_win.setText("Win");
    btn_lalt.setUserValue(0x106);   btn_lalt.setText("Alt");
    btn_space.setUserValue(' ');    btn_space.setText("");
    btn_ralt.setUserValue(0x107);   btn_ralt.setText("Alt");
    btn_menu.setUserValue(0x108);   btn_menu.setText("Menu");
    btn_rctrl.setUserValue(0x109);  btn_rctrl.setText("Ctrl");

    btn_caps.setBackground(Color::Gray30, Color::Gray70);
    btn_lshift.setBackground(Color::Gray30, Color::Gray70);
    btn_rshift.setBackground(Color::Gray30, Color::Gray70);
}

// Keyboard highighting so you can see what button you are pressing
void hiKeyboard(Event *e) {
    ShinyButton *w = (ShinyButton *)e->source;
    w->setBackground(Color::Snow, Color::Gray30);
}

// And the lowlighting as well.
void loKeyboard(Event *e) {
    ShinyButton *w = (ShinyButton *)e->source;
    w->setBackground(Color::Gray70, Color::Gray30);
}

// This is where all the keyboard magic takes place. It's called whenever
// a key is pressed and the widget's user data is used to work out what
// key has been pressed and what to do.
void doKeyboard(Event *e) {
    ShinyButton *w = (ShinyButton *)e->source;

    int c = w->getUserValue();

    switch (c) {
        // Unshifted variants
        case 0x101: // Caps
            tempShift = false;
            setupKeyboardDataShift();
            break;            
        case 0x102: // Left Shift
        case 0x103: // Right Shift
            tempShift = true;
            setupKeyboardDataShift();
            break;
        case 0x104: // Left Ctrl
        case 0x105: // Win
        case 0x106: // Left Alt
        case 0x107: // Right Alt
        case 0x108: // Menu
        case 0x109: // Right Ctrl
            break;
        case 0x201: // Caps
        case 0x202: // Left Shift
        case 0x203: // Right Shift
            setupKeyboardDataNormal();
            break;
        case 0x204: // Left Ctrl
        case 0x205: // Win
        case 0x206: // Left Alt
        case 0x207: // Right Alt
        case 0x208: // Menu
        case 0x209: // Right Ctrl
            break;

        case 8: // Backspace
            if (ipos > 0) {
                ipos--;
                input[ipos] = 0;
                textUpdate = true;
            }
            // Return to normal mode if it was shifted (not caps).
            if (tempShift) {
                tempShift = false;
                setupKeyboardDataNormal();
            }
            break;
        case 11: // Tab
            break;
        case 13: // Return
            break;
        default: // Everything else
            // If it's printable:
            if ((c >= ' ') && (c <= 127)) {
                if (ipos < (TEXTSIZE-1)) {
                    input[ipos++] = c;
                    input[ipos] = 0;
                    textUpdate = true;
                }
            }
            // Return to normal mode if it was shifted (not caps).
            if (tempShift) {
                tempShift = false;
                setupKeyboardDataNormal();
            }
            break;       
    }
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

    // Set up the keyboard events. Calling functions on the
    // form calls the functions on all the widgets in the form.
    keyboard.onTap(doKeyboard);
    keyboard.onPress(hiKeyboard);
    keyboard.onRelease(loKeyboard);

    // Configure the default keyboard mode
    setupKeyboardDataNormal();

    // Draw a box to display text in.
    tft.setFont(FONT_HUGE);
    int h = tft.stringHeight("|");
    tft.fillRectangle(0, 0, 320, h + 20, Color::White);
}

void loop() {
    // Sample the touch screen and update the keyboard
    // handling any events that occur.
    ts.sample();
    keyboard.render();

    // If the text has changed then update the display
    if  (textUpdate) {
        textUpdate = false;
        tft.setCursor(10, 10);
        tft.setTextColor(Color::Black, Color::White);
        tft.setFont(FONT_HUGE);
        int h = tft.stringHeight(input);
        int w = tft.stringWidth(input);
        tft.print(input);
        tft.fillRectangle(10 + w, 10, 300 - w, h, Color::White);
        tft.print("|");
    }
}
