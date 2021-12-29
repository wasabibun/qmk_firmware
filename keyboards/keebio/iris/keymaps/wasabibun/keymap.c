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

// Use https://config.qmk.fm/#/keebio/iris/rev4/LAYOUT to set up initial layout
// We can convert the json to a .c file by using https://jhelvy.shinyapps.io/qmkjsonconverter/
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] =
{
   [_LAYER0] = LAYOUT(KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_DEL, KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC, KC_LSFT, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_LCTL, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_HOME, KC_SPC, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_ENT, KC_LGUI, KC_NO, TO(1), KC_SPC, KC_NO, KC_RALT),

   [_LAYER1] = LAYOUT(KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_NO, KC_NO, KC_NO, KC_PGUP, KC_NO, KC_NO, KC_NO, KC_NO, KC_UP, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_HOME, KC_PGDN, KC_END, KC_NO, KC_NO, KC_LEFT, KC_DOWN, KC_RGHT, KC_NO, KC_NO, RESET, KC_NO, KC_NO, KC_PSCR, KC_LBRC, KC_RBRC, KC_NO, KC_SPC, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_PENT, KC_LPRN, KC_RPRN, TO(2), KC_SPC, KC_LCBR, KC_RCBR),

   [_LAYER2] = LAYOUT(KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_BSPC, RGB_TOG, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSLS, KC_LSFT, KC_MPRV, KC_MNXT, KC_VOLU, KC_PGUP, KC_UNDS, KC_EQL, KC_HOME, RGB_HUI, RGB_SAI, RGB_VAI, KC_TRNS, KC_MUTE, KC_MSTP, KC_MPLY, KC_VOLD, KC_PGDN, KC_MINS, KC_TRNS, KC_SPC, KC_PLUS, KC_END, RGB_HUD, RGB_SAD, RGB_VAD, KC_ENT, KC_LPRN, KC_RPRN, TO(0), KC_SPC, KC_LBRC, KC_RBRC) 
};

void persistent_default_layer_set(uint16_t default_layer) 
{
   eeconfig_update_default_layer(default_layer);
   default_layer_set(default_layer);
}

void matrix_init_user(void) 
{
   rgblight_enable();
}

void matrix_scan_user(void) 
{
   #ifdef RGBLIGHT_ENABLE

   static uint8_t old_layer = 255;
   uint8_t new_layer = biton32(layer_state);

   if (old_layer != new_layer) {
      switch (new_layer) {
      case _LAYER0:
         rgblight_sethsv(HSV_CORAL);
         break;
      case _LAYER1:
         rgblight_sethsv(HSV_TEAL);
         break;
      case _LAYER2:
         rgblight_sethsv(HSV_PURPLE);
         break;
      }

      old_layer = new_layer;
  }

  #endif //RGBLIGHT_ENABLE
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  return true;
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