#include "jonas.h"

user_config_t user_config;

void matrix_init_user(void) { user_config.raw = eeconfig_read_user(); }

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case TOGGLE_CODING_OVERLAY:
            if (!record->event.pressed) {
                user_config.coding_overlay_active = !user_config.coding_overlay_active;
                eeconfig_update_user(user_config.raw);
            }
            return false;
        default:
            return true;
    }
}

// PoC of using key overrides as layer toggle key. Here holding two mods together momentarily activates the FN layer. Use an FN layer without having to use an extra dedicated key to activate it!
bool momentary_layer(bool key_down, void *layer) {
    if (key_down) {
        layer_on((uint8_t)(uintptr_t)layer);
    } else {
        layer_off((uint8_t)(uintptr_t)layer);
    }

    return false;
}

const key_override_t fnOverride = {.trigger_modifiers         = MOD_BIT(KC_RGUI) | MOD_BIT(KC_RCTL),     //
                             .layers                    = ~(1 << LAYER_FN),                        //
                             .suppressed_mods           = MOD_BIT(KC_RGUI) | MOD_BIT(KC_RCTL),     //
                             .allowed_activation_events = ko_activation_events_default,            //
                             .options                   = ko_option_exclusive_key_on_activate,     //
                             .negative_modifier_mask    = (uint8_t)~(MOD_BIT(KC_RGUI) | MOD_BIT(KC_RCTL)),  //
                             .custom_action             = momentary_layer,                         //
                             .context                   = (void *)LAYER_FN,                        //
                             .trigger                   = KC_NO,                                   //
                             .replacement               = KC_NO,                                   //
                             .enabled                   = NULL};

// maps shift + backspace to delete
const key_override_t backSpaceDeleteOverride = ko_make_basic(MOD_MASK_SHIFT, KC_BSPACE, KC_DELETE);

// ctrl/alt/cmd/shift + next track = Previous track
const key_override_t prevTrackOverride = {.trigger_modifiers                   = MOD_MASK_CSAG,             //
                                    .layers                              = ~0,                        //
                                    .suppressed_mods                     = MOD_MASK_CSAG,             //
                                    .allowed_activation_events           = ko_activation_events_all,  //
                                    .options                             = ko_option_one_mod,         //
                                    .negative_modifier_mask              = 0,                         //
                                    .custom_action                       = NULL,                      //
                                    .context                             = NULL,                      //
                                    .trigger                             = KC_MEDIA_NEXT_TRACK,       //
                                    .replacement                         = KC_MEDIA_PREV_TRACK,       //
                                    .enabled                             = NULL};

// In coding mode the ö and ä keys are mapped to { and }. With the shift key they are shifted to [ and ]. With control give back ö and ä.

// { and [
const key_override_t curlyLeftBraceCodingModeOverride = {.trigger_modifiers                   = 0,               //
                                                   .layers                              = 1 << LAYER_MAC,  //
                                                   .suppressed_mods                     = 0,               //
                                          .allowed_activation_events = ko_activation_events_default, //
                                          .options = ko_option_exclusive_key_during_active, //
                                                   .negative_modifier_mask              = MOD_MASK_CSAG,   //
                                                   .custom_action                       = NULL,            //
                                                   .context                             = NULL,            //
                                                   .trigger                             = DE_OE,           //
                                                   .replacement                         = LALT(KC_8),      //
                                                   .enabled                             = (bool *)&user_config.raw};

const key_override_t squareLeftBraceCodingModeOverride = {.trigger_modifiers                   = MOD_MASK_SHIFT,  //
                                                    .suppressed_mods                     = MOD_MASK_SHIFT,  //
                                                    .layers                              = 1 << LAYER_MAC,  //
                                          .allowed_activation_events = ko_activation_events_default, //
                                          .options = ko_option_exclusive_key_during_active, //
                                                    .negative_modifier_mask              = MOD_MASK_CAG,    //
                                                    .custom_action                       = NULL,            //
                                                    .context                             = NULL,            //
                                                    .trigger                             = DE_OE,           //
                                                    .replacement                         = LALT(KC_5),      //
                                                    .enabled                             = (bool *)&user_config.raw};

