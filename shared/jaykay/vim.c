#include QMK_KEYBOARD_H
#include "config.h"
#include "user_layers.h"
#include "user_keycodes.h"
#include "vim.h"

enum evim_modes
{
    VIM_MODE_CHAR    = 0,
    VIM_MODE_WORD    = 1,
    VIM_MODE_DELI    = 2,
    VIM_MODE_LINE    = 3,
    VIM_MODE_PAGE    = 4,
    VIM_MODE_DOCU    = 5,
    VIM_MODE_APP     = 6,
    VIM_MODE_DESKTOP = 7,
};

enum evim_selection
{
    VIM_SELECT_OBJECT,
    VIM_SELECT_BEFORE,
    VIM_SELECT_AFTER,
};

static uint8_t s_vim_enabled = 0;
static uint8_t s_vim_mode    = VIM_MODE_CHAR;
static uint8_t s_vim_select  = VIM_SELECT_AFTER;

static void vim_reset(void)
{
    s_vim_mode   = VIM_MODE_WORD;
    s_vim_select = VIM_SELECT_AFTER;
    unregister_code(KC_LSHIFT);
}

void vim_enable()
{
    s_vim_enabled = 1;
    user_layer_on(LAYER_VIM);
}

void vim_disable()
{
    user_layer_on(LAYER_QWERTY);
    unregister_code(KC_LEFT_SHIFT);
    s_vim_enabled = 0;
}

bool vim_is_active() { return (s_vim_enabled == 1); }

#define CMD_MOVE_LEFT_CHAR     tap_code(KC_LEFT)
#define CMD_MOVE_LEFT_WORD     tap_code16(A(KC_LEFT))
#define CMD_MOVE_LEFT_LINE     tap_code(KC_HOME)
#define CMD_MOVE_UP_LINE       tap_code(KC_UP)
#define CMD_MOVE_LEFT_PAGE     tap_code16(KC_PGUP)
#define CMD_MOVE_LEFT_DELI     tap_code16(A(C(KC_UP))) // Previous Delimiter = Alt-Control-Up
#define CMD_MOVE_LEFT_DOCU     tap_code16(C(S(KC_TAB)))
#define CMD_MOVE_LEFT_APP      tap_code16(G(S(KC_GRV)))
#define CMD_MOVE_RIGHT_APP     tap_code16(G(KC_GRV))
#define CMD_MOVE_LEFT_DESKTOP  tap_code16(C(KC_LEFT))
#define CMD_MOVE_RIGHT_DESKTOP tap_code16(C(KC_RIGHT))
#define CMD_MOVE_RIGHT_CHAR    tap_code(KC_RIGHT)
#define CMD_MOVE_RIGHT_WORD    tap_code16(A(KC_RIGHT))
#define CMD_MOVE_RIGHT_LINE    tap_code(KC_END)
#define CMD_MOVE_DOWN_LINE     tap_code(KC_DOWN)
#define CMD_MOVE_RIGHT_PAGE    tap_code16(KC_PGDOWN)
#define CMD_MOVE_RIGHT_DELI    tap_code16(A(C(KC_DOWN))) // Next Delimiter = Alt-Control-Down
#define CMD_MOVE_RIGHT_DOCU    tap_code16(C(KC_TAB))
#define CMD_MOVE_TOP_DOCU      tap_code16(G(KC_UP))
#define CMD_MOVE_END_DOCU      tap_code16(G(KC_DOWN))
#define CMD_DELETE_LEFT_LINE \
    tap_code16(S(KC_HOME));  \
    tap_code(KC_DELETE)
#define CMD_DELETE_RIGHT_LINE \
    tap_code16(S(KC_END));    \
    tap_code(KC_DELETE)
#define CMD_CHANGE_LINE     \
    tap_code(KC_END);       \
    tap_code16(S(KC_HOME)); \
    tap_code(KC_DELETE)
#define CMD_DELETE_LINE tap_code16(C(S(KC_D))) // Delete Line = Ctrl-Shift-D
#define CMD_DELETE_LEFT_WORD   \
    tap_code16(S(A(KC_LEFT))); \
    tap_code(KC_DELETE)
#define CMD_DELETE_RIGHT_WORD   \
    tap_code16(S(A(KC_RIGHT))); \
    tap_code(KC_DELETE)
#define CMD_DELETE_INSIDE_WORD  \
    tap_code(KC_RIGHT);         \
    tap_code16(A(KC_LEFT));     \
    tap_code16(A(S(KC_RIGHT))); \
    tap_code(KC_DELETE)

