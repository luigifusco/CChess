#ifndef INCLUDE_MOVE_H
#define INCLUDE_MOVE_H

#include <stdbool.h>
#include "gamestate.h"
#include "types.h"

#define INBOUNDS(x) (x >= 0 && x < 64)

int Move_GetPawnMoves(Move *moves, Gamestate *state, char pos, bool isWhite);

int Move_GetBishopMoves(Move *moves, Gamestate *state, char pos, bool isWhite);

int Move_GetRookMoves(Move *moves, Gamestate *state, char pos, bool isWhite);

int Move_GetKnightMoves(Move *moves, Gamestate *state, char pos, bool isWhite);

int Move_GetKingMoves(Move *moves, Gamestate *state, char pos, bool isWhite);

#endif
