#ifndef LED_TWINKLE
#define LED_TWINKLE

#include <Adafruit_NeoPixel.h>
#include <stdint.h>

class LedTwinkle
{
  private:
  Adafruit_NeoPixel *strip;
  uint8_t numPixels;
  
  uint8_t * currentR;
  uint8_t * currentG;
  uint8_t * currentB;
  
  uint8_t * setpointR;
  uint8_t * setpointG;
  uint8_t * setpointB;
  
  uint8_t starCounter;
  uint8_t starCounterMax;
  
  uint8_t fadeRate;
  
  uint8_t color;
  uint8_t brightness;
  
public:

  LedTwinkle( )
  {
    starCounter = 0;
    starCounterMax = 3;
    
    fadeRate = 20;
        
    color = 1;
    brightness = 255;
  }
  
  void init( Adafruit_NeoPixel * inStrip, uint8_t inNumPixels )
  {
    strip = inStrip;
    numPixels = inNumPixels;
    
    currentR = (uint8_t *)malloc( numPixels );
    currentG = (uint8_t *)malloc( numPixels );
    currentB = (uint8_t *)malloc( numPixels );
    
    setpointR = (uint8_t *)malloc( numPixels );
    setpointG = (uint8_t *)malloc( numPixels );
    setpointB = (uint8_t *)malloc( numPixels );
    
    for( uint8_t i=0; i<numPixels; i++ )
    {    
      setCurrentColor( i, 0, 0, 0 );
      setSetpointColor( i, 0, 0, 0 );
    }
    
    randomSeed( analogRead(0) );   
  }

  void doAction()
  {
    starCounter++;
    if( starCounter >= starCounterMax )
    {
      starCounter = 0;
      createStar();
    }
    
    fadeStrip();
    
    writeStrip();   
  }
  
  void createStar()
  {
    uint8_t pixelNum = random( numPixels );
    
    uint8_t r=0, g=0, b=0;
       
    r = random( 256 );
    g = random( 256 );
    b = random( 256 );

    setCurrentColor( pixelNum, r, g, b );
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

  void setColor( uint8_t inColor )
  {
    //color = inColor;
  }
  
  void setBrightness( uint8_t inBrightness )
  {
    if( brightness >= 255 )
    {
      brightness = 255;
    }
    else
    {
      brightness = inBrightness;
    }
    
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

  void setNumPixels( uint8_t inNumPixels )
  {
    numPixels = inNumPixels; 
  }  
  
};
#endif