const key_override_t normalOeCodingModeOverride = {.trigger_modifiers                   = MOD_MASK_CTRL,   //
                                             .layers                              = 1 << LAYER_MAC,  //
                                             .suppressed_mods                     = MOD_MASK_CTRL,   //
                                    .allowed_activation_events           = ko_activation_events_all,  //
                                    .options                             = ko_option_one_mod,         //
                                             .negative_modifier_mask              = 0,               //
                                             .custom_action                       = NULL,            //
                                             .context                             = NULL,            //
                                             .trigger                             = DE_OE,           //
                                             .replacement                         = DE_OE,           //
                                             .enabled                             = (bool *)&user_config.raw};

// } and ]
const key_override_t curlyRightBraceCodingModeOverride = {.trigger_modifiers                   = 0,               //
                                                    .layers                              = 1 << LAYER_MAC,  //
                                                    .suppressed_mods                     = 0,               //
                                          .allowed_activation_events = ko_activation_events_default, //
                                          .options = ko_option_exclusive_key_during_active, //
                                                    .negative_modifier_mask              = MOD_MASK_CSAG,   //
                                                    .custom_action                       = NULL,            //
                                                    .context                             = NULL,            //
                                                    .trigger                             = DE_AE,           //
                                                    .replacement                         = LALT(KC_9),      //
                                                    .enabled                             = (bool *)&user_config.raw};

const key_override_t squareRightBraceCodingModeOverride = {.trigger_modifiers                   = MOD_MASK_SHIFT,  //
                                                     .layers                              = 1 << LAYER_MAC,  //
                                                     .suppressed_mods                     = MOD_MASK_SHIFT,  //
                                          .allowed_activation_events = ko_activation_events_default, //
                                          .options = ko_option_exclusive_key_during_active, //
                                                     .negative_modifier_mask              = MOD_MASK_CAG,    //
                                                     .custom_action                       = NULL,            //
                                                     .context                             = NULL,            //
                                                     .trigger                             = DE_AE,           //
                                                     .replacement                         = LALT(KC_6),      //
                                                     .enabled                             = (bool *)&user_config.raw};

const key_override_t normalAeCodingModeOverride = {.trigger_modifiers                   = MOD_MASK_CTRL,   //
                                             .suppressed_mods                     = MOD_MASK_CTRL,   //
                                             .layers                              = 1 << LAYER_MAC,  //
                                    .allowed_activation_events           = ko_activation_events_all,  //
                                    .options                             = ko_option_one_mod,         //
                                             .negative_modifier_mask              = 0,               //
                                             .custom_action                       = NULL,            //
                                             .context                             = NULL,            //
                                             .trigger                             = DE_AE,           //
                                             .replacement                         = DE_AE,           //
                                             .enabled                             = (bool *)&user_config.raw};

// (
const key_override_t leftBraceCodingModeOverride = {.trigger_modifiers                   = 0,               //
                                              .layers                              = 1 << LAYER_MAC,  //
                                              .suppressed_mods                     = 0,               //
                                          .allowed_activation_events = ko_activation_events_default, //
                                          .options = ko_option_exclusive_key_during_active, //
                                              .negative_modifier_mask              = MOD_MASK_CSAG,   //
                                              .custom_action                       = NULL,            //
                                              .context                             = NULL,            //
                                              .trigger                             = DE_SS,           //
                                              .replacement                         = LSFT(KC_8),      //
                                              .enabled                             = (bool *)&user_config.raw};

const key_override_t normalssCodingModeOverride = {.trigger_modifiers                   = MOD_MASK_CTRL,   //
                                             .layers                              = 1 << LAYER_MAC,  //
                                             .suppressed_mods                     = MOD_MASK_CTRL,   //
                                    .allowed_activation_events           = ko_activation_events_all,  //
                                    .options                             = ko_option_one_mod,         //
                                             .negative_modifier_mask              = 0,               //
                                             .custom_action                       = NULL,            //
                                             .context                             = NULL,            //
                                             .trigger                             = DE_SS,           //
                                             .replacement                         = DE_SS,           //
                                             .enabled                             = (bool *)&user_config.raw};

