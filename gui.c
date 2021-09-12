#include <stdio.h>
#include "gui.h"

void GUI_Init(GUI *gui, int w, int h, bool reversed) {
    SDL_Surface *pieces_surface, *board_surface;

    GUI_MakeDPIAware();
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    gui->w = w;
    gui->h = h;
    gui->window = SDL_CreateWindow("Chessplus", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h,
                                   SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_SHOWN);
    gui->renderer = SDL_CreateRenderer(gui->window, -1, 0);
    pieces_surface = SDL_LoadBMP("chesspieces.bmp");
    board_surface = SDL_LoadBMP("chessboard.bmp");
    gui->pieces_texture = SDL_CreateTextureFromSurface(gui->renderer, pieces_surface);
    gui->board_texture = SDL_CreateTextureFromSurface(gui->renderer, board_surface);
    gui->reversed = reversed;
    SDL_FreeSurface(pieces_surface);
    SDL_FreeSurface(board_surface);
}

void GUI_MakeDPIAware() {
#ifdef _WIN32
    typedef enum PROCESS_DPI_AWARENESS {
        PROCESS_DPI_UNAWARE = 0,
        PROCESS_SYSTEM_DPI_AWARE = 1,
        PROCESS_PER_MONITOR_DPI_AWARE = 2
    } PROCESS_DPI_AWARENESS;

    void *userDLL;
    BOOL (WINAPI *SetProcessDPIAware)(void); // Vista and later
    void *shcoreDLL;
    HRESULT (WINAPI *SetProcessDpiAwareness)(PROCESS_DPI_AWARENESS dpiAwareness); // Windows 8.1 and later

    userDLL = SDL_LoadObject("USER32.DLL");
    if (userDLL) {
        SetProcessDPIAware = (BOOL(WINAPI *)(void)) SDL_LoadFunction(userDLL, "SetProcessDPIAware");
    }

    shcoreDLL = SDL_LoadObject("SHCORE.DLL");
    if (shcoreDLL) {
        SetProcessDpiAwareness = (HRESULT(WINAPI *)(PROCESS_DPI_AWARENESS)) SDL_LoadFunction(shcoreDLL,
                                                                                             "SetProcessDpiAwareness");
    }

    if (SetProcessDpiAwareness) {
        /* Try Windows 8.1+ version */
        HRESULT result = SetProcessDpiAwareness(PROCESS_PER_MONITOR_DPI_AWARE);
    } else if (SetProcessDPIAware) {
        /* Try Vista - Windows 8 version.
        This has a constant scale factor for all monitors.
        */
        BOOL success = SetProcessDPIAware();
    }
#endif
}

void GUI_Render(GUI *gui, Gamestate *gamestate, int present) {
    int i, j;
    char piece;
    SDL_Rect source, dest;

    source.w = PIECESIZE;
    source.h = PIECESIZE;
    dest.w = gui->w / 8;
    dest.h = gui->h / 8;

    SDL_RenderCopy(gui->renderer, gui->board_texture, NULL, NULL);

    for (i = 0; i < 8; ++i) {
        for (j = 0; j < 8; ++j) {
            dest.x = gui->reversed ? dest.w * (7 - j) : dest.w * j;
            dest.y = gui->reversed ? dest.h * (7 - i) : dest.h * i;
            piece = gamestate->board[i * 8 + j];
            switch (piece) {
                case 'p':
                    source.x = PIECESIZE * 5;
                    source.y = PIECESIZE;
                    SDL_RenderCopy(gui->renderer, gui->pieces_texture, &source, &dest);
                    break;
                case 'b':
                    source.x = PIECESIZE * 2;
                    source.y = PIECESIZE;
                    SDL_RenderCopy(gui->renderer, gui->pieces_texture, &source, &dest);
                    break;
                case 'r':
                    source.x = PIECESIZE * 4;
                    source.y = PIECESIZE;
                    SDL_RenderCopy(gui->renderer, gui->pieces_texture, &source, &dest);
                    break;
                case 'n':
                    source.x = PIECESIZE * 3;
                    source.y = PIECESIZE;
                    SDL_RenderCopy(gui->renderer, gui->pieces_texture, &source, &dest);
                    break;
                case 'q':
                    source.x = PIECESIZE * 1;
                    source.y = PIECESIZE;
                    SDL_RenderCopy(gui->renderer, gui->pieces_texture, &source, &dest);
                    break;
                case 'k':
                    source.x = 0;
                    source.y = PIECESIZE;
                    SDL_RenderCopy(gui->renderer, gui->pieces_texture, &source, &dest);
                    break;
                case 'P':
                    source.x = PIECESIZE * 5;
                    source.y = 0;
                    SDL_RenderCopy(gui->renderer, gui->pieces_texture, &source, &dest);
                    break;
                case 'B':
                    source.x = PIECESIZE * 2;
                    source.y = 0;
                    SDL_RenderCopy(gui->renderer, gui->pieces_texture, &source, &dest);
                    break;
                case 'R':
                    source.x = PIECESIZE * 4;
                    source.y = 0;
                    SDL_RenderCopy(gui->renderer, gui->pieces_texture, &source, &dest);
                    break;
                case 'N':
                    source.x = PIECESIZE * 3;
                    source.y = 0;
                    SDL_RenderCopy(gui->renderer, gui->pieces_texture, &source, &dest);
                    break;
                case 'Q':
                    source.x = PIECESIZE * 1;
                    source.y = 0;
                    SDL_RenderCopy(gui->renderer, gui->pieces_texture, &source, &dest);
                    break;
                case 'K':
                    source.x = 0;
                    source.y = 0;
                    SDL_RenderCopy(gui->renderer, gui->pieces_texture, &source, &dest);
                    break;
            }
        }
    }
    if (present)
        SDL_RenderPresent(gui->renderer);
}

