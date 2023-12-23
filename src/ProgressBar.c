#include "ProgressBar.h"
#include "GLCD.h"

void bar_print(const ProgressBar *bar) {
    char a_page = bar->top_left_anchor.v_pages;
    char a_px = bar->top_left_anchor.h_px;
    char last_progress_px = a_px + bar->width - 2;

    writeByte(a_page, a_px, 0xFF);
    writeByte(a_page, a_px + 1, 0b10000001);
    writeByte(a_page, last_progress_px, 0b10000001);
    writeByte(a_page, last_progress_px + 1, 0xFF);
    for (char j = a_px + 2; j < last_progress_px; ++j)
        writeByte(a_page, j, 0b10000001);
}

char bar_increase(ProgressBar *bar, char increase) {
    char progress = bar->progress;
    char max_progress = bar->width - 4;
    char progress_px = bar->top_left_anchor.h_px + 2 + progress;
    char a_page = bar->top_left_anchor.v_pages;

    if (progress == max_progress) return 0;

    if (max_progress - progress <= increase) {
        char max_progress_px = bar->top_left_anchor.h_px + 2 + max_progress;
        for (char j = progress_px; j < max_progress_px; ++j)
            writeByte(a_page, j, 0b10111101);
        bar->progress = max_progress;
    }
    else {
        char last_progress_px = progress_px + increase;
        for (char j = progress_px; j < last_progress_px; ++j)
            writeByte(a_page, j, 0b10111101);
        bar->progress += increase;
    }

    return 1;
}

char bar_decrease(ProgressBar *bar, char decrease) {
    char progress = bar->progress;
    char first_px = bar->top_left_anchor.h_px + 1;
    char progress_px = first_px + progress;
    char a_page = bar->top_left_anchor.v_pages;

    if (progress == 0) return 0;

    if (progress <= decrease) {
        for (char j = progress_px; j > first_px; --j)
            writeByte(a_page, j, 0b10000001);
        bar->progress = 0;
    }
    else {
        char new_progress_px = progress_px - decrease;
        for (char j = progress_px; j > new_progress_px; --j)
            writeByte(a_page, j, 0b10000001);
        bar->progress -= decrease;
    }

    return 1;
}
