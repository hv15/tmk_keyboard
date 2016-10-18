/* Copyright 2012 Jun Wako <wakojun@gmail.com>
 *
 * This is heavily based on phantom/board.{c|h}.
 * https://github.com/BathroomEpiphanies/AVR-Keyboard
 *
 * Copyright (c) 2012 Fredrik Atmer, Bathroom Epiphanies Inc
 * http://bathroomepiphanies.com
 *
 * As for liscensing consult with the original files or its author.
 */
#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>
#include <util/delay.h>
#include "print.h"
#include "debug.h"
#include "util.h"
#include "matrix.h"


#ifndef DEBOUNCE
#   define DEBOUNCE	10
#endif
static uint8_t debouncing = DEBOUNCE;

// bit array of key state(1:on, 0:off)
static matrix_row_t matrix[MATRIX_ROWS];
static matrix_row_t matrix_debouncing[MATRIX_ROWS];

#ifdef MATRIX_HAS_GHOST
static bool matrix_has_ghost_in_row(uint8_t row);
#endif
static uint16_t read_rows(void);
static void init_rows(void);
static void unselect_cols(void);
static void select_col(uint8_t col);

#ifndef SLEEP_LED_ENABLE
static
void setup_leds(void)
{
    // LEDs: LED_A -> PORTB6, LED_B -> PORTB5, LED_C -> PORTB4
    DDRF  |= (1<<4) | (1<<5) | (1<<6);
    PORTF  &= ~((1<<4) | (1<<5) | (1<<6));
}
#endif

inline
uint8_t matrix_rows(void)
{
    return MATRIX_ROWS;
}

inline
uint8_t matrix_cols(void)
{
    return MATRIX_COLS;
}

void matrix_init(void)
{
    // To use PORTF disable JTAG with writing JTD bit twice within four cycles.
    //MCUCR |= (1<<JTD);
    //MCUCR |= (1<<JTD);
	
    // initialize row and col
    unselect_cols();
    init_rows();
#ifndef SLEEP_LED_ENABLE
    setup_leds();
#endif

    // initialize matrix state: all keys off
    for (uint8_t i = 0; i < MATRIX_ROWS; i++)  {
        matrix[i] = 0;
        matrix_debouncing[i] = 0;
    }
}

uint8_t matrix_scan(void)
{
    for (uint8_t col = 0; col < MATRIX_COLS; col++) {  // 0-16
        select_col(col);
        _delay_us(30);       // without this wait it won't read stable value.
        uint16_t rows = read_rows();
        for (uint8_t row = 0; row < MATRIX_ROWS; row++) {  // 0-5
            bool prev_bit = matrix_debouncing[row] & ((matrix_row_t)1<<col);
            bool curr_bit = rows & (1<<row);
            if (prev_bit != curr_bit) {
                matrix_debouncing[row] ^= ((matrix_row_t)1<<col);
                if (debouncing) {
                    dprint("bounce!: "); dprintf("%02X", debouncing); dprintln();
                }
                debouncing = DEBOUNCE;
            }
        }
        unselect_cols();
    }

    if (debouncing) {
        if (--debouncing) {
            _delay_ms(1);
        } else {
            for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
                matrix[i] = matrix_debouncing[i];
            }
        }
    }

    return 1;
}

bool matrix_is_modified(void)
{
    if (debouncing) return false;
    return true;
}

inline
bool matrix_is_on(uint8_t row, uint8_t col)
{
    return (matrix[row] & ((matrix_row_t)1<<col));
}

inline
matrix_row_t matrix_get_row(uint8_t row)
{
    return matrix[row];
}

/*
void matrix_print(void)
{
    print("\nr/c 0123456789ABCDEF\n");
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        xprintf("%02X: %032lb\n", row, bitrev32(matrix_get_row(row)));
    }
}
*/

void matrix_print(void)
{
    print("\nr/c 01234567\n");
    for (uint8_t row = 0; row < matrix_rows(); row++) {
        phex(row); print(": ");
        pbin_reverse(matrix_get_row(row));
#ifdef MATRIX_HAS_GHOST
        if (matrix_has_ghost_in_row(row)) {
            print(" <ghost");
        }
#endif
        print("\n");
    }
}

