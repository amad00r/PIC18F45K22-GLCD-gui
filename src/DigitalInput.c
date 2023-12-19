#include <xc.h>
#include "DigitalInput.h"

char digital_input_check(DigitalInput *input) {
    char port_sample_1 = *(input->port_ptr);
    __delay_ms(10);
    char port_sample_2 = *(input->port_ptr);
    input->prev_state = input->state;
    input->state = (input->state | (port_sample_1 & port_sample_2)) & (port_sample_1 | port_sample_2);
    return input->state != input->prev_state;
}

char input_get_pin_state(char pin_idx, const DigitalInput *input) {
    return (input->state & (1 << pin_idx)) != 0;
}

Edge input_get_pin_edge(char pin_idx, const DigitalInput *input) {
    char mask = (1 << pin_idx);
    char masked_state = input->state & mask;
    if ((input->prev_state & mask) == masked_state) return NULLEDGE;
    return (masked_state ? RISING : FALLING);
}