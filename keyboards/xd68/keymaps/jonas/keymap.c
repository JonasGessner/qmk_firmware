#include QMK_KEYBOARD_H

#include "jonas.h"
#include "config.h"
#include "keymap_german.h"
#include "xd68.h"

#include <print.h>

// Tap Dance declarations
enum {
    TD_CTRL_CAPS,
};

// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_CTRL_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_LCTRL, KC_CAPS),
};

#define LAYER_MAC 0
#define LAYER_WINDOWS 2

// Null should be higher than coding layer and base layers
#define LAYER_NULL 3

// momentary layers, should have the highest numbers.
#define LAYER_FN 4

layer_state_t default_layer_state_set_user(layer_state_t state) {
    layer_state_t layer = get_highest_layer(state);

    eeconfig_update_default_layer(1U << layer);

    return state;
}

// To debug: uncomment and set CONSOLE_ENABLE=yes in rules.mk
void keyboard_post_init_user(void) {
    // Customise these values to desired behaviour
    // debug_enable = true;
    // debug_matrix = true;
    // debug_keyboard = true;
    // debug_mouse=true;
}

// Row 1: 15 keys
// Row 2: 14 keys (without enter)
// Row 3: 15 keys (with enter)
// Row 4: 15 keys
// Row 5: 10 keys

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Keymap LAYER_MAC: (Base Layer) Default Layer
     * ,----------------------------------------------------------------.
     * |Esc | 1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  ß| ´ |Backsp |Vol+|
     * |----------------------------------------------------------------|
     * |Tab  |  Q|  W|  E|  R|  T|  Z|  U|  I|  O|  P|  Ü|  +|     |Vol-|
     * |-------------------------------------------------------    -----|
     * |Ctrl   |  A|  S|  D|  F|  G|  H|  J|  K|  L|  Ö| Ä|  #|Entr|Play|
     * |----------------------------------------------------------------|
     * |Shift| <> |  Y|  X|  C|  V|  B|  N|  M|  ,|  .| -|Rshift|Up| >> |
     * |----------------------------------------------------------------|
     * |Ctrl|Alt |Cmd |        Space          |Cmd|Fn |Ctlr|Lef|Dow|Rig |
     * `----------------------------------------------------------------'
     */
    [LAYER_MAC] = LAYOUT_65_iso(KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, DE_SS, DE_ACUT, KC_BSPC, KC__VOLUP,                      //
                                KC_TAB, DE_Q, DE_W, DE_E, DE_R, DE_T, DE_Z, DE_U, DE_I, DE_O, DE_P, DE_UE, DE_PLUS, KC__VOLDOWN,                             //
                                TD(TD_CTRL_CAPS), DE_A, DE_S, DE_D, DE_F, DE_G, DE_H, DE_J, DE_K, DE_L, DE_OE, DE_AE, DE_HASH, KC_ENT, KC_MEDIA_PLAY_PAUSE,  //
                                KC_LSFT, DE_LESS, DE_Y, DE_X, DE_C, DE_V, DE_B, DE_N, DE_M, DE_COMM, DE_DOT, DE_MINS, KC_RSFT, KC_UP, KC_MEDIA_NEXT_TRACK,   //
                                KC_LCTL, KC_LALT, KC_LGUI, KC_SPC, KC_RGUI, MO(LAYER_FN), KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT),

    /* Keymap LAYER_WINDOWS
     * ,----------------------------------------------------------------.
     * |Esc | 1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  ß| ´ |Backsp |Vol+|
     * |----------------------------------------------------------------|
     * |Tab  |  Q|  W|  E|  R|  T|  Z|  U|  I|  O|  P|  Ü|  +|     |Vol-|
     * |-------------------------------------------------------    -----|
     * |CAPS   |  A|  S|  D|  F|  G|  H|  J|  K|  L|  Ö| Ä|  #|Entr|Play|
     * |----------------------------------------------------------------|
     * |Shift| <> |  Y|  X|  C|  V|  B|  N|  M|  ,|  .| -|Rshift|Up| >> |
     * |----------------------------------------------------------------|
     * |Ctrl|AltGr|Ctrl|        Space          |Alt|Fn |Win|Lef|Dow|Rig |
     * `----------------------------------------------------------------'
     */
    [LAYER_WINDOWS] = LAYOUT_65_iso(KC_ESC, DE_1, DE_2, DE_3, DE_4, DE_5, DE_6, DE_7, DE_8, DE_9, DE_0, DE_SS, DE_ACUT, KC_BSPC, KC_AUDIO_VOL_UP,               //
                                    KC_TAB, DE_Q, DE_W, DE_E, DE_R, DE_T, DE_Z, DE_U, DE_I, DE_O, DE_P, DE_UE, DE_PLUS, KC_AUDIO_VOL_DOWN,                      //
                                    KC_CAPS, DE_A, DE_S, DE_D, DE_F, DE_G, DE_H, DE_J, DE_K, DE_L, DE_OE, DE_AE, DE_HASH, KC_ENT, KC_MEDIA_PLAY_PAUSE,          //
                                    KC_LSFT, DE_LESS, DE_Y, DE_X, DE_C, DE_V, DE_B, DE_N, DE_M, DE_COMM, DE_DOT, DE_MINS, KC_RSFT, KC_UP, KC_MEDIA_NEXT_TRACK,  //
                                    KC_LCTL, KC_RALT, KC_LCTL, KC_SPC, KC_LALT, MO(LAYER_FN), KC_LGUI, KC_LEFT, KC_DOWN, KC_RGHT),

    [LAYER_NULL] = LAYOUT_65_iso(XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  //
                                 XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,           //
                                 XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  //
                                 XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  //
                                 XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, MO(LAYER_FN), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX),

    /* Keymap LAYER_FN: Function Layer 1
     * ,----------------------------------------------------------------.
     * |   | F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12| Delete|Home|
     * |----------------------------------------------------------------|
     * |RESET|   | WIN |   |   |   |   |   |   |   |NULL|  |   |   |PGUP|
     * |-------------------------------------------------------    -----|
     * |       |   |   |   |  |  |  |  |OVRD_TGL|  |   |  |   |    |PGDN|
     * |----------------------------------------------------------------|
     * |    |    |    |    |   |   |   |   | MAC |   |   |   |   |  |END|
     * |----------------------------------------------------------------|
     * |    |    |    |                       |   |   |   |    |   |    |
     * `----------------------------------------------------------------'
     */
    [LAYER_FN] = LAYOUT_65_iso(_______, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, _______, KC_HOME,                                          //
                               RESET, _______, DF(LAYER_WINDOWS), _______, _______, _______, _______, _______, _______, DF(LAYER_NULL), _______, _______, _______, KC_PGUP,               //
                               _______, _______, _______, _______, _______, _______, _______, _______, KEY_OVERRIDE_TOGGLE, _______, _______, _______, _______, _______, KC_PGDN,         //
                               _______, _______, _______, _______, TOGGLE_CODING_OVERLAY, _______, _______, _______, DF(LAYER_MAC), _______, _______, _______, _______, _______, KC_END,  //
                               _______, _______, _______, _______, _______, _______, _______, _______, _______, _______),
};

/*
Blank template:

LAYOUT_65_iso(_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, //
                                           _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          //
                                           _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, //
                                           _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, //
                                           _______, _______, _______, _______, _______, _______, _______, _______, _______, _______),

                                           */

#include "jonas.c"
