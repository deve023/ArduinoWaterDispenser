//=====[Libraries]=============================================================

#include "keyboard.h"

#include <Arduino.h>

//=====[Declaration of private defines]========================================

#define KEYBOARD_MAX_ROWS 4
#define KEYBOARD_MAX_COLS 4
#define KEYBOARD_DEBOUNCE_TIME_MS 40

//=====[Declaration of private data types]=====================================

typedef enum {
    KEYBOARD_SCANNING,
    KEYBOARD_DEBOUNCE,
    KEYBOARD_KEY_HOLD_PRESSED
} KeyboardStatus_t;

//=====[Declaration and initialization of private global variables]============

static char keyboardRowPins[] = {13, 14, 15, 16};
static char keyboardColPins[] = {9, 10, 11, 12};

static KeyboardStatus_t keyboardStatus;
static int timeIncrement_ms;

//=====[Declarations (prototypes) of private functions]========================

/**
 * @brief Scans the keyboard to return the pressed key, if any pressed.
 * 
 * @return char Key pressed. If none pressed: returns '\0'.
 */
static char keyboardScan();

/**
 * @brief Resets the keyboard configuration and status.
 * 
 */
static void keyboardReset();

//=====[Implementations of public functions]===================================

void keyboardInit(int dt)
{
    timeIncrement_ms = dt;
    keyboardStatus = KEYBOARD_SCANNING;

    for(char pinIndex = 0; pinIndex<KEYBOARD_MAX_COLS; pinIndex++)
        pinMode(keyboardColPins[pinIndex], INPUT_PULLUP);
    for(char pinIndex = 0; pinIndex<KEYBOARD_MAX_ROWS; pinIndex++)
        pinMode(keyboardRowPins[pinIndex], OUTPUT);
}

char keyboardUpdate()
{
    static int accumulatedDebounceKeyboardTime = 0;
    static char keyboardLastkeyPressed = '\0';

    char keyDetected = '\0';
    char keyReleased = '\0';

    switch(keyboardStatus) {
        case KEYBOARD_SCANNING:
            keyDetected = keyboardScan();
            if(keyDetected != '\0') {
                keyboardLastkeyPressed = keyDetected;
                accumulatedDebounceKeyboardTime = 0;
                keyboardStatus = KEYBOARD_DEBOUNCE;
            }
            break;
        case KEYBOARD_DEBOUNCE:
            if(accumulatedDebounceKeyboardTime >= KEYBOARD_DEBOUNCE_TIME_MS) {
                keyDetected = keyboardScan();
                if(keyDetected == keyboardLastkeyPressed)
                    keyboardStatus = KEYBOARD_KEY_HOLD_PRESSED;
                else
                    keyboardStatus = KEYBOARD_SCANNING;
            } else {
                accumulatedDebounceKeyboardTime += timeIncrement_ms;
            }
            break;
        case KEYBOARD_KEY_HOLD_PRESSED:
            keyDetected = keyboardScan();
            if(keyDetected != keyboardLastkeyPressed) {
                /* Removed if statement so it always registers released keys.
                if(keyDetected == '\0')
                    keyReleased = keyboardLastkeyPressed;*/
                keyReleased = keyboardLastkeyPressed;
                keyboardStatus = KEYBOARD_SCANNING;
            }
            break;
        default:
            keyboardReset();
    }
    return keyReleased;
}

//=====[Implementations of private functions]==================================

static char keyboardScan()
{
    char row = 0;
    char col = 0;
    char i = 0;

    char keyboardMappingIndexToChar[] = {
        '1', '2', '3', 'A',
        '4', '5', '6', 'B',
        '7', '8', '9', 'C',
        '*', '0', '#', 'D'
    };

    for(row = 0; row < KEYBOARD_MAX_ROWS; row++) {
        for(i = 0; KEYBOARD_MAX_ROWS; i++)
            digitalWrite(keyboardRowPins[i], HIGH);
        digitalWrite(keyboardRowPins[row], LOW);

        for(col = 0; col < KEYBOARD_MAX_COLS; col++) {
            if(digitalRead(keyboardColPins[col]) == LOW)
                return keyboardMappingIndexToChar[row*KEYBOARD_MAX_ROWS+ col];
        }
    }
    return '\0';
}

static void keyboardReset()
{
    keyboardStatus = KEYBOARD_SCANNING;
}