void GUI_ManageEvents(GUI *gui) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) exit(0);
    }
}

Move *GUI_GetMove(GUI *gui, Gamestate *state) {
    bool clicked = false;
    SDL_Event event;
    char posFrom, posTo;
    int i;
    int sq = gui->w / 8;

    GUI_Render(gui, state, 1);
    Gamestate_GetMoves(state);

    for (;;) {
        if (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    exit(0);
                case SDL_MOUSEBUTTONDOWN:
                    if (!clicked) {
                        posFrom = gui->reversed ?
                                  ((gui->w - event.button.x) / sq) + 8 * ((gui->h - event.button.y) / sq) :
                                  (event.button.x / sq) + 8 * (event.button.y / sq);
                        for (i = 0; i < state->nMoves; ++i) {
                            if (state->moves[i].from == posFrom) {
                                clicked = true;
                                printf("selected %c%c\n", posFrom % 8 + 'a', 7 - posFrom / 8 + '1');
                                GUI_Render(gui, state, 0);
                                GUI_HighlightPosition(gui, posFrom);
                                SDL_RenderPresent(gui->renderer);
                                break;
                            }
                            if (i == state->nMoves) puts("invalid piece");
                        }
                    } else {
                        posTo = gui->reversed ?
                                ((gui->w - event.button.x) / sq) + 8 * ((gui->h - event.button.y) / sq) :
                                (event.button.x / sq) + 8 * (event.button.y / sq);
                        for (i = 0; i < state->nMoves; ++i) {
                            if (state->moves[i].from == posTo) {
                                posFrom = posTo;
                                printf("selected %c%c\n", posFrom % 8 + 'a', 7 - posFrom / 8 + '1');
                                GUI_Render(gui, state, 0);
                                GUI_HighlightPosition(gui, posFrom);
                                SDL_RenderPresent(gui->renderer);
                                break;
                            } else if (state->moves[i].from == posFrom &&
                                       state->moves[i].to == posTo) {
                                printf("targeted %c%c\n", posTo % 8 + 'a', 7 - posTo / 8 + '1');
                                return state->moves + i;
                            }
                        }
                        if (i == state->nMoves) {
                            puts("invalid target");
                            clicked = false;
                            GUI_Render(gui, state, 1);
                        }
                    }
            }
        }
        SDL_Delay(10);
    }
}

void GUI_HighlightPosition(GUI *gui, char pos) {
    SDL_Rect rect;
    int i;

    rect.x = gui->reversed ? (7 - pos % 8) * gui->w / 8 : (pos % 8) * gui->w / 8;
    rect.y = gui->reversed ? (7 - pos / 8) * (gui->h / 8) : (pos / 8) * gui->h / 8;
    rect.h = rect.w = gui->w / 8;
    SDL_SetRenderDrawColor(gui->renderer, 127, 127, 127, 255);
    for (i = 0; i < HIGHLIGHTWIDTH; ++i) {
        SDL_RenderDrawRect(gui->renderer, &rect);
        rect.x++;
        rect.y++;
        rect.w -= 2;
        rect.h -= 2;
    }
}
