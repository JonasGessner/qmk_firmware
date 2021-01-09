#include "tapping_action.h"

__attribute__((weak)) tapping_action_t **taps = NULL;

static bool tap_should_receive_record(tapping_action_t *const tap, const keyrecord_t *const record) { return tap->enabled; }

static bool process_record_for_tap(keyrecord_t *const record, tapping_action_t *tap) {
    if (!tap_should_receive_record(tap, record)) {
        return true;
    }

    // Shift old events right once to make space for new action
    tap->recorded_events <<= 1;
    // Add the new action. Key down event is a 1 bit, key up is a 0 bit
    tap->recorded_events |= (record->event.pressed ? 1 : 0);

    // Register the timestamp
    tap->timestamps[tap->end & 15] = record->event.time;
    dprintf("Time: %u\n", record->event.time);

    const uint8_t recorded_events = tap->end - tap->start + 1;
    if (recorded_events == tap->number_of_events) {
        dprintf("Has enough taps\n");
        // Enough events have happened for the tap to activate

        // Check if recorded events match
        const uint16_t mask = (1 << tap->number_of_events) - 1;
        if ((tap->recorded_events & mask) == tap->events) {
            dprintf("Events match\n");

            // Check min and max durations
            const uint16_t start_time = tap->timestamps[tap->start & 15];
            const uint16_t end_time   = tap->timestamps[tap->end & 15];

            const uint16_t elapsed = TIMER_DIFF_16(end_time, start_time);

            do {
                if (elapsed < tap->min_duration) {
                    // no good, too short
                    dprintf("Too short\n");
                    break;
                }

                if (tap->max_duration > 0 && elapsed > tap->max_duration) {
                    // no good, too long
                    dprintf("Too long: %u\n", elapsed);
                    break;
                }

                dprintf("Firing\n");

                return tap->activation_handler(record, tap->context);
            } while (false);
        }
    }

    tap->end++;
    if (recorded_events == tap->number_of_events) {
        // Keep up with the start index of the timestamps
        tap->start++;
    }

    return true;
}

bool process_record_tapping_action(uint16_t keycode, keyrecord_t *record) {
    if (taps == NULL) {
        return true;
    }

    bool send = true;

    for (size_t i = 0;; i++) {
        tapping_action_t *tap = taps[i];

        if (tap == NULL) {
            break;
        }

        if (keycode == 0 || (tap->triggers[0] != keycode && tap->triggers[1] != keycode)) {
            dprintf("Resetting tap\n");
            reset_tap(tap);
            continue;
        }

        dprintf("Sending event to tap\n");
        send = send && process_record_for_tap(record, tap);
    }

    return send;
}

// Public

void reset_tap(tapping_action_t *tap) {
    tap->start = 0;
    tap->end   = 0;
}

void disable_tap(tapping_action_t *tap) {
    reset_tap(tap);
    tap->enabled = false;
}

void enable_tap(tapping_action_t *tap) { tap->enabled = true; }

// Overrides

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_tapping_action(keycode, record) || !process_record_user(keycode, record)) {
        return false;
    }

    return true;
}
