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
#include <EEPROM.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(A5, A2, A1, 10, 7, 2);

byte current_menu = 0;  // 0 = homescreen, 1 = main menu, 2 = settings
byte current_state = 0; // 0 = idle, 1 = spooling, 2 = paused

byte state_length = 0;


float current_EEPROM_version = 0.0;
float configured_EEPROM_version;
byte material;
int spool_size;
int barrel_diameter;
int speed;

int current_length = 0;
int current_weight = 0;

const char* filament_name[] = FILAMENT_NAME;

bool encoder_state;
bool previous_encoder_state = 0;
bool button_state;
bool previous_button_state = 0;


// ------------------------------------------------------------------------- //
// ------------------------------- FUNCTIONS ------------------------------- //
// ------------------------------------------------------------------------- //

void set_pins(){
    DDRB = B00000100;
    DDRC = B00101110;
    DDRD = B10000100;
}

void initialize_display(){
    lcd.begin(20, 4);
    lcd.clear();
    #ifdef BOOTSCREEN
        lcd.setCursor(0, 1); lcd.print(bootscreen_items[0]);
        lcd.setCursor(0, 2); lcd.print(bootscreen_items[1]);
        delay(1000);
    #endif
}

void initialize_EEPROM(){
    configured_EEPROM_version = EEPROM_VERSION;
    EEPROM.get(0, current_EEPROM_version);
    if(current_EEPROM_version != configured_EEPROM_version){
        // Update EEPROM to current version
        EEPROM.put(0, configured_EEPROM_version);
        // Write material
        material = 0;
        EEPROM.write(4, material);
        // Write defualt spool size
        spool_size = DEFAULT_SPOOL_SIZE;
        EEPROM.put(5, spool_size);
        // Write default barrel diameter
        barrel_diameter = DEFAULT_BARREL_DIAMETER;
        EEPROM.put(7, barrel_diameter);
        // Write default speed
        speed = DEFAULT_SPOOLING_SPEED;
        EEPROM.put(9, speed);
    }else{
        material = EEPROM.read(4);
        EEPROM.get(5, spool_size);
        EEPROM.get(7, barrel_diameter);
        EEPROM.get(9, speed);
    }
}

void draw_homescreen(){
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
    current_menu = 1;
    lcd.clear();
    lcd.setCursor(3, 1); lcd.print(main_menu_items[0]);
    lcd.setCursor(12, 1); lcd.print(main_menu_items[current_state + 1]);
    lcd.setCursor(1, 2); lcd.print(main_menu_items[4]);
    lcd.setCursor(12, 2); lcd.print(main_menu_items[current_state + 5]);
}

void draw_settings_menu(){}

void rotary_encoder(){
    encoder_state = (PINB & _BV (5)) == 0; // Read pin 13
    if(!encoder_state && previous_encoder_state){
        if(!(PINC & _BV (0)) == 0){ // Read pin A0
            // Increase selector
        }else{
            // Decrease selector
        }
    }
    previous_encoder_state = encoder_state;
    button_state = (PINC & _BV (4)) == 0;
    if(!button_state && previous_button_state){
        // Button activated
    }
    previous_button_state = button_state;
}

// ------------------------------------------------------------------------- //
// -------------------------------- PROGRAM -------------------------------- //
// ------------------------------------------------------------------------- //

void setup(){
    //Serial.begin(BAUDRATE);
    set_pins();
    initialize_display();
    initialize_EEPROM();
    draw_homescreen();
}


void loop(){
    rotary_encoder();
}