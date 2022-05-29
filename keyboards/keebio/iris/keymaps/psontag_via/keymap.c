#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

#define _MAIN 0
#define _SYM1 1
#define _SYM2 2
#define _ARROW 3


// Required for encoder app change
static bool is_alt_tab_active = false;
static uint16_t alt_tab_timer = 0;
#define TABBING_TIMER 1000

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_MAIN] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    CAPSWRD,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_ESC,MT(MOD_LGUI,KC_A),MT(MOD_LALT,KC_S),MT(MOD_LCTL,KC_D),MT(MOD_LSFT,KC_F),KC_G,KC_H,MT(MOD_RSFT,KC_J),MT(MOD_LCTL,KC_K),MT(MOD_LALT,KC_L),MT(MOD_LGUI,KC_SCLN), KC_QUOT,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_ENTER,          KC_END,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    KC_LGUI,LT(_SYM1,KC_SPC),LT(_SYM2,KC_BSPC), KC_DEL,  LT(_ARROW,KC_ENT), KC_LALT
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_SYM1] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC,                            KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_QUOT,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, RGB_MOD, _______,                            _______, KC_MINS, KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______, RGB_HUD, RGB_SAD, RGB_VAD, RGB_RMOD, _______, _______,          _______, _______, _______, _______, _______, _______, _______,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______, _______, _______,                   _______, _______, _______
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_SYM2] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                            KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     RESET,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_QUOT,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     KC_DEL,  _______, _______, _______, _______, _______,                            KC_RBRC, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     BL_STEP, _______, _______, _______, _______, _______, _______,          _______, _______, _______,  _______, _______, _______, _______,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______, _______, _______,                    _______,  _______, _______
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  ),

  [_ARROW] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_F12,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                              KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, KC_MPRV, KC_MPLY, KC_MSTP, KC_MNXT, KC_VOLU,                            _______, _______, _______, _______, _______, _______,
  //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     _______, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_VOLD,                            KC_HOME, KC_LEFT, KC_DOWN,  KC_UP,  KC_RGHT,  KC_END,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______, _______, _______, _______, _______, _______, KC_SLEP,          _______, _______, _______, KC_PGDN, KC_PGUP, _______, _______,
  //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    _______, _______, _______,                   _______, _______, _______
                                // └────────┴────────┴────────┘                 └────────┴────────┴────────┘
  )

};


bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
    else if (index == 1) {
        if (IS_LAYER_ON(_MAIN)) {
            // Switch between app windows cmd + `
            if (clockwise) {
                tap_code16(G(KC_GRV));
            } else {
                tap_code16(S(G(KC_GRV)));
            }
        } else if (IS_LAYER_ON(_SYM1)) {
            // Switch between apps cmd + tab
            if (!clockwise) {
                if (!is_alt_tab_active) {
                    // Press cmd once
                    is_alt_tab_active = true;
                    register_code(KC_LCMD);
                }
                alt_tab_timer = timer_read();
                tap_code16(KC_TAB);
                // tap_code16(G(KC_TAB));
            } else {
                if (!is_alt_tab_active) {
                    // Press cmd once
                    is_alt_tab_active = true;
                    register_code(KC_LCMD);
                }
                alt_tab_timer = timer_read();
                tap_code16(S(KC_TAB));
                // tap_code16(S(G(KC_TAB)));
            }
        } else if (IS_LAYER_ON(_SYM2)) {
            // Switch between tabs ctrl + tab
            if (clockwise) {
                tap_code16(C(KC_TAB));
            } else {
                tap_code16(S(C(KC_TAB)));
            }
        }
    }
    return true;
}

void matrix_scan_user(void) {
    // Release CMD after TABBING_TIMER expired
    if (is_alt_tab_active) {
        if (timer_elapsed(alt_tab_timer) > TABBING_TIMER) {
            unregister_code(KC_LCMD);
            is_alt_tab_active = false;
        }
    }
}
