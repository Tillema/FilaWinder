// This firmware is written by Simon Tillema for a mechanism to spool filaments
// on empty rolls.
// You can use this firmware without any restriction, but note that using it is
// at your own risk. I do not take any responsibility for any harm caused by my
// code or the self-fabricated mechanism.

// ------------------------------------------------------------------------- //
// ------------------------------- INPUT PINS ------------------------------ //
// ------------------------------------------------------------------------- //

// Encoder pins
#define ENCODER_A_PIN      13
#define ENCODER_B_PIN      A0
#define ENCODER_BUTTON_PIN A4


// ------------------------------------------------------------------------- //
// ------------------------------ OUTPUT PINS ------------------------------ //
// ------------------------------------------------------------------------- //

// Display pins
#define RS_PIN             A5  // DDRC B00100000
#define EN_PIN             A2  // DDRC B00000100
#define D4_PIN             A1  // DDRC B00000010
#define D5_PIN             10  // DDRB B00000100
#define D6_PIN              7  // DDRD B10000000
#define D7_PIN              2  // DDRD B00000100
// Buzzer pin
#define BUZZER_PIN         A3  // DDRC B00001000
// Spooler Motor pins
#define DIR_SPOOLER_PIN     3  // DDRD B00001000
#define STEP_SPOOLER_PIN    4  // DDRD B00010000
#define MS1_SPOOLER_PIN     6  // DDRD B01000000
#define MS2_SPOOLER_PIN     5  // DDRD B00100000
// Guider Motor pins
#define DIR_GUIDER_PIN      8  // DDRB B00000001
#define STEP_GUIDER_PIN     9  // DDRB B00000010
#define MS1_GUIDER_PIN     12  // DDRB B00010000
#define MS2_GUIDER_PIN     11  // DDRB B00001000
//                                +------------+
//                                DDRB B00011111
//                                DDRC B00101110
//                                DDRD B11111100