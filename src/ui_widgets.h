#ifndef UI_WIDGETS_H
#define UI_WIDGETS_H

#include "display.h"
#include "display_engine.h"

// FSD 4.2: Abstraction Layer for Display Engine
extern DisplayEngine* p_engine;

// Macro to keep old code working: 'canvas' now redirects to the Engine Interface
#define canvas (*p_engine)
#define p_canvas p_engine

void widgets_init();
void widgets_swap();

// Design tokens used by widgets
#define CARD_RAD 8

// Widget prototypes
void drawCardBase(int x, int y, int w, int h, uint16_t color);
void drawTempCard(int x, int y, int w, int h, const char* label, float value, bool error);
void drawToggleButton(int x, int y, int w, int h, const char* label, bool state);
void drawUpDownButton(int x, int y, int w, int h, const char* label, bool isUp);
void drawPresenceBadge(int x, int y, int w, int h, bool detected);
void drawLuxCard(int x, int y, int w, int h, float lux);
void drawCO2Card(int x, int y, int w, int h, int co2);
void drawNotifBar(bool wifi, bool lan, bool mqtt, const char* conn_status, const char* room_name, const char* time_str);

#endif
