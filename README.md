[![License](http://img.shields.io/:license-mit-blue.svg?style=flat-square)](https://andrsd.mit-license.org/)

# laundrification

Send a notification when laundry is done

# Details

This assumes that your washing machine has some kind of visual indication that the cycle finished - ideally an LED or so.

You will need:

* Arduino MKR1000
* One photocell connected to analog pin 0 (see [tutorial](https://learn.adafruit.com/photocells))
* Set up Maker channel from [IFTTT](https://ifttt.com/)
  - the name of the event is `washing_machine_done` but can be changed in the code

# How to use

* Run the configure script
  - Enter the name of your wifi network
  - Also its password
  - Maker channel key (get it from ifttt)
* Connect your MKR1000
* Compile and upload
* Attach the photocell to the LED indication on your washing machine
  - I cover the cell with duct tape so no residual light can get to it, for example if somebody turns the light on in the laundry room.
* Power the Arduino
* Enjoy
