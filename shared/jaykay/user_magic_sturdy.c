#include QMK_KEYBOARD_H
#include "config.h"
#include "user_keycodes.h"
#include "user_magic_sturdy.h"

// -------------------------------------------------------------------------------------------------
// magic / repeat key

bool remember_last_key_user(uint16_t kc, keyrecord_t* record, uint8_t* remembered_mods)
{
    switch (kc)
    {
        // Ignore Custom Magic Keys
        case CC_MAG_2:
        case CC_MAG_3: return false;
        case CC_CMD: return false;
        case CC_ALT: return false;
        case CC_CTRL: return false;
        case CC_SHFT: return false;
        case CC_FSYM: return false;
        case CC_FNAV: return false;

        case KC_A ... KC_Z:
            if ((*remembered_mods & ~(MOD_MASK_SHIFT)) == 0)
            {
                *remembered_mods &= ~MOD_MASK_SHIFT;
            }
            break;
    }
    return true;
}

uint16_t get_alt_repeat_key_keycode_user(uint16_t kc, uint8_t mods)
{
    switch (kc)
    {
        case KC_C:
        case KC_P:
        case KC_D:
        case KC_G:
        case KC_Z: return KC_Y;
        case KC_Y: return KC_P;
        case KC_R: return KC_L;
        case KC_K: return KC_S;
        case KC_L:
        case KC_S: return KC_K;
        case KC_U: return KC_E;
        case KC_E: return KC_U;
        case KC_O: return KC_A;
        case KC_A: return KC_O;
        case KC_ASTR: return KC_EQL;
        case S(KC_DOT): return MG_COM;
        case KC_DOT:
            if (mods & MOD_MASK_SHIFT)
            {
                return MG_COM;
            }
            else
            {
                return MG_SP_The;
            }
        case KC_COMM:
            if (mods & MOD_MASK_SHIFT)
            {
                return MG_SP_BUT;
            }
            else
            {
                return MG_SP_AND;
            }
        case KC_EQL:
        case KC_MINS: return KC_RABK;
        case KC_Q: return MG_UI;
        case KC_H: return MG_OA;
        case KC_I: return MG_ON;
        case KC_N: return MG_ION;
        case KC_V: return MG_ER;
        case KC_X: return MG_ES;
        case KC_M: return MG_ENT;
        case KC_T: return MG_MENT;
        case KC_J: return MG_UST;
        case KC_B: return MG_EFORE;
        case KC_W: return MG_HICH;
        case KC_1 ... KC_0: return KC_DOT;
    }

    return kc;
}

bool process_magic_key_2(uint16_t prev_keycode, uint8_t prev_mods)
{
    switch (prev_keycode)
    {
        case KC_B: SEND_STRING("ecome"); return false;
        case KC_F: SEND_STRING("ollow"); return false;
        case KC_N: SEND_STRING("eighbor"); return false;
        case KC_H: SEND_STRING("owever"); return false;
        case KC_U: SEND_STRING("pgrade"); return false;
        case KC_O: SEND_STRING("ther"); return false;
        case KC_A: SEND_STRING("lready"); return false;
        case KC_P: SEND_STRING("sych"); return false;
        case KC_I: SEND_STRING("'ll"); return false;
        case KC_K: SEND_STRING("now"); return false;
        case KC_T: SEND_STRING("hough"); return false;
        case KC_L: SEND_STRING("ittle"); return false;
        case KC_M:
        case KC_R: SEND_STRING("ight"); return false;
        case KC_J: SEND_STRING("udge"); return false;
        case KC_C: SEND_STRING("ould"); return false;
        case KC_D: SEND_STRING("evelop"); return false;
        case KC_G: SEND_STRING("eneral"); return false;
        case KC_W: SEND_STRING("here"); return false;
        case KC_S: SEND_STRING("hould"); return false;
        case KC_DOT: SEND_STRING("com"); return false;
        case KC_COMM: SEND_STRING(" however"); return false;
        case KC_HASH: SEND_STRING("include \""); return false;
        default: SEND_STRING("'ll"); return false;
    }
    return true;
}

