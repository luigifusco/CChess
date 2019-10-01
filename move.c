#include "move.h"

int Move_GetPawnMoves(Move *moves, Gamestate *state, char pos, bool isWhite) {
    char move;
    char *board = state->board;
    int i = 0;

    if (isWhite) {
        move = pos - 7;
        if (pos % 8 != 7 && ISBLACK(board[move])) moves[i++] = (Move) {.from = pos, .to = move};
        move = pos - 9;
        if (pos % 8 != 0 && ISBLACK(board[move])) moves[i++] = (Move) {.from = pos, .to = move};
        move = pos - 8;
        if (ISFREE(board[move])) {
            moves[i++] = (Move) {.from = pos, .to = move};
            move = pos - 16;
            if (pos / 8 == 6 && ISFREE(board[move])) moves[i++] = (Move) {.from = pos, .to = move};
        }
    } else {
        move = pos + 7;
        if (pos % 8 != 0 && ISWHITE(board[move])) moves[i++] = (Move) {.from = pos, .to = move};
        move = pos + 9;
        if (pos % 8 != 7 && ISWHITE(board[move])) moves[i++] = (Move) {.from = pos, .to = move};
        move = pos + 8;
        if (ISFREE(board[move])) {
            moves[i++] = (Move) {.from = pos, .to = move};
            move = pos + 16;
            if (pos / 8 == 1 && ISFREE(board[move])) moves[i++] = (Move) {.from = pos, .to = move};
        }
    }

    return i;
}

int Move_GetBishopMoves(Move *moves, Gamestate *state, char pos, bool isWhite) {
    char move;
    char *board = state->board;
    int i = 0;

    if (pos % 8 != 0 && pos / 8 != 0) {
        move = pos;
        do {
            move -= 9;
            if (ISFREE(board[move])) {
                moves[i++] = (Move) {.from = pos, .to = move};
            } else if ((isWhite && ISBLACK(board[move])) || (!isWhite && ISWHITE(board[move]))) {
                moves[i++] = (Move) {.from = pos, .to = move};
                break;
            } else break;
        } while (move % 8 != 0 && move / 8 != 0);
    }
    if (pos % 8 != 0 && pos / 8 != 7) {
        move = pos;
        do {
            move += 7;
            if (ISFREE(board[move])) {
                moves[i++] = (Move) {.from = pos, .to = move};
            } else if ((isWhite && ISBLACK(board[move])) || (!isWhite && ISWHITE(board[move]))) {
                moves[i++] = (Move) {.from = pos, .to = move};
                break;
            } else break;
        } while (move % 8 != 0 && move / 8 != 7);
    }
    if (pos % 8 != 7 && pos / 8 != 0) {
        move = pos;
        do {
            move -= 7;
            if (ISFREE(board[move])) {
                moves[i++] = (Move) {.from = pos, .to = move};
            } else if ((isWhite && ISBLACK(board[move])) || (!isWhite && ISWHITE(board[move]))) {
                moves[i++] = (Move) {.from = pos, .to = move};
                break;
            } else break;
        } while (move % 8 != 7 && move / 8 != 0);
    }
    if (pos % 8 != 7 && pos / 8 != 7) {
        move = pos;
        do {
            move += 9;
            if (ISFREE(board[move])) {
                moves[i++] = (Move) {.from = pos, .to = move};
            } else if ((isWhite && ISBLACK(board[move])) || (!isWhite && ISWHITE(board[move]))) {
                moves[i++] = (Move) {.from = pos, .to = move};
                break;
            } else break;
        } while (move % 8 != 7 && move / 8 != 7);
    }

    return i;
}

