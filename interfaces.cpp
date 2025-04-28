#include "interfaces.hpp"

// Define the data pins for the HX711 load cells
#define LOADCELL_LEFT_DOUT_PIN  2  // Example pin, update with real pin
#define LOADCELL_LEFT_SCK_PIN   3  // Example pin, update with real pin
#define LOADCELL_RIGHT_DOUT_PIN 4  // Example pin, update with real pin
#define LOADCELL_RIGHT_SCK_PIN  5  // Example pin, update with real pin

// Initialize the load cells
void LoadCell::init() {
    // Begin communication with each load cell
    scale_left.begin(LOADCELL_LEFT_DOUT_PIN, LOADCELL_LEFT_SCK_PIN);
    scale_right.begin(LOADCELL_RIGHT_DOUT_PIN, LOADCELL_RIGHT_SCK_PIN);

    // Set the scale factor for each load cell
    // You will need to calibrate this value!
    scale_left.set_scale(2280.f);
    scale_right.set_scale(2280.f);

    // Zero the scale (tare) so current weight is treated as 0
    scale_left.tare();
    scale_right.tare();
}

// Read the load cells and return their combined weight
float LoadCell::update() {
    // Read the weight in units from each load cell
    float weight_left = scale_left.get_units();
    float weight_right = scale_right.get_units();

    // Return the total combined weight
    return weight_left + weight_right;
}
