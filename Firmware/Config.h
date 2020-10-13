// This firmware is written by Simon Tillema for a mechanism to spool filaments
// on empty rolls.
// You can use this firmware without any restriction, but note that using it is
// at your own risk. I do not take any responsibility for any harm caused by my
// code or the self-fabricated mechanism.


// In GitHub, click on Watch (upper right) to get notifications in case a newer
// version of the FilaWinder firmware is released. Best to keep your FilaWinder
// as up to date as possible, because discovered bugs and new functions will be
// fixed in newer versions.
#define CONFIG_VERSION 1.0


// ------------------------------------------------------------------------- //
// --------------------------- FILAMENT SETTINGS --------------------------- //
// ------------------------------------------------------------------------- //

// Initial average filament diameter in mm. This setting can not be modified on
// the interface.
// #define FILAMENT_DIAMETER 1.75 // mm

// Filaments with their properties as shown in the selection on the display. It
// is possible to add new filaments to the list by adding them. The order below
// is equal to the order as shown in the menu. This values will be written into
// the EEPROM storage. Filament names may not be longer than 10 characters. The
// first option is selected on the very first boot. Make sure both sets do have
// an equal amount of entities.
#define FILAMENT_NAME    {"PLA", "ABS", "PETG", "Nylon", "Flex", "PVA", "HIPS"}
#define FILAMENT_DENSITY { 1.24,  1.04,   1.23,     1.1,    1.2,  1.23,   1.03}
// used source: simplify3d.com/support/materials-guide/properties-table/


// ------------------------------------------------------------------------- //
// ----------------------------- SPOOL OPTIONS ----------------------------- //
// ------------------------------------------------------------------------- //

// Spool size in kilograms. For non-Metric users: convert your used units to kg
// in order to know the spool size. This could be set in the menu as well. Turn
// off COMPLETING to end the windings halfway to get the exact weight. Enabling
// should result in some overshoot on the spool.
#define DEFAULT_SPOOL_SIZE 1000 // g
// #define COMPLETING

// Set the default diameter of the barrel of the spool. Every spool consists of
// at least 3 parts: the barrel and two sides. This option denotes the diameter
// of that barrel. This could be set in the menu as well.
#define DEFAULT_BARREL_DIAMETER 100.0 // mm


// ------------------------------------------------------------------------- //
// -------------------------- MECHANICAL SETTINGS -------------------------- //
// ------------------------------------------------------------------------- //

// Set the way of spooling by uncommenting one of the two options below. It can
// be done two ways: FILAMENT_CONTINUOUS means that the filament has a constant
// speed while the spool rotate at a varying rotational speed. SPOOL_CONTINUOUS
// is vice versa.
// #define FILAMENT_CONTINUOUS // To use in combination with e.g. a filastruder
// #define SPOOL_CONTINUOUS // Best choice

// Microsteps represents the number of interpolating steps between two steps of
// the stepper motor. The possible values for microsteps are 1 (off), 2 (half),
// 4 (quarter), or 8 (eighth) step. Set the values for both stepper motors. The
// First value represents the guiding mechanism. The Second is for the spooler.
// #define MICROSTEPS {8, 8}

// Number of steps for a full rotation without microstepping turned on. Set the
// values for both stepper motors. First value represents the guiding mechanism
// with spindle. Second is for spooling. NEMA-17 steppers are by default 180.
// #define STEPS_PER_ROTATION_SPOOLER {200, 200}

// Pitch of the leadscrew of the guiding mechanism.
// #define LEADSCREW_PITCH 8 // mm

// Set the default and maximum spooling speeds. The default speed can be set in
// the menu as well. Set the acceleration based on the used stepper currents. A
// high acceleration requires also a higher current which can result in too hot
// motors.
#define DEFAULT_SPOOLING_SPEED 25 // mm/s
#define MAX_SPOOLING_SPEED 50 // mm/s
// #define ACCELERATION 500 // mm/s²

// Set the direction of the home position. This considers the start position of
// the filament on the spool. Set to 0 to start in the back or to 1 to start in
// the front.
// #define HOMING_DIR 0


// ------------------------------------------------------------------------- //
// --------------------------------- OTHER --------------------------------- //
// ------------------------------------------------------------------------- //

// To enable serial communication (via computer) you have to enable both serial
// communication and set the baudrate. Use this option if you want to show some
// information regarding the progress on a serial monitor. Default baudrate for
// an Arduino is either 1200, 4800, 9600, 19200,or 115200.
// Note: a high baudrate makes the process smoother but can cause weird issues.
#define SERIAL_COMMUNICATION
#define BAUDRATE 57600

// Turn on bootscreen to show a bootscreen at boot. This also helps to make the
// system stable after a boot. Set to true or false.
#define BOOTSCREEN
#define BOOTSCREEN_DELAY 1500

// When selecting a menu, the selector will be active for a specified amount of
// time. Set that time with the menu delay. After this timeframe of inactivity,
// the homescreen will appear again.
#define MENU_SPEED_DELAY 5000