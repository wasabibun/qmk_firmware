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
   TD_F1_RESET = 1
};
qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_SHIFT_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS),
  [TD_F1_RESET] = ACTION_TAP_DANCE_DOUBLE(KC_F1, RESET)
};

// Use https://config.qmk.fm/#/keebio/iris/rev4/LAYOUT to set up initial layout
// We can convert the json to a .c file by using https://jhelvy.shinyapps.io/qmkjsonconverter/
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_LAYER0] = LAYOUT(KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_DEL, KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC, TD(TD_SHIFT_CAPS), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_LCTL, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_HOME, KC_SPC, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_ENT, KC_LGUI, MO(2), TO(1), KC_SPC, MO(1), KC_RALT),

[_LAYER1] = LAYOUT(TD(TD_F1_RESET), KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_NO, KC_NO, KC_NO, KC_PGUP, KC_NO, KC_NO, KC_NO, KC_NO, KC_UP, KC_NO, KC_NO, KC_BSPC, KC_NO, KC_NO, KC_HOME, KC_PGDN, KC_END, KC_UNDS, KC_MINS, KC_LEFT, KC_DOWN, KC_RGHT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_PSCR, KC_LPRN, KC_RPRN, KC_NO, KC_SPC, KC_LCBR, KC_RCBR, KC_LBRC, KC_RBRC, KC_NO, KC_PENT, KC_NO, KC_NO, TO(2), KC_SPC, KC_NO, KC_NO),

[_LAYER2] = LAYOUT(KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_BSLS, RGB_TOG, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_BSPC, KC_LSFT, KC_MPRV, KC_MNXT, KC_NO, KC_VOLU, KC_UNDS, KC_MINS, RGB_VAI, KC_NO, RGB_HUI, RGB_SAI, KC_NO, KC_MUTE, KC_MSTP, KC_MPLY, KC_NO, KC_VOLD, KC_EQL, KC_NO, KC_SPC, KC_PLUS, RGB_VAD, KC_NO, RGB_HUD, RGB_SAD, KC_ENT, KC_NO, KC_NO, TO(0), KC_SPC, KC_NO, KC_NO) 

};

void matrix_init_user(void) { // Runs boot tasks for keyboard
#ifdef RGBLIGHT_ENABLE
    // set the layer color at initalization, because it won't set otherwise
    // rgblight_enable_noeeprom(); // enables Rgb, without saving settings
    rgblight_enable();
    rgblight_sethsv_noeeprom(250, 160, 255);
    rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING+2);
#endif
}

uint32_t layer_state_set_kb(uint32_t state) { //try _user?
#ifdef RGBLIGHT_ENABLE
    // change the color any time a layer switches
    // This function is called every time a layer switches, no matter how it switches
    switch (biton32(state)) {
        case _LAYER1:
            rgblight_sethsv_noeeprom(HSV_TURQUOISE);
            rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING+2);
            break;
        case _LAYER2:
            rgblight_sethsv_noeeprom(HSV_PURPLE);
            rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING+2);
            break;
        default: // _LAYER0
            rgblight_sethsv_noeeprom(250, 160, 255);
            rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING+2);
            break;
    }
#endif
   return state;  // this is required, DO NOT REMOVE
}

/*
void rgb_matrix_indicators_user(void) {
    switch (get_highest_layer(layer_state)) {
        case LAYER0:
            break;
        case LAYER1:
            rgb_matrix_set_color_all(0,0,0);
            rgb_matrix_set_color(6, 204, 255, 204);
            break;
        case LAYER2:
            rgb_matrix_set_color_all(0,0,0);
            rgb_matrix_set_color(6, 75, 255, 75);
            rgb_matrix_set_color(7, 75, 255, 75);
            break;
        default:
            break;
    }
*/
/*// Now define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
   my_layer0_layer,    // original layer 0
   my_layer1_layer,    // Overrides other layers
   my_layer2_layer     // Overrides other layers
);

void keyboard_post_init_user(void)
{
   // Enable the LED layers
   rgblight_layers = my_rgb_layers;
}

// Light all LEDs in coral when keyboard layer 1 is active
const rgblight_segment_t PROGMEM my_layer1_layer[] = RGBLIGHT_LAYER_SEGMENTS(
   {0, RGBLED_NUM, HSV_CORAL}
);
// Light all LEDs in teal when keyboard layer 2 is active
const rgblight_segment_t PROGMEM my_layer2_layer[] = RGBLIGHT_LAYER_SEGMENTS(
   {0, RGBLED_NUM, HSV_TEAL}
);*/