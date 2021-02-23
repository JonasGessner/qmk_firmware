#include "jonas.h"

user_config_t user_config;

void matrix_init_user(void) { user_config.raw = eeconfig_read_user(); }

layer_state_t default_layer_state_set_user(layer_state_t state) {
    layer_state_t layer = get_highest_layer(state);

    eeconfig_update_default_layer(1U << layer);

    return state;
}

extern bool scan_keycode(uint8_t keycode);

void keyboard_did_start() {
    if (!scan_keycode(KC_LALT)) {
        writePin(LED_CAPS_LOCK_PIN, LED_PIN_ON_STATE);
        wait_ms(100);
        writePin(LED_CAPS_LOCK_PIN, !LED_PIN_ON_STATE);
        wait_ms(50);
        writePin(LED_CAPS_LOCK_PIN, LED_PIN_ON_STATE);
        wait_ms(100);
    }
    else {
        add_mods(MOD_BIT(KC_LALT));
        send_keyboard_report();

        uint8_t count = 0;
        while (true) {
            if (count == 0) {
                writePin(LED_CAPS_LOCK_PIN, LED_PIN_ON_STATE);
            }

            if (count == 10) {
                writePin(LED_CAPS_LOCK_PIN, !LED_PIN_ON_STATE);
            }

            count++;
            count %= 20;

            matrix_scan();

            add_mods(MOD_BIT(KC_LALT));
            send_keyboard_report();
            
            if (!scan_keycode(KC_LALT)) {
                break;
            }
        }

        del_mods(MOD_BIT(KC_LALT));
        send_keyboard_report();
    }

    writePin(LED_CAPS_LOCK_PIN, host_keyboard_led_state().caps_lock ? LED_PIN_ON_STATE : !LED_PIN_ON_STATE);
}