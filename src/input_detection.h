#ifndef INPUT_DETECTION_H_
#define INPUT_DETECTION_H_

#define _XTAL_FREQ 8000000

typedef enum {
    NULLEDGE,
    RISING,
    FALLING
} Edge;

#define INIT_INPUT { { 0 }, { 0 } }

typedef struct {
    char rcx_state[8];
    Edge rcx_edge[8];
} Input;

char rcx_input(Input *input);

#endif
