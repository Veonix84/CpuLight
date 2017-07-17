#ifndef LED_MODES_CPP
#define LED_MODES_CPP

#include <EEPROM.h>
#include <Adafruit_NeoPixel.h>

#include "LedPixel.cpp"
#include "LedColor.cpp"
#include "LedRainbow.cpp"
#include "LedTwinkle.cpp"
#include "LedKitFade.cpp"
#include "LedPowerLevel.cpp"

const uint8_t ModeAddress = 10;
const uint8_t ColorAddress = 11;
const uint8_t BrightnessAddress = 12;
const uint8_t SpeedAddress = 13;
const uint8_t SleepModeAddress = 14;
const uint8_t AutoModeAddress = 15;
const uint8_t NumPixelsAddress = 16;

class LedModes
{
private:
  Adafruit_NeoPixel *strip;
  uint8_t numPixels;

  LedPixel ledPixel;
  LedColor ledColor;
  LedRainbow ledRainbow;
  LedTwinkle ledTwinkle;
  LedKitFade ledKitFade;
  LedPowerLevel ledPowerLevel;

  uint8_t mode;
  uint8_t speed;
  
  uint16_t delayCounter;
  uint16_t delayValue;

  bool sleepMode;

  bool automodeEnabled;  
  uint32_t automodeCounter;
  uint32_t automodeDelay;
  uint8_t automodeColor;
  
  uint8_t color;
  uint8_t brightness;

public:
  LedModes(  )
  {

  }

  //                                     // BGR 
  static const uint8_t COLOR_BLACK  = 0; // 000
  static const uint8_t COLOR_RED    = 1; // 001
  static const uint8_t COLOR_GREEN  = 2; // 010
  static const uint8_t COLOR_YELLOW = 3; // 011
  static const uint8_t COLOR_BLUE   = 4; // 100
  static const uint8_t COLOR_VIOLET = 5; // 101
  static const uint8_t COLOR_CYAN   = 6; // 110
  static const uint8_t COLOR_WHITE  = 7; // 111

  static const uint8_t MODE_PIXEL = 0;
  static const uint8_t MODE_COLOR = 1;
  static const uint8_t MODE_RAINBOW = 2;
  static const uint8_t MODE_TWINKLE = 3;
  static const uint8_t MODE_KIT = 4;
  static const uint8_t MODE_POWER_LEVEL = 5;
  
  void init( Adafruit_NeoPixel * inStrip )
  {
    strip = inStrip;
        
    strip->begin();
    strip->show(); // Initialize all pixels to 'off'  
    
    //if( loadValue( ModeAddress ) > 4 )
    {
      mode = 0;
      color = 1;
      brightness = 25;
      speed = 200;
      sleepMode = 0;
      automodeEnabled = 0;
      numPixels = 10;
    }
//    else
//    {
//      mode = loadValue( ModeAddress );
//      color = loadValue( ColorAddress );
//      brightness = loadValue( BrightnessAddress );
//      speed = loadValue( SpeedAddress );
//      sleepMode = loadValue( SleepModeAddress );
//      automodeEnabled = loadValue( AutoModeAddress );
//      numPixels = loadValue( NumPixelsAddress );   
//    }

    ledPixel.init( strip, numPixels );
    ledColor.init( strip, numPixels );
    ledRainbow.init( strip, numPixels );
    ledTwinkle.init( strip, numPixels );
    ledKitFade.init( strip, numPixels );
    ledPowerLevel.init( strip, numPixels );
   
    setColor( color );
    setBrightness( brightness );
    setMode( mode );
    setSpeed( speed );
    setSleepMode( sleepMode );
    setAutomode( automodeEnabled );
    setNumPixels( numPixels );
    
    delayCounter = 0;
  }

  void saveValue(uint8_t address, uint8_t value)
  {
    //EEPROM.write(address, value);
  }

  uint8_t loadValue(uint8_t address)
  {
    return EEPROM.read(address);
  }

