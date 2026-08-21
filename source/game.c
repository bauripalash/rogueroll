#include "game.h"
#include "sprite.h"
#include "tilemap.h"

#include "colors.h"
#include "external/mgba.h"
#include "palette.h"
#include "roguehood.h"
#include <tonc.h>

#include "utils.h"

int SpriteTileIndex = 0;
bool PaletteLoaded = false;
int GameObjCount = 0;
OBJ_ATTR GameObjBuffer[OBJ_BUFFER_MAX];
OBJ_AFFINE *GameAffBuffer = (OBJ_AFFINE *)GameObjBuffer;
int Round = 1;
int fc = 0;
char textbuf[512];

Sprite hood;
static void genBoardData(void) {
    int ci = 0;
    int xpos = BOARD_START_TILE_X * 8;
    int ypos = BOARD_START_TILE_Y * 8;
    int xinc = 16;
    int yinc = 0;
    for (ci = 0; ci < MAX_BOARD_CELL; ci++) {
        // BoardCellList[ci] = (BoardCell){.itemPosX = xpos, .itemPosY = ypos};

        if (ci == 7) {
            xinc = 0;
            yinc = 16;
        } else if (ci == 12) {
            xinc = -16;
            yinc = 0;
        } else if (ci == 21) {
            xinc = 0;
            yinc = -16;
            xpos = BOARD_START_TILE_X * 8;
        }

        xpos += xinc;
        ypos += yinc;
    }
}

static void debugBoard(void) {
    for (int ci = 0; ci < MAX_BOARD_CELL; ci++) {
        const BoardCell *cell = &BoardCellList[ci];
        tte_printf(
            "#{P:%d,%d; cx:0x%X000} %d", cell->x, cell->y, PbClrBlack,
            cell->index
        );
    }
}

static void loadBaseMap(void) { LoadMainMap(); }

static void loadPalettes(void) {
    LoadPaletteOnly(
        (SpriteRes){.palette = palettePal, .paletteLen = palettePalLen},
        SPRITE_SIZE_16x16
    );
    memcpy32(pal_bg_mem, palettePal, palettePalLen / 4);
    SetFontColor(PbClrTransparent, PbClrTPinkDark);
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
    genBoardData();
    LoadFont();

    hood = LoadSprite(
        (SpriteRes){
            .tiles = roguehoodTiles, .tilesLen = roguehoodTilesLen, .frames = 8
        },
        SPRITE_SIZE_16x16
    );
    SpriteSetAnimation(&hood, &idle);
    SpriteSetPos(&hood, 48 + 16, 24);
    // SpriteSetVisibility(&hood, false);
    //

    tte_erase_screen();
    tte_printf("#{P:0,0}round:%d", Round);
    // debugBoard();
}

char buf[256];
int cell = 0;
void UpdateGame(void) {
    while (1) {
        VBlankIntrWait();
        key_poll();
        SpritePlayAnimation(&hood);

        UpdateSprites();
        if (fc % 20 == 0) {
            cell++;
            if (cell >= MAX_BOARD_CELL) {
                cell = 0;
            }
        }

        SpriteSetPos(&hood, BoardCellList[cell].x, BoardCellList[cell].y - 8);
        SpriteSetFlip(&hood, ShouldCellFlipH(&BoardCellList[cell]), false);
        fc++;
    }
}

void RunGame(void) {
    mgba_open();
    irq_init(NULL);
    irq_enable(II_VBLANK);

    REG_BG0CNT = BG_CBB(LEVEL_MAP_CBB) | BG_SBB(LEVEL_MAP_SBB) | BG_REG_32x32 |
                 BG_4BPP | BG_PRIO(1);
    REG_BG1CNT = BG_CBB(TEXTUI_CBB) | BG_SBB(TEXTUI_SBB) | BG_REG_32x32 |
                 BG_4BPP | BG_PRIO(0);

    REG_DISPCNT = DCNT_MODE0 | DCNT_BG0 | DCNT_BG1 | DCNT_OBJ | DCNT_OBJ_1D;

    InitFontTTE(1, TEXTUI_CBB, TEXTUI_SBB, &mgFont);
    tte_init_con();
    SetupGame();

    UpdateGame();
}
