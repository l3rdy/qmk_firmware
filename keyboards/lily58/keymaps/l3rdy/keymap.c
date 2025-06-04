#include QMK_KEYBOARD_H
#include "luna.h"

// Layer names for clarity
enum custom_layers {
    _BASE = 0,
    _NAV,
    _FN,
    _RGB,
};

enum custom_keycodes {
    AE_LO_KC = SAFE_RANGE,
    AE_UP_KC,
    OE_LO_KC,
    OE_UP_KC,
    UE_LO_KC,
    UE_UP_KC,
    SZ_LO_KC,
};

#define AE_LO  "\"" "a"   // ä
#define AE_UP  "\"" "A"   // Ä
#define OE_LO  "\"" "o"   // ö
#define OE_UP  "\"" "O"   // Ö
#define UE_LO  "\"" "u"   // ü
#define UE_UP  "\"" "U"   // Ü
#define SZ_LO  "ss"       // ß (no direct dead key, but you can use "ss" or assign Unicode if you want)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
        KC_TAB, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_GRV,
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_QUOT,
        KC_LSFT, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_MINS,
        KC_LCTL, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_LBRC, KC_RBRC, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,
        KC_LGUI, KC_BSPC, MO(_NAV), KC_SPC, KC_ENT, MO(_FN), KC_LALT, KC_RGUI
    ),
    [_NAV] = LAYOUT(
        KC_ESC, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_TRNS, QK_MACRO_0, KC_UP, QK_MACRO_1, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_NO, QK_MACRO_2, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_TRNS, KC_HOME, KC_NO, KC_END, KC_NO, KC_DEL, KC_NO, KC_NO, KC_PIPE, KC_GRV, KC_LCBR, KC_RCBR, KC_NO, KC_NO,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, MO(_RGB), KC_TRNS, KC_TRNS
    ),
    [_FN] = LAYOUT(
        KC_ESC, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11,
        KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_AT, UE_LO_KC, KC_NO, OE_LO_KC, KC_NO, KC_F12,
        KC_TRNS, AE_LO_KC, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_QUOT, KC_QUOT, KC_NO, KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS, KC_NO,
        KC_TRNS, KC_TRNS, MO(_RGB), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
    [_RGB] = LAYOUT(
        RGB_TOG, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_A, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, RGB_SPD, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    luna_process_record(keycode, record); // Always call Luna's handler

    if (!record->event.pressed) return true;

    switch (keycode) {
        case QK_MACRO_0:
            SEND_STRING(SS_DOWN(X_LCTL)SS_DOWN(X_LGUI)SS_TAP(X_LEFT)SS_UP(X_LGUI)SS_UP(X_LCTL));
            return false;
        case QK_MACRO_1:
            SEND_STRING(SS_DOWN(X_LCTL)SS_DOWN(X_LGUI)SS_TAP(X_RIGHT)SS_UP(X_LGUI)SS_UP(X_LCTL));
            return false;
        case QK_MACRO_2:
            SEND_STRING(
                SS_DOWN(X_LCTL) SS_DELAY(50)
                SS_DOWN(X_LALT) SS_DELAY(50)
                SS_TAP(X_HOME) SS_DELAY(50)
                SS_UP(X_LALT) SS_DELAY(50)
                SS_UP(X_LCTL)
            );
            return false;
        case AE_LO_KC:
            if (get_mods() & (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT))) {
                SEND_STRING(AE_UP); // Shift held: send Ä
            } else {
                SEND_STRING(AE_LO); // No shift: send ä
            }
            return false;
        case OE_LO_KC:
            if (get_mods() & (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT))) {
                SEND_STRING(OE_UP);
            } else {
                SEND_STRING(OE_LO);
            }
            return false;
        case UE_LO_KC:
            if (get_mods() & (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT))) {
                SEND_STRING(UE_UP);
            } else {
                SEND_STRING(UE_LO);
            }
            return false;
        case SZ_LO_KC:
            SEND_STRING(SZ_LO);
            return false;
    }
    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    //return update_tri_layer_state(state, _NAV, _FN, _RGB);
    return state; // <-- Remove tri-layer logic, allow direct layer access
}

#ifdef OLED_ENABLE
static const char *get_layer_name(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case _BASE: return "BASE";
        case _NAV:  return "NAV";
        case _FN:   return "FN";
        case _RGB:  return "RGB";
        default:    return "UNDEF";
    }
}

bool oled_task_user(void) {
    oled_set_cursor(0, 0);
    oled_write_ln(get_layer_name(layer_state), false);
    luna_update_status();
    render_luna(0,9);
    return false;
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!is_keyboard_master())
        return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
    return OLED_ROTATION_270; // or OLED_ROTATION_0 depending on your build  
    return rotation;
}
#endif
