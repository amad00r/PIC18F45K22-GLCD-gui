#ifndef GUI_TEXT_H_
#define GUI_TEXT_H_

#include "GLCDUnits.h"

#define TEXT(page_anchor, col_anchor, text, text_size) { { page_anchor, col_anchor }, text, text_size }
#define MAX_CHARS_PER_ROW 25

typedef struct {
    GLCDUnits top_left_anchor;
    char text[MAX_CHARS_PER_ROW];
    char length;
} Text;

typedef enum {
    WHITE,
    BLACK
} TextColor;

void text_print(const Text *t, TextColor color);
void text_clear(const Text *t, TextColor color);
void text_change(Text *t, const char *new_text, char new_text_size);

#endif
