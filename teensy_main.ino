// Snippets of Teensy
#include "interfaces.hpp"  // Include the LoadCell interface

LoadCell load_cell;  // Create a global LoadCell object

void setup() {
    // Other setup code...

    load_cell.init();  // Initialize load cells during setup
}

void send() {
    // Other sensor updates...

    // Update load cell reading and assign it to the outgoing sensor message
    state.load_cell_weight = load_cell.update();
}
