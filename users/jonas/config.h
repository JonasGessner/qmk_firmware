#pragma once

// Debug
// #define DEBUG_
// #define DEBUG_MATRIX_SCAN_RATE
// #define DEBUG_KEY_OVERRIDE

#ifndef DEBUG_
#    ifndef NO_DEBUG
#        define NO_DEBUG
#    endif  // !NO_DEBUG

#    if !defined(NO_PRINT)
#        define NO_PRINT
#    endif  // !NO_PRINT
#endif

// #define NO_ACTION_TAPPING
#define NO_ACTION_ONESHOT
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION
#define DISABLE_LEADER