static void vim_insert(void)
{
    switch (s_vim_mode)
    {
        case VIM_MODE_LINE:
            switch (s_vim_select)
            {
                case VIM_SELECT_BEFORE: tap_code(KC_UP);
                case VIM_SELECT_AFTER:
                    tap_code(KC_END);
                    tap_code(KC_ENTER);
                    break;
            }
            break;

        case VIM_MODE_CHAR:
            switch (s_vim_select)
            {
                case VIM_SELECT_BEFORE: tap_code(KC_LEFT); break;
                case VIM_SELECT_AFTER: tap_code(KC_RIGHT); break;
                case VIM_SELECT_OBJECT: break;
            }

        case VIM_MODE_WORD:
        case VIM_MODE_DELI:
        case VIM_MODE_PAGE:
        case VIM_MODE_DOCU:
        default: break;
    }
}

static void vim_delete(void)
{
    switch (s_vim_mode)
    {
        case VIM_MODE_LINE:
            switch (s_vim_select)
            {
                case VIM_SELECT_BEFORE: CMD_DELETE_LEFT_LINE; break;
                case VIM_SELECT_AFTER: CMD_DELETE_RIGHT_LINE; break;
                case VIM_SELECT_OBJECT: CMD_DELETE_LINE; break;
            }
            break;
        case VIM_MODE_WORD:
            switch (s_vim_select)
            {
                case VIM_SELECT_BEFORE: CMD_DELETE_LEFT_WORD; break;
                case VIM_SELECT_AFTER: CMD_DELETE_RIGHT_WORD; break;
                case VIM_SELECT_OBJECT: CMD_DELETE_INSIDE_WORD; break;
            }
            break;
    }
}

static void vim_change(void)
{
    switch (s_vim_mode)
    {
        case VIM_MODE_LINE:
            switch (s_vim_select)
            {
                case VIM_SELECT_BEFORE: CMD_DELETE_LEFT_LINE; break;
                case VIM_SELECT_AFTER: CMD_DELETE_RIGHT_LINE; break;
                case VIM_SELECT_OBJECT: CMD_CHANGE_LINE; break;
            }
            break;
        case VIM_MODE_WORD:
            switch (s_vim_select)
            {
                case VIM_SELECT_BEFORE: CMD_DELETE_LEFT_WORD; break;
                case VIM_SELECT_AFTER: CMD_DELETE_RIGHT_WORD; break;
                case VIM_SELECT_OBJECT: CMD_DELETE_INSIDE_WORD; break;
            }
            break;
    }
}

static void vim_goto(void)
{
    switch (s_vim_mode)
    {
        case VIM_MODE_WORD: CMD_MOVE_LEFT_WORD; break;
        case VIM_MODE_DELI: CMD_MOVE_LEFT_DELI; break;
        case VIM_MODE_LINE: CMD_MOVE_LEFT_LINE; break;
        case VIM_MODE_PAGE: CMD_MOVE_LEFT_PAGE; break;
        case VIM_MODE_DOCU:
            switch (s_vim_select)
            {
                case VIM_SELECT_BEFORE: CMD_MOVE_TOP_DOCU; break;
                case VIM_SELECT_AFTER: CMD_MOVE_END_DOCU; break;
            }
        default:
        case VIM_MODE_CHAR: CMD_MOVE_LEFT_CHAR; break;
    }
}

static void vim_move_left(void)
{
    switch (s_vim_mode)
    {
        case VIM_MODE_WORD: CMD_MOVE_LEFT_WORD; break;
        case VIM_MODE_DELI: CMD_MOVE_LEFT_DELI; break;
        case VIM_MODE_LINE: CMD_MOVE_LEFT_LINE; break;
        case VIM_MODE_PAGE: CMD_MOVE_LEFT_PAGE; break;
        case VIM_MODE_DOCU: CMD_MOVE_LEFT_DOCU; break;
        case VIM_MODE_APP: CMD_MOVE_LEFT_APP; break;
        case VIM_MODE_DESKTOP: CMD_MOVE_LEFT_DESKTOP; break;
        default:
        case VIM_MODE_CHAR: CMD_MOVE_LEFT_CHAR; break;
    }
}

static void vim_move_up(void)
{
    switch (s_vim_mode)
    {
        case VIM_MODE_WORD: CMD_MOVE_UP_LINE; break;
        case VIM_MODE_DELI: CMD_MOVE_UP_LINE; break;
        case VIM_MODE_LINE: CMD_MOVE_UP_LINE; break;
        case VIM_MODE_PAGE: CMD_MOVE_LEFT_PAGE; break;
        case VIM_MODE_DOCU: CMD_MOVE_LEFT_DOCU; break;
        case VIM_MODE_APP: CMD_MOVE_LEFT_APP; break;
        case VIM_MODE_DESKTOP: CMD_MOVE_LEFT_DESKTOP; break;
        default:
        case VIM_MODE_CHAR: CMD_MOVE_UP_LINE; break;
    }
}

