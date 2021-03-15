#include "jonas.h"
#include "keymap_german.h"

// PoC of using key overrides as layer toggle key. Here holding two mods together momentarily activates the FN layer. Use an FN layer without having to use an extra dedicated key to activate it!
bool momentary_layer(bool key_down, void *layer) {
    if (key_down) {
        layer_on((uint8_t)(uintptr_t)layer);
    } else {
        layer_off((uint8_t)(uintptr_t)layer);
    }

    return false;
}

const key_override_t fnOverride = {.trigger_mods      = MOD_BIT(KC_RGUI) | MOD_BIT(KC_RCTL),                                              //
                                   .layers            = ~(1 << LAYER_FN),                                                                 //
                                   .suppressed_mods   = MOD_BIT(KC_RGUI) | MOD_BIT(KC_RCTL),                                              //
                                   .options           = ko_option_no_unregister_on_other_key_down,  //
                                   .negative_mod_mask = (uint8_t) ~(MOD_BIT(KC_RGUI) | MOD_BIT(KC_RCTL)),                                 //
                                   .custom_action     = momentary_layer,                                                                  //
                                   .context           = (void *)LAYER_FN,                                                                 //
                                   .trigger           = KC_NO,                                                                            //
                                   .replacement       = KC_NO,                                                                            //
                                   .enabled           = NULL};

// clang-format off

#define ko_make_with_layers_negmods_and_enabled(trigger_mods_, trigger_key, replacement_key, layer_mask, negative_mask, enabled_) \
    ((const key_override_t){                                                                \
        .trigger_mods                           = (trigger_mods_),                          \
        .layers                                 = (layer_mask),                             \
        .suppressed_mods                        = (trigger_mods_),                          \
        .options                                = ko_options_default,                       \
        .negative_mod_mask                      = (negative_mask),                          \
        .custom_action                          = NULL,                                     \
        .context                                = NULL,                                     \
        .trigger                                = (trigger_key),                            \
        .replacement                            = (replacement_key),                        \
        .enabled                                = (enabled_)                                \
    })

#define ko_make_with_options(trigger_mods_, trigger_key, replacement_key, options_)         \
    ((const key_override_t){                                                                \
        .trigger_mods                           = (trigger_mods_),                          \
        .layers                                 = ~0,                                       \
        .suppressed_mods                        = (trigger_mods_),                          \
        .options                                = (options_),                               \
        .negative_mod_mask                      = 0,                                        \
        .custom_action                          = NULL,                                     \
        .context                                = NULL,                                     \
        .trigger                                = (trigger_key),                            \
        .replacement                            = (replacement_key),                        \
        .enabled                                = NULL                                      \
    })

// clang-format on

bool windows_shortcut_hook(bool key_down, void *ctx) {
    if (key_down) {
        // tap down ctrl together with gui, this prevents the gui tap from opening the start menu
        add_weak_mods(MOD_BIT(KC_LGUI) | MOD_BIT(KC_LCTL));
        send_keyboard_report();
        del_weak_mods(MOD_BIT(KC_LGUI));
        send_keyboard_report();
    }
    else {
        del_weak_mods(MOD_BIT(KC_LCTL));
    }

    return true;
}

/* Cross-platform overrides: */

// maps shift + backspace to delete
const key_override_t backSpaceDeleteOverride = ko_make_with_options(MOD_MASK_SHIFT, KC_BSPACE, KC_DELETE, ko_option_activation_trigger_down | ko_option_no_reregister_trigger);

// ctrl + next track = Previous track
const key_override_t prevTrackOverride = ko_make_with_options(MOD_MASK_CTRL, KC_MEDIA_NEXT_TRACK, KC_MEDIA_PREV_TRACK, ko_option_activation_trigger_down | ko_option_no_reregister_trigger);

// ctlr/alt/cmd + escape = ^. Allow shift down to shift to °
const key_override_t hatEscOverride = ko_make_with_layers_negmods_and_options(MOD_MASK_CAG,
                                                                              KC_ESC,   //
                                                                              DE_CIRC,  //
                                                                              ~0,       //
                                                                              0,        //
                                                                              ko_option_activation_trigger_down | ko_option_one_mod | ko_option_no_reregister_trigger);

// lctrl + vol up = Screen brightness up
const key_override_t brightnessUpOverride = ko_make_with_layers_and_negmods(MOD_BIT(KC_LCTL),
                                                                            KC_AUDIO_VOL_UP,   //
                                                                            KC_BRIGHTNESS_UP,  //
                                                                            ~0,                //
                                                                            MOD_MASK_SA);

