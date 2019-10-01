#include "config.h"

void Config_GetConfig(Config *config) {
    char in;
    puts("---WELCOME TO CHESSPLUS---");
    puts("Select gamemode (1 is default:");
    puts("1. White vs CPU\t2. Black vs CPU\t3. CPU vs CPU");
    putchar('>');
    in = getchar();
    if (in == '2') config->gamemode = BLACK;
    else if (in == '3') config->gamemode = CPU;
    else config->gamemode = WHITE;
    if (in != '\n') while (getchar() != '\n');
    puts("Select difficulty (1 to 6, 4 is default):");
    putchar('>');
    in = getchar();
    if (in >= '1' && in <= '6') config->minimaxDepth = in - '0';
    else config->minimaxDepth = 4;
    if (in != '\n') while (getchar() != '\n');
    puts("Select board mode (1 is default):");
    puts("1. Straight\t2. Reversed");
    putchar('>');
    in = getchar();
    if (in == '2') config->reversed = config->gamemode == BLACK ? false : true;
    else config->reversed = config->gamemode == BLACK ? true : false;
    if (in != '\n') while (getchar() != '\n');
    puts("Select window size (2 is default):");
    puts("1. 500x500\t2. 800x800\t3. 1000x1000");
    putchar('>');
    in = getchar();
    if (in == '1') config->windowHeight = config->windowWidth = 500;
    else if (in == '3') config->windowHeight = config->windowWidth = 1000;
    else config->windowHeight = config->windowWidth = 800;
    if (in != '\n') while (getchar() != '\n');
}