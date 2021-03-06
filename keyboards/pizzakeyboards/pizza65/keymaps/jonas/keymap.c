#include QMK_KEYBOARD_H

#include "jonas.h"
#include "config.h"
#include "keymap_german.h"
#include "pizza65.h"

#include <print.h>

// clang-format off

enum custom_codes {
    KC_EMOJI_FN = SAFE_RANGE_USERSPACE,
};

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

    //Mac
    &deleteLineOverrideMac,
    &lockScreenOverrideMac,

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

    // // Windows-only overrides
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
     * |Esc | 1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  ß| ´ |Backsp |Mute|
     * |----------------------------------------------------------------|
     * |Tab  |  Q|  W|  E|  R|  T|  Z|  U|  I|  O|  P|  Ü|  +|     |Play|
     * |-------------------------------------------------------    -----|
     * |Ctrl   |  A|  S|  D|  F|  G|  H|  J|  K|  L|  Ö| Ä|  #|Entr| >> |
     * |----------------------------------------------------------------|
     * |Shift| <> |  Y|  X|  C|  V|  B|  N|  M|  ,|  .| -|Rshift|Up|Fn/emoji|
     * |----------------------------------------------------------------|
     * |Ctrl|Alt |Cmd |        Space          |Cmd|Ctlr|   |Lef|Dow|Rig |
     * `----------------------------------------------------------------'
     */
    [LAYER_MAC] = LAYOUT_65_iso_blocker(KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, DE_SS, DE_ACUT, KC_BSPC, KC_AUDIO_MUTE,         //
                                        KC_TAB, DE_Q, DE_W, DE_E, DE_R, DE_T, DE_Z, DE_U, DE_I, DE_O, DE_P, DE_UE, DE_PLUS, KC_MEDIA_PLAY_PAUSE,            //
                                        KC_LCTL, DE_A, DE_S, DE_D, DE_F, DE_G, DE_H, DE_J, DE_K, DE_L, DE_OE, DE_AE, DE_HASH, KC_ENT, KC_MEDIA_NEXT_TRACK,  //
                                        KC_LSFT, DE_LESS, DE_Y, DE_X, DE_C, DE_V, DE_B, DE_N, DE_M, DE_COMM, DE_DOT, DE_MINS, KC_RSFT, KC_UP, KC_EMOJI_FN,  //
                                        KC_LCTL, KC_LALT, KC_LGUI, KC_SPC, KC_RGUI, KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT),

    /* Keymap LAYER_WINDOWS
     * ,----------------------------------------------------------------.
     * |Esc | 1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  ß| ´ |Backsp |Mute|
     * |----------------------------------------------------------------|
     * |Tab  |  Q|  W|  E|  R|  T|  Z|  U|  I|  O|  P|  Ü|  +|     |Play|
     * |-------------------------------------------------------    -----|
     * |CAPS   |  A|  S|  D|  F|  G|  H|  J|  K|  L|  Ö| Ä|  #|Entr| >> |
     * |----------------------------------------------------------------|
     * |Shift| <> |  Y|  X|  C|  V|  B|  N|  M|  ,|  .| -|Rshift|Up|Fn/emoji|
     * |----------------------------------------------------------------|
     * |Ctrl|AltGr|Ctrl|        Space          |Alt|Win |  |Lef|Dow|Rig |
     * `----------------------------------------------------------------'
     */
    [LAYER_WINDOWS] = LAYOUT_65_iso_blocker(KC_ESC, DE_1, DE_2, DE_3, DE_4, DE_5, DE_6, DE_7, DE_8, DE_9, DE_0, DE_SS, DE_ACUT, KC_BSPC, KC_AUDIO_MUTE,         //
                                            KC_TAB, DE_Q, DE_W, DE_E, DE_R, DE_T, DE_Z, DE_U, DE_I, DE_O, DE_P, DE_UE, DE_PLUS, KC_MEDIA_PLAY_PAUSE,            //
                                            KC_CAPS, DE_A, DE_S, DE_D, DE_F, DE_G, DE_H, DE_J, DE_K, DE_L, DE_OE, DE_AE, DE_HASH, KC_ENT, KC_MEDIA_NEXT_TRACK,  //
                                            KC_LSFT, DE_LESS, DE_Y, DE_X, DE_C, DE_V, DE_B, DE_N, DE_M, DE_COMM, DE_DOT, DE_MINS, KC_RSFT, KC_UP, KC_EMOJI_FN,  //
                                            KC_LCTL, KC_RALT, KC_LGUI, KC_SPC, KC_RALT, MO(LAYER_FN), KC_LEFT, KC_DOWN, KC_RGHT),

    [LAYER_NULL] = LAYOUT_65_iso_blocker(XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       //
                                         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                //
                                         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       //
                                         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, MO(LAYER_FN),  //
                                         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, MO(LAYER_FN), XXXXXXX, XXXXXXX, XXXXXXX),

    /* Keymap LAYER_FN: Function Layer 1
     * ,----------------------------------------------------------------.
     * |   | F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12| Delete|Home|
     * |----------------------------------------------------------------|
     * |RESET|   | WIN |   |   |   |   |   |   |   |NULL|  |   |   |PGUP|
     * |-------------------------------------------------------    -----|
     * | |AUDIO|CK_TOGG|CK_UP|CK_DOWN|CK_RST| | |OVRD_TGL| | | | | |PGDN|
     * |----------------------------------------------------------------|
     * |   |  |MU_TOG|MU_MOD|CODING|  |  |  |MAC|   |   |   |   |   |END|
     * |----------------------------------------------------------------|
     * |    |SPAM_ALT|    |                   |   |   |   |    |   |    |
     * `----------------------------------------------------------------'
     */
    [LAYER_FN] = LAYOUT_65_iso_blocker(_______, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, _______, KC_HOME,                                        //
                                       RESET, _______, DF(LAYER_WINDOWS), _______, _______, _______, _______, _______, _______, DF(LAYER_NULL), _______, _______, _______, KC_PGUP,             //
                                       _______, AU_TOG, CK_TOGG, CK_UP, CK_DOWN, CK_RST, _______, _______, KEY_OVERRIDE_TOGGLE, _______, _______, _______, _______, _______, KC_PGDN,           //
                                       _______, _______, MU_TOG, MU_MOD, TOGGLE_CODING_OVERLAY, _______, _______, _______, DF(LAYER_MAC), _______, _______, _______, _______, _______, KC_END,  //
                                       _______, SPAM_ALT, _______, _______, _______, _______, _______, _______, _______),
};

