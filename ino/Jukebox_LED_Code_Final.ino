/*Hello, this code runs a strip of NeoPixel LEDs from Adafruit. It works by using an Arduino to read the voltages being sent by a
 *sound file through a 3.5mm headphone cable that is connected to a sound source. The cable is cut off, exposing the three wires 
 *inside (ground, left and right). The ground is connected to the Arduino's ground and either the right or the left is connected
 *to the A0 pin. THe LED strip is configured to be connected to pin 6 on the Arduino. The code then reads the voltages coming in
 *from the audio source and converts them to a usable number which is then modulus devided to produce numbers from o to 11. Each
 *number in this range is assigned a light show function which produces a cool lighting effect that can be customized.
 *
 *Credits:
 *
 *The framework for this code was written by YouTube channel Robert Robert. Link: https://www.youtube.com/watch?v=pQwgZwrXfhc&t=83s
 *The code has been heavily modified by Brandon Watson during November 2018 to suit the needs of this project.
 *Carter Watson contributed to the modulus equation portion of this code.
 *The various cool animations including (twinkle, bouncy balls, meteor, running lights, cylon effect) were taken from 
 *https://www.tweaking4all.com/hardware/arduino/adruino-led-strip-effects/
 *
 *Colour Instuctions:
 *
 *There are two methods used to assign colours in this program. Standard RGB brightness levels and HTML colour coding.
 *Example1: (255, 0, 0) yeilds green as the NeoPixels are set up as GRB rather than RGB. 255 is the maximum brightness of that colour.
 *Example2: #F156GH is a colour code. Green = 56, Red = F1, Blue = GH (add '0x' to beginning of each) so the code would look like (0x56, 0xF1, 0xGH).
 *For picking your own colours, simply google html colour code finder, pick your colour and place the colour code into this code (colours may varry).
*/

//Code Version: V5

//lines below set variables for neopixels

#include <Adafruit_NeoPixel.h>

#define NUMBER_PIXEL 60 //Set how many LEDs are in the strip being used
#define LEDPIN    6 //Set which pin on the Arduino will controll the LEDs

Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, LEDPIN, NEO_GRB + NEO_KHZ800);  //Various settings for the Adafruit NeoPixel library

int lng = 100;//long delay for various LED functions
int sht = 20;//short delay for various LED functions

long randomA;//random number variable for green LED
long randomB;//random number variable for red LED
long randomC;//random number variable for blue LED
// same for variables below. These extra random variable are for the bouncy ball function
long randomD;
long randomE;
long randomF;
long randomG;
long randomH;
long randomI;

/* random variables are used throughout the program to creat random colours.
 *  if the random variables are created before a 'for' loop, entire strip will be one random colour. 
 *  if the random variables are inside the 'for' loop, each led will be a different colour.
 */

//lines below are for sampling the audio source

const int sampleWindow = 50; // Sample window width in mS (50 mS = 20Hz)
unsigned int sample;

void setup()
{
  strip.begin();//initialises neopixels
  strip.setBrightness(255);// set brightness from 0 to max is 255
  strip.show();//clears any previous data in the strip
  Serial.begin(9600);//set up for checking audio interface is working
  randomSeed(analogRead(1));// set up for the reandom function seed which picks random colours
}


