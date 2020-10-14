// This firmware is written by Simon Tillema for a mechanism to spool filaments
// on empty rolls.
// You can use this firmware without any restriction, but note that using it is
// at your own risk. I do not take any responsibility for any harm caused by my
// code or the self-fabricated mechanism.


// ------------------------------------------------------------------------- //
// -------------------------------- PRESETS -------------------------------- //
// ------------------------------------------------------------------------- //

#include "Config.h"
#include "Pins.h"
#include <LiquidCrystal.h>
#include <EEPROM.h>

// Following variables are configured in Config.h. If those are not defined, or
// configured wrong, the error will be clear.
const uint16_t bootscreen_delay = BOOTSCREEN_DELAY;
double config_version = CONFIG_VERSION;
uint16_t target_weight = DEFAULT_SPOOL_SIZE;
double barrel_diameter = DEFAULT_BARREL_DIAMETER;
uint8_t speed = DEFAULT_SPOOLING_SPEED;
uint8_t max_speed = MAX_SPOOLING_SPEED;
const char* filament_name[] = FILAMENT_NAME;
const float densities[] = FILAMENT_DENSITY;
const unsigned long duration = MENU_SPEED_DELAY;

// In case SERIAL_COMMUNICATION is turned on, every output will start with this
// echo string.
const char* echo_msg = "Echo: ";

// Following variables will be updated through the process.
uint8_t state = 0; // 0 = idle, 1 = spooling, 2 = paused
uint16_t length = 1000;
uint16_t weight = 1000;
uint8_t material = 0;

// Following variables and objects regards the controller.
LiquidCrystal lcd{RS_PIN, EN_PIN, D4_PIN, D5_PIN, D6_PIN, D7_PIN};
bool prev_enc_state_A = 0, curr_enc_state_A, state_B;
bool prev_button_state = 0, curr_button_state;
unsigned long timer = 0;
bool timer_activated = 0;
uint8_t current_menu = 0;
bool homescreen_activated = 0;
uint8_t selection = 0, material_selection = 0, lower_bound = 0;

// Other variables
double EEPROM_version;
const uint8_t num_of_filaments = sizeof(densities) / sizeof(densities[0] - 1);


// ------------------------------------------------------------------------- //
// ------------------------------- FUNCTIONS ------------------------------- //
// ------------------------------------------------------------------------- //

void update_status(){
    if(state < 2){
        state++;
    }else{
        state = 1;
    }
    homescreen_activated = false;
    draw_homescreen();
}
void draw_homescreen(){
    /* Homescreen:
     * ┌-----------------------------------------┐
     * | L e n g t h   X X X m           I D L E | -> length
     * | W e i g h t   X X X X / X X X X g       | -> weight & target_weight
     * | M a t e r i a l   X X X X X X X X X X X | -> material
     * |       M E N U             W A I T       | -> WAIT/START!/RESUME
     * └-----------------------------------------┘
     */
    current_menu = 0;
    lcd.clear();
    // LINE 0 (first line)
    lcd.setCursor(0, 0);
    lcd.print("Length ");
    lcd.print(length);
    lcd.print("m");
    lcd.setCursor(12, 0);
    switch(state){
        case 0:  lcd.print("    IDLE"); break;
        case 1:  lcd.print("SPOOLING"); break;
        default: lcd.print("  PAUSED"); break;
    }
    // LINE 1 (second line)
    lcd.setCursor(0, 1);
    lcd.print("Weight ");
    lcd.print(weight); lcd.print("/");
    lcd.print(target_weight);
    lcd.print("g");
    // LINE 2 (third line)
    lcd.setCursor(0, 2);
    lcd.print("Material ");
    lcd.print(filament_name[material]);
    // SELECTIONS
    draw_selector(0);
}
void draw_main_menu(){
    /* Main menu:
     * ┌-----------------------------------------┐
     * |                                         |
     * |       H o m e       S e t t i n g s     |
     * |     S t a r t !     M a t e r i a l     |
     * |                                         |
     * └-----------------------------------------┘
     */
    current_menu = 1;
    lcd.clear();
    draw_selector(0);
}
void draw_settings_menu(){
    /* Settings menu:
     * ┌-----------------------------------------┐
     * |   B A C K                               |
     * |   S p e e d   X X X X m m / s           |
     * |   S p o o l   s i z e   X X X X g       |
     * |   D i a m e t e r   1 0 0 . 0 m m       |
     * └-----------------------------------------┘
     */
    current_menu = 2;
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("Back");
    lcd.setCursor(1, 1);
    lcd.print("Speed ");
    lcd.print(speed);
    lcd.print("mm/s");
    lcd.setCursor(1, 2);
    lcd.print("Spool size ");
    lcd.print(target_weight);
    lcd.print("g");
    lcd.setCursor(1, 3);
    lcd.print("Diameter ");
    lcd.print(barrel_diameter);
    lcd.print("mm");
}
void update_material_menu(bool direction){
    /* Material menu:
     * ┌-----------------------------------------┐
     * |   M A T E R I A L   1                   | -> Scroll through materials
     * |   M A T E R I A L   2                   | -> Scroll through materials
     * |   M A T E R I A L   3                   | -> Scroll through materials
     * |   M A T E R I A L   4                   | -> Scroll through materials
     * └-----------------------------------------┘
     */
    current_menu = 3;
    lcd.clear();
    if(direction){
        if(material_selection < num_of_filaments) material_selection++;
    }else{
        if(material_selection > 0) material_selection--;
    }
    if(material_selection - 4 > lower_bound) lower_bound++;
    if(material_selection < lower_bound) lower_bound--;
    selection = material_selection - lower_bound;
    lcd.setCursor(1, 0); lcd.print(filament_name[lower_bound]);
    lcd.setCursor(1, 1); lcd.print(filament_name[lower_bound + 1]);
    lcd.setCursor(1, 2); lcd.print(filament_name[lower_bound + 2]);
    lcd.setCursor(1, 3); lcd.print(filament_name[lower_bound + 3]);
}