bool process_magic_key_3(uint16_t prev_keycode, uint8_t prev_mods)
{
    switch (prev_keycode)
    {
        case KC_B: SEND_STRING("etween"); return false;
        case KC_N: SEND_STRING("umber"); return false;
        case KC_U: SEND_STRING("pdate"); return false;
        case KC_A: SEND_STRING("bout"); return false;
        case KC_W: SEND_STRING("orld"); return false;
        case KC_G: SEND_STRING("overn"); return false;
        case KC_P: SEND_STRING("rogram"); return false;
        case KC_Q: SEND_STRING("uestion"); return false;
        case KC_C: SEND_STRING("rowd"); return false;
        case KC_S: SEND_STRING("chool"); return false;
        case KC_T: SEND_STRING("hrough"); return false;
        case KC_M: SEND_STRING("anage"); return false;
        case KC_O: SEND_STRING("xygen"); return false;
        case KC_I: SEND_STRING("'m"); return false;
        case KC_E: SEND_STRING("'re"); return false;
        case KC_DOT: SEND_STRING("com"); return false;
        case KC_COMM: SEND_STRING(" since"); return false;
        default: return false;
    }
}

// -------------------------------------------------------------------------------------------------
// process record user

bool process_magic_sturdy_user(uint16_t kc, keyrecord_t* record)
{
    if (record->event.pressed)
    {
        int rc = get_repeat_key_count();
        if (rc < -1 && kc != MG_UST)
        {
            send_char('n');
            return false;
        }

        switch (kc)
        {
            case CC_MAG_2: return process_magic_key_2(get_last_keycode(), get_last_mods());
            case CC_MAG_3: return process_magic_key_3(get_last_keycode(), get_last_mods());
            case MK_DUND: SEND_STRING(SS_LSFT(SS_TAP(X_4)) SS_DELAY(100) SS_LSFT(SS_TAP(X_MINUS))); return false;
            case MG_ENT: SEND_STRING("ent"); return false;
            case MG_MENT: SEND_STRING("ment"); return false;
            case MG_ER: SEND_STRING("er"); return false;
            case MG_ES: SEND_STRING("es"); return false;
            case MG_UST:
                if (rc < -1)
                {
                    SEND_STRING("ment");
                }
                else
                {
                    SEND_STRING("ust");
                }
                return false;
            case MG_OA: SEND_STRING("oa"); return false;
            case MG_ON: SEND_STRING("on"); return false;
            case MG_ION: SEND_STRING("ion"); return false;
            case MG_SP_BUT: SEND_STRING(" but"); return false;
            case MG_SP_AND: SEND_STRING(" and"); return false;
            case MG_SP_The: SEND_STRING(" The"); return false;
            case MG_EFORE: SEND_STRING("efore"); return false;
            case MG_HICH: SEND_STRING("hich"); return false;
            case MG_UI: SEND_STRING("ui"); return false;
            case MG_QUOT_S: SEND_STRING("'s"); return false;
            case MG_COM: SEND_STRING("com"); return false;
        }

        if (rc > 0)
        {
            switch (kc)
            {
                case KC_DQUO:
                case KC_LPRN:
                case KC_SPC:
                case KC_ENT:
                    unregister_weak_mods(MOD_MASK_CSAG);
                    SEND_STRING("for");
                    return false;
                case KC_I:
                    unregister_weak_mods(MOD_MASK_CSAG);
                    SEND_STRING("ng");
                    return false;
                case KC_DOT:
                case KC_QUES:
                case KC_EXLM:
                case KC_COLN:
                case KC_SCLN:
                    unregister_weak_mods(MOD_MASK_CSAG);
                    send_char(' ');
                    add_oneshot_mods(MOD_MASK_SHIFT);
                    set_last_keycode(KC_SPC);
                    return false;
                case KC_COMM:
                    unregister_weak_mods(MOD_MASK_CSAG);
                    SEND_STRING(" but");
                    return false;
                case KC_A:
                    unregister_weak_mods(MOD_MASK_CSAG);
                    SEND_STRING("nd");
                    return false;
                case KC_N:
                    unregister_weak_mods(MOD_MASK_CSAG);
                    send_char('f');
                    return false;
                case KC_B:
                    unregister_weak_mods(MOD_MASK_CSAG);
                    SEND_STRING("ecause");
                    return false;
                case KC_W:
                    unregister_weak_mods(MOD_MASK_CSAG);
                    SEND_STRING("ould");
                    return false;
                case KC_Y:
                    unregister_weak_mods(MOD_MASK_CSAG);
                    if (rc > 2)
                    {
                        SEND_STRING("ll");
                        return false;
                    }
                    if (rc > 1)
                    {
                        send_char('\'');
                        return false;
                    }
                    SEND_STRING("ou");
                    return false;
            }
        }
    }

    return true;
}
