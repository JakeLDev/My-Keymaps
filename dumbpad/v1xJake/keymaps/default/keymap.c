/* Copyright 2020 imchipwood
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
            BASE LAYER
    /-----------------------------------------------------`
    |             |    7    |    8    |    9    |  Bkspc  |
    |             |---------|---------|---------|---------|
    |             |    4    |    5    |    6    |    +    |
    |             |---------|---------|---------|---------|
    |             |    1    |    2    |    3    |    -    |
    |-------------|---------|---------|---------|---------|
    | Play/pause  |  TT(1)  |    0    |    .    |  Enter  |
    \-----------------------------------------------------'
    */
    [0] = LAYOUT(
                    KC_P7,     KC_P8,   KC_P9,    KC_BSPC,
                    KC_P4,     KC_P5,   KC_P6,    KC_KP_PLUS,
                    KC_P1,     KC_P2,   KC_P3,    KC_KP_MINUS,
        KC_MPLY,    MO(1),     KC_P0,   KC_PDOT,  KC_KP_ENTER
    ),
    /*
          SUB LAYER
     /-----------------------------------------------------`
     |             |   F7    |   F8    |   F9    | Del/NLK |
     |             |---------|---------|---------|---------|
     |             |   F4    |   F5    |   F6    |    *    |
     |             |---------|---------|---------|---------|
     |             |   F1    |   F2    |   F3    |    /    |
     |-------------|---------|---------|---------|---------|
     |    MUTE     |         |  LSFT   |  LCTL   |    =    |
     \-----------------------------------------------------'
    */
    [1] = LAYOUT(
                        KC_F7,          KC_F8,          KC_F9, TD(DEL_NLCK),
                        KC_F4,          KC_F5,          KC_F6,  KC_KP_ASTERISK,
                        KC_F1,          KC_F2,          KC_F3,  KC_KP_SLASH,
        KC_MUTE,      _______,  OSM(MOD_LSFT),  OSM(MOD_LCTL),  KC_KP_EQUAL
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // If console is enabled, it will print the matrix position and status of each key pressed
/*
#ifdef CONSOLE_ENABLE
    uprintf("KL: kc: %u, col: %u, row: %u, pressed: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed);
#endif
*/
    return true;
}

void keyboard_post_init_user(void) {
    // Customise these values to desired behaviour
    //debug_enable = true;
    //debug_matrix = true;
    //debug_keyboard = true;
    //debug_mouse = true;
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    /*  Custom encoder control - handles CW/CCW turning of encoder
     *  Default behavior:
     *    main layer:
     *       CW: redo
     *      CCW: undo
     *    other layers:
     *       CW: volume up
     *      CCW: volume down
     */
    if (index == 0) {
        switch (get_highest_layer(layer_state)) {
            case 0:
                // main layer - volume up (CW) and volume down (CCW)
                if (clockwise) {
                    tap_code16(C(KC_Y));
                } else {
                    tap_code16(C(KC_Z));
                }
                break;

            default:
                // other layers - =/+ (quals/plus) (CW) and -/_ (minus/underscore) (CCW)
                if (clockwise) {
                    tap_code(KC_VOLU);
                } else {
                    tap_code(KC_VOLD);
                }
                break;
        }
    }
    return true;
}
