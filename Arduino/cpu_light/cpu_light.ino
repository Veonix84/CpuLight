#define FILTERSETTLETIME 5000                                           //  Time (ms) to allow the filters to settle before sending data

const int UNO = 0;     // Set to 0 if your not using the UNO bootloader (i.e using Duemilanove) - All Atmega's shipped from OpenEnergyMonitor come with Arduino Uno bootloader

// Libraries
#include <avr/wdt.h>                                                     

#include "LedModes.cpp"
#include <EEPROM.h>
#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel *strip;
const uint8_t MAX_NUM_PIXELS = 10;
LedModes ledModes;

void setValue( uint8_t point, uint8_t value );

void setup() 
{
  strip = new Adafruit_NeoPixel( MAX_NUM_PIXELS, 4, NEO_GRB + NEO_KHZ800);

  ledModes.init( strip );

  ledModes.setMode( LedModes::MODE_POWER_LEVEL );
  ledModes.setNumPixels( MAX_NUM_PIXELS );
  ledModes.setAutomode( 0 );
  ledModes.setSpeed( 100 );
  ledModes.setBrightness( 200 );

  ledModes.setColor( LedModes::COLOR_RED );

  Serial.begin(9600);
}

void loop() 
{ 
  ledModes.doAction();

  if(Serial.available())
  {
    uint8_t value = Serial.read();
    ledModes.setBrightness(value);
  }
}

uint8_t getValue( uint8_t point )
{
  switch( point )
  {
    case 0:
      return ledModes.getColor();
      break;

    case 1:
      return ledModes.getMode();
      break;

    case 2:
      return ledModes.getSpeed();
      break;
    
    case 3:
      return ledModes.getAutomode();
      break;
      
    case 4:
      return ledModes.getBrightness();
      break;
      
   case 7:
     return ledModes.getSleepMode();
     break;

   case 10:
     return ledModes.getNumPixels();
     break;
  };
  
  return 111;
}

void setValue( uint8_t point, uint8_t value )
{
  switch( point )
  {
    case 0:
      ledModes.setColor( value );
      break;

    case 1:
      ledModes.setMode( value );
      break;

    case 2:
      ledModes.setSpeed( value ); 
      break;
    
    case 3:
      ledModes.setAutomode( value );
      break;
      
    case 4:
      ledModes.setBrightness( value );
      break;
      
    case 7:
      ledModes.setSleepMode( value );
      break;
      
    case 10:
      ledModes.setNumPixels( value );
      break;
  };  
}

