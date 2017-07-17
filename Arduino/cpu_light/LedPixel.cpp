#ifndef LED_PIXEL_CPP
#define LED_PIXEL_CPP

#include <Adafruit_NeoPixel.h>
#include <stdint.h>

class LedPixel
{
private:
  Adafruit_NeoPixel *strip;
  uint8_t numPixels;
  
  uint8_t pixelColor;
  uint8_t pixelLocation;
  uint8_t pixelDirection;
  
  uint8_t brightness;


public:

  LedPixel( )
  {
    pixelColor = 1;
    pixelLocation = 0;
    pixelDirection = 0; 
    brightness = 200;
  }
  
  void init( Adafruit_NeoPixel * inStrip, uint8_t inNumPixels )
  {
    strip = inStrip; 
    numPixels = inNumPixels;
  }

  void doAction()
  {
    drawPixel(); 
    updatePixelLocation();
  }

  void drawPixel()
  {
    uint8_t c = pixelColor;
    uint8_t r=0, g=0, b=0;
       
    r = ((c & 1)>>0) * brightness;
    g = ((c & 2)>>1) * brightness;
    b = ((c & 4)>>2) * brightness;

    for( uint8_t i=0; i<numPixels; i++ )
    {
      if( i==pixelLocation )
      {
        strip->setPixelColor( i, r, g, b );
      }
      else
      {
        strip->setPixelColor( i, 0, 0, 0 );
      }
    } 
      
    strip->show();
  }

  void updatePixelLocation()
  { 
    if( pixelDirection==0 )
    {
      pixelLocation++;
      if( pixelLocation>=numPixels-1 )
      {
        pixelDirection = 1;
      }
    }
    else
    {
      pixelLocation--;
      if( pixelLocation<=0 )
      {
        pixelDirection = 0;
      }
    }
  }
  
  void setColor( uint8_t inColor )
  {
    pixelColor = inColor;
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

