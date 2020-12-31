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

key_override_t fnOverride = {.trigger_modifiers                   = MOD_BIT(KC_RGUI) | MOD_BIT(KC_RCTL),  //
                             .one_mod                             = false,                                //
                             .layers                              = ~(1 << LAYER_FN),                     //
                             .suppressed_mods                     = MOD_BIT(KC_RGUI) | MOD_BIT(KC_RCTL),  //
                             .allows_other_keys_down_at_trigger   = false,                                //
                             .allows_other_keys_down_while_active = true,                                 //
                             .reregister_trigger_after_completion = false,                                //
                             .trigger_only_on_trigger_down        = true,                                 //
                             .negative_modifier_mask              = 0,                                    //
                             .custom_action                       = momentary_layer,                      //
                             .context                             = (void *)LAYER_FN,                     //
                             .trigger                             = KC_NO,                                //
                             .replacement                         = KC_NO,                                //
                             .enabled                             = NULL};

// maps shift + backspace to delete
key_override_t backSpaceDeleteOverride = key_override_make_basic(MOD_MASK_SHIFT, KC_BSPACE, KC_DELETE);

// ctrl/alt/cmd/shift + next track = Previous track
key_override_t prevTrackOverride = {.trigger_modifiers                   = MOD_MASK_CSAG,        //
                                    .one_mod                             = true,                 //
                                    .layers                              = ~0,                   //
                                    .suppressed_mods                     = MOD_MASK_CSAG,        //
                                    .allows_other_keys_down_at_trigger   = true,                 //
                                    .allows_other_keys_down_while_active = true,                 //
                                    .reregister_trigger_after_completion = false,                //
                                    .trigger_only_on_trigger_down        = false,                //
                                    .negative_modifier_mask              = 0,                    //
                                    .custom_action                       = NULL,                 //
                                    .context                             = NULL,                 //
                                    .trigger                             = KC_MEDIA_NEXT_TRACK,  //
                                    .replacement                         = KC_MEDIA_PREV_TRACK,  //
                                    .enabled                             = NULL};

// In coding mode the ö and ä keys are mapped to { and }. With the shift key they are shifted to [ and ]. With control give back ö and ä.

// { and [
key_override_t curlyLeftBraceCodingModeOverride = {.trigger_modifiers                   = 0,               //
                                                   .one_mod                             = true,            //
                                                   .layers                              = 1 << LAYER_MAC,  //
                                                   .suppressed_mods                     = 0,               //
                                                   .allows_other_keys_down_at_trigger   = true,            //
                                                   .allows_other_keys_down_while_active = false,           //
                                                   .reregister_trigger_after_completion = false,           //
                                                   .trigger_only_on_trigger_down        = true,           //
                                                   .negative_modifier_mask              = MOD_MASK_CSAG,   //
                                                   .custom_action                       = NULL,            //
                                                   .context                             = NULL,            //
                                                   .trigger                             = DE_OE,           //
                                                   .replacement                         = LALT(KC_8),      //
                                                   .enabled                             = (bool *)&user_config.raw};

key_override_t squareLeftBraceCodingModeOverride = {.trigger_modifiers                   = MOD_MASK_SHIFT,  //
                                                    .one_mod                             = true,            //
                                                    .suppressed_mods                     = MOD_MASK_SHIFT,  //
                                                    .layers                              = 1 << LAYER_MAC,  //
                                                    .allows_other_keys_down_at_trigger   = true,            //
                                                    .allows_other_keys_down_while_active = false,           //
                                                    .reregister_trigger_after_completion = false,           //
                                                    .trigger_only_on_trigger_down        = true,           //
                                                    .negative_modifier_mask              = MOD_MASK_CAG,    //
                                                    .custom_action                       = NULL,            //
                                                    .context                             = NULL,            //
                                                    .trigger                             = DE_OE,           //
                                                    .replacement                         = LALT(KC_5),      //
                                                    .enabled                             = (bool *)&user_config.raw};

key_override_t normalOeCodingModeOverride = {.trigger_modifiers                   = MOD_MASK_CTRL,   //
                                             .one_mod                             = true,            //
                                             .layers                              = 1 << LAYER_MAC,  //
                                             .suppressed_mods                     = MOD_MASK_CTRL,   //
                                             .allows_other_keys_down_at_trigger   = true,            //
                                             .allows_other_keys_down_while_active = true,            //
                                             .reregister_trigger_after_completion = false,           //
                                             .trigger_only_on_trigger_down        = false,           //
                                             .negative_modifier_mask              = 0,               //
                                             .custom_action                       = NULL,            //
                                             .context                             = NULL,            //
                                             .trigger                             = DE_OE,           //
                                             .replacement                         = DE_OE,           //
                                             .enabled                             = (bool *)&user_config.raw};

