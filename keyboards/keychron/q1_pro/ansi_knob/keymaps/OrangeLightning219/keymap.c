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
#include "print.h"

// clang-format off
enum layers{  
  MAC_QWERTY,
  MAC_FN,

  WIN_QWERTY,
  WIN_FN,
};

enum custom_keycodes
{
    SPACE_UNDERSCORE = SAFE_RANGE,
    INV_QUOT,
    INV_1,
    INV_2,
    INV_3,
    INV_4,
    INV_5,
    INV_6,
    INV_7,
    INV_8,
    INV_9,
    INV_0,
    INV_LBRC,
    INV_RBRC
};

#define QWERTY(LCTL, META, LALT, RALT, FN) LAYOUT_ansi_82(                                                                                                                            \
        KC_ESC,                      KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,     KC_F11,     KC_F12,   KC_DEL,   KC_MUTE, \
        KC_GRV,                      KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,       KC_MINS,    KC_EQL,   KC_BSPC,  KC_PGUP, \
        KC_TAB,                      KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,       KC_LBRC,    KC_RBRC,  KC_BSLS,  KC_PGDN, \
        KC_ESC,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,  KC_ENT,                                     KC_HOME, \
        KC_LSFT,                     KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,    KC_RSFT,              KC_UP,             \
        LCTL,                        META,     LALT,                                 SPACE_UNDERSCORE,               RALT,     FN,         KC_RCTL,    KC_LEFT,  KC_DOWN,  KC_RGHT)

/*
NOTE: Inverted symbols
#define QWERTY(LCTL, META, LALT, RALT, FN) LAYOUT_ansi_82(                                                                                                                            \
        KC_ESC,                      KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,     KC_F11,     KC_F12,   KC_DEL,   KC_MUTE, \
        KC_GRV,                      INV_1,    INV_2,    INV_3,    INV_4,    INV_5,    INV_6,    INV_7,    INV_8,    INV_9,    INV_0,      KC_MINS,    KC_EQL,   KC_BSPC,  KC_PGUP, \
        KC_TAB,                      KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,       INV_LBRC,   INV_RBRC, KC_BSLS,  KC_PGDN, \
        KC_ESC,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  INV_QUOT, KC_ENT,                                     KC_HOME, \
        KC_LSFT,                     KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,    KC_RSFT,              KC_UP,             \
        LCTL,                        META,     LALT,                                 SPACE_UNDERSCORE,               RALT,     FN,         KC_RCTL,    KC_LEFT,  KC_DOWN,  KC_RGHT)
*/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [MAC_QWERTY] = QWERTY(KC_LCTL, KC_LOPTN, KC_LCMMD, KC_LCMMD, MO(MAC_FN)),
    
    [MAC_FN] = LAYOUT_ansi_82(
        KC_TRNS,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_TRNS,            RGB_TOG,
        KC_TRNS,  BT_HST1,  BT_HST2,  BT_HST3,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,
        RGB_TOG,  RGB_MOD,  RGB_VAI,  RGB_HUI,  RGB_SAI,  RGB_SPI,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,
        KC_TRNS,  RGB_RMOD, RGB_VAD,  RGB_HUD,  RGB_SAD,  RGB_SPD,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,            KC_END,
        KC_TRNS,            KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  BAT_LVL,  NK_TOGG,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,  KC_TRNS,
        KC_TRNS,  KC_TRNS,  KC_TRNS,                                KC_TRNS,                                KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS),

    [WIN_QWERTY] = QWERTY(KC_LCTL, KC_LGUI, KC_LALT, KC_RALT, MO(WIN_FN)),

    [WIN_FN] = LAYOUT_ansi_82(
        KC_TRNS,  KC_BRID,  KC_BRIU,  KC_TASK,  KC_FILE,  RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,  KC_TRNS,            RGB_TOG,
        KC_TRNS,  BT_HST1,  BT_HST2,  BT_HST3,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,
        RGB_TOG,  RGB_MOD,  RGB_VAI,  RGB_HUI,  RGB_SAI,  RGB_SPI,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,
        KC_TRNS,  RGB_RMOD, RGB_VAD,  RGB_HUD,  RGB_SAD,  RGB_SPD,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,            KC_END,
        KC_TRNS,            KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  BAT_LVL,  NK_TOGG,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,  KC_TRNS,
        KC_TRNS,  KC_TRNS,  KC_TRNS,                                KC_TRNS,                                KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS),

};

#define CUSTOM_KEY(keycode, normal, normal_with_shift, shifted, shifted_without_shift) \
case keycode:                                                       \
{                                                                   \
    if (shift_active)                                               \
    {                                                               \
        if (record->event.pressed)                                  \
        {                                                           \
            if (shifted_without_shift) { del_mods(MOD_MASK_SHIFT); }\
            register_code(shifted);                                 \
            if (shifted_without_shift) { set_mods(mod_state); }     \
        }                                                           \
        else                                                        \
        {                                                           \
            unregister_code(shifted);                               \
            unregister_code(normal);                                \
        }                                                           \
    }                                                               \
    else                                                            \
    {                                                               \
        if (record->event.pressed)                                  \
        {                                                           \
            if (normal_with_shift) { add_mods(MOD_BIT(KC_LSFT)); }  \
            register_code(normal);                                  \
            if (normal_with_shift) { del_mods(MOD_BIT(KC_LSFT)); }  \
        }                                                           \
        else                                                        \
        {                                                           \
            unregister_code(normal);                                \
            unregister_code(shifted);                               \
        }                                                           \
    }                                                               \
    return false;                                                   \
}                                                                   \
break

#define INVERSE_KEY(keycode, key) CUSTOM_KEY(keycode, key, true, key, true)

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
    uint8_t mod_state = get_mods();
    uint8_t shift_active = mod_state & MOD_MASK_SHIFT;
    switch (keycode)
    {
        CUSTOM_KEY(SPACE_UNDERSCORE, KC_SPC, false, KC_MINS, false);
        // INVERSE_KEY(INV_QUOT, KC_QUOT);
        // INVERSE_KEY(INV_1, KC_1);
        // INVERSE_KEY(INV_2, KC_2);
        // INVERSE_KEY(INV_3, KC_3);
        // INVERSE_KEY(INV_4, KC_4);
        // INVERSE_KEY(INV_5, KC_5);
        // INVERSE_KEY(INV_6, KC_6);
        // INVERSE_KEY(INV_7, KC_7);
        // INVERSE_KEY(INV_8, KC_8);
        // INVERSE_KEY(INV_9, KC_9);
        // INVERSE_KEY(INV_0, KC_0);
        // INVERSE_KEY(INV_LBRC, KC_LBRC);
        // INVERSE_KEY(INV_RBRC, KC_RBRC);
    }
    return true;
}

#if defined(ENCODER_MAP_ENABLE)
#define VOLUME_KNOB {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)}
#define RGB_KNOB {ENCODER_CCW_CW(RGB_VAD, RGB_VAI)}
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [MAC_QWERTY] = VOLUME_KNOB,
    [MAC_FN] = RGB_KNOB,
    [WIN_QWERTY] = VOLUME_KNOB,
    [WIN_FN] = RGB_KNOB,
};
#endif // ENCODER_MAP_ENABLE

void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  debug_enable=true;
//   debug_matrix=true;
  debug_keyboard=true;
  //debug_mouse=true;
}