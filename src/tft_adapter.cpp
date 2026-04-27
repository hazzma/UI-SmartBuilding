#include "tft_adapter.h"

TFTAdapter::TFTAdapter(TFT_eSPI* tft_ptr) 
    : _tft(tft_ptr), _canvas0(tft_ptr), _canvas1(tft_ptr) {
    _active_canvas = &_canvas0;
}

bool TFTAdapter::init(int w, int h) {
    _w = w; _h = h;
    _canvas0.setColorDepth(16);
    void* ptr0 = _canvas0.createSprite(w, h);
    
    _canvas1.setColorDepth(16);
    void* ptr1 = _canvas1.createSprite(w, h);

    if (!ptr0 || !ptr1) {
        Serial.println("[HAL] Error: Sprite allocation failed!");
        return false;
    }
    return true;
}

void TFTAdapter::swapBuffers() {
    _active_canvas = (_active_canvas == &_canvas0) ? &_canvas1 : &_canvas0;
}

void TFTAdapter::pushToDisplay(int x, int y) {
    _active_canvas->pushSprite(x, y);
}

void TFTAdapter::clearAll(uint16_t color) {
    _tft->fillScreen(color);
    _canvas0.fillScreen(color);
    _canvas1.fillScreen(color);
}

void TFTAdapter::startWrite() {
    _tft->startWrite();
}

void TFTAdapter::endWrite() {
    _tft->endWrite();
}

void TFTAdapter::fillScreen(uint16_t color) {
    _active_canvas->fillScreen(color);
}

void TFTAdapter::fillRect(int x, int y, int w, int h, uint16_t color) {
    _active_canvas->fillRect(x, y, w, h, color);
}

void TFTAdapter::drawRect(int x, int y, int w, int h, uint16_t color) {
    _active_canvas->drawRect(x, y, w, h, color);
}

void TFTAdapter::fillRoundRect(int x, int y, int w, int h, int r, uint16_t color) {
    _active_canvas->fillRoundRect(x, y, w, h, r, color);
}

void TFTAdapter::drawRoundRect(int x, int y, int w, int h, int r, uint16_t color) {
    _active_canvas->drawRoundRect(x, y, w, h, r, color);
}

void TFTAdapter::fillCircle(int x, int y, int r, uint16_t color) {
    _active_canvas->fillCircle(x, y, r, color);
}

void TFTAdapter::drawFastHLine(int x, int y, int w, uint16_t color) {
    _active_canvas->drawFastHLine(x, y, w, color);
}

void TFTAdapter::setTextColor(uint16_t color) {
    _active_canvas->setTextColor(color);
}

void TFTAdapter::setTextColor(uint16_t color, uint16_t bg) {
    _active_canvas->setTextColor(color, bg);
}

void TFTAdapter::setTextFont(int font) {
    _active_canvas->setTextFont(font);
}

void TFTAdapter::setTextDatum(TextDatum datum) {
    uint8_t tft_datum = TL_DATUM;
    switch (datum) {
        case TextDatum::TopLeft:      tft_datum = TL_DATUM; break;
        case TextDatum::TopCenter:    tft_datum = TC_DATUM; break;
        case TextDatum::TopRight:     tft_datum = TR_DATUM; break;
        case TextDatum::MiddleLeft:   tft_datum = ML_DATUM; break;
        case TextDatum::MiddleCenter: tft_datum = MC_DATUM; break;
        case TextDatum::MiddleRight:  tft_datum = MR_DATUM; break;
        case TextDatum::BottomLeft:   tft_datum = BL_DATUM; break;
        case TextDatum::BottomCenter: tft_datum = BC_DATUM; break;
        case TextDatum::BottomRight:  tft_datum = BR_DATUM; break;
    }
    _active_canvas->setTextDatum(tft_datum);
}

void TFTAdapter::drawString(const char* s, int x, int y) {
    _active_canvas->drawString(s, x, y);
}

int TFTAdapter::textWidth(const char* s) {
    return _active_canvas->textWidth(s);
}

uint16_t TFTAdapter::color565(uint8_t r, uint8_t g, uint8_t b) {
    return _active_canvas->color565(r, g, b);
}
