#include QMK_KEYBOARD_H
#include "config.h"
#include "user_layers.h"
#include "user_keycodes.h"
#include "vim.h"

enum evim_scope
{
    VIM_SCOPE_CHAR = 0,
    VIM_SCOPE_WORD = 1,
    VIM_SCOPE_DELI = 2,
    VIM_SCOPE_LINE = 3,
    VIM_SCOPE_PAGE = 4,
    VIM_SCOPE_DOCU = 5,
};

enum evim_selection
{
    VIM_SELECT_OBJECT,
    VIM_SELECT_BEFORE,
    VIM_SELECT_AFTER,
};

static uint8_t s_vim_mode   = VIM_MODE_INSERT;
static int8_t  s_vim_raise  = 0;
static uint8_t s_vim_scope  = VIM_SCOPE_CHAR;
static uint8_t s_vim_select = VIM_SELECT_AFTER;

static void vim_reset(void)
{
    s_vim_mode   = VIM_MODE_NORMAL;
    s_vim_raise  = 0;
    s_vim_scope  = VIM_SCOPE_WORD;
    s_vim_select = VIM_SELECT_AFTER;
    unregister_code(KC_LSHIFT);
}

void vim_mode_toggle(void)
{
    unregister_code(KC_LEFT_SHIFT);
    s_vim_mode  = 1 - s_vim_mode;
    s_vim_raise = 0;
}

void vim_mode_insert(void)
{
    unregister_code(KC_LEFT_SHIFT);
    s_vim_mode  = VIM_MODE_INSERT;
    s_vim_raise = 0;
}

int8_t vim_mode() { return s_vim_mode; }
bool   vim_raise(void) { return s_vim_raise != 0; }

static void vim_register1(uint16_t k1, bool press)
{
    if (press)
    {
        register_code16(k1);
    }
    else
    {
        unregister_code16(k1);
    }
}


#define send_taps1(tap1) tap_code16(tap1)
#define send_taps2(tap1, tap2) \
    tap_code16(tap1);          \
    tap_code16(tap2)
#define send_taps3(tap1, tap2, tap3) \
    tap_code16(tap1);                \
    tap_code16(tap2);                \
    tap_code16(tap3)


#define CMD_MOVE_LEFT_CHAR(press)     vim_register1(KC_LEFT, press)
#define CMD_MOVE_LEFT_WORD(press)     vim_register1(A(KC_LEFT), press)
#define CMD_MOVE_LEFT_LINE(press)     vim_register1(KC_HOME, press)
#define CMD_MOVE_UP_LINE(press)       vim_register1(KC_UP, press)
#define CMD_MOVE_LEFT_PAGE(press)     vim_register1(KC_PGUP, press)
#define CMD_MOVE_LEFT_DELI(press)     vim_register1(A(C(KC_UP)), press)
#define CMD_MOVE_LEFT_DOCU(press)     vim_register1(C(S(KC_TAB)), press)
#define CMD_MOVE_LEFT_APP(press)      vim_register1(G(S(KC_GRV)), press)
#define CMD_MOVE_RIGHT_APP(press)     vim_register1(G(KC_GRV), press)
#define CMD_MOVE_LEFT_DESKTOP(press)  vim_register1(C(KC_LEFT), press)
#define CMD_MOVE_RIGHT_DESKTOP(press) vim_register1(C(KC_RIGHT), press)
#define CMD_MOVE_RIGHT_CHAR(press)    vim_register1(KC_RIGHT, press)
#define CMD_MOVE_RIGHT_WORD(press)    vim_register1(A(KC_RIGHT), press)
#define CMD_MOVE_RIGHT_LINE(press)    vim_register1(KC_END, press)
#define CMD_MOVE_DOWN_LINE(press)     vim_register1(KC_DOWN, press)
#define CMD_MOVE_RIGHT_PAGE(press)    vim_register1(KC_PGDOWN, press)
#define CMD_MOVE_RIGHT_DELI(press)    vim_register1(A(C(KC_DOWN)), press)
#define CMD_MOVE_RIGHT_DOCU(press)    vim_register1(C(KC_TAB), press)
#define CMD_MOVE_TOP_DOCU(press)      vim_register1(G(KC_UP), press)
#define CMD_MOVE_END_DOCU(press)      vim_register1(G(KC_DOWN), press)
#define CMD_DELETE_LINE(press)        vim_register1(C(S(KC_D)), press) // Delete Line = Ctrl-Shift-D

