#include "minimax.h"
#include <omp.h>

Move *MiniMax_GetMove(Gamestate *state, GUI *gui, int depth) {
    int values[140], toRet;
    int i, idToRet = 0;

    if (!Gamestate_IsValid(state))
        exit(0);

    Gamestate_GetMoves(state);

#pragma omp parallel for
    for (i = 0; i < state->nMoves; ++i) {
        values[i] = MiniMax_Recursive(state, state->moves + i, INT_MIN, INT_MAX, depth);
        GUI_ManageEvents(gui);
    }

    toRet = values[0];
    if (state->isWhite) {
        for (i = 1; i < state->nMoves; ++i)
            if (values[i] > toRet) {
                toRet = values[i];
                idToRet = i;
            }
        if (toRet == INT_MIN)
            exit(0);
    } else {
        for (i = 1; i < state->nMoves; ++i)
            if (values[i] < toRet) {
                toRet = values[i];
                idToRet = i;
            }
        if (toRet == INT_MAX)
            exit(0);
    }

    return state->moves + idToRet;
}

int MiniMax_Recursive(Gamestate *prevState, Move *move, int alpha, int beta, int depth) {
    Gamestate newState;
    int values[140], toRet, val;
    int i;

    Gamestate_ApplyMove(&newState, prevState, move);

    if (!Gamestate_IsValid(&newState))
        return prevState->isWhite ? INT_MIN : INT_MAX;


    if (depth == 0) {
        return Gamestate_Score(&newState);
    }

    Gamestate_GetMoves(&newState);

    if (newState.isWhite) {
        toRet = INT_MIN;
        for (i = 0; i < newState.nMoves; ++i) {
            val = MiniMax_Recursive(&newState, newState.moves + i, alpha, beta, depth - 1);
            if (val > toRet)
                toRet = val;
            if (val > alpha)
                alpha = val;
            if (beta <= alpha)
                return toRet;
        }
    } else {
        toRet = INT_MAX;
        for (i = 0; i < newState.nMoves; ++i) {
            val = MiniMax_Recursive(&newState, newState.moves + i, alpha, beta, depth - 1);
            if (val < toRet)
                toRet = val;
            if (val < beta)
                beta = val;
            if (beta <= alpha)
                return toRet;
        }
    }

    return toRet;
}