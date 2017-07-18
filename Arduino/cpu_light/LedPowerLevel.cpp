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

  uint8_t currentBrightness;
  
public:

  LedPowerLevel( )
  {
    setColor( 1 );  
  }
  
  void init( Adafruit_NeoPixel * inStrip, uint8_t inNumPixels )
  {
    strip = inStrip;
    numPixels = inNumPixels;
    
    currentBrightness = 0;
  }

  void doAction()
  {
    if(currentBrightness > brightness) 
    {
      currentBrightness--;
    }
    else if(currentBrightness < brightness) 
    {
      currentBrightness++;
    }
    setLeds();
  }

  void setLeds()
  {
    uint16_t tmpBrightness = currentBrightness;
    
    for(uint8_t i=0; i<numPixels; i++)
    {
      uint8_t r = 0;
      uint8_t g = 0;
      uint8_t b = 0;
      
      uint8_t bVal = 0;
      if(tmpBrightness > 20) 
      {
        bVal = 20;
        tmpBrightness -= 20;
      }
      else 
      {
        bVal = tmpBrightness;
        tmpBrightness = 0;
      }
        
      r = ((color >> 0) & 1) * bVal * 10;  // bit 0
      g = ((color >> 1) & 1) * bVal * 10;  // bit 1
      b = ((color >> 2) & 1) * bVal * 10;  // bit 2 
      
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
    brightness = inBrightness;
  }

  void setNumPixels( uint8_t inNumPixels )
  {
    numPixels = inNumPixels; 
  }
};

#endif
