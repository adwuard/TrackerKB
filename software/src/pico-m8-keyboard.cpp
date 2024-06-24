/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2024 Hsuan Han Lai
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 *
 * Changes Made:
    ## 06-18-2024
    - HID keyboard implementation
    - Added multi-keys support and key defintion for M8 Tracker Headless
 */

#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "pico/binary_info.h"

#include "includes/usb.h"
#include "includes/Adafruit_USBD_CDC-stub.h"
#include "Adafruit_TinyUSB_Arduino/src/Adafruit_TinyUSB.h"
#include "TinyUSB_Mouse_and_Keyboard/TinyUSB_Mouse_and_Keyboard.h"

// GPIO pins of the key switch
#define KEY_UP_PIN 9
#define KEY_DOWN_PIN 10
#define KEY_LEFT_PIN 7
#define KEY_RIGHT_PIN 8
#define KEY_OPTION_PIN 11
#define KEY_EDIT_PIN 12
#define KEY_SHIFT_PIN 13
#define KEY_PLAY_PIN 14

// Adafruit TinyUSB instance
extern Adafruit_USBD_Device TinyUSBDevice;

// Key code mapping for the keys
static const int kMaxKeys = 8;
static const char keys_map[kMaxKeys][2] = {
    {KEY_UP_PIN, KEY_UP_ARROW}, //mapped to arrow up
    {KEY_DOWN_PIN, KEY_DOWN_ARROW}, //mapped to arrow down
    {KEY_LEFT_PIN, KEY_LEFT_ARROW}, //mapped to arrow left
    {KEY_RIGHT_PIN, KEY_RIGHT_ARROW}, //mapped to arrow right 
    {KEY_OPTION_PIN, 'z'}, //mapped to z key
    {KEY_EDIT_PIN, 'x'}, //mapped to x Key
    {KEY_SHIFT_PIN, KEY_LEFT_SHIFT}, //mapped to  Left shift
    {KEY_PLAY_PIN, ' '}  //mapped to Space-bar
};

static const int kDebounceDelay = 5;
static uint32_t debounce[kMaxKeys][2];

int main() {
    bi_decl(bi_program_description("Dirtywave M8 Tracker Keyboard"));
    bi_decl(bi_program_feature("USB HID Device"));

    board_init();
    TinyUSBDevice.begin();
    Keyboard.begin();

    for (int i = 0; i < kMaxKeys; i++) {
        gpio_init(keys_map[i][0]);
        gpio_set_dir(keys_map[i][0], GPIO_IN);
        gpio_pull_down(keys_map[i][0]);
        debounce[i][0] = 0;
        debounce[i][1] = to_ms_since_boot(get_absolute_time());
    }

    while (1) {
        for (int i = 0; i < kMaxKeys; i++) {
            bool state = gpio_get(keys_map[i][0]);
            uint32_t now = to_ms_since_boot(get_absolute_time());
            if ((now - debounce[i][1] > kDebounceDelay) && state != debounce[i][0]) {
                if (!state)
                    Keyboard.release(keys_map[i][1]);
                else
                    Keyboard.press(keys_map[i][1]);
                debounce[i][0] = state;
                debounce[i][1] = now;
            }
        }
    }
}