#ifdef MATRIX_HAS_GHOST
inline
static bool matrix_has_ghost_in_row(uint8_t row)
{
    // no ghost exists in case less than 2 keys on
    if (((matrix[row] - 1) & matrix[row]) == 0)
        return false;

    // ghost exists in case same state as other row
    for (uint8_t i=0; i < MATRIX_ROWS; i++) {
        if (i != row && (matrix[i] & matrix[row]))
            return true;
    }
    return false;
}
#endif

uint8_t matrix_key_count(void)
{
    uint8_t count = 0;
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        count += bitpop32(matrix[i]);
    }
    return count;
}

/* Row pin configuration
 * row: 0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15
 * pin: C7 C6 C5 C4 C3 C2 C1 C0 E1 E0 D7 D0 D5 D4 D3 D2
 * pin: D7 E0 E1 C0 C1 C2 C3 C4 C5 C6 C7 B7 D0 D1 D2 D3 Teensy 2.0++
 */
static void init_rows(void)
{
    // Input with pull-up(DDR:0, PORT:1)
    DDRC  &= ~0b11111111;
    PORTC |=  0b11111111;
    DDRE  &= ~0b00000011;
    PORTE |=  0b00000011;
    DDRD  &= ~0b10001111;
    PORTD |=  0b10001111;
    DDRB  &= ~0b10000000;
    PORTB |=  0b10000000;
}

static uint16_t read_rows(void)
{
    return (PIND&(1<<7) ? 0 : (1<<0)) |
           (PINE&(1<<0) ? 0 : (1<<1)) |
           (PINE&(1<<1) ? 0 : (1<<2)) |
           (PINC&(1<<0) ? 0 : (1<<3)) |
           (PINC&(1<<1) ? 0 : (1<<4)) |
           (PINC&(1<<2) ? 0 : (1<<5)) |
           (PINC&(1<<3) ? 0 : (1<<6)) |
           (PINC&(1<<4) ? 0 : (1<<7)) |
           (PINC&(1<<5) ? 0 : (1<<8)) |
           (PINC&(1<<6) ? 0 : (1<<9)) |
           (PINC&(1<<7) ? 0 : (1<<10)) |
           (PINB&(1<<7) ? 0 : (1<<11)) |
           (PIND&(1<<0) ? 0 : (1<<12)) |
           (PIND&(1<<1) ? 0 : (1<<13)) |
           (PIND&(1<<2) ? 0 : (1<<14)) |
           (PIND&(1<<3) ? 0 : (1<<15));
}

/* Column pin configuration
 * col:  0  1  2  3  4  5  6  7
 * pin: F0 F1 F2 F3 F4 F5 F6 E7
 * pin: B6 B5 B4 B3 B2 B1 B0 E7 Teensy 2.0++
 * pin: F0 F1 F2 F3 F4 F5 F6 F7 Teensy 2.0++
 */
static void unselect_cols(void)
{
    // Hi-Z(DDR:0, PORT:0) to unselect
    DDRF  |= 0b11111111; // PB: 7 6 5 4 3 2 1 0
    PORTF |= 0b11111111; // PB: 7 6 5 4 3 2 1 0
}

static void select_col(uint8_t col)
{
    switch (col) {
        case 6:
            DDRF  |=  (1 << 6);
            PORTF &= ~(1 << 6);
            break;
        case 5:
            DDRF  |=  (1 << 5);
            PORTF &= ~(1 << 5);
            break;
        case 4:
            DDRF  |=  (1 << 4);
            PORTF &= ~(1 << 4);
            break;
        case 3:
            DDRF  |=  (1 << 3);
            PORTF &= ~(1 << 3);
            break;
        case 2:
            DDRF  |=  (1 << 2);
            PORTF &= ~(1 << 2);
            break;
        case 1:
            DDRF  |=  (1 << 1);
            PORTF &= ~(1 << 1);
            break;
        case 0:
            DDRF  |=  (1 << 0);
            PORTF &= ~(1 << 0);
            break;
        case 7:
            DDRF  |=  (1 << 7);
            PORTF &= ~(1 << 7);
            break;
        default:
            dprint("WTF"); dprintln();
    }
}