// lctrl + vol down = Screenn brightness down
const key_override_t brightnessDownOverride = ko_make_with_layers_and_negmods(MOD_BIT(KC_LCTL),
                                                                              KC_AUDIO_VOL_DOWN,   //
                                                                              KC_BRIGHTNESS_DOWN,  //
                                                                              ~0,                  //
                                                                              MOD_MASK_ALT);

/* Mac overrides: */

// In coding mode the ö and ä keys are mapped to { and }. With the shift key they are shifted to [ and ]. With control give back ö and ä.

// { and [
const key_override_t curlyLeftBraceCodingModeOverride = ko_make_with_layers_negmods_and_enabled(0,
                                                                                                DE_OE,           //
                                                                                                LALT(KC_8),      //
                                                                                                1 << LAYER_MAC,  //
                                                                                                MOD_MASK_CSAG,   //
                                                                                                (bool *)&user_config.raw);

const key_override_t squareLeftBraceCodingModeOverride = ko_make_with_layers_negmods_and_enabled(MOD_MASK_SHIFT,
                                                                                                 DE_OE,           //
                                                                                                 LALT(KC_5),      //
                                                                                                 1 << LAYER_MAC,  //
                                                                                                 MOD_MASK_CAG,    //
                                                                                                 (bool *)&user_config.raw);

const key_override_t normalOeCodingModeOverride = ko_make_with_layers_negmods_and_enabled(MOD_MASK_CTRL,
                                                                                          DE_OE,           //
                                                                                          DE_OE,           //
                                                                                          1 << LAYER_MAC,  //
                                                                                          0,               //
                                                                                          (bool *)&user_config.raw);

// } and ]
const key_override_t curlyRightBraceCodingModeOverride = ko_make_with_layers_negmods_and_enabled(0,
                                                                                                 DE_AE,           //
                                                                                                 LALT(KC_9),      //
                                                                                                 1 << LAYER_MAC,  //
                                                                                                 MOD_MASK_CSAG,   //
                                                                                                 (bool *)&user_config.raw);

const key_override_t squareRightBraceCodingModeOverride = ko_make_with_layers_negmods_and_enabled(MOD_MASK_SHIFT,
                                                                                                  DE_AE,           //
                                                                                                  LALT(KC_6),      //
                                                                                                  1 << LAYER_MAC,  //
                                                                                                  MOD_MASK_CAG,    //
                                                                                                  (bool *)&user_config.raw);

const key_override_t normalAeCodingModeOverride = ko_make_with_layers_negmods_and_enabled(MOD_MASK_CTRL,
                                                                                          DE_AE,           //
                                                                                          DE_AE,           //
                                                                                          1 << LAYER_MAC,  //
                                                                                          0,               //
                                                                                          (bool *)&user_config.raw);

// (
const key_override_t leftBraceCodingModeOverride = ko_make_with_layers_negmods_and_enabled(0,
                                                                                           DE_SS,           //
                                                                                           LSFT(KC_8),      //
                                                                                           1 << LAYER_MAC,  //
                                                                                           MOD_MASK_CSAG,   //
                                                                                           (bool *)&user_config.raw);

const key_override_t normalssCodingModeOverride = ko_make_with_layers_negmods_and_enabled(MOD_MASK_CTRL,
                                                                                          DE_SS,           //
                                                                                          DE_SS,           //
                                                                                          1 << LAYER_MAC,  //
                                                                                          0,               //
                                                                                          (bool *)&user_config.raw);

// )
const key_override_t rightBraceCodingModeOverride = ko_make_with_layers_negmods_and_enabled(0,
                                                                                            DE_ACUT,         //
                                                                                            LSFT(KC_9),      //
                                                                                            1 << LAYER_MAC,  //
                                                                                            MOD_MASK_CSAG,   //
                                                                                            (bool *)&user_config.raw);

const key_override_t normalAcutCodingModeOverride = ko_make_with_layers_negmods_and_enabled(MOD_MASK_CTRL,
                                                                                            DE_ACUT,         //
                                                                                            DE_ACUT,         //
                                                                                            1 << LAYER_MAC,  //
                                                                                            0,               //
                                                                                            (bool *)&user_config.raw);

// / and | and \ .

const key_override_t slashCodingModeOverride = ko_make_with_layers_negmods_and_enabled(0,
                                                                                       DE_UE,           //
                                                                                       LSFT(KC_7),      //
                                                                                       1 << LAYER_MAC,  //
                                                                                       MOD_MASK_CSAG,   //
                                                                                       (bool *)&user_config.raw);

