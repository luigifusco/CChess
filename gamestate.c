#include "gamestate.h"
#include "score.h"

void Gamestate_Init(Gamestate *state) {
    int i;
    const char rows[4][8] = {
            {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
            {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}
    };

    state->wSmallCastle = true;
    state->wBigCastle = true;
    state->bSmallCastle = true;
    state->bBigCastle = true;
    state->isWhite = true;
    state->score = 0;
    memset(state->board, 0, 64);
    for (i = 0; i < 8; ++i) {
        state->board[i] = rows[0][i];
        state->board[8 + i] = rows[1][i];
        state->board[48 + i] = rows[2][i];
        state->board[56 + i] = rows[3][i];
    }
}

int Gamestate_Score(Gamestate *state) {
    int i;
    char *board = (char *) state->board;
    int score = 0;

    for (i = 0; i < 64; ++i) {
        switch (board[i]) {
            case 'p':
                score -= 100;
                score -= pTable[63 - i];
                break;
            case 'b':
                score -= 330;
                score -= bTable[63 - i];
                break;
            case 'r':
                score -= 500;
                score -= rTable[63 - i];
                break;
            case 'n':
                score -= 320;
                score -= nTable[63 - i];
                break;
            case 'q':
                score -= 900;
                score -= qTable[63 - i];
                break;
            case 'k':
                score -= kTable[63 - i];
                break;
            case 'P':
                score += 100;
                score += pTable[i];
                break;
            case 'B':
                score += 330;
                score += bTable[i];
                break;
            case 'R':
                score += 500;
                score += rTable[i];
                break;
            case 'N':
                score += 320;
                score += nTable[i];
                break;
            case 'Q':
                score += 900;
                score += qTable[i];
                break;
            case 'K':
                score += kTable[i];
                break;
        }
    }

    return score;
}

void Gamestate_GetMoves(Gamestate *state) {
    int i, nMoves = 0;

    if (state->isWhite)
        for (i = 0; i < 64; ++i) {
            switch (state->board[i]) {
                case 'P':
                    nMoves += Move_GetPawnMoves(state->moves + nMoves, state, i, true);
                    break;
                case 'B':
                    nMoves += Move_GetBishopMoves(state->moves + nMoves, state, i, true);
                    break;
                case 'R':
                    nMoves += Move_GetRookMoves(state->moves + nMoves, state, i, true);
                    break;
                case 'N':
                    nMoves += Move_GetKnightMoves(state->moves + nMoves, state, i, true);
                    break;
                case 'Q':
                    nMoves += Move_GetBishopMoves(state->moves + nMoves, state, i, true);
                    nMoves += Move_GetRookMoves(state->moves + nMoves, state, i, true);
                    break;
                case 'K':
                    nMoves += Move_GetKingMoves(state->moves + nMoves, state, i, true);
                    break;
            }
        }
    else
        for (i = 0; i < 64; ++i) {
            switch (state->board[i]) {
                case 'p':
                    nMoves += Move_GetPawnMoves(state->moves + nMoves, state, i, false);
                    break;
                case 'b':
                    nMoves += Move_GetBishopMoves(state->moves + nMoves, state, i, false);
                    break;
                case 'r':
                    nMoves += Move_GetRookMoves(state->moves + nMoves, state, i, false);
                    break;
                case 'n':
                    nMoves += Move_GetKnightMoves(state->moves + nMoves, state, i, false);
                    break;
                case 'q':
                    nMoves += Move_GetBishopMoves(state->moves + nMoves, state, i, false);
                    nMoves += Move_GetRookMoves(state->moves + nMoves, state, i, false);
                    break;
                case 'k':
                    nMoves += Move_GetKingMoves(state->moves + nMoves, state, i, false);
                    break;
            }
        }


    state->nMoves = nMoves;
}

bool Gamestate_IsValid(Gamestate *state) {
    char pos;
    Move moves[27];
    int nMoves, i, diff;

    if (!state->isWhite) {
        for (pos = 0; state->board[pos] != 'K'; ++pos);
        nMoves = Move_GetBishopMoves(moves, state, pos, true);
        for (i = 0; i < nMoves; ++i) {
            switch (state->board[moves[i].to]) {
                case 'q':
                case 'b':
                    return false;
                case 'k':
                    diff = moves[i].from - moves[i].to;
                    if (diff == 7 || diff == 9 ||
                        diff == -7 || diff == -9)
                        return false;
                case 'p':
                    diff = moves[i].from - moves[i].to;
                    if (diff == 7 || diff == 9) return false;

            }
        }
        nMoves = Move_GetRookMoves(moves, state, pos, true);
        for (i = 0; i < nMoves; ++i) {
            switch (state->board[moves[i].to]) {
                case 'q':
                case 'r':
                    return false;
                case 'k':
                    diff = moves[i].from - moves[i].to;
                    if (diff == 8 || diff == -8 ||
                        diff == 1 || diff == -1)
                        return false;
            }
        }
        nMoves = Move_GetKnightMoves(moves, state, pos, true);
        for (i = 0; i < nMoves; ++i)
            if (state->board[moves[i].to] == 'n')
                return false;
    } else {
        for (pos = 0; state->board[pos] != 'k'; ++pos);
        nMoves = Move_GetBishopMoves(moves, state, pos, false);
        for (i = 0; i < nMoves; ++i) {
            switch (state->board[moves[i].to]) {
                case 'Q':
                case 'B':
                    return false;
                case 'K':
                    diff = moves[i].from - moves[i].to;
                    if (diff == 7 || diff == 9 ||
                        diff == -7 || diff == -9)
                        return false;
                case 'P':
                    diff = moves[i].from - moves[i].to;
                    if (diff == -7 || diff == -9) return false;

            }
        }
        nMoves = Move_GetRookMoves(moves, state, pos, false);
        for (i = 0; i < nMoves; ++i) {
            switch (state->board[moves[i].to]) {
                case 'Q':
                case 'R':
                    return false;
                case 'K':
                    diff = moves[i].from - moves[i].to;
                    if (diff == 8 || diff == -8 ||
                        diff == 1 || diff == -1)
                        return false;
            }
        }
        nMoves = Move_GetKnightMoves(moves, state, pos, false);
        for (i = 0; i < nMoves; ++i)
            if (state->board[moves[i].to] == 'N')
                return false;
    }

    return true;
}

bool Gamestate_IsNotCheck(Gamestate *state, char pos) {
    Move moves[27];
    int nMoves, i, diff;

    if (state->isWhite) {
        nMoves = Move_GetBishopMoves(moves, state, pos, true);
        for (i = 0; i < nMoves; ++i) {
            switch (state->board[moves[i].to]) {
                case 'q':
                case 'b':
                    return false;
                case 'k':
                    diff = moves[i].from - moves[i].to;
                    if (diff == 7 || diff == 9 ||
                        diff == -7 || diff == -9)
                        return false;
                case 'p':
                    diff = moves[i].from - moves[i].to;
                    if (diff == 7 || diff == 9) return false;

            }
        }
        nMoves = Move_GetRookMoves(moves, state, pos, true);
        for (i = 0; i < nMoves; ++i) {
            switch (state->board[moves[i].to]) {
                case 'q':
                case 'r':
                    return false;
                case 'k':
                    diff = moves[i].from - moves[i].to;
                    if (diff == 8 || diff == -8 ||
                        diff == 1 || diff == -1)
                        return false;
            }
        }
        nMoves = Move_GetKnightMoves(moves, state, pos, true);
        for (i = 0; i < nMoves; ++i)
            if (state->board[moves[i].to] == 'n')
                return false;
    } else {
        nMoves = Move_GetBishopMoves(moves, state, pos, false);
        for (i = 0; i < nMoves; ++i) {
            switch (state->board[moves[i].to]) {
                case 'Q':
                case 'B':
                    return false;
                case 'K':
                    diff = moves[i].from - moves[i].to;
                    if (diff == 7 || diff == 9 ||
                        diff == -7 || diff == -9)
                        return false;
                case 'P':
                    diff = moves[i].from - moves[i].to;
                    if (diff == -7 || diff == -9) return false;

            }
        }
        nMoves = Move_GetRookMoves(moves, state, pos, false);
        for (i = 0; i < nMoves; ++i) {
            switch (state->board[moves[i].to]) {
                case 'Q':
                case 'R':
                    return false;
                case 'K':
                    diff = moves[i].from - moves[i].to;
                    if (diff == 8 || diff == -8 ||
                        diff == 1 || diff == -1)
                        return false;
            }
        }
        nMoves = Move_GetKnightMoves(moves, state, pos, false);
        for (i = 0; i < nMoves; ++i)
            if (state->board[moves[i].to] == 'N')
                return false;
    }

    return true;
}

void Gamestate_ApplyMove(Gamestate *to, Gamestate *from, Move *move) {
    bool castled = false;

    memcpy(to->board, from->board, 64);
    to->isWhite = !from->isWhite;
    to->bBigCastle = from->bBigCastle;
    to->bSmallCastle = from->bSmallCastle;
    to->wBigCastle = from->wBigCastle;
    to->wSmallCastle = from->wSmallCastle;

    switch (move->from) {
        case 0:
            to->bBigCastle = false;
            break;
        case 7:
            to->bSmallCastle = false;
            break;
        case 56:
            to->wBigCastle = false;
            break;
        case 63:
            to->wSmallCastle = false;
            break;
        case 4:
            if (to->board[4] == 'k') {
                if (move->to == 2) {
                    castled = true;
                    to->board[0] = 0;
                    to->board[2] = 'k';
                    to->board[3] = 'r';
                    to->board[4] = 0;
                } else if (move->to == 6) {
                    castled = true;
                    to->board[4] = 0;
                    to->board[5] = 'r';
                    to->board[6] = 'k';
                    to->board[7] = 0;
                }
                to->bBigCastle = false;
                to->bSmallCastle = false;
            }
            break;
        case 60:
            if (to->board[60] == 'K') {
                if (move->to == 58) {
                    castled = true;
                    to->board[56] = 0;
                    to->board[58] = 'K';
                    to->board[59] = 'R';
                    to->board[60] = 0;
                } else if (move->to == 62) {
                    castled = true;
                    to->board[60] = 0;
                    to->board[61] = 'R';
                    to->board[62] = 'K';
                    to->board[63] = 0;
                }
                to->wBigCastle = false;
                to->wSmallCastle = false;
            }
            break;

    }
    if (!castled) {
        to->board[move->to] = to->board[move->from];
        to->board[move->from] = 0;
        if (move->to / 8 == 0 && to->board[move->to] == 'P') to->board[move->to] = 'Q';
        else if (move->to / 8 == 7 && to->board[move->to] == 'p') to->board[move->to] = 'q';
    }
}

void Gamestate_Copy(Gamestate *to, Gamestate *from) {
    memcpy(to->board, from->board, 64);
    to->isWhite = from->isWhite;
    to->bBigCastle = from->bBigCastle;
    to->bSmallCastle = from->bSmallCastle;
    to->wBigCastle = from->wBigCastle;
    to->wSmallCastle = from->wSmallCastle;
}
