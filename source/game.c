#include "game.h"

#include <tonc.h>

int SpriteTileIndex = 0;
bool PaletteLoaded = false;
int GameObjCount = 0;
OBJ_ATTR GameObjBuffer[OBJ_BUFFER_MAX];
OBJ_AFFINE *GameAffBuffer = (OBJ_AFFINE *)GameObjBuffer;
int fc = 0;

static void loadBaseMap(void) {}

void SetupGame(void) {
    oam_init(GameObjBuffer, OBJ_BUFFER_MAX);
    loadBaseMap();
}

char buf[256];
void UpdateGame(void) {
    while (1) {
        VBlankIntrWait();
        key_poll();
        tte_erase_screen();
        fc++;
    }
}

void RunGame(void) {
    irq_init(NULL);
    irq_enable(II_VBLANK);
    REG_DISPCNT = DCNT_MODE0 | DCNT_BG0 | DCNT_BG1 | DCNT_OBJ | DCNT_OBJ_1D;

    SetupGame();

    UpdateGame();
}
