# Read Me file for understanding how to use the Buggy.

## Functionality of the Buggy. 
The Buggy has 3 main forms forms of interaction; a remote mode where the buggy can be controlled by the user through Bluetooth/WiFi/IR commands, an autonomous mode where the buggy is commanded by the user to roam freely without colliding into obstacles and a measuring mode where the buggy will move around autonomously but will take temperature and water level reading when it stops due to an obstacle. 

## How to use the IR Remote. 
The IR remote is the most simple way of interacting with the buggy.

![IMG_1905](https://user-images.githubusercontent.com/72760747/101768046-0326f400-3add-11eb-893b-139e595ca14c.JPG)

The function each button has is as follows:  
* 1 - Move the buggy farwards slowly.
* 2 - Move the buggy forwards 
* 3 or up arrow - Move the buggy forwards at maximum speed. 
* down arrow - Reverse the buggy
* ok - Stop the buggy
* Left arrow - Rotates the buggy left
* Right arrow - rotates the buggy right
* \* - take a temperature reading and display it on the LCD screen
* \# - Stops the buggy before taking a water level reading. 

## How to control the bugy using Bluetooth low energy (BLE).
When the Bluetooth code has been uploaded to the ESP32 you can connect an android device only (IOS does not support BLE).
By going into the android device settings, "ESP32test" will be able to be paired with the device. 