#define CMD_DELETE_LEFT_LINE          send_taps2(S(KC_HOME), KC_DELETE)
#define CMD_DELETE_RIGHT_LINE         send_taps2(S(KC_END), KC_DELETE)
#define CMD_CHANGE_LINE               send_taps3(KC_END, S(KC_HOME), KC_DELETE)
#define CMD_DELETE_LEFT_WORD          send_taps2(S(A(KC_LEFT)), KC_DELETE)
#define CMD_DELETE_RIGHT_WORD         send_taps2(S(A(KC_RIGHT)), KC_DELETE)
#define CMD_DELETE_INSIDE_WORD        send_taps3(A(KC_LEFT), A(S(KC_RIGHT)), KC_DEL)

static void vim_insert(bool press)
{
    switch (s_vim_scope)
    {
        case VIM_SCOPE_LINE:
            switch (s_vim_select)
            {
                case VIM_SELECT_BEFORE: vim_register1(KC_HOME, press); break;
                case VIM_SELECT_AFTER: vim_register1(KC_END, press); break;
            }
            break;

        case VIM_SCOPE_CHAR:
            switch (s_vim_select)
            {
                case VIM_SELECT_BEFORE: vim_register1(KC_LEFT, press); break;
                case VIM_SELECT_AFTER: vim_register1(KC_RIGHT, press); break;
                case VIM_SELECT_OBJECT: break;
            }
            break;

        case VIM_SCOPE_WORD:
            switch (s_vim_select)
            {
                case VIM_SELECT_BEFORE: vim_register1(A(KC_LEFT), press); break;
                case VIM_SELECT_AFTER: vim_register1(A(KC_RIGHT), press); break;
                case VIM_SELECT_OBJECT: break;
            }
            break;
        case VIM_SCOPE_DELI:
        case VIM_SCOPE_PAGE:
        case VIM_SCOPE_DOCU:
        default: break;
    }

    if (!press)
    {
        vim_mode_insert();
    }
}

static void vim_delete(bool press)
{
    // if raise is true
    if (s_vim_raise)
    {
        CMD_DELETE_LINE(press);
    }
    else
    {
        switch (s_vim_scope)
        {
            case VIM_SCOPE_LINE:
                switch (s_vim_select)
                {
                    case VIM_SELECT_BEFORE: CMD_DELETE_LEFT_LINE; break;
                    case VIM_SELECT_AFTER: CMD_DELETE_RIGHT_LINE; break;
                    case VIM_SELECT_OBJECT: CMD_DELETE_LINE(press); break;
                }
                break;
            case VIM_SCOPE_WORD:
                switch (s_vim_select)
                {
                    case VIM_SELECT_BEFORE: CMD_DELETE_LEFT_WORD; break;
                    case VIM_SELECT_AFTER: CMD_DELETE_RIGHT_WORD; break;
                    case VIM_SELECT_OBJECT: CMD_DELETE_INSIDE_WORD; break;
                }
                break;
        }
    }
}

static void vim_change(bool press)
{
    switch (s_vim_scope)
    {
        case VIM_SCOPE_LINE:
            switch (s_vim_select)
            {
                case VIM_SELECT_BEFORE: CMD_DELETE_LEFT_LINE; break;
                case VIM_SELECT_AFTER: CMD_DELETE_RIGHT_LINE; break;
                case VIM_SELECT_OBJECT: CMD_CHANGE_LINE; break;
            }
            break;
        case VIM_SCOPE_WORD:
            switch (s_vim_select)
            {
                case VIM_SELECT_BEFORE: CMD_DELETE_LEFT_WORD; break;
                case VIM_SELECT_AFTER: CMD_DELETE_RIGHT_WORD; break;
                case VIM_SELECT_OBJECT: CMD_DELETE_INSIDE_WORD; break;
            }
            break;
    }
}

