// This firmware is written by Simon Tillema for a mechanism to spool filaments
// on empty rolls.
// You can use this firmware without any restriction, but note that using it is
// at your own risk. I do not take any responsibility for any harm caused by my
// code or the self-fabricated mechanism.


// ------------------------------------------------------------------------- //
// -------------------------------- PRESETS -------------------------------- //
// ------------------------------------------------------------------------- //

#include "Config.h"

const uint16_t* steps[] = STEPS_PER_ROTATION;
const uint8_t* microsteps[] = MICROSTEPS;
uint16_t target_speed = DEFAULT_SPOOLING_SPEED;
uint16_t acceleration = ACCELERATION;
double barrel_diameter = DEFAULT_BARREL_DIAMETER;
double filament_diameter = FILAMENT_DIAMETER;

uint8_t state = 1;

unsigned long current_time;
unsigned long previous_time = 0;

double current_diameter = barrel_diameter + filament_diameter;

unsigned long current_speed = 200;
unsigned int delta_speed;
unsigned long delta_time;
long delta_interval;
unsigned long end_time;
unsigned long starting_point;
double slope;

#define steps_per_rev_spooler (uint16_t)steps[0] * (uint16_t)microsteps[0]
#define fixed_part 500000 * PI / steps_per_rev_spooler
unsigned long current_interval = 0;
unsigned long target_interval = 0;


// ------------------------------------------------------------------------- //
// ------------------------------- FUNCTIONS ------------------------------- //
// ------------------------------------------------------------------------- //


// ------------------------------------------------------------------------- //
// ------------------------------- MAIN CODE ------------------------------- //
// ------------------------------------------------------------------------- //

void setup(){
    // Initialize IO
    DDRB = B00011111; DDRC = B00101110; DDRD = B11111100;
    Serial.begin(57600);
}

void loop(){
    current_time = micros();
    if(state == 1){
        // Increment
        if(current_speed != target_speed){
            delta_speed = abs(target_speed - current_speed);
            delta_time = 1000000 * delta_speed / acceleration;
            end_time = current_time + delta_time;
            // Calculate current_interval and final_interval
            current_interval = fixed_part * current_diameter / current_speed;
            target_interval = fixed_part * current_diameter / target_speed;
            delta_interval = target_interval - current_interval;
            slope = (double)delta_interval / (double)delta_time;
            Serial.println(delta_interval);
            Serial.println(delta_time);
            Serial.println(slope);
            starting_point = current_interval - slope * current_time;
            Serial.println(starting_point);
            current_speed = target_speed;
        }
        if(current_time <= end_time){
            // Calculate accelerated interval
            current_interval = slope * current_time + starting_point;
        }
        // Take step
        if(current_time - previous_time >= current_interval){
            PORTD = PORTD ^ B00010000;
            previous_time = current_time;
            //Serial.println(current_interval);
        }
    }
}