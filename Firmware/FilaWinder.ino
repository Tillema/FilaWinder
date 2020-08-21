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


// ------------------------------------------------------------------------- //
// -------------------------------- PROGRAM -------------------------------- //
// ------------------------------------------------------------------------- //

void setup(){
    Serial.begin(BAUDRATE);
    set_pins();
    initialize_display();
}


void loop(){
}