void loop()
{
  //open void loop
  //first run the sound sampling
  unsigned long startMillis = millis(); // Start of sample window
  unsigned int peakToPeak = 0;   // peak-to-peak level

  unsigned int signalMax = 0;
  unsigned int signalMin = 1024;

  // collect data for 50 mS
  while (millis() - startMillis < sampleWindow)
  {
    //open while loop
    sample = analogRead(0);
    if (sample < 1024)  // toss out spurious readings
    {
      //open 1st if loop in while
      if (sample > signalMax)
      {
        //open 2nd if
        signalMax = sample;  // save just the max levels
      }//close 2nd if
      else if (sample < signalMin)
      {
        //open 3rd if
        signalMin = sample;  // save just the min levels
      }//close 3rd if
    }//close 1st if
  }//close while loop
  peakToPeak = signalMax - signalMin;  // max - min = peak-peak amplitude
  double volts = (peakToPeak * 3.3) / 1024;  // convert to volts

//section below maps the signal from the microphone on to 12 options for LED effects

  int sound = (volts * 100); // multiply volts by 100 to make all values easier to visualize and work with modulus
  sound = (sound%11); // modulus divide to make sure that all volume levels play nice on 0 to 11 numbers for animations

  int soundLevel = map(sound, 0, 10, 0, 11);
  Serial.print("The volt level is  "); // for testing the values coming in from audio source
  Serial.println(volts);//for debugging
  Serial.println(sound);// added to see what 'if' statement should be running (0 means 0 if statement should be running)


//next section is a series of 12 (0-11) 'if' statements which trigger different patterns and animations.
//it is a combination of a traditional VU style meter fill of the strip
// combined with randomised animated patterns to keep it interesting
  if (soundLevel == 0)
  {
    //open if sound = 0. When there is silence a rainbow pattern runs
    
    rainbowCycle(3);//from the neopixel library

  }//close if 0 statement
  
  if(soundLevel == 1) //open if sound = 1. Colour wipe Red
  {
    for (int i = 0; i<30;i++)
    {
    strip.setPixelColor((i+30), strip.Color(0,255,0));
    strip.setPixelColor((29-i), strip.Color(0,255,0));
    strip.show();
    delay(sht); //short delay will make animation faster
    }

  }//close if 1 statement
  
  if(soundLevel == 2) //open if sound = 2. Take sound samples in to assign each section a certain amount od LEDs
    {
    // set 3 random variables to set one random colour for entire animation  
    randomA = random(0, 255);
    randomB = random(0, 255);
    randomC = random(0, 255);
    for (int i = 0; i<30;i++){
      
    // below sets an animation up by volume level, it has three areas tha can be different sizes depending on volume level
    
    if (i < sound){ 
    
         strip.setPixelColor((i+30), strip.Color(randomA,randomB,randomC));
         strip.setPixelColor((29-i), strip.Color(randomA,randomB,randomC));
    }
    else if (i < (sound + 9)) {
      
         strip.setPixelColor((i+30), strip.Color(255,0,0));
         strip.setPixelColor((29-i), strip.Color(255,0,0));
      
    }
    else
    {
         randomA = random(0, 255);
         randomB = random(0, 255);
         randomC = random(0, 255);
         strip.setPixelColor((i+30), strip.Color(randomA,randomB,randomC));
         strip.setPixelColor((29-i), strip.Color(randomA,randomB,randomC));
    }
   
  strip.show(); 
  delay(sht); //short delay will make animation faster
}
  }//close if 2 statement

  if(soundLevel == 3) //open if sound = 3. Do a random colour wipe
    {
    //assign random numbers to 3 variables so that all LEDs can be controlled by random variables
    randomA = random(0, 255);
    randomB = random(0, 255);
    randomC = random(0, 255);
    //colorWipe(strip.Color(255, 0, 255), 20); // magenta
    colorWipe(strip.Color(randomA, randomB, randomC), 20); // random colour as all three leds are assigned random variables
    strip.show();
    
  }//close if 3 statement
  
  if(soundLevel == 4) //open if sound = 4. Sets each LED in sequence to a random colour
    {
    randomA = random(0, 255);
    randomB = random(0, 255);
    randomC = random(0, 255);
    for (int i = 0; i<30;i++)// for loop to set each light in sequence to a colour
    {
    strip.setPixelColor((i+30), strip.Color(randomA,randomB,randomC));
    strip.setPixelColor((29-i), strip.Color(randomA,randomB,randomC));
    strip.show();
    delay(sht);
    }
    for (int j = 30; j>0;j--)// for loop to set each light i sequence to a colour backwards
    {
    strip.setPixelColor((j+30), strip.Color(255,0,0));
    strip.setPixelColor((29-j), strip.Color(255,0,0));
    strip.show();
    delay(sht);
    }
  }//close if 4 statement

  if(soundLevel == 5) //open if sound = 5. Creates 3 random colour combinations and assigns them to three bouncy balls
    {
     // set three random variables for each bouncy ball (9 variables in total)
     randomA = random(0, 255);
     randomB = random(0, 255);
     randomC = random(0, 255);
     randomD = random(0, 255);
     randomE = random(0, 255);
     randomF = random(0, 255);
     randomG = random(0, 255);
     randomH = random(0, 255);
     randomI = random(0, 255);
     byte colors[3][3] = { {randomA, randomB, randomC}, {randomD, randomE, randomF}, {randomG, randomH, randomI} };
     BouncingColoredBalls(3, colors); // call bouncy ball function with 3 balls and the colours being used
    
  }//close if 5 statement

  if(soundLevel == 6) //open if sound = 6. Creates a meteor effect with decaying tail and sparkling LEDs
    {
    randomA = random(0, 255);
    randomB = random(0, 255);
    randomC = random(0, 255);
    meteorRain(randomA,randomB,randomC,10, 64, true, 30);

  }//close if 6 statment

  if(soundLevel == 7) //open if sound = 7. Creates a running lights effect (Sections of 5 LEDs run accross the strip)
    {
    RunningLights(0,0,0xff, 50); 

  }//close if 7 statement

  if(soundLevel == 8) //open if sound = 8. Creates a random colour Cylon effect
    {
    randomA = random(0,255);
    randomB = random(0,255);
    randomC = random(0,255);
    CylonBounce(randomA, randomB, randomC, 4, 10, 50);

  }//close if 8 statement

  if(soundLevel == 9) //open if sound = 9
    {
    for (int i = 0; i<30;i++)
    {
    strip.setPixelColor((i+30), strip.Color(50,150,0));
    strip.setPixelColor((29-i), strip.Color(50,150,0));
    strip.show();
    delay(sht);
    }
  }//close if 9 statement

  if(soundLevel == 10) //open if sound = 10
    {
    for (int i = 0; i<30;i++)
    {
    strip.setPixelColor((i+30), strip.Color(100,140,200));
    strip.setPixelColor((29-i), strip.Color(100,140,200));
    strip.show();
    delay(sht);
    }
  }//close if 10 statement

  if(soundLevel == 11) //open if sound = 11. Generates a bunch of randomly twinkling LEDs and colours
    {
    TwinkleRandom(20, 100, false);

  }//close if 11 statement


}//close void loop()


