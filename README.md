Problem Statement :-

The robotic arm shall be operated remotely using wireless communications with no time delay. The robotic arm is expected to perform a set of intricate operations.
The tasks include:
1. Picking up a cache and traversing to the panel. Cache will have a handle at least 10 cm long and not more than 5 cm in diameter. Cache will weigh less than 5 kg.
2. Open a drawer, to place the cache inside it and close the drawer.
3. Push buttons, flip switches, turn knobs.
4. Operate a joystick.
5. Undo latches.
6. Open panels.

The Solution :-

The programming was done in such a way that the 'Robotic Arm' is controlled by a Wireless Glove. The Wireless Glove trasmits the values trigerred by the change of its angular position and finger movements(in the glove) which are then recieved by the Robotic Arm to move as per the requirement of various tasks.

There were a total of 3 teams which contributed toward the completion of this project.
1. Mechanical Team - To build the basic structure of the Robotic Arm including the assembly of parts.
2. Electrical Team - To create PCB's for the project and connecting/make circuits as per the model and code.
3. Coding Team - To program the working of all the various devices and modules and to make sure that they work in syncronization.


Hardware Used :-

1. Transmission:-
    ->  nrf24l01 wireless module x2 (transceiver module)
    ->  MPU-6050 x2
    ->  Flex sensors x2
    ->  Arduino NANO    

2. Recieve:- 
    ->  Servo Gripper Mini Motor (AC SG90 Servo Motor x2 For both axis)
    ->  Firgelli Linear Actuator
    ->  Hydraulic Linear Actuator (Large)
    ->  Power Window Motor
    ->  Arduino Mega


The concept behind the Robotic Arm is as follows:-

    ->  Power Window Motor will be used to rotate the whole arm from the base.

    ->  Hydraulic Linear Actuator (Large) will be used to move the arm in y-axis.(no requirement in x-axis as the base is fixed)

    ->  Firgelli Linear Actuator will be used for the movement of the gripper arm in y-axis.

    ->  Servo Gripper Mini Motor used for precisely picking or poking, one servo at the base to rotate the gripper 360 degrees other servo to control the grasping motion of the gripper.


    ->  MPU-6050 x2 = MPU-6050 (1) is placed on the arm-region (facing upward) next to where the Arduino NANO will be placed, whereas MPU-6050 (2) is placed on the wrist-region, it is done so, so that there can the value of y-axis due to wrist movement is unique only to the second MPU-6050 (2). 

    ->  MPU-6050 (1) is used as its value will change in accordance with the Wireless Glove, we input its value of x-axis and y-axis in a specified range (keeping a margin of error) to determine the movement of the  Hydraulic Linear Actuator (Large)  and  Power Window Motor  respectively.

    ->  Flex sensors will be used to control the Gripper entirely, the input of one flex sensor (1) in a certain range (with margin of error) will be used to get the  Firgelli Linear Actuator  at the base of the Gripper to function  and  the other flex sensor (2) in a certain range (with margin of error) will be used to get the Servo Motor to function which monitors the grasping and relaxing motion of the gripper.

    ->  MPU-6050 (2) will be used in controlling the rotation of Servo Motor at the base of the Gripper within a certain range of the value of y-axis (with margin of error).  

    ->  nrf24l01 wireless module will be used to transfer all the values from  Wireless Glove  as well as  to recieve all the values in the Robotic Arm (transceiver module). It will only be required to confire the device once for its working.


Connections to:-
     Arduino NANO
    ->  nrf24l01 wireless module x1 (transceiver module)
    ->  MPU-6050 x2
    ->  Flex sensors x2
     Arduino Mega
    ->  Servo Gripper Mini Motor (AC SG90 Servo Motor x2 For both axis)
    ->  Firgelli Linear Actuator
    ->  Hydraulic Linear Actuator (Large)
    ->  Power Window Motor