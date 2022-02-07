#include QMK_KEYBOARD_H
#include "oled.h"
#include "layers.h"
#include "smart.h"
#include "oneshot.h"
#include "cushi.h"
#include "cukey.h"
#include "secrets.x"

#define KC_VBAR LSFT(KC_BSLASH)

#define KC_TRANS KC_TRANSPARENT
#define xxxx     KC_TRANSPARENT

#define KC_DQUOTE  LSFT(KC_QUOTE)
#define KC_LBRACE  LSFT(KC_9)
#define KC_RBRACE  LSFT(KC_0)
#define KC_LCBRACE LSFT(KC_LBRACKET)
#define KC_RCBRACE LSFT(KC_RBRACKET)

#define LA_SYM   MO(_SYM)
#define LA_NAV   MO(_NAV)
#define LA_NUM   MO(_NUM)
#define LA_QCAPS MO(_QWERTY_CAPS)
#define LA_RCAPS MO(_RSTHD_CAPS)
#define LT_MOS   TG(_MOUS)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    //#                         ╭───────╮                                                                        ╭───────╮                          
    //#                 ╭───────╯   e   ╰───────╮                                                        ╭───────╯   i   ╰───────╮                  
    //#                 │   w   │       │   r   ╭───────╮                                        ╭───────╮   u   │       │   o   │                  
    //# ╭───────╮───────╯       ╰───────╯       │   t   │                                        │   y   │       ╰───────╯       ╰───────╭───────╮  
    //# │       │   q   ╰───────╯   d   ╰───────╯       │                                        │       ╰───────╯   k   ╰───────╯   p   │       │  
    //# │       │       │   s   │       │   f   ╰───────╯                                        ╰───────╯   j   │       │   l   │       │       │  
    //# ╰───────╯───────╯       ╰───────╯       │   g   │                                        │   h   │       ╰───────╯       ╰───────╰───────╯  
    //# │       │   a   ╰───────╯   c   ╰───────╯       │                                        │       ╰───────╯  SYM  ╰───────╯   ;   │       │  
    //# │       │       │   x   │       │   v   ╰───────╯                                        ╰───────╯   m   │       │   .   │       │       │  
    //# ╰───────╯───────╯       ╰───────╯       │   b   │ ╭───────╮                    ╭───────╮ │   n   │       ╰───────╯       ╰───────╰───────╯  
    //# │       │   z   ╰───────╯       ╰───────╯       │ │  PDT  ╰───────╮    ╭───────╯  NDT  │ │       ╰───────╯       ╰───────╯   ,   │       │  
    //# │       │       │              ╭───────╮╰───────╯ │       │       │    │       │       │ ╰───────╯╭───────╮              │       │       │  
    //# ╰───────╯───────╯     ╭───────╮│ SMNUM ╰───────╮  ╰───────╯       │    │       ╰───────╯  ╭───────╯ SCAPS │╭───────╮     ╰───────╰───────╯  
    //#                       │ T_MOS ││       │ A_NAV ╰───────╮  ╰───────╯    ╰───────╯  ╭───────╯ A_SYM │       ││ T_MOS │                        
    //#                       │       │╰───────╯       │ SPACE ╰───────╮          ╭───────╯   ⌫   │       ╰───────╯│       │                        
    //#                       ╰encodr─╯        ╰───────╯       │       │          │       │       ╰───────╯        ╰encodr─╯                        
    //#                                                ╰───────╯       │          │       ╰───────╯                                                 
    //#                                                        ╰───────╯          ╰───────╯                                                         
  [_QWERTY] = LAYOUT(
    xxxx, KC_Q, KC_W, KC_E,   KC_R,    KC_T,                                       KC_Y,   KC_U,     KC_I,       KC_O,   KC_P,     xxxx, 
    xxxx, KC_A, KC_S, KC_D,   KC_F,    KC_G,                                       KC_H,   KC_J,     KC_K,       KC_L,   KC_SCLN,  xxxx, 
    xxxx, KC_Z, KC_X, KC_C,   KC_V,    KC_B,   KC_OS_PDT, xxxx,   xxxx, KC_OS_NDT, KC_N,   KC_M,     OSL(_SSYM), KC_DOT, KC_COMMA, xxxx, 
                      LT_MOS, KC_SNUM, LA_NAV, KC_SPACE,  xxxx,   xxxx, KC_BSPACE, LA_SYM, KC_SCAPS, LT_MOS                              
  ),
  [_RSTHD] = LAYOUT(
    xxxx, KC_J,    KC_C, KC_Y,   KC_F,    KC_K,                                 KC_Z,   KC_L,     KC_BSPACE,  KC_U,   KC_Q,     xxxx, 
    xxxx, KC_R,    KC_S, KC_T,   KC_H,    KC_D,                                 KC_M,   KC_N,     KC_A,       KC_I,   KC_O,     xxxx, 
    xxxx, KC_UNDS, KC_V, KC_G,   KC_P,    KC_B,   xxxx,     xxxx,   xxxx, xxxx, KC_X,   KC_W,     OSL(_SSYM), KC_DOT, KC_COMMA, xxxx, 
                         LT_MOS, KC_SNUM, LA_NAV, KC_SPACE, xxxx,   xxxx, KC_E, LA_SYM, KC_SCAPS, LT_MOS                              
  ),
    //#                         ╭───────╮                                                                        ╭───────╮                          
    //#                 ╭───────╯   E   ╰───────╮                                                        ╭───────╯   I   ╰───────╮                  
    //#                 │   W   │       │   R   ╭───────╮                                        ╭───────╮   U   │       │   O   │                  
    //# ╭───────╮───────╯       ╰───────╯       │   T   │                                        │   Y   │       ╰───────╯       ╰───────╭───────╮  
    //# │       │   Q   ╰───────╯   D   ╰───────╯       │                                        │       ╰───────╯   K   ╰───────╯   P   │       │  
    //# │       │       │   S   │       │   F   ╰───────╯                                        ╰───────╯   J   │       │   L   │       │       │  
    //# ╰───────╯───────╯       ╰───────╯       │   G   │                                        │   H   │       ╰───────╯       ╰───────╰───────╯  
    //# │       │   A   ╰───────╯   C   ╰───────╯       │                                        │       ╰───────╯  SYM  ╰───────╯   _   │       │  
    //# │       │       │   X   │       │   V   ╰───────╯                                        ╰───────╯   M   │       │   .   │       │       │  
    //# ╰───────╯───────╯       ╰───────╯       │   B   │ ╭───────╮                    ╭───────╮ │   N   │       ╰───────╯       ╰───────╰───────╯  
    //# │       │   Z   ╰───────╯       ╰───────╯       │ │       ╰───────╮    ╭───────╯       │ │       ╰───────╯       ╰───────╯   ,   │       │  
    //# │       │       │              ╭───────╮╰───────╯ │       │       │    │       │       │ ╰───────╯╭───────╮              │       │       │  
    //# ╰───────╯───────╯     ╭───────╮│       ╰───────╮  ╰───────╯       │    │       ╰───────╯  ╭───────╯       │╭───────╮     ╰───────╰───────╯  
    //#                       │       ││       │       ╰───────╮  ╰───────╯    ╰───────╯  ╭───────╯       │       ││       │                        
    //#                       │       │╰───────╯       │       ╰───────╮          ╭───────╯       │       ╰───────╯│       │                        
    //#                       ╰encodr─╯        ╰───────╯       │       │          │       │       ╰───────╯        ╰encodr─╯                        
    //#                                                ╰───────╯       │          │       ╰───────╯                                                 
    //#                                                        ╰───────╯          ╰───────╯                                                         
  [_QWERTY_CAPS] = LAYOUT(
    xxxx, LSFT(KC_Q), LSFT(KC_W), LSFT(KC_E), LSFT(KC_R), LSFT(KC_T),                                           LSFT(KC_Y), LSFT(KC_U), LSFT(KC_I), LSFT(KC_O), LSFT(KC_P), xxxx, 
    xxxx, LSFT(KC_A), LSFT(KC_S), LSFT(KC_D), LSFT(KC_F), LSFT(KC_G),                                           LSFT(KC_H), LSFT(KC_J), LSFT(KC_K), LSFT(KC_L), KC_UNDS,    xxxx, 
    xxxx, LSFT(KC_Z), LSFT(KC_X), LSFT(KC_C), LSFT(KC_V), LSFT(KC_B), xxxx,     xxxx,       xxxx,     xxxx,     LSFT(KC_N), LSFT(KC_M), OSL(_SSYM), KC_DOT,     KC_COMMA,   xxxx, 
                                  KC_TRANS,   xxxx,       KC_TRANS,   KC_TRANS, KC_TRANS,   KC_TRANS, KC_TRANS, KC_TRANS,   KC_TRANS,   KC_TRANS                                  
  ),
  [_RSTHD_CAPS] = LAYOUT(
    xxxx, LSFT(KC_J), LSFT(KC_C), LSFT(KC_Y), LSFT(KC_F), LSFT(KC_K),                                             LSFT(KC_Z), LSFT(KC_L), KC_BSPACE,  LSFT(KC_U), LSFT(KC_Q), xxxx, 
    xxxx, LSFT(KC_R), LSFT(KC_S), LSFT(KC_T), LSFT(KC_H), LSFT(KC_D),                                             LSFT(KC_M), LSFT(KC_N), LSFT(KC_A), LSFT(KC_I), LSFT(KC_O), xxxx, 
    xxxx, KC_UNDS,    LSFT(KC_V), LSFT(KC_G), LSFT(KC_P), LSFT(KC_B), xxxx,     xxxx,       xxxx,     xxxx,       LSFT(KC_X), LSFT(KC_W), OSL(_SSYM), KC_DOT,     KC_COMMA,   xxxx, 
                                  KC_TRANS,   xxxx,       KC_TRANS,   KC_TRANS, KC_TRANS,   KC_TRANS, LSFT(KC_E), KC_TRANS,   KC_TRANS,   KC_TRANS                                  
  ),
  /* 
     Symbols (C++) in order of frequency space _ * , . ) ( ; - = / > " { & } : + # ` ] [ < % ! ' | ? @ $ ^ ~ \ 

      <   >   {   }    %                              ^   -   +   /   $
      :   =   _   *    !                              `   (   )   |   ;
      ~   ?       '    [  xx   xx           xx   xx   ]   &   ,   \   @
              xx  xx   #  xx   xx           xx   xx   "   xx  xx 
  */
    //#                         ╭───────╮                                                                        ╭───────╮                          
    //#                 ╭───────╯   {   ╰───────╮                                                        ╭───────╯   +   ╰───────╮                  
    //#                 │   >   │       │   }   ╭───────╮                                        ╭───────╮   -   │       │   /   │                  
    //# ╭───────╮───────╯       ╰───────╯       │   %   │                                        │   ^   │       ╰───────╯       ╰───────╭───────╮  
    //# │       │   <   ╰───────╯   *   ╰───────╯       │                                        │       ╰───────╯   )   ╰───────╯   $   │       │  
    //# │       │       │   =   │       │   _   ╰───────╯                                        ╰───────╯   (   │       │   |   │       │       │  
    //# ╰───────╯───────╯       ╰───────╯       │   !   │                                        │   `   │       ╰───────╯       ╰───────╰───────╯  
    //# │       │   :   ╰───────╯   .   ╰───────╯       │                                        │       ╰───────╯   ,   ╰───────╯   ;   │       │  
    //# │       │       │   ?   │       │   '   ╰───────╯                                        ╰───────╯   &   │       │   \   │       │       │  
    //# ╰───────╯───────╯       ╰───────╯       │   [   │ ╭───────╮                    ╭───────╮ │   ]   │       ╰───────╯       ╰───────╰───────╯  
    //# │       │   ~   ╰───────╯       ╰───────╯       │ │       ╰───────╮    ╭───────╯       │ │       ╰───────╯       ╰───────╯   @   │       │  
    //# │       │       │              ╭───────╮╰───────╯ │       │       │    │       │       │ ╰───────╯╭───────╮              │       │       │  
    //# ╰───────╯───────╯     ╭───────╮│ SPACE ╰───────╮  ╰───────╯       │    │       ╰───────╯  ╭───────╯ SPACE │╭───────╮     ╰───────╰───────╯  
    //#                       │ SPACE ││       │   #   ╰───────╮  ╰───────╯    ╰───────╯  ╭───────╯   "   │       ││ SPACE │                        
    //#                       │       │╰───────╯       │ SPACE ╰───────╮          ╭───────╯ SPACE │       ╰───────╯│       │                        
    //#                       ╰encodr─╯        ╰───────╯       │ SPACE │          │ SPACE │       ╰───────╯        ╰encodr─╯                        
    //#                                                ╰───────╯       │          │       ╰───────╯                                                 
    //#                                                        ╰───────╯          ╰───────╯                                                         
    [_SSYM] = LAYOUT( 
    xxxx, KC_LABK,  KC_RABK,  KC_LCBR,  KC_RCBR,  KC_PERC,                                           KC_CIRC, KC_MINUS, KC_PLUS,  KC_SLASH,  KC_DLR,  xxxx, 
    xxxx, KC_COLN,  KC_EQUAL, KC_ASTR,  KC_UNDS,  KC_EXLM,                                           KC_GRV,  KC_LPRN,  KC_RPRN,  KC_PIPE,   KC_SCLN, xxxx, 
    xxxx, KC_TILDE, KC_QUES,  KC_DOT,   KC_QUOT,  KC_LBRC, xxxx,     xxxx,       xxxx,     xxxx,     KC_RBRC, KC_AMPR,  KC_COMMA, KC_BSLASH, KC_AT,   xxxx, 
                              KC_SPACE, KC_SPACE, KC_HASH, KC_SPACE, KC_SPACE,   KC_SPACE, KC_SPACE, KC_DQUO, KC_SPACE, KC_SPACE                            
  ),
  /*
      <   /   (   )    {                              }   7   8   9   $
      :   =   _   *    +                              -   1   2   3   ;
      >   \   .    ,   [  xx   xx           xx   xx   ]   4   5   6   @
              xx  xx  xx  xx   xx           xx   xx   0   xx  xx 
  */
    //#                         ╭───────╮                                                                        ╭───────╮                          
    //#                 ╭───────╯   (   ╰───────╮                                                        ╭───────╯   8   ╰───────╮                  
    //#                 │   /   │       │   )   ╭───────╮                                        ╭───────╮   7   │       │   9   │                  
    //# ╭───────╮───────╯       ╰───────╯       │   {   │                                        │   }   │       ╰───────╯       ╰───────╭───────╮  
    //# │       │   <   ╰───────╯   _   ╰───────╯       │                                        │       ╰───────╯   2   ╰───────╯   $   │       │  
    //# │       │       │   =   │       │   *   ╰───────╯                                        ╰───────╯   1   │       │   3   │       │       │  
    //# ╰───────╯───────╯       ╰───────╯       │   +   │                                        │   -   │       ╰───────╯       ╰───────╰───────╯  
    //# │       │   :   ╰───────╯   ,   ╰───────╯       │                                        │       ╰───────╯   5   ╰───────╯   ;   │       │  
    //# │       │       │   \   │       │   .   ╰───────╯                                        ╰───────╯   4   │       │   6   │       │       │  
    //# ╰───────╯───────╯       ╰───────╯       │   [   │ ╭───────╮                    ╭───────╮ │   ]   │       ╰───────╯       ╰───────╰───────╯  
    //# │       │   >   ╰───────╯       ╰───────╯       │ │       ╰───────╮    ╭───────╯       │ │       ╰───────╯       ╰───────╯   @   │       │  
    //# │       │       │              ╭───────╮╰───────╯ │       │       │    │       │       │ ╰───────╯╭───────╮              │       │       │  
    //# ╰───────╯───────╯     ╭───────╮│       ╰───────╮  ╰───────╯       │    │       ╰───────╯  ╭───────╯       │╭───────╮     ╰───────╰───────╯  
    //#                       │ SPACE ││       │       ╰───────╮  ╰───────╯    ╰───────╯  ╭───────╯   0   │       ││ SPACE │                        
    //#                       │       │╰───────╯       │ SPACE ╰───────╮          ╭───────╯   ⌫   │       ╰───────╯│       │                        
    //#                       ╰encodr─╯        ╰───────╯       │ SPACE │          │ SPACE │       ╰───────╯        ╰encodr─╯                        
    //#                                                ╰───────╯       │          │       ╰───────╯                                                 
    //#                                                        ╰───────╯          ╰───────╯                                                         
  [_NUM] = LAYOUT(
    xxxx, KC_LABK, KC_SLASH,  KC_LPRN,  KC_RPRN,  KC_LCBR,                                             KC_RCBR,  KC_7,     KC_8,     KC_9, KC_DLR,  xxxx, 
    xxxx, KC_COLN, KC_EQUAL,  KC_UNDS,  KC_ASTR,  KC_PLUS,                                             KC_MINUS, KC_1,     KC_2,     KC_3, KC_SCLN, xxxx, 
    xxxx, KC_RABK, KC_BSLASH, KC_COMMA, KC_DOT,   KC_LBRC,  xxxx,     xxxx,       xxxx,     xxxx,      KC_RBRC,  KC_4,     KC_5,     KC_6, KC_AT,   xxxx, 
                              KC_SPACE, KC_TRANS, KC_TRANS, KC_SPACE, KC_SPACE,   KC_SPACE, KC_BSPACE, KC_0,     KC_TRANS, KC_SPACE                       
  ),
  [_MOUS] = LAYOUT(
    xxxx, KC_MPLY,    MU_TOG,      MU_MOD,      KC_OLED,  RGB_SAD,                                             KC_MS_WH_UP,   KC_MS_BTN1,    KC_MS_UP,   KC_MS_BTN2,     RGB_SAI, xxxx, 
    xxxx, OS_CMD,     OS_ALT,      OS_CTRL,     OS_SHFT,  RGB_HUD,                                             KC_MS_WH_DOWN, KC_MS_LEFT,    KC_MS_DOWN, KC_MS_RIGHT,    RGB_HUI, xxxx, 
    xxxx, KC_OS_MODE, KC_OS_PMODE, KC_PASSWORD, KC_TRANS, RGB_VAD,  xxxx,     xxxx,       xxxx,     xxxx,      KC_TRANS,      KC_MS_WH_LEFT, KC_MS_BTN3, KC_MS_WH_RIGHT, RGB_VAI, xxxx, 
                                   KC_TRANS,    KC_TRANS, KC_TRANS, KC_RSTHD, KC_TRANS,   KC_TRANS, KC_QWERTY, KC_TRANS,      KC_TRANS,      KC_TRANS                                   
  ),
  /*
     Symbols in order of frequency                 # | & { } , ? [ ] _ < > $ % ` ' / - : \ ( ) = ^ ~ " ! . + @ *  
     Symbols (C++) in order of frequency     space _ * , . ) ( ; - = / > " { & } : + # ` ] [ < % ! ' | ? @ $ ^ ~ 

       <    >   ({   )}   %^                               '     -    +    /    $
      ;:   "!   _~    *   =|                               `    SFT  CTL  ALT  CMD    
       ~    ?    [    ]   EE   xx   xx           xx   xx   EE    &    #    \    @
                xx   xx   xx   xx   xx           xx   xx   SYM   xx   xx 
  */
    //#                         ╭───────╮                                                                        ╭───────╮                          
    //#                 ╭───────╯   ({  ╰───────╮                                                        ╭───────╯   +   ╰───────╮                  
    //#                 │   >   │       │   )}  ╭───────╮                                        ╭───────╮   -   │       │   /   │                  
    //# ╭───────╮───────╯       ╰───────╯       │   %^  │                                        │   '   │       ╰───────╯       ╰───────╭───────╮  
    //# │       │   <   ╰───────╯   _~  ╰───────╯       │                                        │       ╰───────╯   ^   ╰───────╯   $   │       │  
    //# │       │       │   "!  │       │   *   ╰───────╯                                        ╰───────╯   ⇧   │       │   ⎇   │       │       │  
    //# ╰───────╯───────╯       ╰───────╯       │   =|  │                                        │   `   │       ╰───────╯       ╰───────╰───────╯  
    //# │       │   ;:  ╰───────╯   [   ╰───────╯       │                                        │       ╰───────╯   #   ╰───────╯   ⌘   │       │  
    //# │       │       │   ?   │       │   ]   ╰───────╯                                        ╰───────╯   &   │       │   \   │       │       │  
    //# ╰───────╯───────╯       ╰───────╯       │   EE  │ ╭───────╮                    ╭───────╮ │   EE  │       ╰───────╯       ╰───────╰───────╯  
    //# │       │   ~   ╰───────╯       ╰───────╯       │ │       ╰───────╮    ╭───────╯       │ │       ╰───────╯       ╰───────╯   @   │       │  
    //# │       │       │              ╭───────╮╰───────╯ │       │       │    │       │       │ ╰───────╯╭───────╮              │       │       │  
    //# ╰───────╯───────╯     ╭───────╮│       ╰───────╮  ╰───────╯       │    │       ╰───────╯  ╭───────╯       │╭───────╮     ╰───────╰───────╯  
    //#                       │       ││       │       ╰───────╮  ╰───────╯    ╰───────╯  ╭───────╯       │       ││       │                        
    //#                       │       │╰───────╯       │       ╰───────╮          ╭───────╯       │       ╰───────╯│       │                        
    //#                       ╰encodr─╯        ╰───────╯       │       │          │       │       ╰───────╯        ╰encodr─╯                        
    //#                                                ╰───────╯       │          │       ╰───────╯                                                 
    //#                                                        ╰───────╯          ╰───────╯                                                         
  [_SYM] = LAYOUT(
    xxxx, KC_LABK,      KC_RABK,      KC_LPRN_LCBR, KC_RPRN_RCBR, KC_PERC_CIRC,                                           KC_QUOT,  KC_MINUS, KC_PLUS,  KC_SLASH,  KC_DLR, xxxx, 
    xxxx, KC_SCLN_COLN, KC_DQUO_EXCL, KC_UNDS_TLD,  KC_ASTR,      KC_EQUL_PIPE,                                           KC_GRV,   OS_SHFT,  OS_CTRL,  OS_ALT,    OS_CMD, xxxx, 
    xxxx, KC_TILDE,     KC_QUES,      KC_LBRC,      KC_RBRC,      SH_TG,        xxxx,     xxxx,       xxxx,     xxxx,     SH_TG,    KC_AMPR,  KC_HASH,  KC_BSLASH, KC_AT,  xxxx, 
                                      KC_TRANS,     KC_TRANS,     KC_TRANS,     KC_TRANS, KC_TRANS,   KC_TRANS, KC_TRANS, KC_TRANS, KC_TRANS, KC_TRANS                           
  ),
    //#                         ╭───────╮                                                                        ╭───────╮                          
    //#                 ╭───────╯  ESC  ╰───────╮                                                        ╭───────╯   ⇤   ╰───────╮                  
    //#                 │ CLOSE │       │   ⏎   ╭───────╮                                        ╭───────╮   ⇞   │       │ Insrt │                  
    //# ╭───────╮───────╯       ╰───────╯       │  TAB  │                                        │ Insrt │       ╰───────╯       ╰───────╭───────╮  
    //# │       │ _REDO ╰───────╯   ^   ╰───────╯       │                                        │       ╰───────╯   U   ╰───────╯  NDT  │       │  
    //# │       │       │   ⎇   │       │   ⇧   ╰───────╯                                        ╰───────╯   D   │       │   R   │       │       │  
    //# ╰───────╯───────╯       ╰───────╯       │   ⌦   │                                        │   L   │       ╰───────╯       ╰───────╰───────╯  
    //# │       │   ⌘   ╰───────╯  Copy ╰───────╯       │                                        │       ╰───────╯   ⇥   ╰───────╯  PDT  │       │  
    //# │       │       │  Cut  │       │ Paste ╰───────╯                                        ╰───────╯   ⇟   │       │       │       │       │  
    //# ╰───────╯───────╯       ╰───────╯       │   EE  │ ╭───────╮                    ╭───────╮ │   EE  │       ╰───────╯       ╰───────╰───────╯  
    //# │       │  Undo ╰───────╯       ╰───────╯       │ │       ╰───────╮    ╭───────╯       │ │       ╰───────╯       ╰───────╯       │       │  
    //# │       │       │              ╭───────╮╰───────╯ │       │       │    │       │       │ ╰───────╯╭───────╮              │       │       │  
    //# ╰───────╯───────╯     ╭───────╮│       ╰───────╮  ╰───────╯       │    │       ╰───────╯  ╭───────╯       │╭───────╮     ╰───────╰───────╯  
    //#                       │       ││       │       ╰───────╮  ╰───────╯    ╰───────╯  ╭───────╯       │       ││       │                        
    //#                       │       │╰───────╯       │   ⌫   ╰───────╮          ╭───────╯   ⌦   │       ╰───────╯│       │                        
    //#                       ╰encodr─╯        ╰───────╯       │       │          │       │       ╰───────╯        ╰encodr─╯                        
    //#                                                ╰───────╯       │          │       ╰───────╯                                                 
    //#                                                        ╰───────╯          ╰───────╯                                                         
  [_NAV] = LAYOUT(
    xxxx, KC_OS_REDO, KC_OS_CLOSE, KC_ESCAPE,  KC_ENTER,    KC_TAB,                                                KC_INSERT, KC_PGUP,   KC_HOME,  KC_INSERT, KC_OS_NDT, xxxx, 
    xxxx, OS_CMD,     OS_ALT,      OS_CTRL,    OS_SHFT,     KC_DELETE,                                             KC_LEFT,   KC_DOWN,   KC_UP,    KC_RIGHT,  KC_OS_PDT, xxxx, 
    xxxx, KC_OS_UNDO, KC_OS_CUT,   KC_OS_COPY, KC_OS_PASTE, SH_TG,     xxxx,      xxxx,       xxxx,     xxxx,      SH_TG,     KC_PGDOWN, KC_END,   KC_TRANS,  KC_TRANS,  xxxx, 
                                   KC_TRANS,   KC_TRANS,    KC_TRANS,  KC_BSPACE, KC_TRANS,   KC_TRANS, KC_DELETE, KC_TRANS,  KC_TRANS,  KC_TRANS                              
  ),
  //   F8   F9   F10  F11                 F1   F2   F3   F4   
  //   CMD  ALT  CTRL SHFT  F12           F12  F5   F6   F7   F8
  //    
    //#                         ╭───────╮                                                                        ╭───────╮                          
    //#                 ╭───────╯ KC_F7 ╰───────╮                                                        ╭───────╯ KC_F3 ╰───────╮                  
    //#                 │ KC_F6 │       │ KC_F8 ╭───────╮                                        ╭───────╮ KC_F2 │       │ KC_F4 │                  
    //# ╭───────╮───────╯       ╰───────╯       │       │                                        │ KC_F1 │       ╰───────╯       ╰───────╭───────╮  
    //# │       │       ╰───────╯   ^   ╰───────╯       │                                        │       ╰───────╯ C_F10 ╰───────╯       │       │  
    //# │       │       │   ⎇   │       │   ⇧   ╰───────╯                                        ╰───────╯ C_F11 │       │ KC_F9 │       │       │  
    //# ╰───────╯───────╯       ╰───────╯       │ C_F12 │                                        │ KC_F5 │       ╰───────╯       ╰───────╰───────╯  
    //# │       │   ⌘   ╰───────╯       ╰───────╯       │                                        │       ╰───────╯       ╰───────╯       │       │  
    //# │       │       │       │       │       ╰───────╯                                        ╰───────╯       │       │       │       │       │  
    //# ╰───────╯───────╯       ╰───────╯       │       │ ╭───────╮                    ╭───────╮ │       │       ╰───────╯       ╰───────╰───────╯  
    //# │       │       ╰───────╯       ╰───────╯       │ │       ╰───────╮    ╭───────╯       │ │       ╰───────╯       ╰───────╯       │       │  
    //# │       │       │              ╭───────╮╰───────╯ │       │       │    │       │       │ ╰───────╯╭───────╮              │       │       │  
    //# ╰───────╯───────╯     ╭───────╮│       ╰───────╮  ╰───────╯       │    │       ╰───────╯  ╭───────╯       │╭───────╮     ╰───────╰───────╯  
    //#                       │       ││       │       ╰───────╮  ╰───────╯    ╰───────╯  ╭───────╯       │       ││       │                        
    //#                       │       │╰───────╯       │       ╰───────╮          ╭───────╯       │       ╰───────╯│       │                        
    //#                       ╰encodr─╯        ╰───────╯       │       │          │       │       ╰───────╯        ╰encodr─╯                        
    //#                                                ╰───────╯       │          │       ╰───────╯                                                 
    //#                                                        ╰───────╯          ╰───────╯                                                         
  [_RAISE] = LAYOUT(
    xxxx, KC_TRANS, KC_F6,    KC_F7,    KC_F8,    KC_TRANS,                                           KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_TRANS, xxxx, 
    xxxx, OS_CMD,   OS_ALT,   OS_CTRL,  OS_SHFT,  KC_F12,                                             KC_F5,    KC_F11,   KC_F10,   KC_F9,    KC_TRANS, xxxx, 
    xxxx, KC_TRANS, KC_TRANS, KC_TRANS, KC_TRANS, KC_TRANS, xxxx,     xxxx,       xxxx,     xxxx,     KC_TRANS, KC_TRANS, KC_TRANS, KC_TRANS, KC_TRANS, xxxx, 
                              KC_TRANS, KC_TRANS, KC_TRANS, KC_TRANS, KC_TRANS,   KC_TRANS, KC_TRANS, KC_TRANS, KC_TRANS, KC_TRANS                            
  )
};
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) { return update_tri_layer_state(state, _NAV, _SYM, _RAISE); }

