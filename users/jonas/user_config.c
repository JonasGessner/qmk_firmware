#include "jonas.h"

user_config_t user_config;

void matrix_init_user(void) { user_config.raw = eeconfig_read_user(); }

layer_state_t default_layer_state_set_user(layer_state_t state) {
    layer_state_t layer = get_highest_layer(state);

    eeconfig_update_default_layer(1U << layer);

    return state;
}
