# FABS

Force-Based Acceleration Braking System (FABS)  

OVERVIEW 

The field of automobile and automation have seen tremendous growth in the past few years. 
Many classical features in vintage automobiles have been replaced by the innovative ones which 
have helped driving become easy and safe. 
But still, the world is stuck with the mechanical accelerator and brake pedals. As they are 
mechanical in nature they carry the risk of mechanical failure, Also some objects, like a bottle, 
shoe etc, may get stuck under the pedal thereby blocking the pedal. These may lead to many 
accidents. 
Taking a step towards innovation, the mechanical pedals can be replaced by electric pedals. The 
mechanical gear system can be replaced by programmable weight sensors where the pedal 
action is achieved by applying a variable amount of force applied on the sensor.  
These sensors can also be placed on the steering wheels where the force is applied by the 
palms, especially for differently abled people. 

PROJECT DESCRIPTION 

In this project weight sensors are used to replicate the action of mechanical pedals. There are 2 
Arduinos. One to control the motors of the vehicle and other to get inputs from the weight 
sensors. This data is transferred through Bluetooth modules.  
There are four additional different modes available. Each mode has a different scaling factor for 
acceleration and braking. This mode is also shown on the serial monitor on the vehicle so that 
the neighbouring automobiles are aware of the mode the vehicle is in. The following is the 
description for each mode: 
 
● Traffic : Less Acceleration, Faster Braking.
● Highway : More Acceleration, Faster Braking.
● Learner : Slower Acceleration with a limit, Faster Braking.
● Rain    : Normal Acceleration with a limit, Medium Braking so the vehicle doesn’t skid. 
 
COMPONENTS :

The list of components used in the project is as follows: 
1. 2 x Weight Sensors HX711 
2. 2 x Arduino UNO/Nano 
3. 2 x Bluetooth Module HC-05
4. Motors 300 RPM
5. Motor Driver
6. Chassis, Wheels, Castor Wheel 
7. Serial LED Monitor 
8. Breadboards and Jumper Wires 
9. LEDs 
10. Toggle Switches   
11. Batteries 

