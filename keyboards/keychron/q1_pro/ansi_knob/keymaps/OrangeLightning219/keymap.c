/* Copyright 2023 @ Keychron (https://www.keychron.com)
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
#include "OrangeLightning219.h"
// clang-format off
enum layers{
  WIN_DVORAK = 0,
  WIN_DVORAK_SHIFT,
  WIN_QWERTY,
  WIN_FN,

  MAC_DVORAK,
  MAC_DVORAK_SHIFT,
  MAC_QWERTY,
  MAC_FN
};

// Tap Dance keycodes
enum td_keycodes {
    SHIFT_UNDERSCORE
};

// Define a type containing as many tapdance states as you need
typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
} td_state_t;

// Create a global instance of the tapdance state type
static td_state_t td_state;

// Declare your tapdance functions:

// Function to determine the current tapdance state
td_state_t cur_dance(tap_dance_state_t *state);

// `finished` and `reset` functions for each tapdance keycode
void shift_underscore_finished(tap_dance_state_t *state, void *user_data);
void shift_underscore_reset(tap_dance_state_t *state, void *user_data);

// Define `ACTION_TAP_DANCE_FN_ADVANCED()` for each tapdance keycode, passing in `finished` and `reset` functions
tap_dance_action_t tap_dance_actions[] = {
    [SHIFT_UNDERSCORE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, shift_underscore_finished, shift_underscore_reset)
};

#define QWERTY(LCTL, META, LALT, RALT, FN, TOGGLE_LAYER) LAYOUT_ansi_82(                                                                                                             \
        KC_ESC,                KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,      KC_F10,   KC_F11,   KC_F12,   KC_DEL,   TT(TOGGLE_LAYER), \
        KC_GRV,                KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,       KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,  KC_PGUP,          \
        KC_TAB,                KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,       KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,  KC_PGDN,          \
        MT(MOD_LCTL, KC_ESC),  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,       KC_SCLN,  KC_QUOT,            KC_ENT,   KC_HOME,          \
        KC_LSFT,               KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,     KC_SLSH,  KC_RSFT,            KC_UP,                      \
        LCTL,                  META,     LALT,                                 KC_SPC,                         RALT,       FN,       KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT)

        
#define PRIME_DVORAK(LCTL, META, LALT, RALT, FN, QWERTY_LAYER, SHIFT_LAYER) LAYOUT_ansi_82(                                                                                                 \
        KC_ESC,                KC_F1,      KC_F2,    KC_F3,      KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,      KC_F9,    KC_F10,  KC_F11,     KC_F12,     KC_DEL,   TT(QWERTY_LAYER), \
        S(KC_4),               S(KC_EQL),  KC_LBRC,  S(KC_LBRC), S(KC_9),  S(KC_7),  KC_EQL,   S(KC_0),  S(KC_RBRC), KC_RBRC,  S(KC_8), S(KC_1),    S(KC_BSLS), KC_BSPC,  KC_PGUP,          \
        KC_TAB,                KC_SCLN,    KC_COMM,  KC_DOT,     KC_P,     KC_Y,     KC_F,     KC_G,     KC_C,       KC_R,     KC_L,    KC_SLSH,    S(KC_2),    KC_BSLS,  KC_PGDN,          \
        MT(MOD_LCTL, KC_ESC),  KC_A,       KC_O,     KC_E,       KC_U,     KC_I,     KC_D,     KC_H,     KC_T,       KC_N,     KC_S,    S(KC_MINS),             KC_ENT,   KC_HOME,          \
        MO(SHIFT_LAYER),       S(KC_QUOT), KC_Q,     KC_J,       KC_K,     KC_X,     KC_B,     KC_M,     KC_W,       KC_V,     KC_Z,    MO(SHIFT_LAYER),        KC_UP,                      \
        LCTL,                  META,       LALT,                                 KC_SPC,                             RALT,     FN,      KC_RCTL,    KC_LEFT,    KC_DOWN,  KC_RGHT)

#define PRIME_DVORAK_SHIFT() LAYOUT_ansi_82(                                                                                                                         \
        KC_ESC,   KC_TRNS,    KC_TRNS,    KC_TRNS,   KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS,  KC_TRNS,    KC_TRNS,    KC_TRNS,  KC_TRNS, \
        S(KC_GRV),   KC_1,       KC_2,       KC_3,      KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,    KC_0,  S(KC_5),    KC_GRV,     KC_TRNS,  KC_TRNS, \
        KC_TRNS,  S(KC_SCLN), S(KC_COMM), S(KC_DOT), S(KC_P),  S(KC_Y),  S(KC_F),  S(KC_G),  S(KC_C),  S(KC_R), S(KC_L),  S(KC_SLSH), S(KC_6),    S(KC_3),  KC_TRNS, \
        KC_TRNS,  S(KC_A),    S(KC_O),    S(KC_E),   S(KC_U),  S(KC_I),  S(KC_D),  S(KC_H),  S(KC_T),  S(KC_N), S(KC_S),  KC_MINS,                KC_TRNS,  KC_TRNS, \
        KC_TRNS,  KC_QUOT,    S(KC_Q),    S(KC_J),   S(KC_K),  S(KC_X),  S(KC_B),  S(KC_M),  S(KC_W),  S(KC_V), S(KC_Z),  KC_TRNS,                KC_TRNS,           \
        KC_TRNS,  KC_TRNS,    KC_TRNS,                                 KC_TRNS,                        KC_TRNS, KC_TRNS,  KC_TRNS,    KC_TRNS,    KC_TRNS,  KC_TRNS) 
/*TD(SHIFT_UNDERSCORE)*/
/*MT(MOD_MEH, KC_SPC)*/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [WIN_DVORAK] = PRIME_DVORAK(KC_LCTL, KC_LGUI, KC_LALT, KC_RALT, MO(WIN_FN), WIN_QWERTY, WIN_DVORAK_SHIFT),
    [WIN_DVORAK_SHIFT] = PRIME_DVORAK_SHIFT(),
    [WIN_QWERTY] = QWERTY(KC_LCTL, KC_LGUI, KC_LALT, KC_RALT, MO(WIN_FN), WIN_QWERTY),

    [WIN_FN] = LAYOUT_ansi_82(
        KC_TRNS,  KC_BRID,  KC_BRIU,  KC_TASK,  KC_FILE,  RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,  KC_TRNS,            RGB_TOG,
        KC_TRNS,  BT_HST1,  BT_HST2,  BT_HST3,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,
        RGB_TOG,  RGB_MOD,  RGB_VAI,  RGB_HUI,  RGB_SAI,  RGB_SPI,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,
        KC_TRNS,  RGB_RMOD, RGB_VAD,  RGB_HUD,  RGB_SAD,  RGB_SPD,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,            KC_END,
        KC_TRNS,            KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  BAT_LVL,  NK_TOGG,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,  KC_TRNS,
        KC_TRNS,  KC_TRNS,  KC_TRNS,                                KC_TRNS,                                KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS),
    
    [MAC_DVORAK] = PRIME_DVORAK(KC_LCTL, KC_LOPTN, KC_LCMMD, KC_LCMMD, MO(MAC_FN), MAC_QWERTY, MAC_DVORAK_SHIFT),
    [MAC_DVORAK_SHIFT] = PRIME_DVORAK_SHIFT(),
    [MAC_QWERTY] = QWERTY(KC_LCTL, KC_LOPTN, KC_LCMMD, KC_LCMMD, MO(MAC_FN), MAC_QWERTY),
    
    [MAC_FN] = LAYOUT_ansi_82(
        KC_TRNS,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_TRNS,            RGB_TOG,
        KC_TRNS,  BT_HST1,  BT_HST2,  BT_HST3,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,
        RGB_TOG,  RGB_MOD,  RGB_VAI,  RGB_HUI,  RGB_SAI,  RGB_SPI,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,
        KC_TRNS,  RGB_RMOD, RGB_VAD,  RGB_HUD,  RGB_SAD,  RGB_SPD,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,            KC_END,
        KC_TRNS,            KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  BAT_LVL,  NK_TOGG,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,  KC_TRNS,
        KC_TRNS,  KC_TRNS,  KC_TRNS,                                KC_TRNS,                                KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS)
};

