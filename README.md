# mbed_CAN_SY202_LAB
CAN network of mbeds distributing a closed loop controller using a servo arm and a BNO055 IMU for controlling an angle. The topology can be used to demonstrate a cyber attack and acts as the basis for additional cyber physical systems labs.

SY202 mbed CAN bus example. Listener eavesdrops on the CAN bus traffic and sends to a serial terminal. Could be used to inject packets (CANMessage) on the bus to disrupt closed loop controller.

This apparatus was designed for a lab in the Weapons, Robotics, and Control Engineering Department at the US Naval Academy for teaching cyber physical systems. The components consist of a mechanical base and servo actuated arm comprised of Tetrix components, four mbed micro-controllers using a custom printed circuit board (PCB). The PCB provides power regulation, an MCP2551 / MCP2561 CAN transceiver IC and screw terminals for tying the CAN bus together, and external ports for interfacing additional peripheral devices.

https://youtu.be/1Udcn8rp8nM

The three primary mbeds create a closed loop controller for controlling the servo actuated arm using the BNO055 IMU to provide angular position feedback. The mbed reading the BNO055 data transmits the arm angle over the CAN network to the mbed running the code for the closed loop controller. The controller mbed then calculates a correction and transmits the new servo position to the mbed connected to the servo. The servo mbed reads the CAN packet and adjusts the servo output signal to drive the actuated arm to the commanded angle. A USB (virtual COM port) serial interface to the controller mbed allows the user to also adjust the desired set-point of the servo angle.

https://github.com/jebradshaw/mbed_CAN_Servo - mbed servo code

https://github.com/jebradshaw/mbed_CAN_controller - mbed controller code

https://github.com/jebradshaw/mbed_CAN_BNO055_20180208 - mbed IMU code using the BNO-055

The fourth mbed connected to the CAN network simulates a stealth device that can observe traffic on the CAN bus and inject packets which alter the behavior of the closed loop controller.

The PCB design was done using ExpressPCB.

![pcb_softwarelayout](https://user-images.githubusercontent.com/5246863/200646783-e05e1d85-7d8c-49e6-bd36-7074e70ee755.jpg)

![mbede_can_interface_board](https://user-images.githubusercontent.com/5246863/200646828-b1bed2e8-5fdf-49e9-a73a-dbf0180f95be.jpg)

IEEE Conference Paper 2018

https://pdfs.semanticscholar.org/ed6c/8beb25762b597f48f59022b88f7dc22198e5.pdf