// )
const key_override_t rightBraceCodingModeOverride = {.trigger_modifiers                   = 0,               //
                                               .layers                              = 1 << LAYER_MAC,  //
                                               .suppressed_mods                     = 0,               //
                                          .allowed_activation_events = ko_activation_events_default, //
                                          .options = ko_option_exclusive_key_during_active, //
                                               .negative_modifier_mask              = MOD_MASK_CSAG,   //
                                               .custom_action                       = NULL,            //
                                               .context                             = NULL,            //
                                               .trigger                             = DE_ACUT,         //
                                               .replacement                         = LSFT(KC_9),      //
                                               .enabled                             = (bool *)&user_config.raw};

const key_override_t normalAcutCodingModeOverride = {.trigger_modifiers                   = MOD_MASK_CTRL,   //
                                               .layers                              = 1 << LAYER_MAC,  //
                                               .suppressed_mods                     = MOD_MASK_CTRL,   //
                                    .allowed_activation_events           = ko_activation_events_all,  //
                                    .options                             = ko_option_one_mod,         //
                                               .negative_modifier_mask              = 0,               //
                                               .custom_action                       = NULL,            //
                                               .context                             = NULL,            //
                                               .trigger                             = DE_ACUT,         //
                                               .replacement                         = DE_ACUT,         //
                                               .enabled                             = (bool *)&user_config.raw};

// / and | and \ .

const key_override_t slashCodingModeOverride = {.trigger_modifiers                   = 0,               //
                                          .layers                              = 1 << LAYER_MAC,  //
                                          .suppressed_mods                     = 0,               //
                                          .allowed_activation_events = ko_activation_events_default, //
                                          .options = ko_option_exclusive_key_during_active, //
                                          .negative_modifier_mask              = MOD_MASK_CSAG,   //
                                          .custom_action                       = NULL,            //
                                          .context                             = NULL,            //
                                          .trigger                             = DE_UE,           //
                                          .replacement                         = LSFT(KC_7),      //
                                          .enabled                             = (bool *)&user_config.raw};

const key_override_t pipeCodingModeOverride = {.trigger_modifiers                   = MOD_MASK_ALT,    //
                                         .layers                              = 1 << LAYER_MAC,  //
                                         .suppressed_mods                     = 0,               //
                                          .allowed_activation_events = ko_activation_events_default, //
                                          .options = ko_option_exclusive_key_during_active, //
                                         .negative_modifier_mask              = MOD_MASK_CG,     //
                                         .custom_action                       = NULL,            //
                                         .context                             = NULL,            //
                                         .trigger                             = DE_UE,           //
                                         .replacement                         = LALT(KC_7),      //
                                         .enabled                             = (bool *)&user_config.raw};

const key_override_t backslashCodingModeOverride = {.trigger_modifiers                   = MOD_MASK_SHIFT,  //
                                              .layers                              = 1 << LAYER_MAC,  //
                                              .suppressed_mods                     = 0,               //
                                          .allowed_activation_events = ko_activation_events_default, //
                                          .options = ko_option_exclusive_key_during_active, //
                                              .negative_modifier_mask              = MOD_MASK_CAG,    //
                                              .custom_action                       = NULL,            //
                                              .context                             = NULL,            //
                                              .trigger                             = DE_UE,           //
                                              .replacement                         = LALT(KC_7),      //
                                              .enabled                             = (bool *)&user_config.raw};

const key_override_t normalUeCodingModeOverride = {.trigger_modifiers                   = MOD_MASK_CTRL,   //
                                             .layers                              = 1 << LAYER_MAC,  //
                                             .suppressed_mods                     = MOD_MASK_CTRL,   //
                                    .allowed_activation_events           = ko_activation_events_all,  //
                                    .options                             = ko_option_one_mod,         //
                                             .negative_modifier_mask              = 0,               //
                                             .custom_action                       = NULL,            //
                                             .context                             = NULL,            //
                                             .trigger                             = DE_UE,           //
                                             .replacement                         = DE_UE,           //
                                             .enabled                             = (bool *)&user_config.raw};

