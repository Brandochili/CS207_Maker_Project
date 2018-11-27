# CS207_Maker_Project

The project being designed for CS207 is a touchscreen jukebox.

This jukebox runs a free and open source software called Volumio. The jukebox is being run by a combination of a Raspberry Pi and Arduino to do the music and software proccessing and LED lightshow control. The Raspberry Pi will run Volumio and the touchscreen to interface with the music sources. The output will go to an amplifier and the Arduino Uno which will use the incoming oltage signal from the Raspberry Pi to control some NeoPixel digitally controlable LEDs.


Bill of Materials:
- 1 x Raspberry Pi B
- 1 x Arduino Uno
- 1 x Amplifier()
- 2 x speakers
- 1 x Adafruit NeoPixel 1 meter strip
- 1 x 12 volt switching power supply
- 1 x 19 volt laptop power supply
- 1 x Justboom Stereo DAC
- 1 x Raspberry Pi Official Touchscreen
- 1 x Old Computer Power Supply
- 1 x Volumio Software Installed on Micro SD Card and Volumio Account
- 1 x PTFE clear 1/2 outer diameter tubing
- 1 x 4ft by 2ft sheet of 3/4 inch thick plywood
- 1 x 4ft by 2ft sheet of 1/4 inch thick plywood
- 1 x box of 1 inch screws
- 1 x box of 3/4 inch screws
- 1 x box of 1 1/4 inch screws
- 1 x 12 ft of wiring for the LEDs
- 1 x 1000uF Capacitor
- 1 x 12v to 5v stepdown module
- 1 x 12v to 5v USB stepdown module with USB outputs
- 1 x 560 Ohm resistor
- 1 x 6ft of speaker wire
- 1 x USB drive for storing music
- 1 x 1ft by 96 inch role of walnut veneer (optional)
- 1 x 3ft by 1.5ft panel of solid walnut (optional)
- a woodworking shop and fine woodworking tools (optional)


The Build Instructions:

A huge portion of this poject is woodworking. I understand that the techniques used in this project are more advanced than a lot of people would like to take on but it doesnt have to be complicated. You can simply make a plywood box and paint it or find an already built box and modify it to meet the needs of this project.

Lets start with the software:
Go to www.volumio.com and download the software package from the download tab of the website. Select the Raspberry Pi code choise as this is what we will be using for this project. Once downloaded, using a flashing software, fsh the volumio software onto a 8gb micro SD card. Once complete, the SD card can be plugged into the Raspberry Pi (RPi). Before you power on the RPi, make a volumio account. A bonus feature you get from a volumio account is the ability to cloud save your volumio device settings for poweroutages. Don't power the RPi on at this point.

Next lets look at installing the RPi Official Touchscreen:
There is an excelent video on youtube demonstrating how to do this. The link is here: https://www.youtube.com/watch?v=tK-w-wDvRTg
Please note that for this project, we will use the dual micro USB cable method of powering the devices. Don't apply power yet.

First bootup:
before you boot up the RPi, download the volumio app from the App Store or the Play Store or have an internet browser open. Plug an ethernet cable into the RPi for internet and apply power to the RPi. Volumio is not set up to stream to the touchscreen so you will only get lines of code. Use the app to automatically find the RPi or find the IP address on the touchscreen and enter that into your browser. You will now be able to control the RPi volumio system. Go to plugins and download the Raspberry Pi Official Touchscreen plugin (it may take quite a while so let it instll fully) and then enable it. Using the app or browser, restart the RPi in settings tab and when the RPi restarts, volumio should now be on the touchscreen! If it doesnt, go back to re-flashing the micro SD card and start over.

Lets talk about the Arduino and NeoPixel circuitry now:
The Arduino Uno can't supply enough power to power all of the LEDs so we will need to power the LEDs seperately. To do this, we will use a 12 volt switching power supply. The circuitry diagram can be seen below but here is a discription of what is going on. The positive and negative (ground) wire from the power supply will  be wired to a 12v to 5v stepdown module and then soldered onto a proto board. They will first go through a 1000uF capacitor to smooth out the voltage to protect the LEDs. From the capacitor, the positive end will be connected to the 5V input on the LED strip and the ground will be connected to the ground on the LED strip. The ground wil also go to one of the ground pins on the Arduino as the LED strip must be grounded to the Arduino as well (Do not connect the positive to the Arduino). The digital control lead from the LED strip will be connected to pin 6 on the Arduino with a 560 Ohm resistor in line to make sure that the signal stays smooth. Now that the LEDs and Arduino are connected, let move on!

Connecting the Arduino to the Raspberry Pi:
This is fairly simple. If using the headphone jack from the RPi for your music output, simply cut an old heaphone cable at one end to expose the left, right and ground wires. Plug a AUX splitter into the RPi and plug the cut headphone calbe into the splitter. Now plug either the left or right channel into the Arduino's A0 pin and th ground into the Arduino's ground pin. Plug the Arduino into the RPi using the USB cable.





Updates for CS 207 Project to come.

October 28th: All electronic components needed for this build have been ordered from various websites. The Sure Electronics AA-AB32174 2x50W TDA7492 Class-D Amplifier Board was chosen for the amplifier as it is a good quality unit that comes at a good price. Two 3.5 inch Dayton Audio Midrange woofers were used for the sound output for the jukebox as they have great bass response for the price and punch way about their weight class. The JustBoom stero DAC was used  to improve the sound quality being output from the Raspberry Pi. The official Raspberry Pi touchscreen was used as it has a wel established functionality with the Raspberry Pi and Volumio which is very important as Volumio is meant to be a cloud based service rather than a 'same machine' screen service. This device will have a more finished look than the general 'maker' theme as it will be used by many people and will hopefully end up being a showpiece. It will be made out of walnut and bloodwood.

October 29th: The basic framing for the LED light show coding has been taken from the Youtuber Robert Robert who made an excelent Neopixel based LED lightshow tht is music responsive. A basic explanation as to how the code works. The arduino pulls in 50ms of music sample from an auto gain adjustment microphone and through a combination of eqations, assigns the incoming voltage samples to a number from 0 to 11. A seriese of 'if' statements is then used to 'ick' and run a LED lightshow function. For exmple, if the number is 0, a rainbow effect is run. If the nuber is 4, an old style movie theatre lightshow is displayed. This code repeats on a loop and when no music is playing, the rainbow fucntion is run.

November 1st - Coding challenges:
Seeing as the code framework used for this build was designed around an auto gain adjustment microphone, a new equation had to be used to balance out the voltage readings coming in from the audio source (a headphone cable connected directly to the Arduino's ground and A0 pin). A microphone was not used for this projct as it was decided that the jukebox LEDs should only respond to the music from the jukebox and not outside noices and voices. The problem then arizes that the voltage can heavily range with volume. The detected ranges for voltage were 0 to 500. Therefore, a modulus divide equation was used to make sure that the LEDs function properly for any volume level.

November 4th - 