// } and ]
key_override_t curlyRightBraceCodingModeOverride = {.trigger_modifiers                   = 0,               //
                                                    .one_mod                             = true,            //
                                                    .layers                              = 1 << LAYER_MAC,  //
                                                    .suppressed_mods                     = 0,               //
                                                    .allows_other_keys_down_at_trigger   = true,            //
                                                    .allows_other_keys_down_while_active = false,           //
                                                    .reregister_trigger_after_completion = false,           //
                                                    .trigger_only_on_trigger_down        = true,           //
                                                    .negative_modifier_mask              = MOD_MASK_CSAG,   //
                                                    .custom_action                       = NULL,            //
                                                    .context                             = NULL,            //
                                                    .trigger                             = DE_AE,           //
                                                    .replacement                         = LALT(KC_9),      //
                                                    .enabled                             = (bool *)&user_config.raw};

key_override_t squareRightBraceCodingModeOverride = {.trigger_modifiers                   = MOD_MASK_SHIFT,  //
                                                     .one_mod                             = true,            //
                                                     .layers                              = 1 << LAYER_MAC,  //
                                                     .suppressed_mods                     = MOD_MASK_SHIFT,  //
                                                     .allows_other_keys_down_at_trigger   = true,            //
                                                     .allows_other_keys_down_while_active = false,           //
                                                     .reregister_trigger_after_completion = false,           //
                                                     .trigger_only_on_trigger_down        = true,           //
                                                     .negative_modifier_mask              = MOD_MASK_CAG,    //
                                                     .custom_action                       = NULL,            //
                                                     .context                             = NULL,            //
                                                     .trigger                             = DE_AE,           //
                                                     .replacement                         = LALT(KC_6),      //
                                                     .enabled                             = (bool *)&user_config.raw};

key_override_t normalAeCodingModeOverride = {.trigger_modifiers                   = MOD_MASK_CTRL,   //
                                             .one_mod                             = true,            //
                                             .suppressed_mods                     = MOD_MASK_CTRL,   //
                                             .layers                              = 1 << LAYER_MAC,  //
                                             .allows_other_keys_down_at_trigger   = true,            //
                                             .allows_other_keys_down_while_active = true,            //
                                             .reregister_trigger_after_completion = false,           //
                                             .trigger_only_on_trigger_down        = false,           //
                                             .negative_modifier_mask              = 0,               //
                                             .custom_action                       = NULL,            //
                                             .context                             = NULL,            //
                                             .trigger                             = DE_AE,           //
                                             .replacement                         = DE_AE,           //
                                             .enabled                             = (bool *)&user_config.raw};

// (
key_override_t leftBraceCodingModeOverride = {.trigger_modifiers                   = 0,               //
                                              .one_mod                             = true,            //
                                              .layers                              = 1 << LAYER_MAC,  //
                                              .suppressed_mods                     = 0,               //
                                              .allows_other_keys_down_at_trigger   = true,            //
                                              .allows_other_keys_down_while_active = false,           //
                                              .reregister_trigger_after_completion = false,           //
                                              .trigger_only_on_trigger_down        = true,           //
                                              .negative_modifier_mask              = MOD_MASK_CSAG,   //
                                              .custom_action                       = NULL,            //
                                              .context                             = NULL,            //
                                              .trigger                             = DE_SS,           //
                                              .replacement                         = LSFT(KC_8),      //
                                              .enabled                             = (bool *)&user_config.raw};

key_override_t normalssCodingModeOverride = {.trigger_modifiers                   = MOD_MASK_CTRL,   //
                                             .one_mod                             = true,            //
                                             .layers                              = 1 << LAYER_MAC,  //
                                             .suppressed_mods                     = MOD_MASK_CTRL,   //
                                             .allows_other_keys_down_at_trigger   = true,            //
                                             .allows_other_keys_down_while_active = true,            //
                                             .reregister_trigger_after_completion = false,           //
                                             .trigger_only_on_trigger_down        = false,           //
                                             .negative_modifier_mask              = 0,               //
                                             .custom_action                       = NULL,            //
                                             .context                             = NULL,            //
                                             .trigger                             = DE_SS,           //
                                             .replacement                         = DE_SS,           //
                                             .enabled                             = (bool *)&user_config.raw};

