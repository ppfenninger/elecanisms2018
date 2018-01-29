## Hardware Setup
You will need: 
A NO switch 
A breadboard
2 jumper cables
A 10k ohm resistor

Put the switch into the breadboard (so that the two ends are in different rows)
Attach a jumper cable from one end of the switch to D0 on the elecanisms board
Put the 10k resistor going from the other end of the switch to one of the rails on the breadboard
Connect that rail to Vdd on the elecanisms board with the other jumper cable

## Compiling/Loading Software
### These directions work in Ubuntu 16.04 and 14.04
You will need to have installed:
Python
Microchip’s Compiler Software
Scons 
PyUSB

You will also need to download the elecanisms2018 repository found here:
https://github.com/ppfenninger/elecanisms2018.git

1. Navigate to the “/elecanisms2018/blinkpoll” folder through your terminal window
2. Run the “scons” command. It should generate a .hex file of the code that will be used later.
3. Run the bootloadergui by typing “python ../elecanisms2018/bootloader/software/bootloadergui.py” into the command line.
4. The PIC24FJ USB bootloader interface should open
5. Press the reset button while pressing and holding the SW1 button on the elecanisms board
6. Press the Connect button on the bootloader interface
7. Go to File>ImportHex and use the pop-out window to choose the .hex file generated in step 2
8. Press the write button
9. Press the Disconnect/Run button

## Using blinkpoll
1. The program has 3 modes that determines which LED is blinking. In mode 1, LED1 blinks, in mode 2 LED2 blinks, and in mode 3, LED3 blinks. 
2. To turn on the other two LEDs (the ones that are not blinking) press and hold switches 2 or 3. 3. Each switch will turn on one of the two LEDs that is not blinking. The LEDs turn on when you hold the buttons down and turn off when you release the buttons. 
4. To change modes, press the button on the breadboard. The mode will then increase by 1. 
5. To change the mode multiple times, you have to keep pressing and then releasing the button (you cannot press and hold the button to cycle between modes).
The program starts in mode 2 (green LED blinking)

