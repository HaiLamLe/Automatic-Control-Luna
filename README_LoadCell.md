Load cells
Difficulty: 1 

This project will serve as the initial onboarding project for the Firmware subteam. 
Prerequisites: C++, Github

On the robot, we have a pair of load cells underneath the main deposition bucket. Their purpose was supposed to be to let us know when the robot was full, allowing it to autonomously know when to stop digging and when the time comes to deposit. However, the code for them was never finished. 
At the end of this project, you should have integrated a feature that adds the combined load cell total to the robot’s “sensors” message. 

You will not need to write all the code from scratch. The HX711 Arduino library will be of great use. The library is already included in the main robot code; you can just include it. 

This is a general set of steps as to what will need to happen. This does not cover every detail. If you get stuck, please ask for help. We encourage working together! Also, don’t be shy to ask the leads. We don’t bite!
Create a new github branch based off “feature/behavior” titled “onboarding/username-load-cell” where username is some identifier for you (first initial last name, first name last name, last name, first name last initial, something else?) 
If you receive an error, you may need to be added to the github team. Let one of the leads know and we can help you out. 
The load cells are plugged into our “Teensy” (similar to an arduino), which handles all of our firmware code. We need to communicate this data to our “Jetson” (similar to a raspberry pi), the main robot computer. On a high level, you will need to add a “load_cell::update” function to the “send” function in the teensy_main.ino file. 
As an argument, provide state.load_cell_weight. 
This function is a member of a class that you will define in interfaces.hpp. Reference the AMT13_Angle_Bus code, as it’s pretty similar to what you will need to do. You may need to add another function to initialize the load cells (perhaps titled “init”?).
Once you set up your class, it’s time to actually write the load cell code. In the interfaces.cpp file, add your functions and fill them with code. You can reference the read_enc function, although they do slightly different things at this point. The HX711 documentation will be more useful. Make sure to add both load cell values to get the total weight on the system. 
If you have your “scale” objects in a list/array, then you will need to initialize that array in this file as well. Take a look at how the AMT13_Angle_Bus::encs is initialized for an example on how to do this. 
If you used an init function, add it in the “setup” function of teensy_main.ino
Now that the actual code is written, you need to edit the message that’s being sent from the Teensy to the Jetson to add a new data value. Remember that “state.load_cell_weight”? You need to create that. In the RobotMsgs.proto file, add a new line to the end of the sensor message. This must be titled the same as your argument from part 2a. Following this guide, that would be “load_cell_weight”. The data type is a float. 
In theory there is an autogenerator you can run, but I haven’t been able to get it working. If you find this process annoying enough, maybe your next project can be the NanoPB autogenerator :)? In RobotMsgs.pb.h, add your “load_cell_weight” to the end of the sensors struct. Add an extra zero to the RobotSensors_init_default and to RobotSensors_init_zero. Add an extra #define to the large block, following the existing examples. Add another line to the #define RobotSensors_FIELDLIST(X, a). Watch out for the slash at the end of every line except the last one…
Congratulations! Your code should now work! In theory… If you haven’t already you’ll need to install the arduino-cli compiler. Instructions on how to install are located on the arduino website. 
Compile your code. The command is provided in the next line. If you’re unfamiliar with using the command line, come and ask one of the leads. 
arduino-cli compile --build-path build --libraries lib --fqbn teensy:avr:teensy41:usb=rawhid teensy_main.ino
If your code compiles, excellent! Let one of the leads know and we can test it on real hardware. If it doesn’t, try and fix whatever errors it spits out. Don’t be afraid to ask for help here, compilers (especially GCC) tend to give terrible error messages. 
This project should be complete! If you’re confused about anything you did or curious about how anything works, please ask! The robot is a big mess of things talking to other things and all doing stuff; the more of it you understand the more useful you will be to the team! 
