#pragma once

#include QMK_KEYBOARD_H

typedef struct {
    const uint16_t events;
    const uint8_t  number_of_events;
    // const uint16_t min_intervals[15];
    // const uint16_t max_intervals[15];

    const uint16_t triggers[2];

    const uint16_t min_duration;
    const uint16_t max_duration;

    bool enabled;

    bool (*const activation_handler)(keyrecord_t *const record, void *context);
    void *context;

    uint16_t recorded_events;

    // Ring buffer
    uint16_t timestamps[16];
    // Non-modded indices! (https://www.snellman.net/blog/archive/2016-12-13-ring-buffers/)
    uint8_t start;
    uint8_t end;
} tapping_action_t;

void reset_tap(tapping_action_t *tap);
void disable_tap(tapping_action_t *tap);
void enable_tap(tapping_action_t *tap);

#define tapping_action_make_single_tap(name, keycodes, callback_code)                                              \
    static bool      __callback_tapping_action_##name (keyrecord_t *const record, void *context) { callback_code; } \
    tapping_action_t name = {                                                                                      \
        .events             = 0b10,                                                                                \
        .recorded_events    = 0,                                                                                   \
        .number_of_events   = 2,                                                                                   \
        .triggers           = {keycodes},                                                                            \
        .activation_handler = __callback_tapping_action_##name,                                                 \
        .context            = NULL,                                                                                \
        .enabled            = true,                                                                                \
        .min_duration       = 0,                                                                                   \
        .max_duration       = 0,                                                                                   \
        .timestamps         = {0},                                                                                 \
        .start              = 0,                                                                                   \
        .end                = 0,                                                                                   \
    }

#define tapping_action_make_single_tap_with_max_duration(name, keycodes, max_duration_, callback_code)             \
    static bool      __callback_tapping_action_##name (keyrecord_t *const record, void *context) { callback_code; } \
    tapping_action_t name = {                                                                                      \
        .events             = 0b10,                                                                                \
        .recorded_events    = 0,                                                                                   \
        .number_of_events   = 2,                                                                                   \
        .triggers           = {keycodes},                                                                            \
        .activation_handler = __callback_tapping_action_##name,                                                 \
        .context            = NULL,                                                                                \
        .enabled            = true,                                                                                \
        .min_duration       = 0,                                                                                   \
        .max_duration       = max_duration_,                                                                       \
        .timestamps         = {0},                                                                                 \
        .start              = 0,                                                                                   \
        .end                = 0,                                                                                   \
    }

#define tapping_action_make_double_tap_with_max_duration(name, keycodes, max_duration_, callback_code)             \
    static bool      __callback_tapping_action_##name (keyrecord_t *const record, void *context) { callback_code; } \
    tapping_action_t name = {                                                                                      \
        .events             = 0b1010,                                                                              \
        .recorded_events    = 0,                                                                                   \
        .number_of_events   = 4,                                                                                   \
        .triggers           = {keycodes},                                                                            \
        .activation_handler = __callback_tapping_action_##name,                                                 \
        .context            = NULL,                                                                                \
        .enabled            = true,                                                                                \
        .min_duration       = 0,                                                                                   \
        .max_duration       = max_duration_,                                                                       \
        .timestamps         = {0},                                                                                 \
        .start              = 0,                                                                                   \
        .end                = 0,                                                                                   \
    }

#define tapping_action_triggers(...) __VA_ARGS__

extern tapping_action_t **taps;
