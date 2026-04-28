#include "ui_widgets.h"
#include "data.h"
#include <stdio.h>

// ── Display Engine Reference ───────────────────────────────
DisplayEngine* p_engine = nullptr;

void widgets_init() {
    // Widgets are now engine-agnostic. 
    // p_engine must be assigned before calling any widget functions.
}
    Serial.println("\n[HAL] --- Display Engine Initialization ---");
    
    if (p_engine->init(480, 320)) {
        Serial.println("[HAL] Engine initialized successfully ✓");
    } else {
        Serial.println("[HAL] Engine initialization FAILED!");
    }
    
    Serial.printf("[MEM] Free PSRAM: %d KB\n", ESP.getFreePsram() / 1024);
    Serial.println("[HAL] --------------------------\n");
    
    p_engine->fillScreen(COLOR_BG_MAIN);
}

void widgets_swap() {
    p_engine->swapBuffers();
}

// ── Widget Implementations ──────────────────────────────────────

void drawCardBase(int x, int y, int w, int h, uint16_t color) {
    p_engine->fillRoundRect(x, y, w, h, CARD_RAD, color);
    p_engine->drawRoundRect(x, y, w, h, CARD_RAD, p_engine->color565(40, 50, 80)); // Border
}

void drawTempCard(int x, int y, int w, int h, const char* label, float temp, bool error) {
    drawCardBase(x, y, w, h, COLOR_CARD_BG);
    
    p_engine->setTextColor(COLOR_TEXT_SEC);
    p_engine->setTextFont(2);
    p_engine->drawString(label, x + 8, y + 8);
    
    if (error) {
        p_engine->setTextColor(COLOR_STAT_ERR);
        p_engine->drawString("ERROR", x + 8, y + 35);
    } else if (temp < -50.0f) {
        p_engine->setTextColor(COLOR_TEXT_SEC);
        p_engine->setTextFont(4);
        p_engine->drawString("NULL", x + 8, y + 32);
    } else {
        p_engine->setTextColor(COLOR_ACCENT_MAIN);
        p_engine->setTextFont(4);
        char val_buf[16];
        snprintf(val_buf, sizeof(val_buf), "%.1f", temp);
        p_engine->drawString(val_buf, x + 8, y + 32);
        
        int off_x = p_engine->textWidth(val_buf);
        p_engine->setTextFont(2);
        p_engine->drawString("C", x + 8 + off_x + 4, y + 35);
    }
}

void drawToggleButton(int x, int y, int w, int h, const char* label, bool state) {
    uint16_t btnColor = state ? COLOR_STAT_ON : COLOR_STAT_OFF;
    drawCardBase(x, y, w, h, COLOR_CARD_BG);
    
    int swW = 40, swH = 20;
    int swX = x + w - swW - 10;
    int swY = y + (h - swH) / 2;
    p_engine->fillRoundRect(swX, swY, swW, swH, 10, p_engine->color565(30, 40, 60));
    
    int kR = 8;
    int kX = state ? (swX + swW - kR - 2) : (swX + kR + 2);
    p_engine->fillCircle(kX, swY + swH/2, kR, btnColor);
    
    p_engine->setTextColor(COLOR_TEXT_MAIN);
    p_engine->setTextFont(2);
    p_engine->setTextDatum(TextDatum::MiddleLeft);
    p_engine->drawString(label, x + 12, y + h/2);
    p_engine->setTextDatum(TextDatum::TopLeft);
}

void drawUpDownButton(int x, int y, int w, int h, const char* label, bool isUp) {
    drawCardBase(x, y, w, h, COLOR_CARD_BG);
    
    p_engine->setTextFont(2);
    p_engine->setTextDatum(TextDatum::MiddleCenter);
    p_engine->drawString(label, x + w/2, y + h/2);
    p_engine->setTextDatum(TextDatum::TopLeft);
}

void drawPresenceBadge(int x, int y, int w, int h, bool detected) {
    drawCardBase(x, y, w, h, COLOR_CARD_BG);
    
    p_engine->setTextColor(COLOR_TEXT_SEC);
    p_engine->setTextFont(2);
    p_engine->drawString("Presence", x + 10, y + 8);
    
    uint16_t dotColor = detected ? COLOR_STAT_ON : COLOR_STAT_OFF;
    p_engine->fillCircle(x + 18, y + 35, 6, dotColor);
    
    p_engine->setTextColor(COLOR_TEXT_MAIN);
    p_engine->drawString(detected ? "Detected" : "Empty", x + 35, y + 27);
}

