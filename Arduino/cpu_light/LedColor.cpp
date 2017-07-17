#ifndef LED_COLOR_CPP
#define LED_COLOR_CPP
#include <Adafruit_NeoPixel.h>
#include <stdint.h>

class LedColor
{
private:
  Adafruit_NeoPixel *strip;
  uint8_t numPixels;
  
  uint8_t color;
  
  uint8_t currentRGB[3]; 
  uint8_t setRGB[3];
  
  uint8_t NumColors;
  
  uint8_t brightness;
  
  uint8_t fadeRate;

public:

  LedColor( )
  {
    NumColors = 7;
    
    //NumColors = 63;
       
    currentRGB[0] = 0;
    currentRGB[1] = 0;
    currentRGB[2] = 0;
    
    brightness = 250;
    
    fadeRate = 1;
    
    setColor( 1 );  
  }
  
  void init( Adafruit_NeoPixel * inStrip, uint8_t inNumPixels )
  {
    strip = inStrip;
    numPixels = inNumPixels;
  }

  void doAction()
  {   
    fadeToColor();
  }

  void fadeToColor()
  {   
    for( uint8_t i=0; i<numPixels; i++ )
    {
      for( uint8_t j=0; j<3; j++ )
      {
        if( currentRGB[j] > setRGB[j] )
        {
          if( currentRGB[j] + fadeRate >= setRGB[j] )
          {
            currentRGB[j] = setRGB[j];
          }
          else
          {
            currentRGB[j] += fadeRate;
          }
        }
        else if( currentRGB[j] < setRGB[j] )
        {
          if( currentRGB[j] - fadeRate <= setRGB[j] )
          {
            currentRGB[j] = setRGB[j];
          }
          else
          {
            currentRGB[j] -= fadeRate; 
          }
        }
      }
      
      strip->setPixelColor( i, currentRGB[0], currentRGB[1], currentRGB[2] );
    } 
      
    strip->show();
  }

  void setColor( uint8_t inColor )
  {
    color = inColor;
    
    if( color > NumColors )
    {
      color = NumColors-1;
    }

    setRGB[0] = ((color >> 0) & 1) * brightness;  // bit 1
    setRGB[1] = ((color >> 1) & 1) * brightness;  // bit 1
    setRGB[2] = ((color >> 2) & 1) * brightness;  // bit 2 
    
  } 
 
  void setBrightness( uint8_t inBrightness )
  {
    brightness = inBrightness;
    setColor( color );
  }

  void setNumPixels( uint8_t inNumPixels )
  {
    numPixels = inNumPixels; 
  }
  
};


#endif
