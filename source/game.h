#ifndef PBGBA_GAME_H
#define PBGBA_GAME_H

#include <tonc.h>

#define OBJ_BUFFER_MAX  128
#define SCREEN_W_CENTER 176
#define SCREEN_H_CENTER 96

extern int SpriteTileIndex;
extern bool PaletteLoaded;
extern int GameObjCount;
extern OBJ_ATTR GameObjBuffer[OBJ_BUFFER_MAX];
extern OBJ_AFFINE *GameAffBuffer;
extern int fc;

void RunGame(void);
#endif
