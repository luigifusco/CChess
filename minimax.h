#ifndef INCLUDE_MINIMAX_H
#define INCLUDE_MINIMAX_H

#include "gamestate.h"
#include "move.h"
#include "gui.h"
#include "constants.h"
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>

Move *MiniMax_GetMove(Gamestate *state, GUI *gui, int depth);

int MiniMax_Recursive(Gamestate *prevState, Move *move, int alpha, int beta, int depth);

#endif