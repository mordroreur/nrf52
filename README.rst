.. _peripheral_hr:

Key-Finder
########################

Overview
********

Project in objective to create a working code of key-finder.


Requirements
************

* BlueZ running on the host, or
* A board with BLE support

Building and Running
********************

Using Visual Studio code with the nrf extension, you can run the project.

Uses
********************

When launched, the card is named "Math Test" (the name can be changed in the prj.conf file). The service with the UUID 0x1401 contains two important elements:

 -   The UUID 0x1404 in notify mode signals when the button is pressed.
 -   The UUID 0x1405 in write mode, when the sent signal is greater than 0x80 (equals 124), lights up Led 1.


Limitations
********************

The objective is not only to light up LED 1 but also to generate some noise with a buzzer when it receives a high value. However, this functionality is not implemented yet because I am currently unable to use an output from the card as a PWM (Pulse Width Modulation) output.

Origin
********************

This code was entirely created by me, drawing significant inspiration and guidance from the Git repository: "https://github.com/nrfconnect/sdk-zephyr/blob/v2.7.99-ncs1-1/samples/basic/".
