// This firmware is written by Simon Tillema for a mechanism to spool filaments
// on empty rolls.
// You can use this firmware without any restriction, but note that using it is
// at your own risk. I do not take any responsibility for any harm caused by my
// code or the self-fabricated mechanism.


// ------------------------------------------------------------------------- //
// --------------------------- FILAMENT SETTINGS --------------------------- //
// ------------------------------------------------------------------------- //

// Initial average filament diameter in mm. This setting can be modified on the
// display and will be written to the EEPROM storage.
// #define DEFAULT_FILAMENT_DIAMETER 1.75 // mm

// Filaments with their properties as shown in the selection on the display. It
// is possible to add new filaments to the list by adding them. The order below
// is equal to the order as shown in the menu. This values will be written into
// the EEPROM storage. Filament names may not be longer than 11 characters. The
// first option is selected on the very first boot.
#define FILAMENT_NAME    {"PLA", "ABS", "PETG", "Nylon", "Flex", "PVA", "HIPS"}
// #define FILAMENT_DENSITY { 1.24,  1.04,   1.23,     1.1,    1.2,  1.23,   1.03}
// used source: simplify3d.com/support/materials-guide/properties-table/


// ------------------------------------------------------------------------- //
// ----------------------------- SPOOL OPTIONS ----------------------------- //
// ------------------------------------------------------------------------- //

// Spool size in kilograms. For non-Metric users: convert your used units to kg
// in order to know the spool size. Set COMPLETING to false in order to end the
// windings halfway the spool in order to get the exact weight. Enabling should
// result in some overshoot on a spool.
// #define DEFAULT_SPOOL_SIZE 1000 // g
//#define COMPLETING

// Set the default diameter of the barrel of the spool. Every spool consists of
// at least 3 parts: the barrel and two sides. This option denotes the diameter
// of that barrel. Integers only allowed.
// #define DEFAULT_BARREL_DIAMETER 100 // mm


// ------------------------------------------------------------------------- //
// -------------------------- MECHANICAL SETTINGS -------------------------- //
// ------------------------------------------------------------------------- //

// Set the way of spooling by uncommenting one of the two options below. It can
// be done two ways: FILAMENT_CONTINUOUS means that the filament has a constant
// speed while the spool rotate at a varying rotational speed. SPOOL_CONTINUOUS
// is vice versa.
//#define FILAMENT_CONTINUOUS // To use in combination with e.g. a filastruder
//#define SPOOL_CONTINUOUS // Best choice

// Microsteps represents the number of interpolating steps between two steps of
// the stepper motor. The possible values for microsteps are 1 (off), 2 (half),
// 4 (quarter), or 8 (eighth) step. Set the values for both stepper motors. The
// First value represents the guiding mechanism. The Second is for the spooler.
//#define MICROSTEPS_SPOOLER {8, 8}

// Number of steps for a full rotation without microstepping turned on. Set the
// values for both stepper motors. First value represents the guiding mechanism
// with spindle. Second is for spooling. NEMA-17 steppers are by default 180.
//#define STEPS_PER_ROTATION_SPOOLER {200, 200}

// Pitch of the leadscrew of the guiding mechanism, and the gear ratio used for
// the spooling stepper motor. Set the gear ratio to 1 to disable.
//#define LEADSCREW_PITCH 8 // mm
//#define GEAR_RATIO 36

// Set the default and maximum spooling speeds. The default speed can be set on
// the display. Set the acceleration based on the used stepper current. Stepper
// motors with a high current can handle higher acceleration values.
// #define DEFAULT_SPOOLING_SPEED 25 // mm/s
//#define MAX_SPOOLING_SPEED 50 // mm/s
// #define ACCELERATION 500 // mm/s²

// Set the direction of the home position. This considers the start position of
// the filament on the spool. Set to 0 to start in the back or to 1 to start in
// the front.
//#define HOMING_DIR 0


// ------------------------------------------------------------------------- //
// --------------------------------- OTHER --------------------------------- //
// ------------------------------------------------------------------------- //

// Set the baudrate for the communication with the computer. Use this option in
// case you want to show information regarding the process on a serial monitor.
// Default baudrates for Arduino's are 1200, 4800, 9600, 19200, 115200, etc.
#define BAUDRATE 9600

// Set the used board. By default the Arduino Nano is used. Set this to set the
// pins correctly. Pins could also be changed by modifying pins.h.
// Other board options are:
// 1: Arduino Uno
// 2: Arduino Mega
// 3: Arduino Nano
//#define MOTHERBOARD 3

// Turn on bootscreen to show a bootscreen at boot.
#define BOOTSCREEN