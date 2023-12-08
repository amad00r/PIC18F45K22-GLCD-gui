#include "GLCD.h"
#include "Button.h"

void print_button(const Button *b) {
    char pages = b->size.v_pages;
    char px = b->size.h_px;
    char a_page = b->top_left_anchor.v_pages;
    char a_px = b->top_left_anchor.h_px;
    char a_page_lowest_vpx = a_page<<3;
    char hline_px_end = a_px + px - 1;

    print_text(&b->text, BLACK);

    if (b->size.v_pages == 1) {
        char a_page_highest_vpx = a_page_lowest_vpx + 7;
        
        writeByte(a_page, a_px, 0xFF);
        writeByte(a_page, hline_px_end, 0xFF);
        for (int j = a_px + 1; j < hline_px_end; ++j) {
            SetDot(a_page_lowest_vpx, j);
            SetDot(a_page_highest_vpx, j);
        }
    }
    else {
        char last_page_highest_vpx = ((a_page + pages - 1)<<3) + 7;

        for (char i = a_page; i < a_page + pages; ++i) {
            writeByte(i, a_px, 0b11111111);
            writeByte(i, hline_px_end, 0b11111111);
        }
        for (int j = a_px + 1; j < hline_px_end; ++j) {
            SetDot(a_page_lowest_vpx, j);
            SetDot(last_page_highest_vpx, j);
        }
    }
}

void toggle_button_highlight(const Button *b, Edge edge) {
    char pages = b->size.v_pages;
    char px = b->size.h_px;
    char a_page = b->top_left_anchor.v_pages;
    char a_px = b->top_left_anchor.h_px;

    char text_page = b->text.top_left_anchor.v_pages;
    char text_px = b->text.top_left_anchor.h_px;
    char text_end = text_px + b->text.length*5;

    char highlight_px_start = a_px + 2;
    char highlight_px_end = a_px + px - 2;

    char bytedata = (edge == RISING ? 0xFF : 0);
   
    if (pages == 1) {
        char top_bottom_bytedata = (bytedata & 0b00111100) | 0b10000001;
 
        for (char j = highlight_px_start; j < text_px; ++j)
            writeByte(a_page, j, top_bottom_bytedata);
        for (char j = text_px; j < text_end; ++j)
            writeByte(a_page, j, (~readByte(a_page, j) & 0b00111100) | 0b10000001);
        for (char j = text_end; j < highlight_px_end; ++j)
            writeByte(a_page, j, top_bottom_bytedata);
    }
    else if (pages == 2) {
        char top_bytedata = (bytedata & 0b11111100) | 1;
        char bottom_bytedata = (bytedata & 0b00111111) | 0b10000000;
      
        for (char j = highlight_px_start; j < highlight_px_end; ++j)
            writeByte(a_page, j, top_bytedata);
        for (char j = highlight_px_start; j < text_px; ++j)
            writeByte(text_page, j, bottom_bytedata);
        for (char j = text_px; j < text_end; ++j)
            writeByte(text_page, j, (~readByte(text_page, j) & 0b00111111) | 0b10000000);
        for (char j = text_end; j < highlight_px_end; ++j)
            writeByte(text_page, j, bottom_bytedata);
    }
    else {
        char top_bytedata = (bytedata & 0b11111100) | 1;
        char bottom_bytedata = (bytedata & 0b00111111) | 0b10000000;

        char last_page = a_page + pages - 1;
        for (char j = highlight_px_start; j < highlight_px_end; ++j) {
            writeByte(a_page, j, top_bytedata);
            writeByte(last_page, j, bottom_bytedata);
        }
      
        for (char i = a_page + 1; i < text_page; ++i)
            for (char j = highlight_px_start; j < highlight_px_end; ++j)
                writeByte(i, j, bytedata);

        for (char j = highlight_px_start; j < text_px; ++j)
            writeByte(text_page, j, bytedata);
        print_text(&b->text, (edge == RISING ? WHITE : BLACK));
        for (char j = text_end; j < highlight_px_end; ++j)
            writeByte(text_page, j, bytedata);
    }
}
