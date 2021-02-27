#pragma once

#include QMK_KEYBOARD_H

#include "config.h"
#include "tapping_action.h"

// User config

typedef union {
    uint32_t raw;
    struct {
        bool coding_overlay_active : 1;
    };
} user_config_t;

extern user_config_t user_config;

// Custom keycodes

enum my_keycodes_userspace {
    TOGGLE_CODING_OVERLAY = SAFE_RANGE,
    SAFE_RANGE_USERSPACE,
};

// Layers

#define LAYER_MAC 0
#define LAYER_WINDOWS 1

// Null should be higher than coding layer and base layers
#define LAYER_NULL 2

// momentary layers, should have the highest numbers.
#define LAYER_FN 3

// Tap

extern tapping_action_t enable_caps_tap;
extern tapping_action_t disable_caps_tap;
extern tapping_action_t toggle_coding_mode_tap;

// Overrides

extern const key_override_t backSpaceDeleteOverride;
extern const key_override_t prevTrackOverride;
extern const key_override_t hatEscOverride;
extern const key_override_t brightnessUpOverride;
extern const key_override_t brightnessDownOverride;

// Mac
extern const key_override_t deleteLineOverrideMac;
extern const key_override_t lockScreenOverrideMac;

extern const key_override_t smallBrightnessUpOverrideMac;
extern const key_override_t smallBrightnessDownOverrideMac;
extern const key_override_t smallVolumeUpOverrideMac;
extern const key_override_t smallVolumeDownOverrideMac;

// Coding mode overrides
extern const key_override_t curlyLeftBraceCodingModeOverride;
extern const key_override_t squareLeftBraceCodingModeOverride;
extern const key_override_t normalOeCodingModeOverride;

extern const key_override_t curlyRightBraceCodingModeOverride;
extern const key_override_t squareRightBraceCodingModeOverride;
extern const key_override_t normalAeCodingModeOverride;

extern const key_override_t leftBraceCodingModeOverride;
extern const key_override_t normalssCodingModeOverride;
extern const key_override_t rightBraceCodingModeOverride;
extern const key_override_t normalAcutCodingModeOverride;

extern const key_override_t slashCodingModeOverride;
extern const key_override_t pipeCodingModeOverride;
extern const key_override_t backslashCodingModeOverride;
extern const key_override_t normalUeCodingModeOverride;

// Windows-only overrides
extern const key_override_t lockScreenOverrideWindows;

extern bool windows_shortcut_hook(bool key_down, void *ctx);

#define WIN_SHORTCUT_OVERRIDE(keycode) \
    ((const key_override_t){                                                                \
        .trigger_mods                           = MOD_BIT(KC_LGUI),                         \
        .layers                                 = (1 << LAYER_WINDOWS),                     \
        .suppressed_mods                        = MOD_BIT(KC_LGUI),                         \
        .options                                = 0,                                        \
        .negative_mod_mask                      = 0,                                        \
        .custom_action                          = windows_shortcut_hook,                    \
        .context                                = NULL,                                     \
        .trigger                                = keycode,                                  \
        .replacement                            = C(keycode),                               \
        .enabled                                = NULL                                      \
    })

// Extra stuff
extern const key_override_t fnOverride;