// This has a strict requirement that no other mods can be down (hence negative_modifier_mask is ~MOD_MASK_CS). This is because ctrl + alt + shift + vol up is mapped to shift + alt + brightness up (ctrl + vol up has an override that turns it into brightness up) which is a small brightness increase on macOS.
const key_override_t lockScreenOverrideMac = {.trigger_modifiers         = MOD_MASK_CS,               //
                                        .layers                    = 1 << LAYER_MAC,            //
                                        .suppressed_mods           = 0,                         //
                                        .allowed_activation_events = ko_activation_events_all,  //
                                        .options                   = 0,                         //
                                        .negative_modifier_mask    = ~MOD_MASK_CS,              //
                                        .custom_action             = NULL,                      //
                                        .context                   = NULL,                      //
                                        .trigger                   = KC__VOLUP,                 //
                                        .replacement               = KC_POWER,                  //
                                        .enabled                   = NULL};

// shift + backspace = delete. delete + cmd = delete entire line (right of cursor), analog to cmd backspace (deletes left of cursor). Macos does this with ctrl + k for some reason, apparently this is some UNIX thing.
const key_override_t deleteLineOverrideMac = {.trigger_modifiers         = MOD_MASK_SG,                            //
                                        .layers                    = 1 << LAYER_MAC,                         //
                                        .suppressed_mods           = MOD_MASK_SG,                            //
                                        .allowed_activation_events = ko_activation_events_default,           //
                                        .options                   = ko_option_exclusive_key_during_active,  //
                                        .negative_modifier_mask    = 0,                                      //
                                        .custom_action             = NULL,                                   //
                                        .context                   = NULL,                                   //
                                        .trigger                   = KC_BSPACE,                              //
                                        .replacement               = C(KC_K),                                //
                                        .enabled                   = NULL};

// ctlr/alt/cmd + escape = ^ (not sctrict modifier requirement to allow using shift to modify to °)
const key_override_t hatEscOverrideMac = {.trigger_modifiers                   = MOD_MASK_CAG,                                               //
                                    .layers                              = 1 << LAYER_MAC,                                             //
                                    .suppressed_mods                     = MOD_MASK_CAG,                                               //
                                    .allowed_activation_events           = ko_activation_events_default,                               //
                                    .options                             = ko_option_exclusive_key_during_active | ko_option_one_mod,  //
                                    .negative_modifier_mask              = 0,                                                          //
                                    .custom_action                       = NULL,                                                       //
                                    .context                             = NULL,                                                       //
                                    .trigger                             = KC_ESC,                                                     //
                                    .replacement                         = DE_CIRC,                                                    //
                                    .enabled                             = NULL};

// lctrl + vol up = Screen brightness up
const key_override_t brightnessUpOverrideMac = {.trigger_modifiers                   = MOD_BIT(KC_LCTRL),                                          //
                                          .layers                              = 1 << LAYER_MAC,                                             //
                                          .suppressed_mods                     = MOD_BIT(KC_LCTRL),                                          //
                                          .allowed_activation_events           = ko_activation_events_all,                               //
                                          .options                             = ko_option_exclusive_key_during_active | ko_option_reregister_trigger_on_deactivation,  //
                                          .negative_modifier_mask              = MOD_MASK_ALT,                                               //
                                          .custom_action                       = NULL,                                                       //
                                          .context                             = NULL,                                                       //
                                          .trigger                             = KC__VOLUP,                                                  //
                                          .replacement                         = KC_BRIGHTNESS_UP,                                           //
                                          .enabled                             = NULL};

