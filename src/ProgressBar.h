#ifndef GUI_PROGRESSBAR_H_
#define GUI_PROGRESSBAR_H_

#include "GLCDUnits.h"

#define PROGRESSBAR(page_anchor, col_anchor, width) { { page_anchor, col_anchor }, width, 0 }

typedef struct {
    const GLCDUnits top_left_anchor;
    const char width;
    char progress;
} ProgressBar;

void bar_print(const ProgressBar *bar);
char bar_increase(ProgressBar *bar, char increase);
char bar_decrease(ProgressBar *bar, char decrease);

#endif
