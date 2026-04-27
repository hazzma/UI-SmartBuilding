#ifndef TFT_ADAPTER_H
#define TFT_ADAPTER_H

#include "display_engine.h"
#include <TFT_eSPI.h>

/**
 * TFTAdapter - Implementation of DisplayEngine using TFT_eSPI.
 * Uses double-buffered sprites in PSRAM for smooth rendering.
 */
class TFTAdapter : public DisplayEngine {
public:
    TFTAdapter(TFT_eSPI* tft_ptr);
    
    bool init(int w, int h) override;
    void swapBuffers() override;
    void pushToDisplay(int x, int y) override;
    void clearAll(uint16_t color) override;
    void startWrite() override;
    void endWrite() override;

    void fillScreen(uint16_t color) override;
    void fillRect(int x, int y, int w, int h, uint16_t color) override;
    void drawRect(int x, int y, int w, int h, uint16_t color) override;
    void fillRoundRect(int x, int y, int w, int h, int r, uint16_t color) override;
    void drawRoundRect(int x, int y, int w, int h, int r, uint16_t color) override;
    void fillCircle(int x, int y, int r, uint16_t color) override;
    void drawFastHLine(int x, int y, int w, uint16_t color) override;

    void setTextColor(uint16_t color) override;
    void setTextColor(uint16_t color, uint16_t bg) override;
    void setTextFont(int font) override;
    void setTextDatum(TextDatum datum) override;
    void drawString(const char* s, int x, int y) override;
    int  textWidth(const char* s) override;

    uint16_t color565(uint8_t r, uint8_t g, uint8_t b) override;

private:
    TFT_eSPI*   _tft;
    TFT_eSprite _canvas0;
    TFT_eSprite _canvas1;
    TFT_eSprite* _active_canvas;
    int _w, _h;
};

#endif
