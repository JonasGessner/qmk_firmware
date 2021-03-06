#include "jonas.h"
#include "tapping_action.h"

tapping_action_make_double_tap_with_max_duration(enable_caps_tap, tapping_action_triggers(KC_LSFT, KC_RSFT), 400, {
    tap_code(KC_CAPS);
    return true;
});

tapping_action_make_single_tap_with_max_duration(disable_caps_tap, tapping_action_triggers(KC_LSFT, KC_RSFT), 400, {
    tap_code(KC_CAPS);
    return true;
});

tapping_action_make_single_tap(toggle_coding_mode_tap, TOGGLE_CODING_OVERLAY, {
    user_config.coding_overlay_active = !user_config.coding_overlay_active;
    eeconfig_update_user(user_config.raw);
    return false;
});

static void update_caps_taps(led_t led_state) {
    const bool caps_on = led_state.caps_lock;

    if (caps_on) {
        disable_tap(&enable_caps_tap);
        enable_tap(&disable_caps_tap);
    } else {
        enable_tap(&enable_caps_tap);
        disable_tap(&disable_caps_tap);
    }
}

bool led_update_user(led_t led_state) {
    update_caps_taps(led_state);
    return true;
}

// To debug: uncomment and set CONSOLE_ENABLE=yes in rules.mk
void keyboard_post_init_user(void) {
    update_caps_taps(host_keyboard_led_state());
    // Customise these values to desired behaviour
#ifdef DEBUG_
    debug_enable   = true;
    debug_matrix   = true;
    debug_keyboard = true;
    debug_mouse    = true;
#else
    debug_enable   = false;
    debug_matrix   = false;
    debug_keyboard = false;
    debug_mouse    = false;
#endif
}