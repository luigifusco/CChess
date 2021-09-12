#define SDL_MAIN_HANDLED

#include "gui.h"
#include "gamestate.h"
#include "move.h"
#include "minimax.h"
#include "constants.h"
#include "config.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
    GUI gui;
    Gamestate state, newState;
    Move *move;
    Config config;

    Config_GetConfig(&config);
    Gamestate_Init(&state);
    GUI_Init(&gui, config.windowWidth, config.windowHeight, config.reversed);
    Gamestate_GetMoves(&state);
    GUI_Render(&gui, &state, 1);
    if (config.gamemode == CPU) {
        for (;;) {
            printf("thinking...");
            move = MiniMax_GetMove(&state, &gui, config.minimaxDepth);
            puts("done");
            Gamestate_ApplyMove(&state, &state, move);
            GUI_ManageEvents(&gui);
            GUI_Render(&gui, &state, 1);
        }
    } else {
        for (;;) {
            if ((config.gamemode == WHITE && state.isWhite) ||
                (config.gamemode == BLACK && !state.isWhite)) {
                for (;;) {
                    move = GUI_GetMove(&gui, &state);
                    Gamestate_ApplyMove(&newState, &state, move);
                    if (!Gamestate_IsValid(&newState)) {
                        puts("invalid move");
                        GUI_Render(&gui, &state, 1);
                    } else break;
                }
                Gamestate_Copy(&state, &newState);
                GUI_Render(&gui, &state, 1);
            } else {
                printf("thinking...");
                move = MiniMax_GetMove(&state, &gui, config.minimaxDepth);
                puts("done");
                printf("score: %.1f\n", (double) Gamestate_Score(&state) / 100.);
                Gamestate_ApplyMove(&state, &state, move);
                GUI_ManageEvents(&gui);
                GUI_Render(&gui, &state, 1);
            }
        }
    }

    return 0;
}