// )
key_override_t rightBraceCodingModeOverride = {.trigger_modifiers                   = 0,               //
                                               .one_mod                             = true,            //
                                               .layers                              = 1 << LAYER_MAC,  //
                                               .suppressed_mods                     = 0,               //
                                               .allows_other_keys_down_at_trigger   = true,            //
                                               .allows_other_keys_down_while_active = false,           //
                                               .reregister_trigger_after_completion = false,           //
                                               .trigger_only_on_trigger_down        = true,           //
                                               .negative_modifier_mask              = MOD_MASK_CSAG,   //
                                               .custom_action                       = NULL,            //
                                               .context                             = NULL,            //
                                               .trigger                             = DE_ACUT,         //
                                               .replacement                         = LSFT(KC_9),      //
                                               .enabled                             = (bool *)&user_config.raw};

key_override_t normalAcutCodingModeOverride = {.trigger_modifiers                   = MOD_MASK_CTRL,   //
                                               .one_mod                             = true,            //
                                               .layers                              = 1 << LAYER_MAC,  //
                                               .suppressed_mods                     = MOD_MASK_CTRL,   //
                                               .allows_other_keys_down_at_trigger   = true,            //
                                               .allows_other_keys_down_while_active = true,            //
                                               .reregister_trigger_after_completion = false,           //
                                               .trigger_only_on_trigger_down        = false,           //
                                               .negative_modifier_mask              = 0,               //
                                               .custom_action                       = NULL,            //
                                               .context                             = NULL,            //
                                               .trigger                             = DE_ACUT,         //
                                               .replacement                         = DE_ACUT,         //
                                               .enabled                             = (bool *)&user_config.raw};

// / and | and \ .

key_override_t slashCodingModeOverride = {.trigger_modifiers                   = 0,               //
                                          .one_mod                             = true,            //
                                          .layers                              = 1 << LAYER_MAC,  //
                                          .suppressed_mods                     = 0,               //
                                          .allows_other_keys_down_at_trigger   = true,            //
                                          .allows_other_keys_down_while_active = false,           //
                                          .reregister_trigger_after_completion = false,           //
                                          .trigger_only_on_trigger_down        = false,           //
                                          .negative_modifier_mask              = MOD_MASK_CSAG,   //
                                          .custom_action                       = NULL,            //
                                          .context                             = NULL,            //
                                          .trigger                             = DE_UE,           //
                                          .replacement                         = LSFT(KC_7),      //
                                          .enabled                             = (bool *)&user_config.raw};

key_override_t pipeCodingModeOverride = {.trigger_modifiers                   = MOD_MASK_ALT,    //
                                         .one_mod                             = true,            //
                                         .layers                              = 1 << LAYER_MAC,  //
                                         .suppressed_mods                     = 0,               //
                                         .allows_other_keys_down_at_trigger   = true,            //
                                         .allows_other_keys_down_while_active = false,           //
                                         .reregister_trigger_after_completion = false,           //
                                         .trigger_only_on_trigger_down        = false,           //
                                         .negative_modifier_mask              = MOD_MASK_CG,     //
                                         .custom_action                       = NULL,            //
                                         .context                             = NULL,            //
                                         .trigger                             = DE_UE,           //
                                         .replacement                         = LALT(KC_7),      //
                                         .enabled                             = (bool *)&user_config.raw};

key_override_t backslashCodingModeOverride = {.trigger_modifiers                   = MOD_MASK_SHIFT,  //
                                              .one_mod                             = true,            //
                                              .layers                              = 1 << LAYER_MAC,  //
                                              .suppressed_mods                     = 0,               //
                                              .allows_other_keys_down_at_trigger   = true,            //
                                              .allows_other_keys_down_while_active = false,           //
                                              .reregister_trigger_after_completion = false,           //
                                              .trigger_only_on_trigger_down        = false,           //
                                              .negative_modifier_mask              = MOD_MASK_CAG,    //
                                              .custom_action                       = NULL,            //
                                              .context                             = NULL,            //
                                              .trigger                             = DE_UE,           //
                                              .replacement                         = LALT(KC_7),      //
                                              .enabled                             = (bool *)&user_config.raw};

