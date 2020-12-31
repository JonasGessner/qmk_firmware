#pragma once

#include QMK_KEYBOARD_H

#include "config.h"
#include "keymap_german.h"

typedef union {
    uint32_t raw;
    struct {
        bool coding_overlay_active : 1;
    };
} user_config_t;

extern user_config_t user_config;

enum my_keycodes { TOGGLE_CODING_OVERLAY = SAFE_RANGE };