void draw_selector(bool direction){
    const char* status[] = {" START! ", "  WAIT  ", " RESUME "};
    const char* status_selected[] = {">START!<", " >WAIT< ", ">RESUME<"};
    if(direction){
        selection++;
    }else{
        if(selection > 0) selection--;
    }
    if(current_menu == 0){ // Homescreen
        if(direction) homescreen_activated = true;
        if(selection > 1) selection = 1;
        if(!homescreen_activated) selection = -1;
        lcd.setCursor(2, 3);
        lcd.print(selection == 0 ? ">MENU<  " : " MENU   ");
        lcd.print(selection == 1 ? status_selected[state] : status[state]);
    }else if(current_menu == 1){ // Main menu
        if(selection > 3) selection = 3;
        lcd.setCursor(2, 1);
        lcd.print(selection == 0 ? ">HOME< " : " HOME  ");
        lcd.print(selection == 2 ? ">Settings<" : " Settings ");
        lcd.setCursor(1, 2);
        lcd.print(selection == 1 ? status_selected[state] : status[state]);
        lcd.print(selection == 3 ? ">Material<" : " Material ");
    }else if(current_menu == 2){ // Settings menu
        if(selection > 3) selection = 3;
        for(int i = 0; i < 4; i++){
            lcd.setCursor(0, i);
            lcd.print((selection == i) ? ">" : " ");
        }
    }else if(current_menu == 3){ // Material menu
        update_material_menu(direction);
        if(selection > 3) selection = 3;
        for(int i = 0; i < 4; i++){
            lcd.setCursor(0, i);
            lcd.print((selection == i) ? ">" : " ");
        }
    }else if(current_menu == 4){
        if(direction){
            if(speed != max_speed) speed++;
        }else{
            if(speed > 1) speed--;
        }
        lcd.setCursor(1, 2);
        lcd.print("   ");
        lcd.setCursor(1, 2);
        lcd.print(speed);
    }else if(current_menu == 5){
        if(direction){
            target_weight += 10;
        }else{
            if(target_weight > 10) target_weight -= 10;
        }
        lcd.setCursor(1, 2);
        lcd.print("    ");
        lcd.setCursor(1, 2);
        lcd.print(target_weight);
    }else if(current_menu == 6){
        if(direction){
            barrel_diameter += 0.2;
        }else{
            if(barrel_diameter > 10.0) barrel_diameter -= 0.2;
        }
        lcd.setCursor(1, 2);
        lcd.print("     ");
        lcd.setCursor(1, 2);
        lcd.print(barrel_diameter);
    }
}
void select(){
    if(current_menu == 0){ // Homescreen
        if(selection == 0){
            draw_main_menu();
            draw_selector(0);
        }else if(selection == 1){
            update_status();
        }
    }else if(current_menu == 1){ // Main menu
        if(selection == 0){
            homescreen_activated = false;
            draw_homescreen();
        }else if(selection == 2){
            draw_settings_menu();
        }else if(selection == 1){
            update_status();
        }else if(selection == 3){
            update_material_menu(0);
        }
    }else if(current_menu == 2){ // Settings menu
        if(selection == 0){
            draw_main_menu();
        }else{
            current_menu = selection + 3;
            lcd.clear();
            lcd.setCursor(0, 1);
            switch(selection){
                case 1:  lcd.print("Speed (mm/s"); break;
                case 2:  lcd.print("Spool size (g)"); break;
                case 3:  lcd.print("Barrel diameter (mm)"); break;
                default: break;
            }
            lcd.setCursor(1, 2);
            switch(selection){
                case 1:  lcd.print(speed); break;
                case 2:  lcd.print(target_weight); break;
                case 3:  lcd.print(barrel_diameter); break;
                default: break;
            }
        }
    }else if(current_menu == 3){
        material = material_selection;
        EEPROM.write(4, material);
        draw_main_menu();
    }else{
        if(current_menu == 4){
            EEPROM.put(11, speed);
        }else if(current_menu == 5){
            EEPROM.put(5, target_weight);
        }else if(current_menu == 6){
            EEPROM.put(7, barrel_diameter);
        }
        draw_settings_menu();
    }
    selection = 0;
    if(current_menu < 4) draw_selector(0);
}

