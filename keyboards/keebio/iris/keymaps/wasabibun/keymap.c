#include QMK_KEYBOARD_H

#define _LAYER0 0
#define _LAYER1 1
#define _LAYER2 2

enum custom_keycodes
{
   LAYER0 = SAFE_RANGE,
   LAYER1,
   LAYER2,
};

enum tapDances
{
   TD_SHIFT_CAPS = 0,
   TD_F1_RESET = 1,
};

void safe_reset(qk_tap_dance_state_t *state, void *user_data) 
{
    if (state->count == 1)
    {
        tap_code(KC_F1);
    }
    if (state->count >= 3)
    {
        // Reset the keyboard if you tap the key more than three times
        reset_keyboard();
    }
    reset_tap_dance(state);
}

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_SHIFT_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_RSFT, KC_CAPS),
  [TD_F1_RESET] = ACTION_TAP_DANCE_FN(safe_reset),
};

// Use https://config.qmk.fm/#/keebio/iris/rev4/LAYOUT to set up initial layout
// We can convert the json to a .c file by using https://jhelvy.shinyapps.io/qmkjsonconverter/
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤                             KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘


[_LAYER0] = LAYOUT(KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5,                            KC_6, KC_7, KC_8, KC_9, KC_0, KC_DEL, 
                   KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T,                            KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC, 
                   KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_G,                 KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT,
                   KC_LCTL, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_HOME,              KC_SPC, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, TD(TD_SHIFT_CAPS),
                                        KC_LGUI, TT(2), KC_ENT,                 KC_SPC, TT(1), KC_RALT),

[_LAYER1] = LAYOUT(TD(TD_F1_RESET), KC_F2, KC_F3, KC_F4, KC_F5, KC_F6,              KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12,
                   KC_NO, KC_NO, KC_NO, KC_PGUP, KC_NO, KC_NO,                      KC_NO, KC_NO, KC_UP, KC_NO, KC_NO, KC_BSPC,
                   KC_NO, KC_NO, KC_HOME, KC_PGDN, KC_END, KC_UNDS,                 KC_MINS, KC_LEFT, KC_DOWN, KC_RGHT, KC_NO, KC_NO,
                   KC_NO, KC_NO, KC_NO, KC_PSCR, KC_LPRN, KC_RPRN, KC_NO,       KC_SPC, KC_LCBR, KC_RCBR, KC_LBRC, KC_RBRC, KC_NO, TD(TD_SHIFT_CAPS),
                                                KC_NO, TT(0), KC_ENT,           KC_SPC, TT(2), KC_NO),

[_LAYER2] = LAYOUT(KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5,                            KC_6, KC_7, KC_8, KC_9, KC_0, KC_BSLS, 
                   RGB_TOG, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_BSPC, 
                   KC_NO, KC_MPRV, KC_MNXT, KC_NO, KC_VOLU, KC_UNDS,              KC_MINS, RGB_VAI, KC_NO, RGB_HUI, RGB_SAI, KC_NO, 
                   KC_MUTE, KC_MSTP, KC_MPLY, KC_NO, KC_VOLD, KC_EQL, KC_NO,    KC_SPC, KC_PLUS, RGB_VAD, KC_NO, RGB_HUD, RGB_SAD, TD(TD_SHIFT_CAPS),
                    KC_NO, KC_TRNS /*issue going back to _LAYER1*/, KC_ENT,       KC_SPC, TO(0), KC_NO) 

};

void matrix_init_user(void)
{ // Runs boot tasks for keyboard
#ifdef RGBLIGHT_ENABLE
    // set the layer color at initalization, because it won't set otherwise
    // rgblight_enable_noeeprom(); // enables Rgb, without saving settings
    rgblight_enable();
    rgblight_sethsv_noeeprom(250, 160, 255);
    rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING+3);
#endif
}

uint32_t layer_state_set_kb(uint32_t state) //try _user?
{
#ifdef RGBLIGHT_ENABLE
    // change the color any time a layer switches
    // This function is called every time a layer switches, no matter how it switches
    switch (biton32(state))
    {
        case _LAYER1:
            rgblight_sethsv_noeeprom(HSV_TURQUOISE);
            rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING+3);
            break;
        case _LAYER2:
            rgblight_sethsv_noeeprom(HSV_PURPLE);
            rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING+3);
            break;
        default: // _LAYER0
            rgblight_sethsv_noeeprom(250, 160, 255);
            rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING+3);
            break;
    }
#endif
   return state;  // this is required, DO NOT REMOVE
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) 
    {
        switch (get_highest_layer(layer_state))
        {
            case _LAYER1:
                if (clockwise)
                {
                    tap_code16(LCTL(KC_PPLS)); // CTRL+NumpadPlus -> Zoom in
                } 
                else 
                {
                    tap_code16(LCTL(KC_PMNS)); // CTRL+NumpadMinus -> Zoom out
                }
                break;
            case _LAYER2:
                if (clockwise)
                {
                    tap_code(KC_BRIU);
                } 
                else 
                {
                    tap_code(KC_BRID);
                }
                break;
            default: // _LAYER0 and all layers
                if (clockwise)
                {
                    tap_code(KC_VOLU);
                } 
                else 
                {
                    tap_code(KC_VOLD);
                }
                break;
        }
    }
    return true;
}