int Move_GetRookMoves(Move *moves, Gamestate *state, char pos, bool isWhite) {
    char move;
    char *board = state->board;
    int i = 0;

    if (pos / 8 != 0) {
        move = pos;
        do {
            move -= 8;
            if (ISFREE(board[move])) {
                moves[i++] = (Move) {.from = pos, .to = move};
            } else if ((isWhite && ISBLACK(board[move])) || (!isWhite && ISWHITE(board[move]))) {
                moves[i++] = (Move) {.from = pos, .to = move};
                break;
            } else break;
        } while (move / 8 != 0);
    }
    if (pos / 8 != 7) {
        move = pos;
        do {
            move += 8;
            if (ISFREE(board[move])) {
                moves[i++] = (Move) {.from = pos, .to = move};
            } else if ((isWhite && ISBLACK(board[move])) || (!isWhite && ISWHITE(board[move]))) {
                moves[i++] = (Move) {.from = pos, .to = move};
                break;
            } else break;
        } while (move / 8 != 7);
    }
    if (pos % 8 != 7) {
        move = pos;
        do {
            move++;
            if (ISFREE(board[move])) {
                moves[i++] = (Move) {.from = pos, .to = move};
            } else if ((isWhite && ISBLACK(board[move])) || (!isWhite && ISWHITE(board[move]))) {
                moves[i++] = (Move) {.from = pos, .to = move};
                break;
            } else break;
        } while (move % 8 != 7);
    }
    if (pos % 8 != 0) {
        move = pos;
        do {
            move--;
            if (ISFREE(board[move])) {
                moves[i++] = (Move) {.from = pos, .to = move};
            } else if ((isWhite && ISBLACK(board[move])) || (!isWhite && ISWHITE(board[move]))) {
                moves[i++] = (Move) {.from = pos, .to = move};
                break;
            } else break;
        } while (move % 8 != 0);
    }

    return i;
}

int Move_GetKnightMoves(Move *moves, Gamestate *state, char pos, bool isWhite) {
    char move;
    char *board = state->board;
    int i = 0;

    if (pos / 8 >= 2) {
        move = pos - 17;
        if (pos % 8 >= 1)
            if (ISFREE(board[move]) || (isWhite && ISBLACK(board[move])) || (!isWhite && ISWHITE(board[move])))
                moves[i++] = (Move) {.from = pos, .to = move};
        move = pos - 15;
        if (pos % 8 <= 6)
            if (ISFREE(board[move]) || (isWhite && ISBLACK(board[move])) || (!isWhite && ISWHITE(board[move])))
                moves[i++] = (Move) {.from = pos, .to = move};
    }
    if (pos / 8 <= 5) {
        move = pos + 15;
        if (pos % 8 >= 1)
            if (ISFREE(board[move]) || (isWhite && ISBLACK(board[move])) || (!isWhite && ISWHITE(board[move])))
                moves[i++] = (Move) {.from = pos, .to = move};
        move = pos + 17;
        if (pos % 8 <= 6)
            if (ISFREE(board[move]) || (isWhite && ISBLACK(board[move])) || (!isWhite && ISWHITE(board[move])))
                moves[i++] = (Move) {.from = pos, .to = move};
    }
    if (pos / 8 >= 1) {
        move = pos - 10;
        if (pos % 8 >= 2)
            if (ISFREE(board[move]) || (isWhite && ISBLACK(board[move])) || (!isWhite && ISWHITE(board[move])))
                moves[i++] = (Move) {.from = pos, .to = move};
        move = pos - 6;
        if (pos % 8 <= 5)
            if (ISFREE(board[move]) || (isWhite && ISBLACK(board[move])) || (!isWhite && ISWHITE(board[move])))
                moves[i++] = (Move) {.from = pos, .to = move};
    }
    if (pos / 8 <= 6) {
        move = pos + 6;
        if (pos % 8 >= 2)
            if (ISFREE(board[move]) || (isWhite && ISBLACK(board[move])) || (!isWhite && ISWHITE(board[move])))
                moves[i++] = (Move) {.from = pos, .to = move};
        move = pos + 10;
        if (pos % 8 <= 5)
            if (ISFREE(board[move]) || (isWhite && ISBLACK(board[move])) || (!isWhite && ISWHITE(board[move])))
                moves[i++] = (Move) {.from = pos, .to = move};
    }

    return i;
}

