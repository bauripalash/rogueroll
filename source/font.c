#include "external/mgba.h"
#include "game.h"
#include "string.h"
#include "tilemap.h"
#include "ursafont.h"
#include "utils.h"
#include <tonc.h>

const TFont mgFont = {
    .data = ursafontTiles,
    .widths = NULL,
    .heights = NULL,
    .charOffset = 0,
    .charCount = 256,
    .charW = 8,
    .charH = 8,
    .cellW = 8,
    .cellH = 8,
    .cellSize = 32,
    .bpp = 4,
    .extra = 0,
};

void LoadFont(void) {
    LoadTilesets(ursafontTiles, ursafontTilesLen, TEXTUI_CBB);
}

int GetTextWidth(const char *s) { return strlen(s) * 8; }

void SetFontColor(COLOR bg, COLOR fg) {
    pal_bg_bank[FONT_PALETTE][0] = bg;
    pal_bg_bank[FONT_PALETTE][1] = fg;
}

void InitFontTTE(int bg, int cbb, int sbb, const TFont *font) {
    tte_init_se(
        bg, BG_CBB(cbb) | BG_SBB(sbb), FONT_PALETTE_HEX, CLR_WHITE, 0, font,
        se_drawg_s
    );
}