//*******************************************************************************************************************************************************
//*******************************************************************************************************************************************************

//Below are the functions for the various color and animation functions each function separated by line of stars
//for support and more details on these animations, check out the source of the code at: https://www.tweaking4all.com/hardware/arduino/adruino-led-strip-effects/



//Color wipe function which makes entire strip on colour in a wiping animation from one side to the other:

void colorWipe(uint32_t c, uint8_t wait)
{
  //open colowipe
  for(uint16_t i = 0; i < strip.numPixels(); i++)
  {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}//close colorWipe function

//************************************************************************************************************************

//Theatre Chase function which makes LEDs chase eachother in alternating 'on' 'off' pattern:

void theaterChase(uint32_t c, uint8_t wait)
{
  //open theaterchase function
  for (int j = 0; j < 3; j++) //do 3 cycles of chasing
  {
    for (int q = 0; q < 3; q++)
    {
      for (int i = 0; i < strip.numPixels(); i = i + 3)
      {
        strip.setPixelColor(i + q, c);  //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (int i = 0; i < strip.numPixels(); i = i + 3)
      {
        strip.setPixelColor(i + q, 0);      //turn every third pixel off
      }
    }
  }
}
//close theater chase function

//**********************************************************************************************************************

//Rainbow Cycle function which cycles through the colour spectrum as it passes through the LED strip:

void rainbowCycle(uint8_t wait)  //open rainbow function
{
  uint16_t i, j;

  for(j = 0; j < 256; j++) // 1 cycles of all colors on wheel
  {
    for(i = 0; i < strip.numPixels(); i++)
    {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}//close rainbow function

//**********************************************************************************************************************

//you need to included the code below for the neopixel functions that use the 'wheel' code:

uint32_t Wheel(byte WheelPos)
{
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85)
  {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170)
  {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}//close wheel function

//*********************************************************************************************************************

//Bouncing ball function creates 3 bouncing ball animations:

void BouncingColoredBalls(int BallCount, byte colors[][3]) {
  float Gravity = -9.81;
  int StartHeight = 1;
  
  float Height[BallCount];
  float ImpactVelocityStart = sqrt( -2 * Gravity * StartHeight );
  float ImpactVelocity[BallCount];
  float TimeSinceLastBounce[BallCount];
  int   Position[BallCount];
  long  ClockTimeSinceLastBounce[BallCount];
  float Dampening[BallCount];

  for (int i = 0 ; i < BallCount ; i++) {
    ClockTimeSinceLastBounce[i] = millis();
    Height[i] = StartHeight;
    Position[i] = 0;
    ImpactVelocity[i] = ImpactVelocityStart;
    TimeSinceLastBounce[i] = 0;
    Dampening[i] = 0.90 - float(i)/pow(BallCount,2); 
   }
   
  unsigned long bounceMillis = millis(); //create a millis for bounce function to control how long the function runs for
  while (millis() - bounceMillis < 5000) { //run function for 5 seconds
    for (int i = 0 ; i < BallCount ; i++) {
      TimeSinceLastBounce[i] = millis() - ClockTimeSinceLastBounce[i];
      Height[i] = 0.5 * Gravity * pow( TimeSinceLastBounce[i]/1000 , 2.0 ) + ImpactVelocity[i] * TimeSinceLastBounce[i]/1000;

      if ( Height[i] < 0 ) {
        Height[i] = 0;
        ImpactVelocity[i] = Dampening[i] * ImpactVelocity[i];
        ClockTimeSinceLastBounce[i] = millis();

        if ( ImpactVelocity[i] < 0.01 ) {
        ImpactVelocity[i] = ImpactVelocityStart;
      }
    }
      Position[i] = round( Height[i] * (NUMBER_PIXEL - 1) / StartHeight);
    }

    for (int i = 0 ; i < BallCount ; i++) {
      strip.setPixelColor(Position[i],colors[i][0],colors[i][1],colors[i][2]);
    }

    strip.show();
    setAll(0,0,0);
  }
}//close bouncing ball function

//*********************************************************************************************************************

//below is the functions specifically for NeoPixel and FastLED to run the various functions

void setPixel(int Pixel, byte red, byte green, byte blue) {
 #ifdef ADAFRUIT_NEOPIXEL_H 
   // NeoPixel
   strip.setPixelColor(Pixel, strip.Color(red, green, blue));
 #endif
 #ifndef ADAFRUIT_NEOPIXEL_H 
   // FastLED
   leds[Pixel].r = red;
   leds[Pixel].g = green;
   leds[Pixel].b = blue;
 #endif
}

void setAll(byte red, byte green, byte blue) {
  for(int i = 0; i < NUMBER_PIXEL; i++ ) {
    setPixel(i, red, green, blue); 
  }
  strip.show();
}

//******************************************************************************************************************************************************

// below is the meteor function which creates a meteor effect that has a decaying tail

void meteorRain(byte green, byte red, byte blue, byte meteorSize, byte meteorTrailDecay, boolean meteorRandomDecay, int SpeedDelay) {  
  setAll(0,0,0);
  unsigned long meteorMillis = millis(); //create a millis for bounce function to control how long the function runs for
  while (millis() - meteorMillis < 4000) {  //runs for a total of 4 seconds
  
  for(int i = 0; i < NUMBER_PIXEL+NUMBER_PIXEL; i++) {
    
    
    // fade brightness all LEDs one step
    for(int j=0; j<NUMBER_PIXEL; j++) {
      if( (!meteorRandomDecay) || (random(10)>5) ) {
        fadeToBlack(j, meteorTrailDecay );        
      }
    }
    
    // draw meteor
    for(int j = 0; j < meteorSize; j++) {
      if( ( i-j <NUMBER_PIXEL) && (i-j>=0) ) {
        setPixel(i-j, red, green, blue);
      } 
    }
   
    strip.show();
    delay(SpeedDelay);
  }
}
}

void fadeToBlack(int ledNo, byte fadeValue) { //to make the tail fade and decay slowly
 #ifdef ADAFRUIT_NEOPIXEL_H 
    // NeoPixel
    uint32_t oldColor;
    uint8_t r, g, b;
    int value;
    
    oldColor = strip.getPixelColor(ledNo);
    r = (oldColor & 0x00ff0000UL) >> 16;
    g = (oldColor & 0x0000ff00UL) >> 8;
    b = (oldColor & 0x000000ffUL);

    r=(r<=10)? 0 : (int) r-(r*fadeValue/256);
    g=(g<=10)? 0 : (int) g-(g*fadeValue/256);
    b=(b<=10)? 0 : (int) b-(b*fadeValue/256);
    
    strip.setPixelColor(ledNo, r,g,b);
 #endif
 #ifndef ADAFRUIT_NEOPIXEL_H
   // FastLED
   leds[ledNo].fadeToBlackBy( fadeValue );
 #endif  
}//end meteor functions

//******************************************************************************************************************************

//below is a function for twinkling the LEDs with random colours

void TwinkleRandom(int Count, int SpeedDelay, boolean OnlyOne) {
  setAll(0,0,0);
  unsigned long twinkleMillis = millis(); //create a millis for twinkle function to control how long function runs for 
  while (millis() - twinkleMillis < 5000) { //runs for a total of 5 seconds
    
  for (int i=0; i<Count; i++) {
     setPixel(random(NUMBER_PIXEL),random(0,255),random(0,255),random(0,255));
     strip.show();
     delay(SpeedDelay);
     if(OnlyOne) { 
       setAll(0,0,0); 
     }
   }
  
  delay(SpeedDelay);
}
}//end twinkle function

//******************************************************************************************************************************

//below is the function to create a Cylon effect

void CylonBounce(byte green, byte red, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay){

  for(int i = 0; i < NUMBER_PIXEL-EyeSize-2; i++) {
    setAll(0,0,0);
    setPixel(i, red/10, green/10, blue/10);
    for(int j = 1; j <= EyeSize; j++) {
      setPixel(i+j, red, green, blue); 
    }
    setPixel(i+EyeSize+1, red/10, green/10, blue/10);
    strip.show();
    delay(SpeedDelay);
  }

  delay(ReturnDelay);

  for(int i = NUMBER_PIXEL-EyeSize-2; i > 0; i--) {
    setAll(0,0,0);
    setPixel(i, red/10, green/10, blue/10);
    for(int j = 1; j <= EyeSize; j++) {
      setPixel(i+j, red, green, blue); 
    }
    setPixel(i+EyeSize+1, red/10, green/10, blue/10);
    strip.show();
    delay(SpeedDelay);
  }
  
  delay(ReturnDelay);
}//end Cylon function

//*****************************************************************************************************************************

//below is a function for running lites which is a series of groups of lights that move around the LED strip

//

void RunningLights(byte red, byte green, byte blue, int WaveDelay) {
  int Position=0;
  
  for(int j=0; j<NUMBER_PIXEL*2; j++)
  {
      Position++; // = 0; //Position + Rate;
      for(int i=0; i<NUMBER_PIXEL; i++) {
        // sine wave, 3 offset waves make a rainbow!
        //float level = sin(i+Position) * 127 + 128;
        //setPixel(i,level,0,0);
        //float level = sin(i+Position) * 127 + 128;
        setPixel(i,((sin(i+Position) * 127 + 128)/255)*red,
                   ((sin(i+Position) * 127 + 128)/255)*green,
                   ((sin(i+Position) * 127 + 128)/255)*blue);
      }
      
      strip.show();
      delay(WaveDelay);
  }
}
