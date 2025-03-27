// RoboEyes_TFT.h
#ifndef ROBOEYES_TFT_H
#define ROBOEYES_TFT_H

#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <SPI.h>

#define TFT_BLK  5
#define TFT_CS   6
#define TFT_DC   7
#define TFT_RST  8

#define CANV_W 240
#define CANV_H 280

#define MAINCOLOR ST77XX_CYAN
#define BGCOLOR ST77XX_BLACK

// For mood type switch
#define STANDARD 0
#define TIRED 1
#define ANGRY 2
#define HAPPY 3

// For turning things on or off
#define ON 1
#define OFF 0

// For switch "predefined positions"
#define N 1 // north, top center
#define NE 2 // north-east, top right
#define E 3 // east, middle right
#define SE 4 // south-east, bottom right
#define S 5 // south, bottom center
#define SW 6 // south-west, bottom left
#define W 7 // west, middle left
#define NW 8 // north-west, top left 
// for middle center set "STANDARD"

class RoboEyes {

public:
    RoboEyes();
    ~RoboEyes();
    void begin(int width, int height, byte frameRate);
    void drawEyes();
    void update();
    void setFramerate(byte fps);
    void setWidth(byte leftEye, byte rightEye);
    void setHeight(byte leftEye, byte rightEye);
    void setBorderradius(byte leftEye, byte rightEye);
    void setSpacebetween(int space);
    void setMood(unsigned char mood);
    void setPosition(unsigned char position);
    void setAutoblinker(bool active, int interval, int variation);
    void setAutoblinker(bool active);
    void setIdleMode(bool active, int interval, int variation);
    void setIdleMode(bool active);
    void setCuriosity(bool curiousBit);
    void setCyclops(bool cyclopsBit);
    void setHFlicker(bool flickerBit, byte Amplitude);
    void setHFlicker(bool flickerBit);
    void setVFlicker(bool flickerBit, byte Amplitude);
    void setVFlicker(bool flickerBit);
    void open();
    void open(bool left, bool right);
    void close();
    void close(bool left, bool right);
    void blink();
    void blink(bool left, bool right);
    void anim_confused();
    void anim_laugh();


private:
    Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);
    GFXcanvas16 *eyeCanvas;

    // Fps Counter
    unsigned long fpsMillis = 0;
    unsigned long fpsCounter = 0;

    // For general setup - screen size and max. frame rate
    int screenWidth = 128; //128 OLED display width, in pixels
    int screenHeight = 64; //64 OLED display height, in pixels
    int frameInterval = 20; // default value for 50 frames per second (1000/50 = 20 milliseconds)
    unsigned long fpsTimer = 0; // for timing the frames per second

    // For controlling mood types and expressions
    bool tired = 0;
    bool angry = 0;
    bool happy = 0;
    bool curious = 0; // if true, draw the outer eye larger when looking left or right
    bool cyclops = 0; // if true, draw only one eye
    bool eyeL_open = 0; // left eye opened or closed?
    bool eyeR_open = 0; // right eye opened or closed?

    //*********************************************************************************************
    //  Eyes Geometry
    //********************************************************************************************* 
    
    // EYE LEFT - size and border radius
    int eyeLwidthDefault = 36;
    int eyeLheightDefault = 36;
    int eyeLwidthCurrent = eyeLwidthDefault;
    int eyeLheightCurrent = 1; // start with closed eye, otherwise set to eyeLheightDefault
    int eyeLwidthNext = eyeLwidthDefault;
    int eyeLheightNext = eyeLheightDefault;
    int eyeLheightOffset = 0;

    // Border Radius Left Eye
    byte eyeLborderRadiusDefault = 8;
    byte eyeLborderRadiusCurrent = eyeLborderRadiusDefault;
    byte eyeLborderRadiusNext = eyeLborderRadiusDefault;

    // EYE RIGHT - size and border radius
    int eyeRwidthDefault = eyeLwidthDefault;
    int eyeRheightDefault = eyeLheightDefault;
    int eyeRwidthCurrent = eyeRwidthDefault;
    int eyeRheightCurrent = 1; // start with closed eye, otherwise set to eyeRheightDefault
    int eyeRwidthNext = eyeRwidthDefault;
    int eyeRheightNext = eyeRheightDefault;
    int eyeRheightOffset = 0;

    // Border Radius
    byte eyeRborderRadiusDefault = 8;
    byte eyeRborderRadiusCurrent = eyeRborderRadiusDefault;
    byte eyeRborderRadiusNext = eyeRborderRadiusDefault;

    // EYE LEFT - Coordinates
    int eyeLxDefault = ((screenWidth)-(eyeLwidthDefault+spaceBetweenDefault+eyeRwidthDefault))/2;
    int eyeLyDefault = ((screenHeight-eyeLheightDefault)/2);
    int eyeLx = eyeLxDefault;
    int eyeLy = eyeLyDefault;
    int eyeLxNext = eyeLx;
    int eyeLyNext = eyeLy;
    int old_eyeLx;
    int old_eyeLy;

    // EYE RIGHT - Coordinates
    int eyeRxDefault = eyeLx+eyeLwidthCurrent+spaceBetweenDefault;
    int eyeRyDefault = eyeLy;
    int eyeRx = eyeRxDefault;
    int eyeRy = eyeRyDefault;
    int eyeRxNext = eyeRx;
    int eyeRyNext = eyeRy;
    int old_eyeRx;
    int old_eyeRy;

    // BOTH EYES 
    // Eyelid top size
    byte eyelidsHeightMax = eyeLheightDefault/2; // top eyelids max height
    byte eyelidsTiredHeight = 0;
    byte eyelidsTiredHeightNext = eyelidsTiredHeight;
    byte eyelidsAngryHeight = 0;
    byte eyelidsAngryHeightNext = eyelidsAngryHeight;
    // Bottom happy eyelids offset
    byte eyelidsHappyBottomOffsetMax = (eyeLheightDefault/2)+3;
    byte eyelidsHappyBottomOffset = 0;
    byte eyelidsHappyBottomOffsetNext = 0;
    // Space between eyes
    int spaceBetweenDefault = 10;
    int spaceBetweenCurrent = spaceBetweenDefault;
    int spaceBetweenNext = 10;

    //*********************************************************************************************
    //  Macro Animations
    //*********************************************************************************************

    // Animation - horizontal flicker/shiver
    bool hFlicker = 0;
    bool hFlickerAlternate = 0;
    byte hFlickerAmplitude = 2;

    // Animation - vertical flicker/shiver
    bool vFlicker = 0;
    bool vFlickerAlternate = 0;
    byte vFlickerAmplitude = 10;
    
    // Animation - auto blinking
    bool autoblinker = 0; // activate auto blink animation
    int blinkInterval = 1; // basic interval between each blink in full seconds
    int blinkIntervalVariation = 4; // interval variaton range in full seconds, random number inside of given range will be add to the basic blinkInterval, set to 0 for no variation
    unsigned long blinktimer = 0; // for organising eyeblink timing
    
    // Animation - idle mode: eyes looking in random directions
    bool idle = 0;
    int idleInterval = 1; // basic interval between each eye repositioning in full seconds
    int idleIntervalVariation = 3; // interval variaton range in full seconds, random number inside of given range will be add to the basic idleInterval, set to 0 for no variation
    unsigned long idleAnimationTimer = 0; // for organising eyeblink timing
    
    // Animation - eyes confused: eyes shaking left and right
    bool confused = 0;
    unsigned long confusedAnimationTimer = 0;
    int confusedAnimationDuration = 500;
    bool confusedToggle = 1;
    
    // Animation - eyes laughing: eyes shaking up and down
    bool laugh = 0;
    unsigned long laughAnimationTimer = 0;
    int laughAnimationDuration = 500;
    bool laughToggle = 1;
    
    int thres = 2;

    int getScreenConstraint_X();
    int getScreenConstraint_Y();
};

#endif