bool dip_switch_update_user(uint8_t index, bool active) 
{
    if (index == 0)
    {
        default_layer_set(1UL << (active ? WIN_DVORAK : MAC_DVORAK));
    } 
    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) 
{
    switch (get_highest_layer(state)) 
    {
    case WIN_DVORAK:
    case WIN_DVORAK_SHIFT:
    case MAC_DVORAK:
    case MAC_DVORAK_SHIFT:
        rgblight_sethsv(203,  255, 255);
        break;
    case WIN_QWERTY:
    case MAC_QWERTY:
        rgblight_sethsv(179,  155, 255);
        break;
    default: //  for any other layers, or the default layer
        rgblight_sethsv(203,  255, 255);
        break;
    }

    return state;
}

#if defined(ENCODER_MAP_ENABLE)
#define VOLUME_KNOB {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)}
#define RGB_KNOB {ENCODER_CCW_CW(RGB_VAD, RGB_VAI)}
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [WIN_QWERTY] = VOLUME_KNOB,
    [WIN_DVORAK] = VOLUME_KNOB,
    [WIN_DVORAK_SHIFT] = VOLUME_KNOB,
    [WIN_FN] = RGB_KNOB,
    [MAC_QWERTY] = VOLUME_KNOB,
    [MAC_DVORAK] = VOLUME_KNOB,
    [MAC_DVORAK_SHIFT] = VOLUME_KNOB,
    [MAC_FN] = RGB_KNOB
};
#endif // ENCODER_MAP_ENABLE

// Determine the tapdance state to return
td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->pressed) return TD_SINGLE_HOLD;
        else return TD_SINGLE_TAP;
    }

    else return TD_UNKNOWN; // Any number higher than the maximum state value you return above
}

// Handle the possible states for each tapdance keycode you define:

void shift_underscore_finished(tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_SINGLE_TAP:
            register_code16(KC_UNDS);
            break;
        case TD_SINGLE_HOLD:
            register_mods(MOD_BIT(KC_LSFT)); // For a layer-tap key, use `layer_on(_MY_LAYER)` here
            break;
        default:
            break;
    }
}

void shift_underscore_reset(tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case TD_SINGLE_TAP:
            unregister_code16(KC_UNDS);
            break;
        case TD_SINGLE_HOLD:
            unregister_mods(MOD_BIT(KC_LSFT)); // For a layer-tap key, use `layer_off(_MY_LAYER)` here
            break;
        default:
            break;
    }
}