const key_override_t pipeCodingModeOverride = ko_make_with_layers_negmods_and_enabled(MOD_MASK_ALT,
                                                                                      DE_UE,           //
                                                                                      LALT(KC_7),      //
                                                                                      1 << LAYER_MAC,  //
                                                                                      MOD_MASK_CG,     //
                                                                                      (bool *)&user_config.raw);

const key_override_t backslashCodingModeOverride = ko_make_with_layers_negmods_and_enabled(MOD_MASK_SHIFT,
                                                                                           DE_UE,           //
                                                                                           A(S(KC_7)),      //
                                                                                           1 << LAYER_MAC,  //
                                                                                           MOD_MASK_CAG,    //
                                                                                           (bool *)&user_config.raw);

const key_override_t normalUeCodingModeOverride = ko_make_with_layers_negmods_and_enabled(MOD_MASK_CTRL,
                                                                                          DE_UE,           //
                                                                                          DE_UE,           //
                                                                                          1 << LAYER_MAC,  //
                                                                                          MOD_MASK_ALT,    //
                                                                                          (bool *)&user_config.raw);

// This has a strict requirement that no other mods can be down (hence negative_mod_mask is ~MOD_MASK_CS). This is because ctrl + alt + shift + vol up is mapped to shift + alt + brightness up (ctrl + vol up has an override that turns it into brightness up) which is a small brightness increase on macOS.
const key_override_t lockScreenOverrideMac = ko_make_with_layers_negmods_and_options(MOD_MASK_CS,
                                                                                     LOCK_SCREEN_OVERRIDE_KEY,       //
                                                                                     LCTL(LSFT(KC_POWER)),  //
                                                                                     1 << LAYER_MAC,        //
                                                                                     ~MOD_MASK_CS,          //
                                                                                     ko_option_activation_trigger_down | ko_option_no_reregister_trigger);

// shift + backspace = delete. delete + cmd = delete entire line (right of cursor), analog to cmd backspace (deletes left of cursor). Macos does this with ctrl + k for some reason, apparently this is some UNIX thing.
const key_override_t deleteLineOverrideMac = ko_make_with_layers_negmods_and_options(MOD_MASK_SG,
                                                                                     KC_BSPACE,       //
                                                                                     C(KC_K),         //
                                                                                     1 << LAYER_MAC,  //
                                                                                     0,               //
                                                                                     ko_option_activation_trigger_down | ko_option_no_reregister_trigger);

// ctrl + alt + vol up = Little screen brightness up
const key_override_t smallBrightnessUpOverrideMac = ko_make_with_layers(MOD_MASK_CA,             //
                                                                        KC_AUDIO_VOL_UP,         //
                                                                        S(A(KC_BRIGHTNESS_UP)),  //
                                                                        1 << LAYER_MAC);

// lctrl + alt + vol down = Little screenn brightness down
const key_override_t smallBrightnessDownOverrideMac = ko_make_with_layers(MOD_MASK_CA,
                                                                          KC_AUDIO_VOL_DOWN,         //
                                                                          S(A(KC_BRIGHTNESS_DOWN)),  //
                                                                          1 << LAYER_MAC);

// alt/rctrl + vol up = little vol up
const key_override_t smallVolumeUpOverrideMac = ko_make_with_layers_negmods_and_options(MOD_MASK_ALT | MOD_BIT(KC_RCTL),
                                                                                        KC_AUDIO_VOL_UP,        //
                                                                                        S(A(KC_AUDIO_VOL_UP)),  //
                                                                                        1 << LAYER_MAC,         //
                                                                                        MOD_BIT(KC_LCTL),      //
                                                                                        ko_option_one_mod);

// alt/rctrl + vol down = little vol down
const key_override_t smallVolumeDownOverrideMac = ko_make_with_layers_negmods_and_options(MOD_MASK_ALT | MOD_BIT(KC_RCTL),
                                                                                          KC_AUDIO_VOL_DOWN,        //
                                                                                          S(A(KC_AUDIO_VOL_DOWN)),  //
                                                                                          1 << LAYER_MAC,           //
                                                                                          MOD_BIT(KC_LCTL),        //
                                                                                          ko_option_one_mod);

/* Windows key overrides: */
const key_override_t lockScreenOverrideWindows = ko_make_with_layers_negmods_and_options(MOD_MASK_CS,
                                                                                         LOCK_SCREEN_OVERRIDE_KEY,     //
                                                                                         LGUI(KC_L),          //
                                                                                         1 << LAYER_WINDOWS,  //
                                                                                         ~MOD_MASK_CS,        //
                                                                                         ko_option_activation_trigger_down | ko_option_no_reregister_trigger);
