#ifndef LED_RAINBOW_CPP
#define LED_RAINBOWL_CPP

#include <Adafruit_NeoPixel.h>
#include <stdint.h>

class LedRainbow
{
private:
  Adafruit_NeoPixel *strip;
  uint8_t numPixels;
  
  uint8_t location;
  uint8_t brightness;


public:

  LedRainbow( )
  {
    location = 0;
    brightness = 200;
  }
  
  void init( Adafruit_NeoPixel * inStrip, uint8_t inNumPixels )
  {
    strip = inStrip; 
    numPixels = inNumPixels;
  }

  void doAction()
  {
    drawRainbow(); 
    updateRainbowLocation();
  }

  void drawRainbow()
  {
    uint8_t c = 1;
    uint8_t r=0, g=0, b=0;
       
    for( uint8_t i=0; i<numPixels; i++ )
    {
      uint8_t c = 0;
      
      if( i<=location && i>location-7 )
      {
        c = location - i + 1;
      }
      
      r = ((c & 1)>>0) * brightness;
      g = ((c & 2)>>1) * brightness;
      b = ((c & 4)>>2) * brightness;

      strip->setPixelColor( i, r, g, b );
    }
    
    strip->show();
  }

  void updateRainbowLocation()
  { 
    location++;
    if( location>=numPixels+7 )
    {
      location = 0;
    }
  }
  
  void setColor( uint8_t inColor )
  {
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

