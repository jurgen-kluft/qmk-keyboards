/*
These are just some thoughts about a simple VIM like mode that could emit key combinations inside vscode for example.
But knowing the key combinations they could be configured in many editors and even in the terminal.

- Extension for supporting certain commands:
  - Temporary vim motions
  - Meta.Go
  - Copy-Word

- (i) put you in insert mode

- h,j,k,l = movement keys
- (w)ord                        *    => CTRL+Right-Arrow          = move forwards by word (position at start of word)
- (b)ack                        *    => CTRL+Left-Arrow           = move backwards by word (position at start of word)
- (W)ord                        *    => GUI+ALT+Right-Arrow       = move forwards by word (position at end of word)
- (B)ack                        *    => GUI+ALT+Left-Arrow        = move backwards by word (position at end of word)

- (c)hange (w)ord               *    => copy-word.cut                                        = will delete word and put you in insert mode
- (c)hange (i)nside             *    => metaGo select inside the surrounding pairs + delete  = will delete inside and put you in insert mode
- (c)hange (l)ine                    => HOME, SHIFT+END, BACKSPACE                           = will delete until end of line and put you in insert mode
- (c)hange (){}[]<>"'           *    => Quick-Select + BACKSPACE                             = will delete between typed delimiter and put you in insert mode

- (t)                           *    => = move forwards to character     (metaGo.Smart)

- (d)elete (w)ord               *    = will delete word
- (d)elete (b)egin              *    = will delete from cursor to begin of line
- (d)elete (e)nd                *    = will delete from cursor to end of line
- (d)elete (l)ine               *    => CTRL+SHIFT+L                                         = will delete line
- (d)elete (i)nside             *    => CTRL+ALT+i, DEL                                      = will delete inside
- (d)elete un(t)il              *    => SHIFT+ALT+, DEL                                      = delete until character
- (d)elete (){}[]<>"'           *    => CTRL+K+({[<"', DEL                                   = delete between typed delimiter

- (y)ank (i)nside               *    => metaGo select inside the surrounding pairs + COPY    = copy inside
- (y)ank un(t)il                *    => SHIFT+ALT+, + COPY                                   = copy until character
- (y)ank (w)ord                 *    = copy word
- (y)ank (y)ank                 *    => CTRL+INSERT                                          = copy line
- (y)ank (){}[]<>"'             *    => CTRL+K+({[<"' + COPY                                 = copy between typed delimiter

- (v)isual mode
  - motion (w)ord/(W)ord/(b)ack/(B)ack
  - motion hjkl
  - select (i)nside
  - select (x)pand
  - select (s)hrink
  - select (){}[]<>"'

- (p)aste = paste
- (P)aste = paste before
- (o)pen = open new line and put you in insert mode
- (O)pen = open new line before and put you in insert mode

- (a)lign current line to (t)op
- (a)lign current line to (c)enter
- (a)lign current line to (b)ottom
- [a]lign current line (u)p  
- [a]lign current line (d)own

- (u)ndo = undo last action
- (r)edo = redo last action

- (n)avigate (d)own           = page down (PAGE_DOWN)
- (n)avigate (u)p             = page up (PAGE UP)
- (n)avigate (b)egin          = begin of line (HOME) 
- (n)avigate (e)nd            = end of line (END)
- (n)avigate (c)eiling        = top of document (CTRL + HOME)
- (n)avigate (h)alf      *    = middle of document 
- (n)avigate (f)loor          = bottom of document (CTRL + END)




const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_VIM] = LAYOUT(
    KC_TRANS, KC_Q, KC_W, KC_E,   KC_R,     KC_T,                                                 KC_Y,      KC_U,     KC_I,     KC_O,   KC_P,     KC_PASSWORD, 
    KC_TRANS, KC_A, KC_S, KC_D,   KC_F,     KC_G,                                                 KC_H,      KC_J,     KC_K,     KC_L,   KC_SCLN,  KC_TRANS, 
    KC_TRANS, KC_Z, KC_X, KC_C,   KC_V,     KC_B,   KC_TRANS,  KC_TRANS,   KC_TRANS,  KC_TRANS,   KC_N,      KC_M,     KC_COMMA, KC_DOT, KC_SLASH, KC_RSTHD, 
                          LT_MOS, KC_SNUM,  LA_NAV, KC_SPACE,  KC_OS_PDT,  KC_OS_NDT, KC_BSPACE,  LA_SYM,    KC_SCAPS, LT_MOS                                
  ),
}

*/