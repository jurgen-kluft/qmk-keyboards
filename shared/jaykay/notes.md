# Notes

## Vim

These are just some thoughts about a simple VIM like mode that could emit key combinations inside vscode for example.
But knowing the key combinations they could be configured in many editors and even in the terminal.
- Extension for supporting certain commands:
  - Temporary vim motions
  - Meta.Go
  - Copy-Word
- (i) put you in insert mode
- h,j,k,l                       *    => LEFT/DOWN/UP/RIGHT ARROW  = movement keys
- (w)ord                        *    => CTRL+Right-Arrow          = move forwards by word (position at start of word)
- (b)ack                        *    => CTRL+Left-Arrow           = move backwards by word (position at start of word)
- (W)ord                        *    => GUI+ALT+Right-Arrow       = move forwards by word (position at end of word)
- (B)ack                        *    => GUI+ALT+Left-Arrow        = move backwards by word (position at end of word)
- (c)hange (w)ord               *    => copy-word.cut                                        = will delete word and put you in insert mode
- (c)hange (i)nside             *    => metaGo select inside the surrounding pairs + delete  = will delete inside and put you in insert mode
- (c)hange (l)ine                    => HOME, SHIFT+END, BACKSPACE                           = will delete until end of line and put you in insert mode
- (c)hange (){}[]<>"'           *    => Quick-Select + BACKSPACE                             = will delete between typed delimiter and put you in insert mode
- (t)                           *    => ALT+S, 'character'                                   = move forwards to character     (metaGo.Smart)
- (d)elete (w)ord               *    = will delete word
- (d)elete (b)egin              *    => SHIFT+HOME, DEL                                      = will delete from cursor to begin of line
- (d)elete (e)nd                *    => SHIFT+END, DEL                                       = will delete from cursor to end of line
- (d)elete (l)ine               *    => CTRL+SHIFT+L                                         = will delete line
- (d)elete (i)nside             *    => CTRL+ALT+i, DEL                                      = will delete inside
- (d)elete un(t)il              *    => SHIFT+ALT+, DEL                                      = delete until character
- (d)elete (){}[]<>"'           *    => CTRL+K+({[<"', DEL                                   = delete between typed delimiter
- (y)ank (i)nside               *    => metaGo select inside the surrounding pairs + COPY    = copy inside
- (y)ank un(t)il                *    => SHIFT+ALT+, + COPY                                   = copy until character
- (y)ank (w)ord                 *    => copy-word.copy                                       = copy word
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
- (o)pen                         *    => GUI+ENTER                                            = open new line and put you in insert mode
- (O)pen                         *    => GUI+SHIFT+ENTER                                      = open new line before and put you in insert mode
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
