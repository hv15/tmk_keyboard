#include "keymap_common.h"

const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* layer 0 */
    KEYMAP(
        ESC, F1, F2, F3, F4,  F5, F6, F7, F8,  F9, F10, F11,   F12,                 PSCR, SLCK, PAUS,
        GRV, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS, EQL, BSPC,     INS,  HOME, PGUP,    NLCK,PSLS,PAST,PMNS,
        TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC, RBRC,BSLS,     DEL, END, PGDN,      P7,  P8,  P9,  PPLS,
        LCTL,A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,     ENT,                            P4,  P5,  P6,
        LSFT,Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,          RSFT,          UP,              P1,  P2,  P3,  PENT,
        LCTL,LALT,                  SPC,                           RALT, RCTL,     LEFT,DOWN,RGHT,       P0,       PDOT
    ),
};

enum macro_id {
    MACRO_0,
    MACRO_1,
    MACRO_2,
    MACRO_3,
    MACRO_4,
    MACRO_5,
    MACRO_6,
    MACRO_7,
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
    keyevent_t event = record->event;
    switch (id) {
        case MACRO_0:
            return (event.pressed ?
                    MACRO( END ) :
                    MACRO( END ));
        case MACRO_1:
            return (event.pressed ?
                    MACRO( END ) :
                    MACRO( END ));
        case MACRO_2:
            return (event.pressed ?
                    MACRO( END ) :
                    MACRO( END ));
        case MACRO_3:
            return (event.pressed ?
                    MACRO( END ) :
                    MACRO( END ));
        case MACRO_4:
            return (event.pressed ?
                    MACRO( END ) :
                    MACRO( END ));
        case MACRO_5:
            return (event.pressed ?
                    MACRO( END ) :
                    MACRO( END ));
        case MACRO_6:
            return (event.pressed ?
                    MACRO( END ) :
                    MACRO( END ));
        case MACRO_7:
            return (event.pressed ?
                    MACRO( END ) :
                    MACRO( END ));
    }
    return MACRO_NONE;
}

const action_t PROGMEM fn_actions[] = {
    [0]  = ACTION_LAYER_MOMENTARY(1),
    [1]  = ACTION_LAYER_MOMENTARY(2),
    [2]  = ACTION_LAYER_MOMENTARY(3),
    [3]  = ACTION_LAYER_MOMENTARY(4),
    [4]  = ACTION_LAYER_MOMENTARY(5),
    [5]  = ACTION_LAYER_MOMENTARY(6),
    [6]  = ACTION_LAYER_MOMENTARY(7),
    [7]  = ACTION_LAYER_TOGGLE(1),
    [8]  = ACTION_LAYER_TOGGLE(2),
    [9]  = ACTION_LAYER_TOGGLE(3),
    [10] = ACTION_LAYER_TOGGLE(4),
    [11] = ACTION_LAYER_TOGGLE(5),
    [12] = ACTION_LAYER_TOGGLE(6),
    [13] = ACTION_LAYER_TOGGLE(7),
    [14] = ACTION_MACRO(MACRO_0),
    [15] = ACTION_MACRO(MACRO_1),
    [16] = ACTION_MACRO(MACRO_2),
    [17] = ACTION_MACRO(MACRO_3),
    [18] = ACTION_MACRO(MACRO_4),
    [19] = ACTION_MACRO(MACRO_5),
    [20] = ACTION_MACRO(MACRO_6),
    [21] = ACTION_MACRO(MACRO_7),
};
