# Read Me file for understanding how to use the Buggy.

## Functionality of the Buggy. 
The Buggy has 3 main forms forms of interaction; a remote mode where the buggy can be controlled by the user through Bluetooth/WiFi/IR commands, an autonomous mode where the buggy is commanded by the user to roam freely without colliding into obstacles and a measuring mode where the buggy will move around autonomously but will take temperature and water level reading when it stops due to an obstacle. 

There are 4 methods of controlling the buggy:
* IR Remote
* Bluetooth LE
* WiFi
* Direclty through the PC serial monitor. 

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

## How to control the buggy using Bluetooth low energy (BLE).
When the Bluetooth code has been uploaded to the ESP32 you can connect an android device only (IOS does not support BLE).
By going into the android device settings, "ESP32test" will be able to be paired with the device. 

![Screenshot_20201210-120007](https://user-images.githubusercontent.com/72760747/101770647-a4637980-3ae0-11eb-90b3-c1a65112bd18.png)

Then using the below Serial Bluetooth terminal, the ESP32 can be set up as a device and connected to the ESP32.

![Screenshot_20201210-121122](https://user-images.githubusercontent.com/72760747/101771232-82b6c200-3ae1-11eb-865b-3e0780de6e02.png)
![Screenshot_20201210-121352](https://user-images.githubusercontent.com/72760747/101771226-80546800-3ae1-11eb-917f-7aa7951a4917.png)

As you can see in the bluetooth terminal there are hot keys provided. Like the IR remote the number "3" will move the buggy at full speed and the hotkey "stop" will stop the buggy. 

![Screenshot_20201210-121931](https://user-images.githubusercontent.com/72760747/101771703-4041b500-3ae2-11eb-9962-0ce28e43cd8e.png)

To allow the buggy to roam autonomously and roam autonomously while taking temperature, humidity and water level measurements, "E" and "M" can be sent to the terminal respectively. To stop the buggy roaming autonomously just press the "stop" hotkey.

![Screenshot_20201210-122609](https://user-images.githubusercontent.com/72760747/101772454-48e6bb00-3ae3-11eb-9699-0c3f66796c41.png)
![Screenshot_20201210-122649](https://user-images.githubusercontent.com/72760747/101772429-42f0da00-3ae3-11eb-8097-cd1bd1506f4e.png)

As you can see the buggy will do an initial assessment of its surroundings and checks the distance in front of it (Cdist), to the left of it (Ldist) and to the right of it (Rdist). It will then choose which is greatest and move in that direction. It will then stream the distance it has until its next obstacle. When the distance is under 30cm it will stop and reasses it's surroundings to find the greatest clearance. 

You can also request a temperature/humidity or water level reading in the remote control setup by sending "T" and "W" respectively. 

## Using WiFi to controll the buggy. 
The ESP32 needs to be programmed in either the Blynk method which is highly customizable or by using a standard WiFi connection which controls the buggy using a WiFi terminal. (These are IOS friendly).
### Blynk
Blynk is a app which is extremely user friendly! It is highly customizable and relatively simple to use. 


### Standard 


## Using the Serial monitor to control the buggy.

## Security features
 