void drawCO2Card(int x, int y, int w, int h, int co2) {
    uint16_t valColor = COLOR_STAT_ON;
    if (co2 > 1500) valColor = COLOR_STAT_ERR;
    else if (co2 > 1000) valColor = COLOR_STAT_WARN;

    drawCardBase(x, y, w, h, COLOR_CARD_BG);
    
    p_engine->setTextFont(2);
    p_engine->setTextColor(COLOR_TEXT_SEC);
    p_engine->setTextDatum(TextDatum::TopLeft);
    p_engine->drawString("CO2", x + 10, y + 8);
    
    p_engine->setTextColor(valColor);
    p_engine->setTextFont(4);
    p_engine->setTextDatum(TextDatum::MiddleCenter);
    char buf[16];
    if (co2 == -1) {
        strcpy(buf, "NULL");
        p_engine->setTextColor(COLOR_TEXT_SEC);
    } else {
        snprintf(buf, 16, "%d", co2);
    }
    p_engine->drawString(buf, x + w/2, y + h/2 + 5);
    
    p_engine->setTextFont(2);
    p_engine->setTextColor(COLOR_TEXT_SEC);
    p_engine->setTextDatum(TextDatum::TopLeft);
    p_engine->drawString("ppm", x + w - 25, y + h - 15);
    p_engine->fillCircle(x + w - 15, y + 15, 4, valColor);
}

void drawNotifBar(bool wifi, bool lan, bool mqtt, const char* conn_status, const char* room_name, const char* time_str) {
    p_engine->fillRect(0, 0, 480, 28, COLOR_BG_MAIN);
    p_engine->drawFastHLine(0, 27, 480, p_engine->color565(40, 50, 80));
    
    p_engine->setTextColor(COLOR_TEXT_MAIN);
    p_engine->setTextFont(2);
    
    p_engine->fillRect(10, 14 - 6, 20, 3, COLOR_TEXT_MAIN);
    p_engine->fillRect(10, 14, 20, 3, COLOR_TEXT_MAIN);
    p_engine->fillRect(10, 14 + 6, 20, 3, COLOR_TEXT_MAIN);

    p_engine->setTextColor(COLOR_ACCENT_MAIN);
    p_engine->setTextFont(4);
    p_engine->setTextDatum(TextDatum::MiddleCenter);
    p_engine->drawString(time_str, 240, 14);
    
    p_engine->setTextFont(2);
    if (conn_status && strlen(conn_status) > 0) {
        if (strstr(conn_status, "Fail") != nullptr || strstr(conn_status, "DISCONNECTED") != nullptr) {
            p_engine->setTextColor(COLOR_STAT_ERR);
        } else if (strstr(conn_status, "Connecting") != nullptr) {
            p_engine->setTextColor(p_engine->color565(255, 165, 0)); 
        } else {
            p_engine->setTextColor(COLOR_STAT_ON);
        }
        p_engine->setTextDatum(TextDatum::MiddleRight);
        p_engine->drawString(conn_status, 190, 14);
    }
    
    if (g_state.sensor.human_presence) {
        p_engine->setTextColor(COLOR_STAT_ON);
        p_engine->setTextDatum(TextDatum::MiddleLeft);
        p_engine->drawString("PRES", 290, 14);
    }
    
    p_engine->setTextDatum(TextDatum::TopLeft);
    
    int iconX = 390; 
    p_engine->fillCircle(iconX, 14, 4, wifi ? COLOR_STAT_ON : COLOR_STAT_ERR);
    p_engine->fillCircle(iconX + 12, 14, 4, lan ? COLOR_STAT_ON : COLOR_STAT_ERR);
    p_engine->fillCircle(iconX + 24, 14, 4, mqtt ? COLOR_STAT_ON : COLOR_STAT_ERR);
}

void drawLuxCard(int x, int y, int w, int h, float lux) {
    drawCardBase(x, y, w, h, COLOR_CARD_BG);
    
    p_engine->setTextFont(2);
    p_engine->drawString("Luminance", x + 10, y + 8);
    
    char buf[16];
    if (lux < 0) {
        strcpy(buf, "NULL");
        p_engine->setTextColor(COLOR_TEXT_SEC);
    } else {
        snprintf(buf, sizeof(buf), "%.0f lx", lux);
        p_engine->setTextColor(COLOR_TEXT_MAIN);
    }
    
    p_engine->setTextFont(4);
    p_engine->setTextDatum(TextDatum::MiddleCenter);
    p_engine->drawString(buf, x + w/2, y + h/2 + 5);
    p_engine->setTextDatum(TextDatum::TopLeft);
}
