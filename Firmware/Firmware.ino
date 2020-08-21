// This firmware is written by Simon Tillema for a mechanism to spool filaments
// on empty rolls.
// You can use this firmware without any restriction, but note that using it is
// at your own risk. I do not take any responsibility for any harm caused by my
// code or the self-fabricated mechanism.


// ------------------------------------------------------------------------- //
// --------------------------- INCLUDES, OBJECTS --------------------------- //
// ------------------------------------------------------------------------- //

#include "Configuration.h"
#include "Display.h"
#include <LiquidCrystal.h>

LiquidCrystal lcd(PIN_RS, PIN_EN, PIN_LCD4, PIN_LCD5, PIN_LCD6, PIN_LCD7);

byte current_menu = 0;  // 0 = homescreen, 1 = main menu, 2 = settings
byte current_state = 0; // 0 = idle, 1 = spooling, 2 = paused

byte state_length = 0;
const char* filament_name[] = FILAMENT_NAME;

byte material = 0;
int current_length = 200;
int current_weight = 1050;

int spool_size = 1000;

// ------------------------------------------------------------------------- //
// ------------------------------- FUNCTIONS ------------------------------- //
// ------------------------------------------------------------------------- //

void set_pins(){
    DDRB = DDRC = DDRD = 0;
    DDRB |= DDRB_controller_mask;
    DDRC |= DDRC_controller_mask;
    DDRD |= DDRC_controller_mask;
}

void initialize_display(){
    lcd.begin(20, 4);
    lcd.clear();
    #ifdef BOOTSCREEN
        lcd.setCursor(0, 1); lcd.print(bootscreen_items[0]);
        lcd.setCursor(0, 2); lcd.print(bootscreen_items[1]);
    #endif
}

void draw_homescreen(){
    /* Homescreen:
     * ┌----------------------┐
     * | Length XXXm     IDLE | -> IDLE/SPOOLING/PAUSED
     * | Weight XXXX/XXXXg    |
     * | Material XXXXXXXXXXX |
     * |    MENU      WAIT    | -> WAIT/START!/RESUME
     * └----------------------┘
     */
    current_menu = 0;
    lcd.clear();
    // FIRST LINE
    lcd.setCursor(0, 0); lcd.print(homescreen_items[0]);
    lcd.print(String(current_length) + "mm");
    if(!current_state){
        state_length = 4;
    }else if(current_state){
        state_length = 8;
    }else{
        state_length = 6;
    }
    lcd.setCursor(20 - state_length, 0);
    lcd.print(homescreen_items[current_state + 1]);
    // SECOND LINE
    lcd.setCursor(0, 1); lcd.print(homescreen_items[4]);
    lcd.print(String(current_weight) + "/" + String(spool_size) + "g");
    // THIRD LINE
    lcd.setCursor(0, 2); lcd.print(homescreen_items[5]);
    lcd.print(filament_name[material]);
    // FOURTH LINE
    lcd.setCursor(3, 4); lcd.print(homescreen_items[6]);
    lcd.setCursor(14, 4); lcd.print(homescreen_items[current_state + 7]);
}

void draw_main_menu(){
    /* Main menu:
     * ┌----------------------┐
     * |                      |
     * |   Home      Start!   | -> Start!/Wait/Resume
     * | Settings    Reboot   | -> Reboot/Kill
     * |                      |
     * └----------------------┘
     */
    current_menu = 1;
    lcd.clear();
    lcd.setCursor(3, 1); lcd.print(main_menu_items[0]);
    lcd.setCursor(12, 1); lcd.print(main_menu_items[current_state + 1]);
    lcd.setCursor(1, 2); lcd.print(main_menu_items[4]);
    lcd.setCursor(12, 2); lcd.print(main_menu_items[current_state + 5]);
}

// ------------------------------------------------------------------------- //
// -------------------------------- PROGRAM -------------------------------- //
// ------------------------------------------------------------------------- //

void setup(){
    Serial.begin(BAUDRATE);
    set_pins();
    initialize_display();
    draw_homescreen();
}


void loop(){
}