/*
Blank template:

LAYOUT_65_iso_blocker(_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, //
                                           _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          //
                                           _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, //
                                           _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, //
                                           _______, _______, _______, _______, _______, _______, _______, _______, _______),

                                           */

// Emoji/fn key

static uint16_t emoji_key_down_time = 0;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (keycode == KC_EMOJI_FN) {
        if (record->event.pressed) {
            layer_on(LAYER_FN);
            emoji_key_down_time = timer_read();
            if (emoji_key_down_time == 0) {
                emoji_key_down_time = 1;
            }
        } else {
            layer_off(LAYER_FN);
            if (emoji_key_down_time != 0 && timer_elapsed(emoji_key_down_time) < 200) {
                tap_code16(C(G(KC_SPACE)));
            }
        }

        return false;
    } else {
        emoji_key_down_time = 0;
    }

    return true;
}

// Encoder

static int16_t clicks = 0;
static int16_t  brightness_clicks = 0;

static uint16_t register_time = 0;

static uint16_t encoder_keycode = 0;

void encoder_update_user(uint8_t index, bool clockwise) {
    if (clockwise) {
        if ((get_mods() & MOD_MASK_CTRL) != 0) {
            brightness_clicks++;
        } else {
            clicks++;
        }
    } else {
        if ((get_mods() & MOD_MASK_CTRL) != 0) {
            brightness_clicks--;
        } else {
            clicks--;
        }
    }
}

uint16_t current_delay = 10;

void matrix_scan_user() {
   if (register_time == 0) {
        
    }
    else if (timer_elapsed(register_time) > current_delay) {
        if (encoder_keycode != 0) {
            unregister_code16(encoder_keycode);

            register_time = timer_read();
            encoder_keycode   = 0;

            current_delay = 10;
            return;
        }
        else {
            current_delay = 10;
        }
    }
    else {
        return;
    }

    if (clicks > 0) {
        if ((get_mods() & MOD_MASK_ALT) != 0) {
            encoder_keycode = A(S(KC__VOLUP));
        }
        else {
            encoder_keycode = KC__VOLUP;
        }
        clicks--;
    }
    else if (clicks < 0) {
        if ((get_mods() & MOD_MASK_ALT) != 0) {
            encoder_keycode = A(S(KC__VOLDOWN));
        } else {
            encoder_keycode = KC__VOLDOWN;
        }
        clicks++;
    } else {
        if (brightness_clicks > 0) {
            if ((get_mods() & MOD_MASK_ALT) != 0) {
                encoder_keycode = A(S(KC_BRMU));
            } else {
                encoder_keycode = KC_BRMU;
            }
            brightness_clicks--;
        } else if (brightness_clicks < 0) {
            if ((get_mods() & MOD_MASK_ALT) != 0) {
                encoder_keycode = A(S(KC_BRMD));
            } else {
                encoder_keycode = KC_BRMD;
            }
            brightness_clicks++;
        } else {
            register_time = 0;
            return;
        }
    }

    register_code16(encoder_keycode);

    register_time = timer_read();
}