void activate_timer(){
    timer = millis();
    timer_activated = true;
}


// ------------------------------------------------------------------------- //
// ------------------------------- MAIN CODE ------------------------------- //
// ------------------------------------------------------------------------- //

void setup(){
    // Initialize IO
    DDRB = B00011111; DDRC = B00101110; DDRD = B11111100;
    #ifdef SERIAL_COMMUNICATION
        Serial.begin(BAUDRATE);
        Serial.print(echo_msg);
        Serial.println("Booting system...");
    #endif
    // Initialize display
    lcd.begin(20, 4);
    lcd.clear();
    #ifdef BOOTSCREEN
        /* Bootscreen:
         * ┌-----------------------------------------┐
         * |                                         |
         * |           F I L A W I N D E R           |
         * |     b y   S i m o n   T i l l e m a     |
         * |                                         |
         * └-----------------------------------------┘
         */
        lcd.setCursor(5, 1); lcd.print("FILAWINDER");
        lcd.setCursor(2, 2); lcd.print("by Simon Tillema");
        delay(bootscreen_delay);
    #endif
    // Initialize EEPROM
    EEPROM.get(0, EEPROM_version);
    if(EEPROM_version != config_version){
        #ifdef SERIAL_COMMUNICATION
            Serial.print(echo_msg);
            Serial.println("Writing EEPROM..");
        #endif
        EEPROM.put(0, config_version);
        EEPROM.write(4, material);
        EEPROM.put(5, target_weight);
        EEPROM.put(7, barrel_diameter);
        EEPROM.put(11, speed);
    }else{
        #ifdef SERIAL_COMMUNICATION
            Serial.print(echo_msg);
            Serial.println("Initializing EEPROM...");
        #endif
        material = EEPROM.read(4);
        EEPROM.get(5, target_weight);
        EEPROM.get(7, barrel_diameter);
        EEPROM.get(11, speed);
    }
    // Draw Homescreen
    draw_homescreen();
    #ifdef SERIAL_COMMUNICATION
        Serial.print(echo_msg);
        Serial.println("System initialized");
    #endif
}

void loop(){
    // Read timer
    if(timer_activated){
        if(millis() - timer >= duration){ // if timer expired
            homescreen_activated = false;
            draw_homescreen();
            timer_activated = false;
        }
    }
    // Read encoder
    curr_enc_state_A = (PINB & _BV (5)) == 0;
    state_B = (PINC & _BV (0)) == 0;
    curr_button_state = (PINC & _BV (4)) == 0;
    if(prev_enc_state_A && !curr_enc_state_A){
        draw_selector(state_B);
        activate_timer();
    }
    prev_enc_state_A = curr_enc_state_A;
    // Encoder button
    if(prev_button_state && !curr_button_state){
        select();
        activate_timer();
    }
    prev_button_state = curr_button_state;
}