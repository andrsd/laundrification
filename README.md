# Description

Send a notification when laundry is done

# Details

This assumes that your washing machine has some kind of visual indication that the cycle finished - ideally an LED or so.

You will need:

* [Arduino MKR1000](https://store.arduino.cc/usa/arduino-mkr1000)
* One photoresistor connected to analog pin 0
* [IFTTT](https://ifttt.com/)'s webhooks channel activated

## Photoresistor

I used Sunkee GM5539 photoresister. See [tutorial](https://learn.adafruit.com/photocells) to learn how to connect
it to the Arduino.

## Setup IFTTT

* Log in to your account or create one if you do not have it yet.
* Activate webhooks service if you did not do so yet..
  You will need the key from it later when programming the Arduino.
* Create a new applet by clicking __My Applets | New Applet__
* Select __Webhooks__ for service and select __Receive a web request__
* Enter `washing_machine_done` for __event name__ and click __Create trigger__
* Select __Notification__ for action service and select __Send a notification from the IFTTT app__
* Enter `Washing machine finished` for __notification__ and click __Create action__
* Click __Finish__

## Setup Arduino

* Run the configure script
  - Enter the name of your wifi network
  - Also its password
  - Webhook service key from IFTTT
* Connect your MKR1000
* Compile and upload (Arduino IDE should work)
* Attach the photocell to the LED indication on your washing machine
  - I cover the cell with duct tape so no residual light can get to it, for example if somebody turns the light on in the laundry room.
* Power the Arduino


# Customization

* To change the pin to which the sensor is connected, update the value of `PHOTOCELL_PIN` variable.
* You can change the event name to what ever you want, but you will also need to change in the source file.
  The event name is stored in `WASHING_MACHINE_DONE` variable and you will need to use the same name in the
  IFTTT applet.

# More...

You could probably open the washing machine and connect to its LED wires directly. I did not do that to not void
the warranty and because I just wanted an non-intrusive solution.

If you are experiencing problems, the code sends debug messages on serial port which you can read via Arduino IDE.

[![License](http://img.shields.io/:license-mit-blue.svg?style=flat-square)](https://andrsd.mit-license.org/)