static void vim_goto(bool press)
{
    switch (s_vim_scope)
    {
        case VIM_SCOPE_WORD: CMD_MOVE_LEFT_WORD(press); break;
        case VIM_SCOPE_DELI: CMD_MOVE_LEFT_DELI(press); break;
        case VIM_SCOPE_LINE:
            switch (s_vim_select)
            {
                case VIM_SELECT_BEFORE: /*start of line*/ break;
                case VIM_SELECT_AFTER: /*end of line*/ break;
                case VIM_SELECT_OBJECT: tap_code16(C(KC_G)); break;
            }
            break;

        case VIM_SCOPE_PAGE:
            switch (s_vim_select)
            {
                case VIM_SELECT_BEFORE: /*top of page*/ break;
                case VIM_SELECT_AFTER: /*bottom of page*/ break;
                case VIM_SELECT_OBJECT: /*centre page at cursor*/ break;
            }
            break;
        case VIM_SCOPE_DOCU:
            switch (s_vim_select)
            {
                case VIM_SELECT_BEFORE: CMD_MOVE_TOP_DOCU(press); break;
                case VIM_SELECT_AFTER: CMD_MOVE_END_DOCU(press); break;
            }
        default:
        case VIM_SCOPE_CHAR: tap_code16(A(KC_S)); break;
    }
}

static void vim_move_left(bool press)
{
    switch (s_vim_scope)
    {
        case VIM_SCOPE_WORD: CMD_MOVE_LEFT_WORD(press); break;
        case VIM_SCOPE_DELI: CMD_MOVE_LEFT_DELI(press); break;
        case VIM_SCOPE_LINE: CMD_MOVE_LEFT_LINE(press); break;
        case VIM_SCOPE_PAGE: CMD_MOVE_LEFT_PAGE(press); break;
        case VIM_SCOPE_DOCU: CMD_MOVE_LEFT_DOCU(press); break;
        default:
        case VIM_SCOPE_CHAR: CMD_MOVE_LEFT_CHAR(press); break;
    }
}

static void vim_move_up(bool press)
{
    switch (s_vim_scope)
    {
        case VIM_SCOPE_WORD: CMD_MOVE_UP_LINE(press); break;
        case VIM_SCOPE_DELI: CMD_MOVE_UP_LINE(press); break;
        case VIM_SCOPE_LINE: CMD_MOVE_UP_LINE(press); break;
        case VIM_SCOPE_PAGE: CMD_MOVE_LEFT_PAGE(press); break;
        case VIM_SCOPE_DOCU: CMD_MOVE_LEFT_DOCU(press); break;
        default:
        case VIM_SCOPE_CHAR: CMD_MOVE_UP_LINE(press); break;
    }
}

static void vim_move_right(bool press)
{
    switch (s_vim_scope)
    {
        case VIM_SCOPE_WORD: CMD_MOVE_RIGHT_WORD(press); break;
        case VIM_SCOPE_DELI: CMD_MOVE_RIGHT_DELI(press); break;
        case VIM_SCOPE_LINE: CMD_MOVE_RIGHT_LINE(press); break;
        case VIM_SCOPE_PAGE: CMD_MOVE_RIGHT_PAGE(press); break;
        case VIM_SCOPE_DOCU: CMD_MOVE_RIGHT_DOCU(press); break;
        default:
        case VIM_SCOPE_CHAR: CMD_MOVE_RIGHT_CHAR(press); break;
    }
}

static void vim_move_down(bool press)
{
    switch (s_vim_scope)
    {
        case VIM_SCOPE_WORD: CMD_MOVE_DOWN_LINE(press); break;
        case VIM_SCOPE_DELI: CMD_MOVE_DOWN_LINE(press); break;
        case VIM_SCOPE_LINE: CMD_MOVE_DOWN_LINE(press); break;
        case VIM_SCOPE_PAGE: CMD_MOVE_RIGHT_PAGE(press); break;
        case VIM_SCOPE_DOCU: CMD_MOVE_RIGHT_DOCU(press); break;
        default:
        case VIM_SCOPE_CHAR: CMD_MOVE_DOWN_LINE(press); break;
    }
}