#ifdef ENABLE_ONESHOT

bool is_oneshot_modifier_cancel_key(uint16_t keycode)
{
    switch (keycode)
    {
        case LA_NAV:
        case LA_NUM:
        case LA_QCAPS:
        case KC_SNUM:
        case KC_SCAPS: return true;
        default: return false;
    }
}

bool is_oneshot_modifier_ignored_key(uint16_t keycode)
{
    switch (keycode)
    {
        case LA_SYM:
        case LA_NAV: return true;
    }
    return false;
}

oneshot_mod get_modifier_for_trigger_key(uint16_t keycode)
{
    switch (keycode)
    {
        case OS_SHFT: return ONESHOT_LSFT;
        case OS_CTRL: return ONESHOT_LCTL;
        case OS_ALT: return ONESHOT_LALT;
        case OS_CMD: return ONESHOT_LGUI;
    }
    return ONESHOT_NONE;
}

#endif

bool smart_feature_cancel_key(uint16_t keycode, keyrecord_t* recor)
{
    switch (keycode)
    {
        case LA_SYM:
        case LA_NAV:
        case LA_NUM:
        case LA_QCAPS: return true;
    }
    return false;
}

static uint8_t s_smart_state  = 0;

bool process_record_user(uint16_t keycode, keyrecord_t* record)
{
    process_record_oled(keycode, record);

    switch (keycode)
    {
        case KC_SNUM:
        case KC_SCAPS:
        case LA_NAV:
        case LA_SYM: break;
        default:
            s_smart_state |= (s_smart_state&1) << 1;
            break;
    }

    switch (keycode)
    {
        case KC_OS_MODE ... KC_OS_CLOSE:
        {
            if (!process_cushi_keys(keycode, record))
                return false;

            if (record->event.pressed)
            {
                keycode = process_cukey(keycode);
                if (keycode != KC_NO)
                    tap_code16(keycode);
            }

            return false;
        }
        case KC_PASSWORD:
            if (record->event.pressed)
            {
                SEND_STRING(SECRET_PASSWORD);
            }
            return true;
        case KC_SNUM:
            if (record->event.pressed)
            {
                smart_feature_enable(SMART_NUMBERS, _NUM);
                s_smart_state = 1;
            }
            else
            {
                if (s_smart_state == 3)
                {
                    if (smart_feature_state(SMART_NUMBERS))
                    {
                        smart_feature_disable(SMART_NUMBERS);
                    }
                }
                s_smart_state = 0;
            }
            return true;
        case KC_SCAPS:
            if (record->event.pressed)
            {
                // Layer Bit -> Layer Number
                // _QWERTY   ->  _QWERTY_CAPS
                //     0     ->      2
                // _RSTHD    ->  _RSTHD_CAPS
                //     1     ->      3
                if (default_layer_state == (1 << _QWERTY))
                {
                    smart_feature_enable(SMART_CAPSLOCK, _QWERTY_CAPS);
                    s_smart_state = 1;
                }
                else if (default_layer_state == (1 << _RSTHD))
                {
                    smart_feature_enable(SMART_CAPSLOCK, _RSTHD_CAPS);
                    s_smart_state = 1;
                }
            }
            else
            {
                if (s_smart_state == 3)
                {
                    if (smart_feature_state(SMART_CAPSLOCK))
                    {
                        smart_feature_disable(SMART_CAPSLOCK);
                    }
                }
                s_smart_state = 0;
            }
            return true;
        case KC_OLED:
            if (record->event.pressed)
            {
                toggle_display_oled();
#ifdef RGBLIGHT_ENABLE
                rgblight_enable();
#endif
            }
            return true;
    }

    int8_t keycode_consumed = 0;

    if ((smart_feature_cancel_key(keycode, record)) || ((keycode < QK_MODS_MAX) && (!IS_MOD(keycode))))
    {
        if (s_smart_state == 0)
        {
            if (smart_feature_state(SMART_CAPSLOCK))
            {
                keycode_consumed = 1;
                smart_capslock_process(keycode, record);
            }
            else if (smart_feature_state(SMART_NUMBERS))
            {
                keycode_consumed = 1;
                smart_numbers_process(keycode, record);
            }
        }
    }

#ifdef ENABLE_ONESHOT
    keycode_consumed += update_oneshot_modifiers(keycode, record, keycode_consumed);
#endif

    if (!process_cushi_keys(keycode, record))
    {
        return false;
    }

    switch (keycode)
    {
        case KC_QWERTY:
            if (record->event.pressed)
            {
                set_single_persistent_default_layer(_QWERTY);
            }
            break;
        case KC_RSTHD:
            if (record->event.pressed)
            {
                set_single_persistent_default_layer(_RSTHD);
            }
            break;
    }

    return true;
};

