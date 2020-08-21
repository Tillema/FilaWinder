// This firmware is written by Simon Tillema for a mechanism to spool filaments
// on empty rolls.
// You can use this firmware without any restriction, but note that using it is
// at your own risk. I do not take any responsibility for any harm caused by my
// code or the self-fabricated mechanism.


// ------------------------------------------------------------------------- //
// -------------------------- PINOUT RIBBON CABLE -------------------------- //
// ------------------------------------------------------------------------- //

//                    EXP1
//                  ┌------┐
//    BEEP (buzzer) | 1  2 | BTN (encoder)
// ENABLE (display) | 3  4 | RS (display)
//   LCD4 (display) | 5  6   LCD5 (display)
//   LCD6 (display) | 7  8 | LCD7 (display)
//              GND | 9 10 | VCC
//                  └------┘
//
//                    EXP2
//                  ┌------┐
//                  | 1  2 |
// BT_EN1 (encoder) | 3  4 |
// BT_EN2 (encoder) | 5  6
//                  | 7  8 | RESET (button)
//                  | 9 10 |
//                  └------┘


// ------------------------------------------------------------------------- //
// --------------------------- MENU ITEMS ARRAYS --------------------------- //
// ------------------------------------------------------------------------- //

/* Homescreen:
* ┌----------------------┐
* |                      |
* |      FILAWINDER      |
* |   by Simon Tillema   |
* |                      |
* └----------------------┘
*/

String bootscreen_items[] = {
    "     FILAWINDER     ", // 0
    "  by Simon Tillema  "  // 1
};

/* Homescreen:
* ┌----------------------┐
* | Length XXXm     IDLE | -> IDLE/SPOOLING/PAUSED
* | Weight XXXX/XXXXg    |
* | Material XXXXXXXXXXX |
* |    MENU      WAIT    | -> WAIT/START!/RESUME
* └----------------------┘
*/

String homescreen_items[] = {
    "Length ",              // 0
    "IDLE",                 // 1 -> state == 0
    "SPOOLING",             // 2 -> state == 1
    "PAUSED"                // 3 -> state == 2
    "Weight ",              // 4
    "Material ",            // 5
    "MENU",                 // 6
    "START!",               // 7 BUTTON2 -> state == 0
    " WAIT ",               // 8 BUTTON2 -> state == 1
    "RESUME"                // 9 BUTTON2 -> state == 2
};

/* Main menu:
* ┌----------------------┐
* |                      |
* |   Home      Start!   | -> Start!/Wait/Resume
* | Settings    Reboot   | -> Reboot/Kill
* |                      |
* └----------------------┘
*/

String main_menu_items[] = {
    "Home",                 // 0
    "Start!",               // 1 BUTTON3 -> state == 0
    " Wait ",               // 2 BUTTON3 -> state == 1
    "Resume",               // 3 BUTTON3 -> state == 2
    "Settings",             // 4
    "Reboot",               // 5 BUTTON4 -> state == 0
    "Kill",                 // 6 BUTTON4 -> state == 1
    "Stop"                  // 7 BUTTON4 -> state == 2
};