bool process_vim(uint8_t keycode, keyrecord_t* record)
{
    if (s_vim_mode == VIM_MODE_INSERT)
        return true;

    switch (keycode)
    {
        case CC_FNAV: s_vim_raise = record->event.pressed; return true;
    }

    if (keycode >= TC_RANGE_START && keycode <= TC_RANGE_END)
    {
        if (s_vim_mode == VIM_MODE_NORMAL)
            return false;

        return true;
    }

    if (keycode >= CC_RANGE_VIM_START && keycode <= CC_RANGE_VIM_END)
    {
        bool press = record->event.pressed;

        if (press)
        {
            switch (keycode)
            {
                case CC_VIM_VISUAL:
                    if (((get_mods() | get_weak_mods()) & MOD_MASK_SHIFT) != 0)
                    {
                        unregister_code(KC_LEFT_SHIFT);
                    }
                    else
                    {
                        register_code(KC_LEFT_SHIFT);
                    }
                    return false;
            }
        }
        else
        {
            switch (keycode)
            {
                case CC_VIM_VISUAL: return false;
            }
        }

        switch (keycode)
        {
            case CC_VIM_GOTO: vim_goto(press); break;
            case CC_VIM_INSERT: vim_insert(press); break;

            case CC_VIM_UNDO: vim_register1(G(KC_Z), press); break;
            case CC_VIM_REDO: vim_register1(G(S(KC_Z)), press); break;

            case CC_VIM_INDENT: vim_register1(KC_TAB, press); break;
            case CC_VIM_UNINDENT: vim_register1(S(KC_TAB), press); break;

            case CC_VIM_LEFT: vim_move_left(press); break;
            case CC_VIM_RIGHT: vim_move_right(press); break;
            case CC_VIM_UP: vim_move_up(press); break;
            case CC_VIM_DOWN: vim_move_down(press); break;

            case CC_VIM_CHANGE: vim_change(press); break;
            case CC_VIM_DELETE: vim_delete(press); break;
        }

        if (press)
        {
            switch (keycode)
            {
                case CC_VIM_RAISE: s_vim_raise = true; break;
                case CC_VIM_CLEAR: vim_reset(); break;

                case CC_VIM_CHAR: s_vim_scope = VIM_SCOPE_CHAR; break;
                case CC_VIM_WORD: s_vim_scope = VIM_SCOPE_WORD; break;
                case CC_VIM_DELI: s_vim_scope = VIM_SCOPE_DELI; break;
                case CC_VIM_LINE: s_vim_scope = VIM_SCOPE_LINE; break;
                case CC_VIM_PAGE: s_vim_scope = VIM_SCOPE_PAGE; break;
                case CC_VIM_DOCU: s_vim_scope = VIM_SCOPE_DOCU; break;

                case CC_VIM_END: s_vim_select = VIM_SELECT_AFTER; break;
                case CC_VIM_BEGIN: s_vim_select = VIM_SELECT_BEFORE; break;
                case CC_VIM_INSIDE: s_vim_select = VIM_SELECT_OBJECT; break;

                // Commands
                case CC_VIM_CUT:
                    unregister_code(KC_LEFT_SHIFT);
                    vim_register1(G(KC_X), press);
                    break;
                case CC_VIM_YANK:
                    if (s_vim_raise)
                    {
                        vim_register1(G(KC_V), press);
                    }
                    else
                    {
                        unregister_code(KC_LEFT_SHIFT);
                        vim_register1(G(KC_C), press);
                    }
                    break;
                case CC_VIM_ENTER: vim_register1(KC_ENTER, press); break;
            }

            return false;
        }
        else
        {
            switch (keycode)
            {
                case CC_VIM_RAISE: s_vim_raise = false; break;
                case CC_VIM_SEARCH:
                    switch (s_vim_scope)
                    {
                        case VIM_SCOPE_WORD: CMD_MOVE_LEFT_WORD(press); break;
                        case VIM_SCOPE_PAGE:
                        case VIM_SCOPE_LINE: tap_code16(C(KC_G)); break;
                        default:
                        case VIM_SCOPE_CHAR: tap_code16(A(KC_S)); break;
                    }

                    tap_code16(G(KC_F));
                    break;
            }

            switch (keycode)
            {
                case CC_VIM_SEARCH:
                case CC_VIM_CHANGE:
                case CC_VIM_INSERT: vim_mode_insert(); break;
            }

            return false;
        }

        return false;
    }
    return true;
}