// lctrl + vol down = Screenn brightness down
const key_override_t brightnessDownOverrideMac = {.trigger_modifiers                   = MOD_BIT(KC_LCTRL),   //
                                            .layers                              = 1 << LAYER_MAC,      //
                                            .suppressed_mods                     = MOD_BIT(KC_LCTRL),   //
                                          .allowed_activation_events           = ko_activation_events_all,                               //
                                          .options                             = ko_option_exclusive_key_during_active | ko_option_reregister_trigger_on_deactivation,  //
                                            .negative_modifier_mask              = MOD_MASK_ALT,        //
                                            .custom_action                       = NULL,                //
                                            .context                             = NULL,                //
                                            .trigger                             = KC__VOLDOWN,         //
                                            .replacement                         = KC_BRIGHTNESS_DOWN,  //
                                            .enabled                             = NULL};

// lctrl + alt + vol up = Small screen brightness up
const key_override_t smallBrightnessUpOverrideMac = {.trigger_modifiers                   = MOD_MASK_CA,          //
                                               .layers                              = 1 << LAYER_MAC,       //
                                               .suppressed_mods                     = MOD_MASK_CTRL,        //
                                          .allowed_activation_events           = ko_activation_events_all,                               //
                                          .options                             = ko_option_exclusive_key_during_active | ko_option_reregister_trigger_on_deactivation,  //
                                               .negative_modifier_mask              = 0,                    //
                                               .custom_action                       = NULL,                 //
                                               .context                             = NULL,                 //
                                               .trigger                             = KC__VOLUP,            //
                                               .replacement                         = S(KC_BRIGHTNESS_UP),  //
                                               .enabled                             = NULL};

// lctrl + alt + vol down = Small screenn brightness down
const key_override_t smallBrightnessDownOverrideMac = {.trigger_modifiers                   = MOD_MASK_CA,            //
                                                 .layers                              = 1 << LAYER_MAC,         //
                                                 .suppressed_mods                     = MOD_MASK_CTRL,          //
                                          .allowed_activation_events           = ko_activation_events_all,                               //
                                          .options                             = ko_option_exclusive_key_during_active | ko_option_reregister_trigger_on_deactivation,  //
                                                 .negative_modifier_mask              = 0,                      //
                                                 .custom_action                       = NULL,                   //
                                                 .context                             = NULL,                   //
                                                 .trigger                             = KC__VOLDOWN,            //
                                                 .replacement                         = S(KC_BRIGHTNESS_DOWN),  //
                                                 .enabled                             = NULL};

// alt + vol up = little vol up
const key_override_t smallVolumeUpOverrideMac = {.trigger_modifiers                   = MOD_MASK_ALT | MOD_BIT(KC_RCTRL),  //
                                           .layers                              = 1 << LAYER_MAC,                    //
                                           .suppressed_mods                     = MOD_MASK_ALT | MOD_BIT(KC_RCTRL),  //
                                          .allowed_activation_events           = ko_activation_events_all,                               //
                                          .options                             = ko_option_exclusive_key_during_active | ko_option_reregister_trigger_on_deactivation | ko_option_one_mod,  //
                                           .negative_modifier_mask              = MOD_BIT(KC_LCTRL),                 //
                                           .custom_action                       = NULL,                              //
                                           .context                             = NULL,                              //
                                           .trigger                             = KC__VOLUP,                         //
                                           .replacement                         = LALT(LSFT(KC__VOLUP)),             //
                                           .enabled                             = NULL};

// alt + vol down = little vol down
const key_override_t smallVolumeDownOverrideMac = {.trigger_modifiers                   = MOD_MASK_ALT | MOD_BIT(KC_RCTRL),  //
                                             .layers                              = 1 << LAYER_MAC,                    //
                                             .suppressed_mods                     = MOD_MASK_ALT | MOD_BIT(KC_RCTRL),  //
                                          .allowed_activation_events           = ko_activation_events_all,                               //
                                          .options                             = ko_option_exclusive_key_during_active | ko_option_reregister_trigger_on_deactivation | ko_option_one_mod,  //
                                             .negative_modifier_mask              = MOD_BIT(KC_LCTRL),                 //
                                             .custom_action                       = NULL,                              //
                                             .context                             = NULL,                              //
                                             .trigger                             = KC__VOLDOWN,                       //
                                             .replacement                         = LALT(LSFT(KC__VOLDOWN)),           //
                                             .enabled                             = NULL};

