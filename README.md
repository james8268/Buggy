# Buggy

This file contains the necessary information on how the buggy works in a remote bluetooth non-autonomous mode.

The bluetooth device is an ESP32 and talkes to the mega board through the RX serial pin. Using an android device with bluetooth low energy (BLE) can be use to control the motion of the buggy.

GETTING STARTED

1. plug the buggy into the mains using the power cable provided. The power connection port is located on the Arduino Mega. The red LED should light up on the ESP32.

2. connect the bluetooth device bu clicking the two facing plugs on the top right coner of the android device using the serial bluetooth terminal app provided. If the connection times out press and hold the EN button on the ESP32 for 5 seconds and then try to reconnect.

3. The following commands can be used to move the buggy. The buggy has a 3 power speed system, If "1" is entered into the terminal the buggy will move forwards slowly, "2" will move the buggy forwards at 75% speed and "3" will move the buggy forwards at full speed. "b" will reverse the buggy, "r" will rotate the buggy right by approx 90 degrees, "l" will rotate the buggy left approx 90 degrees and "h" will stop the vehicle. The terminal is already pre-programmed with hotkeys to make life easier. 



Test 1 remarks: The device worked exactly how it should every command button worked as it should. They controls were very easy to understand and get to grips with which means i coukd use the buggy how i wanted with no issues. Only thing i would like to add is the the left and right turns count be a little less agressive. So instead of a 90 degree turn maybe a 45 instead. Also i would like the distance of the sensor to be disblayed on the bluetooth device as well as the lcd screen on the buggy so i dont have to be stood directly over the buggy to know this information, as i think this would make it more user friendly. Other than that it was flawless.