static void vim_move_right(void)
{
    switch (s_vim_mode)
    {
        case VIM_MODE_WORD: CMD_MOVE_RIGHT_WORD; break;
        case VIM_MODE_DELI: CMD_MOVE_RIGHT_DELI; break;
        case VIM_MODE_LINE: CMD_MOVE_RIGHT_LINE; break;
        case VIM_MODE_PAGE: CMD_MOVE_RIGHT_PAGE; break;
        case VIM_MODE_DOCU: CMD_MOVE_RIGHT_DOCU; break;
        case VIM_MODE_APP: CMD_MOVE_RIGHT_APP; break;
        case VIM_MODE_DESKTOP: CMD_MOVE_RIGHT_DESKTOP; break;
        default:
        case VIM_MODE_CHAR: CMD_MOVE_RIGHT_CHAR; break;
    }
}

static void vim_move_down(void)
{
    switch (s_vim_mode)
    {
        case VIM_MODE_WORD: CMD_MOVE_DOWN_LINE; break;
        case VIM_MODE_DELI: CMD_MOVE_DOWN_LINE; break;
        case VIM_MODE_LINE: CMD_MOVE_DOWN_LINE; break;
        case VIM_MODE_PAGE: CMD_MOVE_RIGHT_PAGE; break;
        case VIM_MODE_DOCU: CMD_MOVE_RIGHT_DOCU; break;
        case VIM_MODE_APP: CMD_MOVE_RIGHT_APP; break;
        case VIM_MODE_DESKTOP: CMD_MOVE_RIGHT_DESKTOP; break;
        default:
        case VIM_MODE_CHAR: CMD_MOVE_DOWN_LINE; break;
    }
}

void process_vim(uint8_t keycode, keyrecord_t* record)
{
    if (record->event.pressed)
    {
        switch (keycode)
        {
            case CC_VIM_VISUAL: register_code(KC_LEFT_SHIFT); break;
        }
    }

    switch (keycode)
    {
        case TC_0 ... TC_9:
            user_apply_keycode(keycode, record->event.pressed);
            return;
    }

    if (record->event.pressed)
    {
        switch (keycode)
        {
            case CC_VIM_CLEAR: vim_reset(); break;
            case CC_VIM_RAISE: user_layer_on(LAYER_VIM_RAISE); break;
            case CC_VIM_CHAR: s_vim_mode = VIM_MODE_CHAR; break;
            case CC_VIM_WORD: s_vim_mode = VIM_MODE_WORD; break;
            case CC_VIM_DELI: s_vim_mode = VIM_MODE_DELI; break;
            case CC_VIM_LINE: s_vim_mode = VIM_MODE_LINE; break;
            case CC_VIM_PAGE: s_vim_mode = VIM_MODE_PAGE; break;
            case CC_VIM_DOCU: s_vim_mode = VIM_MODE_DOCU; break;
            case CC_VIM_APP: s_vim_mode = VIM_MODE_APP; break;
            case CC_VIM_DESKTOP: s_vim_mode = VIM_MODE_DESKTOP; break;

            case CC_VIM_END: s_vim_select = VIM_SELECT_AFTER; break;
            case CC_VIM_BEGIN: s_vim_select = VIM_SELECT_BEFORE; break;
            case CC_VIM_INSIDE: s_vim_select = VIM_SELECT_OBJECT; break;

            case CC_VIM_GOTO: vim_goto(); break;
            case CC_VIM_INSERT: vim_insert(); break;
            case CC_VIM_SEARCH: vim_reset(); break;

            case CC_VIM_UNDO: tap_code16(G(KC_Z)); break;
            case CC_VIM_REDO: tap_code16(G(S(KC_Z))); break;

            case CC_VIM_INDENT: tap_code(KC_TAB); break;
            case CC_VIM_UNINDENT: tap_code16(S(KC_TAB)); break;

            case CC_VIM_LEFT: vim_move_left(); break;
            case CC_VIM_RIGHT: vim_move_right(); break;
            case CC_VIM_UP: vim_move_up(); break;
            case CC_VIM_DOWN: vim_move_down(); break;

            case CC_VIM_DELETE_LINE: CMD_DELETE_LINE; break;

            // Commands
            case CC_VIM_CHANGE: vim_change(); break;
            case CC_VIM_DELETE: vim_delete(); break;
            case CC_VIM_CUT:
                unregister_code(KC_LEFT_SHIFT);
                tap_code16(G(KC_X));
                break;
            case CC_VIM_YANK:
                unregister_code(KC_LEFT_SHIFT);
                tap_code16(G(KC_C));
                break;
            case CC_VIM_ENTER: register_code(KC_ENTER); break;
        }
    }
    else
    {
        switch (keycode)
        {
            case CC_VIM_RAISE: user_layer_on(LAYER_VIM); break;
            case CC_VIM_SEARCH: tap_code16(G(KC_F)); break;
            case CC_VIM_ENTER: unregister_code(KC_ENTER); break;
            case CC_VIM_DELETE: break;
        }

        switch (keycode)
        {
            case CC_VIM_SEARCH:
            case CC_VIM_CHANGE:
            case CC_VIM_INSERT:
            case CC_VIM_EXIT: vim_disable(); break;
        }
    }
}
