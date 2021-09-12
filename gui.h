#ifndef INCLUDE_GUI_H
#define INCLUDE_GUI_H

#include <SDL2/SDL.h>
#include "gamestate.h"
#include "constants.h"
#include "types.h"
#include <stdlib.h>

#ifdef _WIN32

#include <windows.h>

#endif

void GUI_Init(GUI *gui, int w, int h, bool reversed);

void GUI_Render(GUI *gui, Gamestate *gamestate, int present);

void GUI_ManageEvents(GUI *gui);

void GUI_MakeDPIAware();

Move *GUI_GetMove(GUI *gui, Gamestate *state);

void GUI_HighlightPosition(GUI *gui, char pos);

#endif