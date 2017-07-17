#ifndef LED_POWER_LEVEL_CPP
#define LED_POWER_LEVEL_CPP
#include <Adafruit_NeoPixel.h>
#include <stdint.h>

class LedPowerLevel
{
private:
  Adafruit_NeoPixel *strip;
  uint8_t numPixels;
  
  uint8_t color;
  uint8_t brightness;

  uint8_t configBrightness;
  
public:

  LedPowerLevel( )
  {
    setColor( 1 );  
  }
  
  void init( Adafruit_NeoPixel * inStrip, uint8_t inNumPixels )
  {
    strip = inStrip;
    numPixels = inNumPixels;
  }

  void doAction()
  {
    if(brightness > configBrightness) 
    {
      brightness--;
    }
    else if(brightness < configBrightness) 
    {
      brightness++;
    }
    setLeds();
  }

  void setLeds()
  {
    for(uint8_t i=0; i<numPixels; i++)
    {
      uint8_t r = ((color >> 0) & 1) * brightness;  // bit 0
      uint8_t g = ((color >> 1) & 1) * brightness;  // bit 1
      uint8_t b = ((color >> 2) & 1) * brightness;  // bit 2 
      
      strip->setPixelColor(i, r, g, b); 
    }
    strip->show();
  }

  void setColor( uint8_t inColor )
  {
    color = inColor;
  } 
 
  void setBrightness( uint8_t inBrightness )
  {
    configBrightness = inBrightness;
  }

  void setNumPixels( uint8_t inNumPixels )
  {
    numPixels = inNumPixels; 
  }
};


#endif
