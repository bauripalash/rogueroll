#include "sprite.h"
#include "game.h"
#include <tonc.h>

void LoadPaletteOnly(SpriteRes res, SpriteSize size) {
    memcpy32(pal_obj_mem, res.palette, res.paletteLen / 4);
    PaletteLoaded = true;
}

Sprite LoadSprite(SpriteRes res, SpriteSize size) {
    const SpriteSizeInfoTable *info = &SpriteSizeInfos[size];

    int tileIndex = SpriteTileIndex;
    int spriteIndex = GameObjCount;

    memcpy32(&tile_mem[4][tileIndex], res.tiles, res.tilesLen / 4);

    if (!PaletteLoaded && res.palette != NULL) {
        memcpy32(pal_obj_mem, res.palette, res.paletteLen / 4);
        PaletteLoaded = true;
    }

    OBJ_ATTR *spriteAttr = &GameObjBuffer[spriteIndex];

    Sprite sprite = {
        .objIndex = spriteIndex,
        .baseTile = tileIndex,
        .size = size,
        .width = info->width,
        .height = info->height,
        .x = 0,
        .y = 0,
        .frameCount = res.frames,
        .player = (SpriteAnimPlayer){.anim = NULL, .current = 0, .timer = 0},
        .obj = spriteAttr,
    };
    int tile = sprite.baseTile + sprite.player.current * info->tileCount;
    obj_set_attr(spriteAttr, info->attr0, info->attr1, ATTR2_BUILD(tile, 0, 0));
    obj_set_pos(spriteAttr, sprite.x, sprite.y);

    GameObjCount++;
    SpriteTileIndex += info->tileCount * res.frames;
    return sprite;
}

void SpriteSetPos(Sprite *s, int x, int y) {
    s->x = x;
    s->y = y;
    obj_set_pos(s->obj, s->x, s->y);
}

bool SpriteSetFrame(Sprite *s, int frame) {
    if (frame >= s->frameCount) {
        return false;
    }
    const SpriteSizeInfoTable *info = &SpriteSizeInfos[s->size];
    int tile = s->baseTile + frame * info->tileCount;
    s->obj->attr2 = ATTR2_BUILD(tile, 0, 0);
    return true;
}

void SpriteSetVisibility(Sprite *s, bool visble) { return; }

void SpriteSetAnimation(Sprite *s, SpriteAnim *anim) {
    if (s == NULL || anim == NULL) {
        return;
    }

    if (s->player.anim == anim) {
        return;
    }

    s->player.anim = anim;
    s->player.timer = 0;
    s->player.current = 0;
}

void SpritePlayAnimation(Sprite *s) {
    if (s == NULL || s->player.anim == NULL) {
        return;
    }

    s->player.timer++;

    if (s->player.timer >= s->player.anim->speed) {
        s->player.timer = 0;
        s->player.current++;
        if (s->player.current >= s->player.anim->count) {
            s->player.current = 0;
        }
    }

    SpriteSetFrame(s, s->player.anim->first + s->player.current);
}

void SpriteSetFlip(Sprite *s, bool h, bool v) {
    // horizontal flip
    if (h) {
        s->obj->attr1 |= ATTR1_HFLIP;
    } else {
        s->obj->attr1 &= ~ATTR1_HFLIP;
    }

    // vertical flip
    if (v) {
        s->obj->attr1 |= ATTR1_VFLIP;
    } else {
        s->obj->attr1 &= ~ATTR1_VFLIP;
    }
}

bool UpdateSprites(void) {
    oam_copy(oam_mem, GameObjBuffer, GameObjCount);
    return true;
}
