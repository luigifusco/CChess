#ifndef INCLUDE_GAMESTATE_H
#define INCLUDE_GAMESTATE_H

#include "move.h"
#include "types.h"
#include <stdbool.h>
#include <string.h>

#define ISBLACK(x) (x >= 'a' && x <= 'z')
#define ISWHITE(x) (x >= 'A' && x <= 'Z')
#define ISFREE(x) (x == 0)

int Gamestate_Score(Gamestate *state);

void Gamestate_Init(Gamestate *state);

void Gamestate_GetMoves(Gamestate *state);

bool Gamestate_IsValid(Gamestate *state);

void Gamestate_ApplyMove(Gamestate *to, Gamestate *from, Move *move);

void Gamestate_Copy(Gamestate *to, Gamestate *from);

bool Gamestate_IsNotCheck(Gamestate *state, char pos);

#endif