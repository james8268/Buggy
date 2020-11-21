# Buggy

#Section 1

This file contains the necessary information on how the buggy works in a remote bluetooth non-autonomous mode.

The bluetooth device is an ESP32 and talkes to the mega board through the RX serial pin. Using an android device with bluetooth low energy (BLE) can be use to control the motion of the buggy.

GETTING STARTED

1. plug the buggy into the mains using the power cable provided. The power connection port is located on the Arduino Mega. The red LED should light up on the ESP32.

2. connect the bluetooth device bu clicking the two facing plugs on the top right coner of the android device using the serial bluetooth terminal app provided. If the connection times out press and hold the EN button on the ESP32 for 5 seconds and then try to reconnect.

3. The following commands can be used to move the buggy. The buggy has a 3 power speed system, If "1" is entered into the terminal the buggy will move forwards slowly, "2" will move the buggy forwards at 75% speed and "3" will move the buggy forwards at full speed. "b" will reverse the buggy, "r" will rotate the buggy right by approx 90 degrees, "l" will rotate the buggy left approx 90 degrees and "h" will stop the vehicle. The terminal is already pre-programmed with hotkeys to make life easier. 



Test 1, getting to gribs with the bluetooth, 28/10/2020: The device worked exactly how it should every command button worked as it should. They controls were very easy to understand and get to grips with which means i coukd use the buggy how i wanted with no issues. Only thing i would like to add is the the left and right turns count be a little less agressive. So instead of a 90 degree turn maybe a 4 instead. Also i would like the distance of the sensor to be disblayed on the bluetooth device as well as the lcd screen on the buggy so i dont have to be stood directly over the buggy to know this information, as i think this would make it more user friendly. Other than that it was flawless./



#Section 2

This test is similar to the last with a few miner changes. This time around the buggy is in a combined remote bluetooth and autonomous mode. The autonomous element will allow the buggy to roam freely while avoiding obstacles. When a transmission is send from the bluetooth terminal then the buggy will perform the command and then return to roaming autonomously. 

Acting on the previous test a feature of being able to see the reading of the ultrasound sensor has now been added and can be viewed in the bluetooth terminal aswell as the turns being less harsh.

Test 2, using the combined autonomous and bluetooth mode, 04/11/2020: self roaming was effective, the buggy avoided obsticals well, although had trouble once it was under a certain distance from complex obsticals. commands were easy to pick up and the buggy was easy to manouver, although lag time could be reduced, or possibly a cut off after x number of comands. possibly introduce a short cut to speed one and/or options for varing stop times, so that when flustered a driver can take time to re-think.

Test 3, test is the same as previous (code remains the same as the last test), 05/11/2020: the buggy avoided the obsticals well however due to lag it made it difficult to manouver,also would be much easier and efficent for the driver if there was a cut off command so that the user can re asses the situation and move from there.  



#section 3

The buggy now has the ability to roam around autonomously while avoiding obstacles and this can then be stopped and a remote mode can be used. its easy to switch between the two, using the bluetooth terminal the "roam" hotkey enters the buggy into an autonomous mode(which can be seen when the android device is tilted on a landscape view and the screen will show more potential hotkeys). when any button/command is used in the bluetooth terminal is then exits the autonomous mode and reverts to a remote mode. 


Test 4, testing combined autonomous and remote modes, 07/11/2020: I enjoyed the new features on the handset. The fact that the buggy now had a roam feature was very interesting. The fact it could now make decisions on what was infront of it and change the course on which it was travelling due to an object being in its way was fasinating. A a cool feature would be if it could decide which way it wanted to turn. For instance left or right depending on the amount of space it has to eaither side, this depends on the amount ultrasound sensors it has available. All the other buttons worked really well and did what I wanted when I asked it to. 



#Section 4

A tilt sensor and servo motor have now been added, the use of WiFi connection is also up and running. Security measures have been added so if wifi or bluetooth connection is lost it will stop the buggy and turn on the front red LED. The servo motor allows the buggy to look left and right and then make a decision on which direction to move. The tilt sensor will monitor the buggy and if it capsises or is flipped over it will stop the buggy and turn on a buzzer as well as notifying the user if in remote mode. 

tests to be completed:  *turning system for servo ultra sensor, just to check its working right. 
                        *tilt sensor while in roam and moving. 
                        *temp and humidity sensor and water sensor while moving and stationary.
                        *disconnect functions via bluetooth, by trying to connect another device (already known that two devices cant connect).
                        *disconnect vie WiFi, turn of router (also try to connect two devices). 
                        *test overall usability.
               
               
  
