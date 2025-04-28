#pragma once
#include <HX711.h>  // Include HX711 library for load cell communication

// Define LoadCell class
class LoadCell {
public:
    // Initialize the load cell hardware
    void init();

    // Read and return the combined weight from both load cells
    float update();

private:
    HX711 scale_left;   // HX711 object for the left load cell
    HX711 scale_right;  // HX711 object for the right load cell
};
