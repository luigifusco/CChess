# CChess
Implementation of a chess playing program in C, using the SDL2 library for graphics and OpenMP for multithreading.
The engine is based on a MiniMax search with alpha-beta pruning.

Compile with:

```bash
gcc *.c -fopenmp -lSDL2 -O3 -o cchess
```

### Sources
Chess pieces: http://commons.wikimedia.org/wiki/Template:SVG_chess_pieces.<br>
Chessboard: https://upload.wikimedia.org/wikipedia/commons/thumb/d/d7/Chessboard480.svg/1200px-Chessboard480.svg.png
