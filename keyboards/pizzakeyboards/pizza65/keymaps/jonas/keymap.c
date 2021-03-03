#include QMK_KEYBOARD_H

#include "jonas.h"
#include "config.h"
#include "keymap_german.h"
#include "pizza65.h"

#include <print.h>

// clang-format off

tapping_action_t **taps = (tapping_action_t *[]){
    &enable_caps_tap,
    &disable_caps_tap,
    &toggle_coding_mode_tap,
    NULL
};

const key_override_t **key_overrides = (const key_override_t *[]){
    // Shared
    &backSpaceDeleteOverride,
    &prevTrackOverride,
    &hatEscOverride,
    &brightnessUpOverride,
    &brightnessDownOverride,

    //Mac
    &deleteLineOverrideMac,
    &lockScreenOverrideMac,

    &smallBrightnessUpOverrideMac,
    &smallBrightnessDownOverrideMac,
    &smallVolumeUpOverrideMac,
    &smallVolumeDownOverrideMac,

    // Coding mode overrides
    &curlyLeftBraceCodingModeOverride,
    &squareLeftBraceCodingModeOverride,
    &normalOeCodingModeOverride,

    &curlyRightBraceCodingModeOverride,
    &squareRightBraceCodingModeOverride,
    &normalAeCodingModeOverride,

    &leftBraceCodingModeOverride,
    &normalssCodingModeOverride,
    &rightBraceCodingModeOverride,
    &normalAcutCodingModeOverride,

    &slashCodingModeOverride,
    &pipeCodingModeOverride,
    &backslashCodingModeOverride,
    &normalUeCodingModeOverride,

    // Windows-only overrides
    &lockScreenOverrideWindows,
    &WIN_SHORTCUT_OVERRIDE(KC_A),
    &WIN_SHORTCUT_OVERRIDE(KC_S),
    &WIN_SHORTCUT_OVERRIDE(KC_X),
    &WIN_SHORTCUT_OVERRIDE(KC_C),
    &WIN_SHORTCUT_OVERRIDE(KC_V),
    &WIN_SHORTCUT_OVERRIDE(KC_Z),
    &WIN_SHORTCUT_OVERRIDE(KC_T),
    &WIN_SHORTCUT_OVERRIDE(KC_W),
    &WIN_SHORTCUT_OVERRIDE(KC_R),
    &WIN_SHORTCUT_OVERRIDE(KC_F),
    &WIN_SHORTCUT_OVERRIDE(KC_N),
    &WIN_SHORTCUT_OVERRIDE(KC_P),

    // Extra stuff
    &fnOverride,

    NULL
};

// clang-format on

// Row 1: 15 keys
// Row 2: 14 keys (without enter)
// Row 3: 15 keys (with enter)
// Row 4: 15 keys
// Row 5: 9 keys

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
    [LAYER_MAC] = LAYOUT_65_iso_blocker(KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, DE_SS, DE_ACUT, KC_BSPC, KC_AUDIO_VOL_UP,               //
                                        KC_TAB, DE_Q, DE_W, DE_E, DE_R, DE_T, DE_Z, DE_U, DE_I, DE_O, DE_P, DE_UE, DE_PLUS, KC_AUDIO_VOL_DOWN,                      //
                                        KC_LCTL, DE_A, DE_S, DE_D, DE_F, DE_G, DE_H, DE_J, DE_K, DE_L, DE_OE, DE_AE, DE_HASH, KC_ENT, KC_MEDIA_PLAY_PAUSE,          //
                                        KC_LSFT, DE_LESS, DE_Y, DE_X, DE_C, DE_V, DE_B, DE_N, DE_M, DE_COMM, DE_DOT, DE_MINS, KC_RSFT, KC_UP, KC_MEDIA_NEXT_TRACK,  //
                                        KC_LCTL, KC_LALT, KC_LGUI, KC_SPC, KC_RGUI, DE_N, KC_LEFT, KC_DOWN, KC_RGHT),

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
    [LAYER_WINDOWS] = LAYOUT_65_iso_blocker(KC_ESC, DE_1, DE_2, DE_3, DE_4, DE_5, DE_6, DE_7, DE_8, DE_9, DE_0, DE_SS, DE_ACUT, KC_BSPC, KC_AUDIO_VOL_UP,               //
                                            KC_TAB, DE_Q, DE_W, DE_E, DE_R, DE_T, DE_Z, DE_U, DE_I, DE_O, DE_P, DE_UE, DE_PLUS, KC_AUDIO_VOL_DOWN,                      //
                                            KC_CAPS, DE_A, DE_S, DE_D, DE_F, DE_G, DE_H, DE_J, DE_K, DE_L, DE_OE, DE_AE, DE_HASH, KC_ENT, KC_MEDIA_PLAY_PAUSE,          //
                                            KC_LSFT, DE_LESS, DE_Y, DE_X, DE_C, DE_V, DE_B, DE_N, DE_M, DE_COMM, DE_DOT, DE_MINS, KC_RSFT, KC_UP, KC_MEDIA_NEXT_TRACK,  //
                                            KC_LCTL, KC_RALT, KC_LGUI, KC_SPC, KC_RALT, MO(LAYER_FN), KC_LEFT, KC_DOWN, KC_RGHT),

    [LAYER_NULL] = LAYOUT_65_iso_blocker(XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  //
                                         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,           //
                                         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  //
                                         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  //
                                         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, MO(LAYER_FN), XXXXXXX, XXXXXXX, XXXXXXX),

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
    [LAYER_FN] = LAYOUT_65_iso_blocker(_______, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, _______, KC_HOME,                                          //
                                       RESET, _______, DF(LAYER_WINDOWS), _______, _______, _______, _______, _______, _______, DF(LAYER_NULL), _______, _______, _______, KC_PGUP,               //
                                       _______, _______, _______, _______, _______, _______, _______, _______, KEY_OVERRIDE_TOGGLE, _______, _______, _______, _______, _______, KC_PGDN,         //
                                       _______, _______, _______, _______, TOGGLE_CODING_OVERLAY, _______, _______, _______, DF(LAYER_MAC), _______, _______, _______, _______, _______, KC_END,  //
                                       _______, _______, _______, _______, _______, _______, _______, _______, _______),
};

/*
Blank template:

LAYOUT_65_iso_blocker(_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, //
                                           _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          //
                                           _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, //
                                           _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, //
                                           _______, _______, _______, _______, _______, _______, _______, _______, _______),

                                           */
