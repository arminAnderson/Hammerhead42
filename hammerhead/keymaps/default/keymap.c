// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = { 
    [0] = LAYOUT( 
		KC_ESC,         KC_Q,           KC_W,           KC_E,                   KC_R,                   KC_T,                       KC_Y,           KC_U,           KC_I,                   KC_O,                   KC_P,           KC_BACKSLASH,
		KC_TAB,         KC_A,           KC_S,           KC_D,                   KC_F,                   KC_G,                       KC_H,           KC_J,           KC_K,                   KC_L,                   KC_SCLN,        KC_ENTER,           
		KC_LEFT_ALT,    KC_Z,           KC_X,           KC_C,                   KC_V,                   KC_B,                       KC_N,           KC_M,           KC_COMM,                KC_DOT,                 KC_SLSH,        KC_RGUI,            
		                                                KC_LEFT_CTRL,           KC_LEFT_SHIFT,          MO(2),                      MO(1),          KC_SPC,         KC_BACKSPACE                      
    ),
 
    [1] = LAYOUT(
        KC_GRAVE,       KC_EXCLAIM,     KC_AT,          KC_HASH,                KC_DOLLAR,              KC_PERCENT,                 KC_CIRCUMFLEX,  KC_UNDERSCORE,  KC_ASTERISK,            KC_LEFT_PAREN,          KC_RIGHT_PAREN, KC_AMPERSAND,      
        _______,        KC_1,           KC_2,           KC_3,                   KC_4,                   KC_5,                       KC_6,           KC_7,           KC_8,                   KC_9,                   KC_0,           KC_QUOTE,             
        KC_CAPS_LOCK,   KC_NO,          KC_NO,          KC_NO,                  KC_NO,                  KC_NO,                      KC_NO,          KC_NO,          KC_NO,                  KC_NO,                  KC_NO,          _______,           
                                                        _______,                _______,                _______,                    _______,        _______,        KC_DELETE
    ),

    [2] = LAYOUT(
        _______,        _______,        _______,        KC_LEFT_PAREN,          KC_RIGHT_PAREN,         _______,                    _______,        _______,        _______,                _______,                _______,        _______,      
        _______,        _______,        _______,        KC_LEFT_CURLY_BRACE,    KC_RIGHT_CURLY_BRACE,   _______,                    _______,        KC_MINUS,       KC_PLUS,                KC_EQUAL,               _______,        _______,             
        _______,        _______,        _______,        KC_LEFT_BRACKET,        KC_RIGHT_BRACKET,       _______,                    _______,        KC_EXCLAIM,     KC_LEFT_ANGLE_BRACKET,  KC_RIGHT_ANGLE_BRACKET, _______,        _______,           
                                                        KC_BTN2,                _______,                _______,                    _______,        _______,        _______
    )  
};

struct PinStates
{
    bool a, b, c, d, center;
} states;

void keyboard_pre_init_user(void) 
{
    pointing_device_set_cpi(1024/4);

    gpio_set_pin_input_high(GP12);
    gpio_set_pin_input_high(GP13);
    gpio_set_pin_input_high(GP14);
    gpio_set_pin_input_high(GP15);
    gpio_set_pin_input_high(GP16);

    states.a = false;
    states.b = false;
    states.c = false;
    states.d = false;
    states.center = false;
}

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(KC_VOLU, KC_VOLD)  },
    [1] = { ENCODER_CCW_CW(KC_MEDIA_NEXT_TRACK, KC_MEDIA_PREV_TRACK)  },
    [2] = { ENCODER_CCW_CW(KC_WH_U, KC_WH_D)  }
};
#endif


static bool pinA = false;
static bool pinB = false;
static bool pinC = false;
static bool pinD = false;
static bool center = false;

void housekeeping_task_user(void) 
{
    pinA   = gpio_read_pin(GP12);
    pinB   = gpio_read_pin(GP13);
    pinC   = gpio_read_pin(GP14);
    pinD   = gpio_read_pin(GP15);
    center = gpio_read_pin(GP16);

    if(pinA != states.a)
    {
        if(!pinA) { register_code(KC_UP); }
        else { unregister_code(KC_UP); }
        states.a = pinA;
    }

    if(pinB != states.b)
    {
        if(!pinB) { register_code(KC_LEFT); }
        else { unregister_code(KC_LEFT); }
        states.b = pinB;
    }

    if(pinC != states.c)
    {
        if(!pinC) { register_code(KC_DOWN); }
        else { unregister_code(KC_DOWN); }
        states.c = pinC;
    }

    if(pinD != states.d)
    {
        if(!pinD) { register_code(KC_RIGHT); }
        else { unregister_code(KC_RIGHT); }
        states.d = pinD;
    }

    if(pinD != states.d)
    {
        if(!pinD) { register_code(KC_RIGHT); }
        else { unregister_code(KC_RIGHT); }
        states.d = pinD;
    }

    if(pinA && pinB && pinC && pinD)
    {
        if(center != states.center)
        {
            if(!center) { register_code(KC_MEDIA_PLAY_PAUSE); }
            else { unregister_code(KC_MEDIA_PLAY_PAUSE); }
            states.center = center;
        }
    }
}
