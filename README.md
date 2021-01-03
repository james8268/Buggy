# Read Me file for understanding how to use the Buggy.

## Functionality of the Buggy. 
The Buggy has 3 main forms forms of interaction; a remote mode where the buggy can be controlled by the user through Bluetooth/WiFi/IR commands, an autonomous mode where the buggy is commanded by the user to roam freely without colliding into obstacles and a measuring mode where the buggy will move around autonomously but will take temperature and water level reading when it stops due to an obstacle. 

There are 4 methods of controlling the buggy:
* IR Remote
* Bluetooth LE
* WiFi
* Direclty through the PC serial monitor. 


## Getting started. 
When using any method of control, when then buggy is powered up it will request the user to present the correct RFID tag/card to the scanner. If the user does not present the correct RFID tag/card then access to the buggy will be denied. In order to be able to use the buggy the RFID tag/card must be presented. 

![IMG_0766](https://user-images.githubusercontent.com/72760747/103211738-e5d98e80-4900-11eb-82b6-94415f369119.JPG)
![IMG_0767](https://user-images.githubusercontent.com/72760747/103211737-e540f800-4900-11eb-8acf-1b2dc2e1cc09.JPG)
![IMG_0768](https://user-images.githubusercontent.com/72760747/103211741-e5d98e80-4900-11eb-806f-392114accec2.JPG)

Once access is granted the user can then control the buggy by any of the control methods. 

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
### BLYNK_WiFi
Blynk is a app which is extremely user friendly! It is highly customizable as you can add joy stick, buttons, sliders and much more. 
When the ESP32 is connecting/connected to your network and to the Blynk server it will display a message when connected to the serial port.

![IMG_1920](https://user-images.githubusercontent.com/72760747/101788748-5eb2ab00-3af8-11eb-98f7-084cdad63003.jpg)
![untitled](https://user-images.githubusercontent.com/72760747/101782557-104dde00-3af1-11eb-9f34-b276a4610234.PNG)

In the Blynk App we can insert a terminal which allows us to control the buggy. Unlike the the bluetooth terminal this does not have hotkeys which means you need to know the directory for how to control the buggy. Which is as follows:
* 3 -Will move the buggy forwards at full speed.
* 2 -will move the buggy forwards
* 1 -will move the buggy forwards slowly
* h -will stop the buggy (Halt)
* b -will reverse the buggy
* l -will rotate the buggy left approximately 50 degrees
* r -will rotate the buggy right approximately 50 degrees
* E -will allow the buggy to roam freely while avoiding ibstacles
* M -will allow the buggy to roam freely will avoiding obstacles and taking temperature, humidity and water level measurements. 
* T -will measure and instant temperature reading
* W -will stop the buggy moving if it is moving and will take a water sensor reading. 

As you can see below it is similar to the bluetooth terminal, just without the hotkeys. 

![IMG_1909](https://user-images.githubusercontent.com/72760747/101783709-7be47b00-3af2-11eb-8d51-f76a57e8f98d.PNG)
![IMG_1910](https://user-images.githubusercontent.com/72760747/101783714-7dae3e80-3af2-11eb-99c2-4978b0398639.PNG)
![IMG_1912](https://user-images.githubusercontent.com/72760747/101783720-7f780200-3af2-11eb-8ea8-3b93eff591be.PNG)


### Standard (Standard_WiFi)
The standard method of using WiFi is very similar but requires a few more steps. 
When the ESP32 Connects to the network and server a message will be displayed in the serial monitor.

![IMG_1913](https://user-images.githubusercontent.com/72760747/101788097-ab49b680-3af7-11eb-8f51-8b0bf3874c48.jpg)
![Untitled1](https://user-images.githubusercontent.com/72760747/101788409-f82d8d00-3af7-11eb-94ab-6365d715e3f8.png)

Using the WiFi serial app, input your IP address displayed in the serial monitor along with the port number which is set to 80. 

![IMG_1914](https://user-images.githubusercontent.com/72760747/101788099-abe24d00-3af7-11eb-8f63-c1130171121e.jpg)

This will then connect you to the ESP32 network and allow you to control the buggy. The top window is when your input commands for the buggy and the bottom window is the feedback which is sent to you. Be warned this specific app has no auto scroll function, so as soon as the feedback window is full you need to clear it by pressing the bin at the bottom. 

![IMG_1915](https://user-images.githubusercontent.com/72760747/101788102-abe24d00-3af7-11eb-898e-7ba4500835d2.jpg)
![IMG_1916](https://user-images.githubusercontent.com/72760747/101788104-ac7ae380-3af7-11eb-9076-5da1e6dde6b9.jpg)
![IMG_1917](https://user-images.githubusercontent.com/72760747/101788105-ac7ae380-3af7-11eb-9a13-57c5e47213c5.jpg)


## Using the Serial monitor to control the buggy.
This method has limitations, for example the buggy must stay plugged into the laptop/PC so limites mobility. However an ESP32 device is not required so there are no connection issues. This method is very useful for running quick tests to see how the buggy operates without having to leave your chair, you can just prop the buggy up to remove contact between the wheels and the floor. 

Some functions are limited also, Roaming autonomously is not recomended as the board has to be manually reset with the reset button on the arduino board. 


You can see below when commands are sent through the command line in the serial monitor window you will still recieve the feedback from the buggy. 

![BR](https://user-images.githubusercontent.com/72760747/101795452-d46e4500-3aff-11eb-9f1e-d3437bd7e846.png)

![brr](https://user-images.githubusercontent.com/72760747/101795458-d59f7200-3aff-11eb-94ec-f4dd3080c1fe.png)

![brrr](https://user-images.githubusercontent.com/72760747/101795456-d59f7200-3aff-11eb-9194-fae3a5a11d4d.png)

![wt](https://user-images.githubusercontent.com/72760747/101796448-d71d6a00-3b00-11eb-8345-d3d821c7b2cb.png)


## Security features
 
Some security features have been added:
* RFID - The buggy requires a correct RFID tag to be presented before anything initially takes place and is also required when any form of autonomous mode is exited, this makes sure the user has visual confirmation of the buggy's loaction. 
* A tilt sensor- If the buggy tips over a tilt sensor will be activated. This will halt the buggy and sound a buzzer. This is activated when the buggy is in a remote or autonomous mode. A message will also be sent to the Bluetooth/WiFi terminal to notify the user.
* Red LED- if connection between Bluetooth/WiFi drops then the Red LED located on the front of the buggy will turn on, the buggy will stop and anything written on the LCD screen is cleared. 

