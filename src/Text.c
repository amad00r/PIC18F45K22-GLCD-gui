#include <string.h>
#include "GLCD.h"
#include "ascii.h"
#include "Text.h"

void precise_putchGLCD(char page, char y, char c, TextColor color) {
    int font_pos = (c - ' ')*5;
    if (color == BLACK)
        for (char i = 0; i < 5; ++i)
            writeByte(page, y + i, font5x7[font_pos + i]);
    else
        for (char i = 0; i < 5; ++i)
            writeByte(page, y + i, ~font5x7[font_pos + i]);  
}

void writestring(char page, char y, const char *s, char length, TextColor color) {
    for (char i = 0; i < length; ++i) {
        precise_putchGLCD(page, y, s[i], color);
        y += 5;
    }
}

void print_text(const Text *t, TextColor color) {
    writestring(t->top_left_anchor.v_pages, t->top_left_anchor.h_px, t->text, t->length, color);
}

void clear_text(const Text *t, TextColor color) {
    char bytedata = (color == BLACK ? 0 : 0xFF);
    char a_px = t->top_left_anchor.h_px;
    char text_end_px = t->length*5 + a_px - 1;
    char a_page = t->top_left_anchor.v_pages;

    for (char j = a_px; j < text_end_px; ++j)
        writeByte(a_page, j, bytedata);
}

void change_text(Text *t, const char *new_text, char new_text_size) {
    t->length = new_text_size;
    memcpy(t->text, new_text, new_text_size);
}
