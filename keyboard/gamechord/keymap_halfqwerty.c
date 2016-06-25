#include "keymap_common.h"

const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // Default
    KEYMAP(    Q,    W,    E,    R,    T, \
               A,    S,    D,    F,    G, \
               Z,    X,    C,    V,    B, \
              NO,   NO, LSFT,  FN0,  FN1),
    // FN0
    KEYMAP(    P,    O,    I,    U,    Y, \
            SCLN,    L,    K,    J,    H, \
            SLSH,  DOT, COMM,    M,    N, \
              NO,   NO, LSFT,  FN0,  FN2),
    // FN1 
    KEYMAP(    1,    2,    3,    4,    5, \
             ESC,  GRV,   UP, LBRC, RBRC, \
             TAB, LEFT, DOWN, RGHT,  ENT, \
              NO,   NO, LSFT,  FN3,  FN1),
    // FN0 -> FN1 (FN2)
    KEYMAP(    0,    9,    8,    7,    6, \
             EQL, MINS, PGUP, QUOT, BSLS, \
             FN4, HOME, PGDN,  END, QUOT, \
              NO,   NO, LSFT,  FN0,  FN2),
    // FN1 -> FN0 (FN3)
    KEYMAP(    0,    9,    8,    7,    6, \
             EQL, MINS, PGUP, QUOT, BSLS, \
             FN4, HOME, PGDN,  END, QUOT, \
              NO,   NO, LSFT,  FN3,  FN1),
    // FN0 + FN1 + K20 = FN4
    KEYMAP(   F1,   F2,   F3,   F4,   F5, \
             EQL, WH_L, WH_D, WH_U, WH_R, \
             FN4, LGUI, MS_D, MS_U, MS_R, \
              NO,   NO, LSFT,  FN3,  FN1),
};
  
const uint16_t PROGMEM fn_actions[] = {
    [0] = ACTION_LAYER_TAP_KEY(1, KC_SPC),  // FN0
    [1] = ACTION_LAYER_TAP_KEY(2, KC_BSPC), // FN1
    [2] = ACTION_LAYER_MOMENTARY(3),        // FN0 -> FN1 = FN2
    [3] = ACTION_LAYER_MOMENTARY(4),        // FN1 -> FN0 = FN3
    [4] = ACTION_LAYER_MOMENTARY(5),        // FN0 + FN1 + K20 = FN4
};
