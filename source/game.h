#ifndef PBGBA_GAME_H
#define PBGBA_GAME_H

#include <tonc.h>

#define OBJ_BUFFER_MAX     128
#define SCREEN_W_CENTER    176
#define SCREEN_H_CENTER    96
#define MAX_BOARD_CELL     26

#define BOARD_START_TILE_X 6
#define BOARD_START_TILE_Y 4

#define FONT_PALETTE       15
#define FONT_PALETTE_HEX   (FONT_PALETTE << 12)

// -----------------------------------------------------------------------------
//                              Global Gameplay Data
// -----------------------------------------------------------------------------

typedef enum BoardCellDir {
    CDIR_TOP = 0,
    CDIR_RIGHT = 1,
    CDIR_BOTTOM = 2,
    CDIR_LEFT = 3,
} BoardCellDir;

typedef struct BoardCell {
    int index;
    int x;
    int y;
    BoardCellDir dir;
} BoardCell;

extern int SpriteTileIndex;
extern bool PaletteLoaded;
extern int GameObjCount;
extern OBJ_ATTR GameObjBuffer[OBJ_BUFFER_MAX];
extern OBJ_AFFINE *GameAffBuffer;
extern int fc;
extern const TFont mgFont;

extern const BoardCell BoardCellList[MAX_BOARD_CELL];

bool ShouldCellFlipH(const BoardCell *cell);
// -----------------------------------------------------------------------------
//                              GAME_FUNCTIONS
// -----------------------------------------------------------------------------

void RunGame(void);

// -----------------------------------------------------------------------------
//                              	FONT
// -----------------------------------------------------------------------------
void LoadFont(void);
void SetFontColor(COLOR bg, COLOR fg);
void InitFontTTE(int bg, int cbb, int sbb, const TFont *font);
int GetTextWidth(const char *s);
#endif