  void doAction()
  {
    if( sleepMode ) return;  // If we are in sleep mode, do not do any actions

    delayCounter++;
    if( delayCounter>delayValue )
    {
      delayCounter=0;
          
      switch( mode )
      {
        case 0:
          ledPixel.doAction();
          break;
      
        case 1:
          ledColor.doAction();
          break;
          
        case 2:
          ledRainbow.doAction();
          break;
          
        case 3:
          ledTwinkle.doAction();
          break;
          
        case 4:
          ledKitFade.doAction();
          break;

        case MODE_POWER_LEVEL:
          ledPowerLevel.doAction();
          break;
      
        default:
          break;
      }
    }
    
    if( automodeEnabled )
    {
      automodeCounter++;
      if( automodeCounter >= automodeDelay )
      {
        automodeCounter = 0;
        
        automodeColor++;
        if( automodeColor>7 )
        {
          automodeColor = 1;
        }
        
        setColor( automodeColor );
      }
    }
  }

  uint8_t getMode()
  {
    return mode; 
  }

  void setMode( uint8_t inMode )
  {
    saveValue( ModeAddress, inMode );
    
    mode = inMode;
    setColor( color );
    setBrightness( brightness );
  }
  
  uint8_t getColor()
  {
    return color;
  }
  
  void setColor( uint8_t inColor )
  {
    //if(inColor > 7)
    //{
    //  return;
    //}
    
    saveValue( ColorAddress, inColor );
    
    color = inColor;

    ledPixel.setColor( color );
    ledColor.setColor( color );
    ledRainbow.setColor( color );
    ledTwinkle.setColor( color );
    ledKitFade.setColor( color );
    ledPowerLevel.setColor( color );
  }
  
  uint8_t getBrightness()
  {
    return brightness;
  }
  
  void setBrightness( uint8_t inBrightness )
  {
    saveValue( BrightnessAddress, inBrightness );

    brightness = inBrightness;
    
    ledPixel.setBrightness( brightness );
    ledColor.setBrightness( brightness );
    ledRainbow.setBrightness( brightness );
    ledTwinkle.setBrightness( brightness );
    ledKitFade.setBrightness( brightness );
    ledPowerLevel.setBrightness( brightness );
  }
  
  uint8_t getNumPixels()
  {
    return numPixels;
  }
  
  void setNumPixels( uint8_t inNumPixels )
  {
    saveValue( NumPixelsAddress, numPixels );

    numPixels = inNumPixels;

    clearStrip();
    
    ledPixel.setNumPixels( numPixels );
    ledColor.setNumPixels( numPixels );
    ledRainbow.setNumPixels( numPixels );
    ledTwinkle.setNumPixels( numPixels );
    ledKitFade.setNumPixels( numPixels );
    ledPowerLevel.setNumPixels( numPixels );
  }
  
  uint8_t getSpeed()
  {
   return speed; 
  }
  
  void setSpeed( uint8_t inSpeed )
  {
    saveValue( SpeedAddress, inSpeed );
    
    speed = inSpeed;
    delayValue = 100 * speed;//1000000/speed/speed;
  }
  
  uint8_t getAutomode()
  {
    return automodeEnabled;
  }
  
  void setAutomode( uint8_t inAutomode )
  {
    saveValue( AutoModeAddress, inAutomode );
        
    automodeEnabled = (inAutomode==1);
    
    if( automodeEnabled )
    {
      automodeColor = 1;
      setColor( automodeColor );
      
      automodeCounter = 0;
      automodeDelay = 1000000;
      automodeColor = 1;
    }
  }
  
  bool getSleepMode( )
  {
    return sleepMode;
  }
  
  void setSleepMode( bool inSleepMode )
  {
    saveValue( SleepModeAddress, inSleepMode );

    if( inSleepMode == true )
    {
      clearStrip();
    }
      
    sleepMode = inSleepMode;
  }
  
  /*
     Turns off all LEDs on the strip.
   */
  void clearStrip()
  {
    for( uint8_t i=0; i<strip->numPixels(); i++ )
    {
      strip->setPixelColor( i, 0, 0, 0 );
    }
    strip->show();    
  }

  void incMode()
  {
    mode++;
    if( mode >= 5 )
    {
      mode = 0;
    }
    
    setMode( mode );     
  }
};

#endif


