#ifndef LED_KIT_FADE
#define LED_KIT_FADE

#include <Adafruit_NeoPixel.h>
#include <stdint.h>

class LedKitFade
{
  private:
  Adafruit_NeoPixel *strip;
  uint8_t numPixels;
  
  uint8_t center;
  
  uint8_t * currentR;
  uint8_t * currentG;
  uint8_t * currentB;
  
  uint8_t * setpointR;
  uint8_t * setpointG;
  uint8_t * setpointB;
  
  uint8_t step;
  uint8_t stepCounter;
  uint8_t stepCounterMax;
  
  uint8_t fadeInOut;
  uint8_t fadeRate;
  
  uint8_t color;
  uint8_t brightness;
  
public:

  LedKitFade( )
  {
    step = 0;
    stepCounter = 0;
    stepCounterMax = 4;
    
    fadeInOut = 0;
    fadeRate = 30;
        
    color = 1;
    brightness = 250;
  }
  
  void init( Adafruit_NeoPixel * inStrip, uint8_t inNumPixels )
  {
    strip = inStrip;
    numPixels = inNumPixels;
    
    findCenter();

    currentR = (uint8_t *)malloc( strip->numPixels() );
    currentG = (uint8_t *)malloc( strip->numPixels() );
    currentB = (uint8_t *)malloc( strip->numPixels() );
    
    setpointR = (uint8_t *)malloc( strip->numPixels() );
    setpointG = (uint8_t *)malloc( strip->numPixels() );
    setpointB = (uint8_t *)malloc( strip->numPixels() );

    
    for( uint8_t i=0; i<numPixels; i++ )
    {    
      setCurrentColor( i, 0, 0, 0 );
      setSetpointColor( i, 0, 0, 0 );
    }
  }

  void findCenter()
  {
    center = numPixels / 2; 
  }

  void doAction()
  {
    stepCounter++;
    if( stepCounter >= stepCounterMax )
    {
      stepCounter = 0;
      doStep();
    }
    
    fadeStrip();
    
    writeStrip();
  }
  
  void doStep()
  {
    uint8_t c = color;
    uint8_t r=0, g=0, b=0;

    //if( fadeInOut == 0 )
    {    
      r = ((c & 1)>>0) * brightness;
      g = ((c & 2)>>1) * brightness;
      b = ((c & 4)>>2) * brightness;
    }

    //clearSetpoints();

    setSetpointColor( center, r, g, b );

    for( uint8_t i=0; i<step; i++ )
    {
      if( fadeInOut == 0  &&  c > 7 )
      {
        r = (((i+1) & 1)>>0) * brightness;
        g = (((i+1) & 2)>>1) * brightness;
        b = (((i+1) & 4)>>2) * brightness;      
      }
      
      setSetpointColor( center+i+1, r, g, b );
      setSetpointColor( center-i-1, r, g, b );
    }
    
    if( step < center )
    {
      step++;
    }
    else
    {
      if( fadeInOut == 1 )
      {
        step = 0;
        fadeInOut = 0;
      }
    }
    
    strip->show();
  }
  
  
  void writeStrip()
  {
    for( uint8_t i=0; i<numPixels; i++ )
    {
      uint8_t r, g, b;
      r = currentR[ i ];
      g = currentG[ i ];
      b = currentB[ i ];

      strip->setPixelColor( i, r, g, b );     
    }
    
    strip->show();
  }
 
  void fadeStrip()
  {
    for( uint8_t i=0; i<numPixels; i++ )
    {
      currentR[i] = calcFadeValue( currentR[i], setpointR[i] );
      currentG[i] = calcFadeValue( currentG[i], setpointG[i] );
      currentB[i] = calcFadeValue( currentB[i], setpointB[i] );
    }   
  }


  void setCurrentColor( uint8_t i, uint8_t r, uint8_t g, uint8_t b )
  {
    currentR[i] = r;
    currentG[i] = g;    
    currentB[i] = b;
  }

  void setSetpointColor( uint8_t i, uint8_t r, uint8_t g, uint8_t b )
  {
    setpointR[i] = r;
    setpointG[i] = g;    
    setpointB[i] = b;
  }


  void nextColor()
  {
   color++;
   if( color > 8 )
   {
     color = 1;
   } 
    
  }

  void setColor( uint8_t inColor )
  {
    color = inColor;
    step = 0;
    fadeInOut = 1;
  }
  
  uint8_t calcFadeValue( uint8_t currentValue, uint8_t setpointValue )
  {
    if( currentValue < setpointValue )
    {
      if( currentValue + fadeRate > setpointValue )
      {
        currentValue = setpointValue;
      }
      else
      {
        currentValue += fadeRate;
      }
    }
    else if( currentValue > setpointValue )
    {
      if( currentValue - fadeRate < setpointValue )
      {
        currentValue = setpointValue;
      }
      else
      {
        currentValue -= fadeRate;
      }
    }
    
    return currentValue;
  }
  
  void clearSetpoints()
  {
    for( uint8_t i=0; i<numPixels; i++ )
    {
      setSetpointColor( i, 0, 0, 0 );
    }
  }

  void setBrightness( uint8_t inBrightness )
  {
    if( inBrightness > 255 )
    {
      brightness = 255;
    }
    else
    {
      brightness = inBrightness;
    }
  }
  
  void setNumPixels( uint8_t inNumPixels )
  {
    numPixels = inNumPixels; 
    findCenter();
  }

};
#endif
