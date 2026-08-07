#ifndef PBGBA_SPRITE_H
#define PBGBA_SPRITE_H

#include <tonc.h>

#define SPRITE_TILE_16x16 4
#define SPRITE_TILE_8x8   1

typedef enum SpriteSize {
    SPRITE_SIZE_8x8 = 0,
    SPRITE_SIZE_16x16,
    SPRITE_SIZE_32x32,
    SPRITE_SIZE_64x64,
    SPRITE_SIZE_COUNT
} SpriteSize;

typedef struct SpriteSizeInfoTable {
    int width;
    int height;
    int tileCount;
    u16 attr0;
    u16 attr1;
} SpriteSizeInfoTable;

static const SpriteSizeInfoTable SpriteSizeInfos[SPRITE_SIZE_COUNT] = {
    [SPRITE_SIZE_8x8] =
        {.width = 8,
         .height = 8,
         .tileCount = 1,
         .attr0 = ATTR0_SQUARE,
         .attr1 = ATTR1_SIZE_8},
    [SPRITE_SIZE_16x16] =
        {.width = 16,
         .height = 16,
         .tileCount = 4,
         .attr0 = ATTR0_SQUARE,
         .attr1 = ATTR1_SIZE_16},
    [SPRITE_SIZE_32x32] =
        {.width = 32,
         .height = 32,
         .tileCount = 16,
         .attr0 = ATTR0_SQUARE,
         .attr1 = ATTR1_SIZE_32},
    [SPRITE_SIZE_64x64] = {
        .width = 64,
        .height = 64,
        .tileCount = 64,
        .attr0 = ATTR0_SQUARE,
        .attr1 = ATTR1_SIZE_64
    },
};

// Sprite Resources
typedef struct SpriteRes {
    // Tiles
    const unsigned int *tiles;
    // Palette
    const unsigned short *palette;

    // Tile count
    int tilesLen;
    // Palette count
    int paletteLen;

    // How many frames
    int frames;
} SpriteRes;

// Animation data for animation player
typedef struct SpriteAnim {
    // First index of the this animation
    int first;
    // How many frames in animation
    int count;
    // Speed of this animation
    int speed;
} SpriteAnim;

typedef struct SpriteAnimPlayer {
    const SpriteAnim *anim;
    int current;
    int timer;
} SpriteAnimPlayer;

// Sprite Object
typedef struct Sprite {
    // The index in GameObjBuffer
    int objIndex;

    // The base tile for this spritesheet
    int baseTile;

    // Width of the sprite image's single frame
    int width;
    // Height of the sprite image's single frame
    int height;

    // Sprite X position in screen
    int x;
    // Sprite Y position in screen
    int y;

    // How many frames are in this spritesheet
    int frameCount;

    // Sprite size (frame's size)
    SpriteSize size;

    // The animation player
    SpriteAnimPlayer player;

    // The object
    OBJ_ATTR *obj;
} Sprite;

// Load the palette from SpriteRes and set PalatteLoaded to true
// Only required fields are
//  {
// 	  .palette
// 	  .paletteLen
// 	}
void LoadPaletteOnly(SpriteRes res, SpriteSize size);

// Load sprite from SpriteRes
// palette data can be omitted
Sprite LoadSprite(SpriteRes res, SpriteSize size);

// Set sprite x,y position
void SpriteSetPos(Sprite *s, int x, int y);

// Set sprite horizontal and vertical flip
void SpriteSetFlip(Sprite *s, bool h, bool v);

// Set frame index to sprite
bool SpriteSetFrame(Sprite *s, int frame);

// Toggle visibility of sprite
void SpriteSetVisibility(Sprite *s, bool visble);

// Set animation for sprite's animation player
void SpriteSetAnimation(Sprite *s, SpriteAnim *anim);

// Play the current animation
void SpritePlayAnimation(Sprite *s);

// Update all the states active sprites
bool UpdateSprites(void);

#endif