// Windows key overrides:
const key_override_t lockScreenOverrideWindows = {.trigger_modifiers                   = MOD_MASK_CS,         //
                                            .layers                              = 1 << LAYER_WINDOWS,  //
                                            .suppressed_mods                     = MOD_MASK_CS,         //
                                          .allowed_activation_events           = ko_activation_events_all,                               //
                                          .options                             = 0,  //
                                            .negative_modifier_mask              = 0,                   //
                                            .custom_action                       = NULL,                //
                                            .context                             = NULL,                //
                                            .trigger                             = KC_AUDIO_VOL_UP,     //
                                            .replacement                         = LGUI(KC_L),          //
                                            .enabled                             = NULL};

// ctlr/alt/cmd + escape = ^ (not sctrict to allow using shift to modify to °)
const key_override_t hatEscOverrideWindows = {.trigger_modifiers                   = MOD_MASK_CAG,        //
                                        .layers                              = 1 << LAYER_WINDOWS,  //
                                        .suppressed_mods                     = MOD_MASK_CAG,        //
                                    .allowed_activation_events           = ko_activation_events_all,  //
                                    .options                             = ko_option_one_mod,         //
                                        .negative_modifier_mask              = 0,                   //
                                        .custom_action                       = NULL,                //
                                        .context                             = NULL,                //
                                        .trigger                             = KC_ESC,              //
                                        .replacement                         = DE_CIRC,             //
                                        .enabled                             = NULL};

// ctrl/alt/shift/cmd + vol up = Screen brightness up
const key_override_t brightnessUpOverrideWindows = {.trigger_modifiers                   = MOD_MASK_CTRL,       //
                                              .layers                              = 1 << LAYER_WINDOWS,  //
                                              .suppressed_mods                     = MOD_MASK_CSAG,       //
                                          .allowed_activation_events           = ko_activation_events_all,                               //
                                          .options                             = ko_option_exclusive_key_during_active | ko_option_reregister_trigger_on_deactivation,  //
                                              .negative_modifier_mask              = 0,                   //
                                              .custom_action                       = NULL,                //
                                              .context                             = NULL,                //
                                              .trigger                             = KC_AUDIO_VOL_UP,     //
                                              .replacement                         = KC_BRIGHTNESS_UP,    //
                                              .enabled                             = NULL};

// ctrl/alt/shift/cmd + vol down = Screenn brightness down
const key_override_t brightnessDownOverrideWindows = {.trigger_modifiers                   = MOD_MASK_CTRL,       //
                                                .layers                              = 1 << LAYER_WINDOWS,  //
                                                .suppressed_mods                     = MOD_MASK_CSAG,       //
                                          .allowed_activation_events           = ko_activation_events_all,                               //
                                          .options                             = ko_option_exclusive_key_during_active | ko_option_reregister_trigger_on_deactivation,  //
                                                .negative_modifier_mask              = 0,                   //
                                                .custom_action                       = NULL,                //
                                                .context                             = NULL,                //
                                                .trigger                             = KC_AUDIO_VOL_DOWN,   //
                                                .replacement                         = KC_BRIGHTNESS_DOWN,  //
                                                .enabled                             = NULL};

// clang-format off

const key_override_t **key_overrides = (const key_override_t *[]){
    // Shared
    &backSpaceDeleteOverride,
    &prevTrackOverride,

    &deleteLineOverrideMac,
    &lockScreenOverrideMac,
    &hatEscOverrideMac,
    &brightnessUpOverrideMac,
    &brightnessDownOverrideMac,
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
    &hatEscOverrideWindows,

    &brightnessUpOverrideWindows,
    &brightnessDownOverrideWindows,

    // Extra stuff
    &fnOverride,

    NULL
};

// clang-format on