key_override_t normalUeCodingModeOverride = {.trigger_modifiers                   = MOD_MASK_CTRL,   //
                                             .one_mod                             = true,            //
                                             .layers                              = 1 << LAYER_MAC,  //
                                             .suppressed_mods                     = MOD_MASK_CTRL,   //
                                             .allows_other_keys_down_at_trigger   = true,            //
                                             .allows_other_keys_down_while_active = true,            //
                                             .reregister_trigger_after_completion = false,           //
                                             .trigger_only_on_trigger_down        = false,           //
                                             .negative_modifier_mask              = 0,               //
                                             .custom_action                       = NULL,            //
                                             .context                             = NULL,            //
                                             .trigger                             = DE_UE,           //
                                             .replacement                         = DE_UE,           //
                                             .enabled                             = (bool *)&user_config.raw};

// This has a strict requirement that no other mods can be down (hence negative_modifier_mask is ~MOD_MASK_CS). This is because ctrl + alt + shift + vol up is mapped to shift + alt + brightness up (ctrl + vol up has an override that turns it into brightness up) which is a small brightness increase on macOS.
key_override_t lockScreenOverrideMac = {.trigger_modifiers                   = MOD_MASK_CS,     //
                                        .one_mod                             = false,           //
                                        .layers                              = 1 << LAYER_MAC,  //
                                        .suppressed_mods                     = 0,               //
                                        .allows_other_keys_down_at_trigger   = false,           //
                                        .allows_other_keys_down_while_active = false,           //
                                        .reregister_trigger_after_completion = false,           //
                                        .trigger_only_on_trigger_down        = false,           //
                                        .negative_modifier_mask              = ~MOD_MASK_CS,    //
                                        .custom_action                       = NULL,            //
                                        .context                             = NULL,            //
                                        .trigger                             = KC__VOLUP,       //
                                        .replacement                         = KC_POWER,        //
                                        .enabled                             = NULL};

// shift + backspace = delete. delete + cmd = delete entire line (right of cursor), analog to cmd backspace (deletes left of cursor). Macos does this with ctrl + k for some reason, apparently this is some UNIX thing.
key_override_t deleteLineOverrideMac = {.trigger_modifiers                   = MOD_MASK_SG,     //
                                        .one_mod                             = false,           //
                                        .layers                              = 1 << LAYER_MAC,  //
                                        .suppressed_mods                     = MOD_MASK_SG,     //
                                        .allows_other_keys_down_at_trigger   = true,            //
                                        .allows_other_keys_down_while_active = true,            //
                                        .reregister_trigger_after_completion = true,            //
                                        .trigger_only_on_trigger_down        = true,           //
                                        .negative_modifier_mask              = 0,               //
                                        .custom_action                       = NULL,            //
                                        .context                             = NULL,            //
                                        .trigger                             = KC_BSPACE,       //
                                        .replacement                         = C(KC_K),         //
                                        .enabled                             = NULL};

// ctlr/alt/cmd + escape = ^ (not sctrict modifier requirement to allow using shift to modify to °)
key_override_t hatEscOverrideMac = {.trigger_modifiers                   = MOD_MASK_CAG,    //
                                    .one_mod                             = true,            //
                                    .layers                              = 1 << LAYER_MAC,  //
                                    .suppressed_mods                     = MOD_MASK_CAG,    //
                                    .allows_other_keys_down_at_trigger   = true,            //
                                    .allows_other_keys_down_while_active = true,            //
                                    .reregister_trigger_after_completion = true,            //
                                    .trigger_only_on_trigger_down        = true,           //
                                    .negative_modifier_mask              = 0,               //
                                    .custom_action                       = NULL,            //
                                    .context                             = NULL,            //
                                    .trigger                             = KC_ESC,          //
                                    .replacement                         = DE_CIRC,         //
                                    .enabled                             = NULL};

// lctrl + vol up = Screen brightness up
key_override_t brightnessUpOverrideMac = {.trigger_modifiers                   = MOD_BIT(KC_LCTRL),  //
                                          .one_mod                             = true,               //
                                          .layers                              = 1 << LAYER_MAC,     //
                                          .suppressed_mods                     = MOD_BIT(KC_LCTRL),  //
                                          .allows_other_keys_down_at_trigger   = false,              //
                                          .allows_other_keys_down_while_active = true,               //
                                          .reregister_trigger_after_completion = true,               //
                                          .trigger_only_on_trigger_down        = true,              //
                                          .negative_modifier_mask              = MOD_MASK_ALT,       //
                                          .custom_action                       = NULL,               //
                                          .context                             = NULL,               //
                                          .trigger                             = KC__VOLUP,          //
                                          .replacement                         = KC_BRIGHTNESS_UP,   //
                                          .enabled                             = NULL};

