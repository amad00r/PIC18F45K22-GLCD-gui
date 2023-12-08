#ifndef GUI_PROGRESSBAR_H_
#define GUI_PROGRESSBAR_H_

#include "GLCDUnits.h"

#define PROGRESSBAR(page_anchor, col_anchor, width) { { page_anchor, col_anchor }, width, 0 }

typedef struct {
    const GLCDUnits top_left_anchor;
    const char width;
    char progress;
} ProgressBar;

void print_progress_bar(const ProgressBar *bar);
void increase_progress_bar(ProgressBar *bar, char increase);
void decrease_progress_bar(ProgressBar *bar, char decrease);

#endif
