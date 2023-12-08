#ifndef GUI_BUTTON_H_
#define GUI_BUTTON_H_

#include "GLCDUnits.h"
#include "Text.h"
#include "input_detection.h"


#define BUTTON(page_anchor, col_anchor, pages_size, pixels_size, text, text_size) { { page_anchor, col_anchor },                        \
                                                                                    { pages_size, pixels_size },                        \
                                                                                    TEXT((pages_size>>1) + page_anchor,                 \
                                                                                    (pixels_size>>1) + col_anchor - ((text_size*5)>>1), \
                                                                                    text,                                               \
                                                                                    text_size) }

typedef struct {
    GLCDUnits top_left_anchor, size;
    Text text;
} Button;

void print_button(const Button *b);
void toggle_button_highlight(const Button *b, Edge edge);

#endif
