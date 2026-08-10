#include "tilemap.h"
#include "maps/basemap.h"

#include "basetiles.h"

void LoadTilesets(const unsigned int *tiles, int len, int cbb) {

    // memset32(&tile_mem[cbb][0], 0, 8);
    memcpy32(&tile_mem[cbb][0], tiles, len / 4);
}

void LoadTilemap(
    const unsigned char *map, uint len, int width, int height, int sbb
) {
    SCR_ENTRY *dst = se_mem[sbb];
    const u16 *src = (const u16 *)map;
    memset16(dst, 0, 32 * 32);

    for (int y = 0; y < height; y++) {
        memcpy16(&dst[y * 32], &src[y * width], width);
    }
}

void LoadMainMap(void) {
    LoadTilesets(basetilesTiles, basetilesTilesLen, LEVEL_MAP_CBB);
    LoadTilemap(
        (const unsigned char *)BaseMap, BASEMAP_LENGTH, BASEMAP_WIDTH,
        BASEMAP_HEIGHT, LEVEL_MAP_SBB
    );
}