int Move_GetKingMoves(Move *moves, Gamestate *state, char pos, bool isWhite) {
    char move;
    char *board = state->board;
    int i = 0;

    if (pos / 8 > 0) {
        move = pos - 8;
        if (ISFREE(board[move]) || (isWhite && ISBLACK(board[move])) || (!isWhite && ISWHITE(board[move])))
            moves[i++] = (Move) {.from = pos, .to = move};
        move = pos - 9;
        if (pos % 8 > 0)
            if (ISFREE(board[move]) || (isWhite && ISBLACK(board[move])) || (!isWhite && ISWHITE(board[move])))
                moves[i++] = (Move) {.from = pos, .to = move};
        move = pos - 7;
        if (pos % 8 < 7)
            if (ISFREE(board[move]) || (isWhite && ISBLACK(board[move])) || (!isWhite && ISWHITE(board[move])))
                moves[i++] = (Move) {.from = pos, .to = move};
    }
    if (pos / 8 < 7) {
        move = pos + 8;
        if (ISFREE(board[move]) || (isWhite && ISBLACK(board[move])) || (!isWhite && ISWHITE(board[move])))
            moves[i++] = (Move) {.from = pos, .to = move};
        move = pos + 7;
        if (pos % 8 > 0)
            if (ISFREE(board[move]) || (isWhite && ISBLACK(board[move])) || (!isWhite && ISWHITE(board[move])))
                moves[i++] = (Move) {.from = pos, .to = move};
        move = pos + 9;
        if (pos % 8 < 7)
            if (ISFREE(board[move]) || (isWhite && ISBLACK(board[move])) || (!isWhite && ISWHITE(board[move])))
                moves[i++] = (Move) {.from = pos, .to = move};
    }
    move = pos - 1;
    if (pos % 8 > 0)
        if (ISFREE(board[move]) || (isWhite && ISBLACK(board[move])) || (!isWhite && ISWHITE(board[move])))
            moves[i++] = (Move) {.from = pos, .to = move};
    move = pos + 1;
    if (pos % 8 < 7)
        if (ISFREE(board[move]) || (isWhite && ISBLACK(board[move])) || (!isWhite && ISWHITE(board[move])))
            moves[i++] = (Move) {.from = pos, .to = move};

    if (state->isWhite) {
        if (state->wBigCastle && ISFREE(board[59]) && ISFREE(board[58]) && ISFREE(board[57]) &&
            Gamestate_IsNotCheck(state, 60) && Gamestate_IsNotCheck(state, 59) && Gamestate_IsNotCheck(state, 58))
            moves[i++] = (Move) {.from = 60, .to = 58};
        if (state->wSmallCastle && ISFREE(board[61]) && ISFREE(board[62]) &&
            Gamestate_IsNotCheck(state, 60) && Gamestate_IsNotCheck(state, 61) && Gamestate_IsNotCheck(state, 62))
            moves[i++] = (Move) {.from = 60, .to = 62};
    } else {
        if (state->bBigCastle && ISFREE(board[3]) && ISFREE(board[2]) && ISFREE(board[1]) &&
            Gamestate_IsNotCheck(state, 4) && Gamestate_IsNotCheck(state, 3) && Gamestate_IsNotCheck(state, 2))
            moves[i++] = (Move) {.from = 4, .to = 2};
        if (state->bSmallCastle && ISFREE(board[5]) && ISFREE(board[6]) &&
            Gamestate_IsNotCheck(state, 4) && Gamestate_IsNotCheck(state, 5) && Gamestate_IsNotCheck(state, 6))
            moves[i++] = (Move) {.from = 4, .to = 6};
    }

    return i;
}