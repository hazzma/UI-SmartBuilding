#ifndef DISPLAY_ENGINE_H
#define DISPLAY_ENGINE_H

#include <Arduino.h>

enum class TextDatum {
    TopLeft = 0,
    TopCenter = 1,
    TopRight = 2,
    MiddleLeft = 3,
    MiddleCenter = 4,
    MiddleRight = 5,
    BottomLeft = 6,
    BottomCenter = 7,
    BottomRight = 8
};

/**
 * DisplayEngine - Hardware Abstraction Layer (HAL) for HMI UI.
 * This class defines the "Contract" between the UI Logic and the Graphics Driver.
 * To migrate to LovyanGFX or other drivers, simply implement a new subclass.
 */
class DisplayEngine {
public:
    virtual ~DisplayEngine() {}

    // --- Lifecycle Management ---
    virtual bool init(int w, int h) = 0;
    virtual void swapBuffers() = 0;
    virtual void pushToDisplay(int x, int y) = 0;
    virtual void clearAll(uint16_t color) = 0;
    virtual void startWrite() = 0;
    virtual void endWrite() = 0;

    // --- Basic Drawing ---
    virtual void fillScreen(uint16_t color) = 0;
    virtual void fillRect(int x, int y, int w, int h, uint16_t color) = 0;
    virtual void drawRect(int x, int y, int w, int h, uint16_t color) = 0;
    virtual void fillRoundRect(int x, int y, int w, int h, int r, uint16_t color) = 0;
    virtual void drawRoundRect(int x, int y, int w, int h, int r, uint16_t color) = 0;
    virtual void fillCircle(int x, int y, int r, uint16_t color) = 0;
    virtual void drawFastHLine(int x, int y, int w, uint16_t color) = 0;

    // --- Text Rendering ---
    virtual void setTextColor(uint16_t color) = 0;
    virtual void setTextColor(uint16_t color, uint16_t bg) = 0;
    virtual void setTextFont(int font) = 0;
    virtual void setTextDatum(TextDatum datum) = 0; 
    virtual void drawString(const char* s, int x, int y) = 0;
    virtual int  textWidth(const char* s) = 0;

    // --- Utility ---
    virtual uint16_t color565(uint8_t r, uint8_t g, uint8_t b) = 0;
};

#endif