// Layer-specific encoder knob functions
#ifdef ENCODER_ENABLE
void encoder_update_user(uint8_t index, bool clockwise)
{
    uint16_t layers = (layer_state | default_layer_state);
    if (index == 0)
    { // left knob
        switch (get_highest_layer(layers))
        {
            case _MOUS: // Underglow color
#ifdef RGBLIGHT_ENABLE
                if (clockwise)
                {
                    rgblight_increase_hue();
                }
                else
                {
                    rgblight_decrease_hue();
                }
#endif
                break;
            default: // Volume Up/Down
                if (clockwise)
                {
                    tap_code(KC_VOLD);
                }
                else
                {
                    tap_code(KC_VOLU);
                }
                break;
        }
    }
    else if (index == 1)
    { // right knob
        switch (get_highest_layer(layers))
        {
            case _MOUS: // Underglow brightness
#ifdef RGBLIGHT_ENABLE
                if (clockwise)
                {
                    rgblight_increase_val();
                }
                else
                {
                    rgblight_decrease_val();
                }
#endif
                break;
            default:
                if (clockwise)
                {
                    tap_code(KC_BRIU);
                }
                else
                {
                    tap_code(KC_BRID);
                }
                break;
        }
    }
}
#endif

/*
qmk-keyboard-format:json:begin
{
  "name": "Kyria",
  "numkeys": 50,
  "rows": [
      [ -3,  0,  1,  2,  3,  4,  5, -1, -1, -2, -1, -1,  6,  7,  8,  9, 10, 11 ],
      [ -3, 12, 13, 14, 15, 16, 17, -1, -1, -2, -1, -1, 18, 19, 20, 21, 22, 23 ],
      [ -3, 24, 25, 26, 27, 28, 29, 30, 31, -2, 32, 33, 34, 35, 36, 37, 38, 39 ],
      [ -3, -1, -1, -1, 40, 41, 42, 43, 44, -2, 45, 46, 47, 48, 49, -1, -1, -1 ]
  ],
  "spacing": [
      0,
      0,
      0,
      2
  ],
  "vizcellwidth": 5,
  "vizemits": [
  ],
  "vizline": "//#",
  "vizemits": [
      { "line": "[_QWERTY] = LAYOUT(", "layer": "_QWERTY" },
      { "line": "[_QWERTY_CAPS] = LAYOUT(", "layer": "_QWERTY_CAPS" },
      { "line": "[_SSYM] = LAYOUT(", "layer": "_SSYM" },
      { "line": "[_NUM] = LAYOUT(", "layer": "_NUM" },
      { "line": "[_SYM] = LAYOUT(", "layer": "_SYM" },
      { "line": "[_NAV] = LAYOUT(", "layer": "_NAV" },
      { "line": "[_RAISE] = LAYOUT(", "layer": "_RAISE" }
  ],
  "vizboard": [
      "    //#                         ╭───────╮                                                                        ╭───────╮                          ",
      "    //#                 ╭───────╯ _003_ ╰───────╮                                                        ╭───────╯ _008_ ╰───────╮                  ",
      "    //#                 │ _002_ │       │ _004_ ╭───────╮                                        ╭───────╮ _007_ │       │ _009_ │                  ",
      "    //# ╭───────╮───────╯       ╰───────╯       │ _005_ │                                        │ _006_ │       ╰───────╯       ╰───────╭───────╮  ",
      "    //# │ _000_ │ _001_ ╰───────╯ _015_ ╰───────╯       │                                        │       ╰───────╯ _020_ ╰───────╯ _010_ │ _011_ │  ",
      "    //# │       │       │ _014_ │       │ _016_ ╰───────╯                                        ╰───────╯ _019_ │       │ _021_ │       │       │  ",
      "    //# ╰───────╯───────╯       ╰───────╯       │ _017_ │                                        │ _018_ │       ╰───────╯       ╰───────╰───────╯  ",
      "    //# │ _012_ │ _013_ ╰───────╯ _027_ ╰───────╯       │                                        │       ╰───────╯ _036_ ╰───────╯ _022_ │ _023_ │  ",
      "    //# │       │       │ _026_ │       │ _028_ ╰───────╯                                        ╰───────╯ _035_ │       │ _037_ │       │       │  ",
      "    //# ╰───────╯───────╯       ╰───────╯       │ _029_ │ ╭───────╮                    ╭───────╮ │ _034_ │       ╰───────╯       ╰───────╰───────╯  ",
      "    //# │ _024_ │ _025_ ╰───────╯       ╰───────╯       │ │ _030_ ╰───────╮    ╭───────╯ _033_ │ │       ╰───────╯       ╰───────╯ _038_ │ _039_ │  ",
      "    //# │       │       │              ╭───────╮╰───────╯ │       │ _031_ │    │ _032_ │       │ ╰───────╯╭───────╮              │       │       │  ",
      "    //# ╰───────╯───────╯     ╭───────╮│ _041_ ╰───────╮  ╰───────╯       │    │       ╰───────╯  ╭───────╯ _048_ │╭───────╮     ╰───────╰───────╯  ",
      "    //#                       │ _040_ ││       │ _042_ ╰───────╮  ╰───────╯    ╰───────╯  ╭───────╯ _047_ │       ││ _049_ │                        ",
      "    //#                       │       │╰───────╯       │ _043_ ╰───────╮          ╭───────╯ _046_ │       ╰───────╯│       │                        ",
      "    //#                       ╰encodr─╯        ╰───────╯       │ _044_ │          │ _045_ │       ╰───────╯        ╰encodr─╯                        ",
      "    //#                                                ╰───────╯       │          │       ╰───────╯                                                 ",
      "    //#                                                        ╰───────╯          ╰───────╯                                                         "
  ],
  "vizsymbols": {
      "xxxx": "     ",
      "SH_TG": "  EE ",
      "TG(_MOUS)": "MOUSE",
      "TG(_SYSTEM)": " SYS ",
      "MO(_NAV)": "NAVI ",
      "MO(_FNC)": "FUNC ",
      "MO(_SYM)": " SYM ",
      "TG(_QWERTY_CAPS)": "CAPS ",
      "TG(_RSTHD_CAPS)": "CAPS ",
      "KC_SNUM": "SMNUM",
      "KC_SCAP": "SMCAP",
      "OSM(MOD_LSFT)": "SHIFT",
      "OSL(_SSYM)": " SYM ",
      "_______": "     ",
      "KC_TRANS": "     ",
      "KC_0": "  0  " ,
      "KC_1": "  1  " ,
      "KC_2": "  2  " ,
      "KC_3": "  3  " ,
      "KC_4": "  4  " ,
      "KC_5": "  5  " ,
      "KC_6": "  6  " ,
      "KC_7": "  7  " ,
      "KC_8": "  8  " ,
      "KC_9": "  9  " ,
      "KC_A": "  a  " ,
      "KC_B": "  b  " ,
      "KC_C": "  c  " ,
      "KC_D": "  d  " ,
      "KC_E": "  e  " ,
      "KC_F": "  f  " ,
      "KC_G": "  g  " ,
      "KC_H": "  h  " ,
      "KC_I": "  i  " ,
      "KC_J": "  j  " ,
      "KC_K": "  k  " ,
      "KC_L": "  l  " ,
      "KC_M": "  m  " ,
      "KC_N": "  n  " ,
      "KC_O": "  o  " ,
      "KC_P": "  p  " ,
      "KC_Q": "  q  " ,
      "KC_R": "  r  " ,
      "KC_S": "  s  " ,
      "KC_T": "  t  " ,
      "KC_U": "  u  " ,
      "KC_V": "  v  " ,
      "KC_W": "  w  " ,
      "KC_X": "  x  " ,
      "KC_Y": "  y  " ,
      "KC_Z": "  z  " ,
      "LSFT(KC_A)": "  A  " ,
      "LSFT(KC_B)": "  B  " ,
      "LSFT(KC_C)": "  C  " ,
      "LSFT(KC_D)": "  D  " ,
      "LSFT(KC_E)": "  E  " ,
      "LSFT(KC_F)": "  F  " ,
      "LSFT(KC_G)": "  G  " ,
      "LSFT(KC_H)": "  H  " ,
      "LSFT(KC_I)": "  I  " ,
      "LSFT(KC_J)": "  J  " ,
      "LSFT(KC_K)": "  K  " ,
      "LSFT(KC_L)": "  L  " ,
      "LSFT(KC_M)": "  M  " ,
      "LSFT(KC_N)": "  N  " ,
      "LSFT(KC_O)": "  O  " ,
      "LSFT(KC_P)": "  P  " ,
      "LSFT(KC_Q)": "  Q  " ,
      "LSFT(KC_R)": "  R  " ,
      "LSFT(KC_S)": "  S  " ,
      "LSFT(KC_T)": "  T  " ,
      "LSFT(KC_U)": "  U  " ,
      "LSFT(KC_V)": "  V  " ,
      "LSFT(KC_W)": "  W  " ,
      "LSFT(KC_X)": "  X  " ,
      "LSFT(KC_Y)": "  Y  " ,
      "LSFT(KC_Z)": "  Z  " ,
      "KC_COMMA": "  ,  ",
      "KC_COMM": "  ,  ",
      "KC_DOT": "  .  ",
      "KC_COLN": "  :  ",
      "KC_SCOLON": "  ;  ",
      "KC_SCLN": "  ;  ",
      "KC_SLASH": "  \/  ",
      "KC_SLSH": "  \/  ",
      "KC_BSLASH": "  \\  ",
      "KC_BSLS": "  \\  ",
      "KC_EXLM": "  !  ",
      "KC_QUES": "  ?  ",
      "KC_PIPE": "  |  ",
      "KC_QUOT": "  '  ",
      "KC_QUOTE": "  '  ",
      "KC_DQUO": "  \"  ",
      "KC_DQT": "  \"  ",
      "KC_HASH": "  #  ",
      "KC_AMPR": "  &  ",
      "KC_PERC": "  %  ",
      "KC_TILDE": "  ~  ",
      "KC_AT": "  @  ",
      "KC_DLR": "  $  ",
      "KC_CIRC": "  ^  ",
      "KC_EQL": "  =  ",
      "KC_EQUAL": "  =  ",
      "KC_ASTR": "  *  ",
      "KC_MINS": "  -  ",
      "KC_MINUS": "  -  ",
      "KC_UNDS": "  _  ",
      "KC_PLUS": "  +  ",
      "KC_LCBR": "  {  ",
      "KC_LBRACKET": "  {  ",
      "KC_RCBR": "  }  ",
      "KC_RBRACKET": "  }  ",
      "KC_LPRN": "  (  ",
      "KC_LPRN_LCBR": "  ({ ",
      "KC_RPRN_RCBR": "  )} ",
      "KC_SCLN_COLN": "  ;: ",
      "KC_DQUO_EXCL": "  \"! ",
      "KC_UNDS_TLD": "  _~ ",
      "KC_PERC_CIRC": "  %^ ",
      "KC_EQUL_PIPE": "  =| ",
      "KC_RPRN": "  )  ",
      "KC_GRV": "  `  ",
      "KC_LBRC": "  [  ",
      "KC_RBRC": "  ]  ",
      "KC_LABK": "  <  ",
      "KC_RABK": "  >  ",
      "KC_TILD": "  ~  ",
      "KC_ESC": " ESC " ,
      "KC_ESCAPE": " ESC " ,
      "KC_OS_NDT": " NDT " ,
      "KC_OS_PDT": " PDT " ,
      "KC_OS_UNDO": " Undo" ,
      "KC_OS_CUT": " Cut " ,
      "KC_OS_COPY": " Copy" ,
      "KC_OS_PASTE": "Paste" ,
      "KC_COPY": " Copy",
      "KC_PASTE": "Paste",
      "KC_CUT":    " Cut " ,
      "KC_UNDO":   " Undo" ,
      "KC_REDO": " Redo " ,
      "KC_VOLU": "  🕪  " ,
      "KC_VOLD": "  🕩  " ,
      "KC_MUTE":   "  🕨  " ,
      "KC_TAB": " TAB " ,
      "KC_MENU": "  𝌆  " ,
      "KC_CAPSLOCK": "  ⇪  " ,
      "KC_NUMLK": "  ⇭  " ,
      "KC_SCRLK": "  ⇳  " ,
      "KC_PRSCR": "  ⎙  " ,
      "KC_PAUSE": "  ⎉  " ,
      "KC_BREAK": "  ⎊  " ,
      "KC_ENTER": "  ⏎  " ,
      "KC_BSPACE": "  ⌫  " ,
      "KC_DELETE": "  ⌦  " ,
      "KC_INSERT": "Insrt" ,
      "KC_LEFT":  "  L  " ,
      "KC_RIGHT": "  R  " ,
      "KC_UP":    "  U  " ,
      "KC_DOWN":  "  D  " ,
      "KC_HOME": "  ⇤  " ,
      "KC_END": "  ⇥  " ,
      "KC_PGUP": "  ⇞  " ,
      "KC_PGDOWN": "  ⇟  " ,
      "KC_LSFT": "  ⇧  " ,
      "KC_RSFT": "  ⇧  " ,
      "OS_SHFT": "  ⇧  " ,
      "KC_LCTL": "  ^  " ,
      "KC_RCTL": "  ^  " ,
      "OS_CTRL": "  ^  " ,
      "KC_LALT": "  ⎇  " ,
      "KC_RALT": "  ⎇  " ,
      "OS_ALT": "  ⎇  " ,
      "KC_HYPER": "  ✧  " ,
      "KC_LGUI": "  ⌘  " ,
      "KC_RGUI": "  ⌘  ",
      "OS_CMD": "  ⌘  "
  }
}
qmk-keyboard-format:json:end
*/
