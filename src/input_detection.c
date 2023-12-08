#include <xc.h>
#include "input_detection.h"

Edge edge_detector(char state, char new_state) {
    if (state == new_state) return NULLEDGE;
    return new_state ? RISING : FALLING;
}

void rcx_wait_and_see(char rcx_new_state[8]) {
    __delay_ms(10);
    rcx_new_state[0] = PORTCbits.RC0;
    rcx_new_state[1] = PORTCbits.RC1;
    rcx_new_state[2] = PORTCbits.RC2;
    rcx_new_state[3] = PORTCbits.RC3;
    rcx_new_state[4] = PORTCbits.RC4;
    rcx_new_state[5] = PORTCbits.RC5;
    rcx_new_state[6] = PORTCbits.RC6;
    rcx_new_state[7] = PORTCbits.RC7;
}

char rcx_input(Input *input) {
    char rcx_new_state[8];
    rcx_wait_and_see(rcx_new_state);

    char found_edge = 0;

    for (char i = 0; i < 8; ++i) {
        input->rcx_edge[i] = edge_detector(input->rcx_state[i], rcx_new_state[i]);
        found_edge |= input->rcx_edge[i] != NULLEDGE;
        input->rcx_state[i] = rcx_new_state[i];
    }

    return found_edge;
}
