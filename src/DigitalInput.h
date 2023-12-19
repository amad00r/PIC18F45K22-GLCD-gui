#ifndef DIGITAL_INPUT_H_
#define DIGITAL_INPUT_H_

#define _XTAL_FREQ 8000000

#define INPUT(port_ptr) { port_ptr, 0, 0 }

typedef struct {
    const volatile char *port_ptr;
    char state;
    char prev_state;
} DigitalInput;

typedef enum {
    NULLEDGE,
    RISING,
    FALLING
} Edge;

char digital_input_check(DigitalInput *input);
char input_get_pin_state(char pin_idx, const DigitalInput *input);
Edge input_get_pin_edge(char pin_idx, const DigitalInput *input);

#endif
