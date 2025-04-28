# Software-Onboarding-Luna-PID
PID Controller
Difficulty: 1

This project will serve as the initial onboarding step for the Autonomy subteam. 
Prerequisites: Python

PID (proportional, integral, derivative) controllers are used throughout the robot. Notable places include controlling the wheel speed while driving at a constant velocity and controlling excavation speed of the robot. For more information, take a look at this introduction to PID or the wikipedia article. Take a look at this video for an example of it being tuned.
In short, the controller aims to minimize the error in a system with three values: Kp, Ki, and Kd. Once again, I direct you to the introduction to PID linked above. 
At the end of this project, you will have written a PID controller, tested, and tuned it on a real world system. 

You will write this code outside of the robot system, so you can learn the fundamentals first. 

This is a general set of steps as to what will need to happen. This does not cover every detail. If you get stuck, please ask for help. We encourage working together! Also, don’t be shy to ask the leads. We don’t bite!
Please download this simple simulation. We have a more advanced one for the whole robot, as well as the actual robot, but those are… messy. This simulation will let you focus on the PID controller instead of making a useful sim. 
You will need pygame. Ask for help if you don’t know how to do this. 
There are a set of values in a large comment block that says TUNE THESE. These are your PID values. You will eventually tune them for best results with your PID loop.
You can write your PID controller wherever you would like, although it’s probably best to initialize it by the “Write your PID controller here” comment.
Finally, there is a comment “Set your speed here” that is where you will set the speed of the object to the output of your PID controller, given the input of the position.
“speed” is the speed variable
“pos” is the position variable
There shouldn’t be anything else that you need to touch in this sim. 
You will need to write a PID controller. It’ll probably be easiest to make it into a class. If you don’t have experience with python classes, take a quick look over this guide. 
Required functions
Ability to set a setpoint (can be only at startup, but would ideally be able to be changed at any time)
Ability to set values for each of Kp, Ki, and Kd (can be only at startup). 
Control function that takes in the current value and produces a PID output based on the PID terms set earlier
Optional but nice-to-have
Ability to limit output to within a certain range. If the robot can’t travel at the speed of light (and it can’t, last I checked), there’s no point in having the controller tell it to. 
If you get stuck, make sure you take a look at the guide linked above. It is really quite useful… Or ask your teammates! 
Once you’ve written your PID controller, put your control function [in location]. It’s now time to tune your values until they work. The Wikipedia guide to tuning is weirdly non-technical. You want the red ball to go to the green line and stop right on it, without overshooting or slowing down too much before getting there. 
In short, increase your Kp term until you get there as fast as you want (and possibly begin to oscillate). Then, increase your Kd to slow down the approach and remove oscillation. If you have steady-state error (your final position is not equal to the target), then increase Ki to account for this.
Quite frequently, just the Kp term is enough for many applications.
Once this works, try enabling random noise to see how well your controller performs. Set noise_enabled near the top to True. 
If your controller still looks good, you should be complete with this project! If you haven’t yet, show one of the leads what you’ve made.

Next steps:
Haven’t done the Load Cell project? Try that! It’s the onboarding project for the firmware side of software. 
Already done Load Cell or just have your heart dead-set on autonomy? Try out one of the other projects that looks interesting!
