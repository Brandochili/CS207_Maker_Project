# CS207_Maker_Project

The project being designed for CS207 is a touchscreen jukebox.

This jukebox runs a free and open source software called Volumio. The jukebox is being run by a combination of a Raspberry Pi and Arduino to do the music and software proccessing and LED lightshow control. The Raspberry Pi will run Volumio and the touchscreen to interface with the music sources. The output will go to an amplifier and the Arduino Uno which will use the incoming oltage signal from the Raspberry Pi to control some NeoPixel digitally controlable LEDs.


Updates for CS 207 Project to come.

October 28th: All electronic components needed for this build have been ordered from various websites. The Sure Electronics AA-AB32174 2x50W TDA7492 Class-D Amplifier Board was chosen for the amplifier as it is a good quality unit that comes at a good price. Two 3.5 inch Dayton Audio Midrange woofers were used for the sound output for the jukebox as they have great bass response for the price and punch way about their weight class. The JustBoom stero DAC was used  to improve the sound quality being output from the Raspberry Pi. The official Raspberry Pi touchscreen was used as it has a wel established functionality with the Raspberry Pi and Volumio which is very important as Volumio is meant to be a cloud based service rather than a 'same machine' screen service. This device will have a more finished look than the general 'maker' theme as itwill be used by many people and will hopefully end up being a showpiece. It will be made out of walnut and bloodwood.

October 29th: The basic framing for the LED light show coding has been taken from the Youtuber Robert Robert who made an excelent Neopixel based LED lightshow tht is music responsive. A basic explanation as to how the code works. The arduino pulls in 50ms of music sample from an auto gain adjustment microphone and through a combination of eqations, assigns the incoming voltage samples to a number from 0 to 11. A seriese of 'if' statements is then used to 'ick' and run a LED lightshow function. For exmple, if the number is 0, a rainbow effect is run. If the nuber is 4, an old style movie theatre lightshow is displayed. This code repeats on a loop and when no music is playing, the rainbow fucntion is run.

November 1st - Coding challenges:
Seeing as the code framework used for this build was designed around an auto gain adjustment microphone, a new equation had to be used to balance out the voltage readings coming in from the audio source (a headphone cable connected directly to the Arduino's ground and A0 pin). A microphone was not used for this projct as it was decided that the jukebox LEDs should only respond to the music from the jukebox and not outside noices and voices. The problem then arizes that the voltage can heavily range with volume. The detected ranges for voltage were 0 to 500. Therefore, a modulus divide equation was used to make sure that the LEDs function properly for any volume level.

November 4th - 
