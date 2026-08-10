#ifndef PBGBA_TILEMAP_H
#define PBGBA_TILEMAP_H

#include <tonc.h>

#define TILE_GROUND            1
#define TILE_PLATFORM          2

#define TILEMAP_LOGICAL_WIDTH  15 // 15 * 16px = 240px
#define TILEMAP_LOGICAL_HEIGHT 10 // 10 * 16px = 160px

#define TILEMAP_SCREEN_WIDTH   30
#define TILEMAP_SCREEN_HEIGHT  20

#define LEVEL_MAP_SBB          28
#define LEVEL_MAP_CBB          0
#define TEXTUI_SBB             31
#define TEXTUI_CBB             1

static const u8 levelMain[TILEMAP_LOGICAL_HEIGHT][TILEMAP_LOGICAL_WIDTH] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {2, 1, 1, 1, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1},
    {3, 1, 1, 1, 2, 2, 3, 2, 2, 2, 1, 1, 1, 1, 1},
    {4, 1, 1, 1, 2, 2, 4, 2, 2, 2, 1, 1, 1, 1, 1},
    {5, 1, 1, 1, 2, 2, 5, 2, 2, 2, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 2, 2, 6, 2, 2, 2, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 2, 2, 7, 2, 2, 2, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 8, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 9, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 10, 1, 1, 1, 1, 1, 1, 1, 1},
};

void LoadTilesets(const unsigned int *tiles, int len, int cbb);
void LoadTilemap(
    const unsigned char *map, uint len, int width, int height, int sbb
);

void LoadMainMap(void);
#endif