// lctrl + vol down = Screenn brightness down
key_override_t brightnessDownOverrideMac = {.trigger_modifiers                   = MOD_BIT(KC_LCTRL),   //
                                            .one_mod                             = true,                //
                                            .layers                              = 1 << LAYER_MAC,      //
                                            .suppressed_mods                     = MOD_BIT(KC_LCTRL),   //
                                            .allows_other_keys_down_at_trigger   = false,               //
                                            .allows_other_keys_down_while_active = true,                //
                                            .reregister_trigger_after_completion = true,                //
                                            .trigger_only_on_trigger_down        = false,               //
                                            .negative_modifier_mask              = MOD_MASK_ALT,        //
                                            .custom_action                       = NULL,                //
                                            .context                             = NULL,                //
                                            .trigger                             = KC__VOLDOWN,         //
                                            .replacement                         = KC_BRIGHTNESS_DOWN,  //
                                            .enabled                             = NULL};

// lctrl + alt + vol up = Small screen brightness up
key_override_t smallBrightnessUpOverrideMac = {.trigger_modifiers                   = MOD_MASK_CA,          //
                                               .one_mod                             = false,                //
                                               .layers                              = 1 << LAYER_MAC,       //
                                               .suppressed_mods                     = MOD_MASK_CTRL,        //
                                               .allows_other_keys_down_at_trigger   = false,                //
                                               .allows_other_keys_down_while_active = true,                 //
                                               .reregister_trigger_after_completion = true,                 //
                                               .trigger_only_on_trigger_down        = false,                //
                                               .negative_modifier_mask              = 0,                    //
                                               .custom_action                       = NULL,                 //
                                               .context                             = NULL,                 //
                                               .trigger                             = KC__VOLUP,            //
                                               .replacement                         = S(KC_BRIGHTNESS_UP),  //
                                               .enabled                             = NULL};

// lctrl + alt + vol down = Small screenn brightness down
key_override_t smallBrightnessDownOverrideMac = {.trigger_modifiers                   = MOD_MASK_CA,            //
                                                 .one_mod                             = false,                  //
                                                 .layers                              = 1 << LAYER_MAC,         //
                                                 .suppressed_mods                     = MOD_MASK_CTRL,          //
                                                 .allows_other_keys_down_at_trigger   = false,                  //
                                                 .allows_other_keys_down_while_active = true,                   //
                                                 .reregister_trigger_after_completion = true,                   //
                                                 .trigger_only_on_trigger_down        = false,                  //
                                                 .negative_modifier_mask              = 0,                      //
                                                 .custom_action                       = NULL,                   //
                                                 .context                             = NULL,                   //
                                                 .trigger                             = KC__VOLDOWN,            //
                                                 .replacement                         = S(KC_BRIGHTNESS_DOWN),  //
                                                 .enabled                             = NULL};

// alt + vol up = little vol up
key_override_t smallVolumeUpOverrideMac = {.trigger_modifiers                   = MOD_MASK_ALT | MOD_BIT(KC_RCTRL),  //
                                           .one_mod                             = true,                              //
                                           .layers                              = 1 << LAYER_MAC,                    //
                                           .suppressed_mods                     = MOD_MASK_ALT | MOD_BIT(KC_RCTRL),  //
                                           .allows_other_keys_down_at_trigger   = false,                             //
                                           .allows_other_keys_down_while_active = true,                              //
                                           .reregister_trigger_after_completion = true,                              //
                                           .trigger_only_on_trigger_down        = false,                             //
                                           .negative_modifier_mask              = MOD_BIT(KC_LCTRL),                 //
                                           .custom_action                       = NULL,                              //
                                           .context                             = NULL,                              //
                                           .trigger                             = KC__VOLUP,                         //
                                           .replacement                         = LALT(LSFT(KC__VOLUP)),             //
                                           .enabled                             = NULL};

