#ifndef INCLUDE_TYPES_H
#define INCLUDE_TYPES_H

#include <SDL2/SDL.h>
#include <stdbool.h>

typedef enum {
    WHITE, BLACK, CPU
} Gamemode;

typedef struct {
    char from, to;
} Move;

typedef struct {
    char board[64];
    bool wSmallCastle, wBigCastle, bSmallCastle, bBigCastle;
    bool isWhite;
    double score;
    int nMoves;
    Move moves[140];
} Gamestate;

typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
    int w, h;
    SDL_Texture *pieces_texture, *board_texture;
    bool reversed;
} GUI;

typedef struct {
    int windowWidth, windowHeight;
    int minimaxDepth;
    Gamemode gamemode;
    bool reversed;
} Config;

#endif
