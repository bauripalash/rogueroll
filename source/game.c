#include "game.h"
#include "sprite.h"
#include "tilemap.h"

#include "hoodknight.h"
#include "palette.h"

#include <tonc.h>

int SpriteTileIndex = 0;
bool PaletteLoaded = false;
int GameObjCount = 0;
OBJ_ATTR GameObjBuffer[OBJ_BUFFER_MAX];
OBJ_AFFINE *GameAffBuffer = (OBJ_AFFINE *)GameObjBuffer;
int fc = 0;

Sprite hood;

static void loadBaseMap(void) {}

static void loadPalettes(void) {
    LoadPaletteOnly(
        (SpriteRes){.palette = palettePal, .paletteLen = palettePalLen},
        SPRITE_SIZE_16x16
    );
    memcpy32(pal_bg_mem, palettePal, palettePalLen / 4);
}

SpriteAnim idle = {.first = 1, .count = 3, .speed = 20};

SpriteAnim defAnim = {
    .first = 0,
    .count = 1,
    .speed = 1,
};

void SetupGame(void) {
    oam_init(GameObjBuffer, OBJ_BUFFER_MAX);
    loadPalettes();
    loadBaseMap();

    hood = LoadSprite(
        (SpriteRes){
            .tiles = hoodknightTiles,
            .tilesLen = hoodknightTilesLen,
            .frames = 8
        },
        SPRITE_SIZE_16x16
    );
    SpriteSetAnimation(&hood, &idle);
}

char buf[256];
void UpdateGame(void) {
    while (1) {
        VBlankIntrWait();
        key_poll();
        tte_erase_screen();
        SpritePlayAnimation(&hood);
        UpdateSprites();
        fc++;
    }
}

void RunGame(void) {
    irq_init(NULL);
    irq_enable(II_VBLANK);

    REG_BG0CNT = BG_CBB(LEVEL_MAP_CBB) | BG_SBB(LEVEL_MAP_SBB) | BG_REG_32x32 |
                 BG_4BPP | BG_PRIO(1);
    REG_BG1CNT = BG_CBB(TEXTUI_CBB) | BG_SBB(TEXTUI_SBB) | BG_REG_32x32 |
                 BG_4BPP | BG_PRIO(0);

    REG_DISPCNT = DCNT_MODE0 | DCNT_BG0 | DCNT_BG1 | DCNT_OBJ | DCNT_OBJ_1D;
    tte_init_se(
        1, BG_CBB(TEXTUI_CBB) | BG_SBB(TEXTUI_SBB), 0, 0, 0, &sys8Font, NULL
    );
    SetupGame();

    UpdateGame();
}