// alt + vol down = little vol down
key_override_t smallVolumeDownOverrideMac = {.trigger_modifiers                   = MOD_MASK_ALT | MOD_BIT(KC_RCTRL),  //
                                             .one_mod                             = true,                              //
                                             .layers                              = 1 << LAYER_MAC,                    //
                                             .suppressed_mods                     = MOD_MASK_ALT | MOD_BIT(KC_RCTRL),  //
                                             .allows_other_keys_down_at_trigger   = false,                             //
                                             .allows_other_keys_down_while_active = true,                              //
                                             .reregister_trigger_after_completion = true,                              //
                                             .trigger_only_on_trigger_down        = false,                             //
                                             .negative_modifier_mask              = MOD_BIT(KC_LCTRL),                 //
                                             .custom_action                       = NULL,                              //
                                             .context                             = NULL,                              //
                                             .trigger                             = KC__VOLDOWN,                       //
                                             .replacement                         = LALT(LSFT(KC__VOLDOWN)),           //
                                             .enabled                             = NULL};

// Windows key overrides:
key_override_t lockScreenOverrideWindows = {.trigger_modifiers                   = MOD_MASK_CS,         //
                                            .one_mod                             = false,               //
                                            .layers                              = 1 << LAYER_WINDOWS,  //
                                            .suppressed_mods                     = MOD_MASK_CS,         //
                                            .allows_other_keys_down_at_trigger   = false,               //
                                            .allows_other_keys_down_while_active = false,               //
                                            .reregister_trigger_after_completion = false,               //
                                            .trigger_only_on_trigger_down        = false,               //
                                            .negative_modifier_mask              = 0,                   //
                                            .custom_action                       = NULL,                //
                                            .context                             = NULL,                //
                                            .trigger                             = KC_AUDIO_VOL_UP,     //
                                            .replacement                         = LGUI(KC_L),          //
                                            .enabled                             = NULL};

// ctlr/alt/cmd + escape = ^ (not sctrict to allow using shift to modify to °)
key_override_t hatEscOverrideWindows = {.trigger_modifiers                   = MOD_MASK_CAG,        //
                                        .one_mod                             = true,                //
                                        .layers                              = 1 << LAYER_WINDOWS,  //
                                        .suppressed_mods                     = MOD_MASK_CAG,        //
                                        .allows_other_keys_down_at_trigger   = true,                //
                                        .allows_other_keys_down_while_active = true,                //
                                        .reregister_trigger_after_completion = false,               //
                                        .trigger_only_on_trigger_down        = false,               //
                                        .negative_modifier_mask              = 0,                   //
                                        .custom_action                       = NULL,                //
                                        .context                             = NULL,                //
                                        .trigger                             = KC_ESC,              //
                                        .replacement                         = DE_CIRC,             //
                                        .enabled                             = NULL};

// ctrl/alt/shift/cmd + vol up = Screen brightness up
key_override_t brightnessUpOverrideWindows = {.trigger_modifiers                   = MOD_MASK_CSAG,       //
                                              .one_mod                             = true,                //
                                              .layers                              = 1 << LAYER_WINDOWS,  //
                                              .suppressed_mods                     = MOD_MASK_CSAG,       //
                                              .allows_other_keys_down_at_trigger   = false,               //
                                              .allows_other_keys_down_while_active = true,                //
                                              .reregister_trigger_after_completion = true,                //
                                              .trigger_only_on_trigger_down        = false,               //
                                              .negative_modifier_mask              = 0,                   //
                                              .custom_action                       = NULL,                //
                                              .context                             = NULL,                //
                                              .trigger                             = KC_AUDIO_VOL_UP,     //
                                              .replacement                         = KC_BRIGHTNESS_UP,    //
                                              .enabled                             = NULL};

// ctrl/alt/shift/cmd + vol down = Screenn brightness down
key_override_t brightnessDownOverrideWindows = {.trigger_modifiers                   = MOD_MASK_CSAG,       //
                                                .one_mod                             = true,                //
                                                .layers                              = 1 << LAYER_WINDOWS,  //
                                                .suppressed_mods                     = MOD_MASK_CSAG,       //
                                                .allows_other_keys_down_at_trigger   = false,               //
                                                .allows_other_keys_down_while_active = true,                //
                                                .reregister_trigger_after_completion = true,                //
                                                .trigger_only_on_trigger_down        = false,               //
                                                .negative_modifier_mask              = 0,                   //
                                                .custom_action                       = NULL,                //
                                                .context                             = NULL,                //
                                                .trigger                             = KC_AUDIO_VOL_DOWN,   //
                                                .replacement                         = KC_BRIGHTNESS_DOWN,  //
                                                .enabled                             = NULL};

// clang-format off

key_override_t **key_overrides = (key_override_t *[]){
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