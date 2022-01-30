/*
These are just some thoughts about a simple VIM like mode that could emit key combinations inside vscode for example.
But knowing the key combinations they could be configured in many editors and even in the terminal.

- Extension for supporting certain commands:
  - Temporary vim motions
  - Meta.Go
  - 

- (i) put you in insert mode

- (c)hange (w)ord               *    => copy-word.cut                                        = will delete word and put you in insert mode
- (c)hange (i)nside             *    => metaGo select inside the surrounding pairs + delete  = will delete inside and put you in insert mode
- (c)hange (l)ine                    => HOME, SHIFT+END, BACKSPACE                           = will delete until end of line and put you in insert mode
- (c)hange (){}[]<>"'           *    => Quick-Select + BACKSPACE                             = will delete between typed delimiter and put you in insert mode

- (f)ind (u)ntil                *    => = move forwards to character     (metaGo.Smart)
- (f)ind (b)ack                 *    = move backwards to character

- (d)elete (w)ord               *    = will delete word
- (d)elete (l)ine               *    = will delete line
- (d)elete (i)nside             *    = will delete inside
- (d)elete (u)ntil (c)          *    = delete until character
- (d)elete (){}[]<>"'           *    = delete between typed delimiter

- (y)ank (i)nside               *    => metaGo select inside the surrounding pairs + copy  = copy inside
- (y)ank (u)ntil (c)haracter    *    = copy until character
- (y)ank (w)ord                 *    = copy word
- (y)ank (y)ank                 *    = copy line
- (y)ank (){}[]<>"'             *    = copy between typed delimiter

- (v)isual select (w)ord
- (v)isual select (l)ine
- (v)isual select (i)nside
- (v)isual select (x)pand
- (v)isual select (s)hrink
- (v)isual select (){}[]<>"'    *    = visual select between typed delimiter

- (w)ord                        *    => MetaWord          = move forwards by word (position at start of word)
- (b)ack                        *    => MetaWord          = move backwards by word
- (e)ord                        *    => MetaWord          = move forwards by word (position at end of word)

- (p)aste = paste
- (P)aste = paste before
- (o)pen = open new line
- (O)pen = open new line before

- h,j,k,l = movement keys

- (s)croll current line to (t)op
- (s)croll current line to (c)enter
- (s)croll current line to (b)ottom
- [s]croll current line (u)p  
- [s]croll current line (d)own

- (u)ndo = undo last action
- (r)edo = redo last action

- (n)avigate (d)own           = page down (PAGE_DOWN)
- (n)avigate (u)p             = page up (PAGE UP)
- (n)avigate (b)egin          = begin of line (HOME) 
- (n)avigate (e)nd            = end of line (END)
- (n)avigate (c)eiling        = top of document (CTRL + HOME)
- (n)avigate (h)alf      *    = middle of document 
- (n)avigate (f)loor          = bottom of document (CTRL + END)

- (:)w = write/save file
- (:)o = open file
- (:)q = close file

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_VIM] = LAYOUT(
    KC_TRANS, KC_Q, KC_W, KC_E,   KC_R,     KC_T,                                                 KC_Y,      KC_U,     KC_I,     KC_O,   KC_P,     KC_PASSWORD, 
    KC_TRANS, KC_A, KC_S, KC_D,   KC_F,     KC_G,                                                 KC_H,      KC_J,     KC_K,     KC_L,   KC_SCLN,  KC_TRANS, 
    KC_TRANS, KC_Z, KC_X, KC_C,   KC_V,     KC_B,   KC_TRANS,  KC_TRANS,   KC_TRANS,  KC_TRANS,   KC_N,      KC_M,     KC_COMMA, KC_DOT, KC_SLASH, KC_RSTHD, 
                          LT_MOS, KC_SNUM,  LA_NAV, KC_SPACE,  KC_OS_PDT,  KC_OS_NDT, KC_BSPACE,  LA_SYM,    KC_SCAPS, LT_MOS                                
  ),
}

*/