#ifndef PBGBA_GAME_H
#define PBGBA_GAME_H

#include <tonc.h>

#define OBJ_BUFFER_MAX  128
#define SCREEN_W_CENTER 176
#define SCREEN_H_CENTER 96
#define MAX_BOARD_CELL 32

#define BOARD_START_TILE_X 6
#define BOARD_START_TILE_Y 4

typedef struct BoardCell {
    int itemPosX;
    int itemPosY;
} BoardCell;

extern int SpriteTileIndex;
extern bool PaletteLoaded;
extern int GameObjCount;
extern OBJ_ATTR GameObjBuffer[OBJ_BUFFER_MAX];
extern OBJ_AFFINE *GameAffBuffer;
extern int fc;
extern BoardCell BoardCellList[MAX_BOARD_CELL];



extern

void RunGame(void);
#endif
