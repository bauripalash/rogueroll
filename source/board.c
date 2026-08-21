#include "game.h"

/* clang-format off */
const BoardCell BoardCellList[MAX_BOARD_CELL] = {
#define TX BOARD_START_TILE_X
#define TY BOARD_START_TILE_Y
	// TOP LINE
	{.index = 0, .x = TX * 8 + (16 * 0), .y = TY * 8, .dir = CDIR_TOP},
	{.index = 1, .x = TX * 8 + (16 * 1), .y = TY * 8, .dir = CDIR_TOP},
	{.index = 2, .x = TX * 8 + (16 * 2), .y = TY * 8, .dir = CDIR_TOP},
	{.index = 3, .x = TX * 8 + (16 * 3), .y = TY * 8, .dir = CDIR_TOP},
	{.index = 4, .x = TX * 8 + (16 * 4), .y = TY * 8, .dir = CDIR_TOP},
	{.index = 5, .x = TX * 8 + (16 * 5), .y = TY * 8, .dir = CDIR_TOP},
	{.index = 6, .x = TX * 8 + (16 * 6), .y = TY * 8, .dir = CDIR_TOP},
	{.index = 7, .x = TX * 8 + (16 * 7), .y = TY * 8, .dir = CDIR_TOP},
	{.index = 8, .x = TX * 8 + (16 * 8), .y = TY * 8, .dir = CDIR_TOP},

	// RIGHT LINE
	{.index = 9, .x = TX * 8 + (16 * 8), .y = TY * 8 + (16 * 1), .dir = CDIR_RIGHT},
	{.index = 10, .x = TX * 8 + (16 * 8), .y = TY * 8 + (16 * 2), .dir = CDIR_RIGHT},
	{.index = 11, .x = TX * 8 + (16 * 8), .y = TY * 8 + (16 * 3), .dir = CDIR_RIGHT},
	{.index = 12, .x = TX * 8 + (16 * 8), .y = TY * 8 + (16 * 4), .dir = CDIR_RIGHT},
	{.index = 13, .x = TX * 8 + (16 * 8), .y = TY * 8 + (16 * 5), .dir = CDIR_RIGHT},

	// BOTTOM LINE
	{.index = 14, .x = TX * 8 + (16 * 7), .y = TY * 8 + (16 * 5), .dir = CDIR_BOTTOM},
	{.index = 15, .x = TX * 8 + (16 * 6), .y = TY * 8 + (16 * 5), .dir = CDIR_BOTTOM},
	{.index = 16, .x = TX * 8 + (16 * 5), .y = TY * 8 + (16 * 5), .dir = CDIR_BOTTOM},
	{.index = 17, .x = TX * 8 + (16 * 4), .y = TY * 8 + (16 * 5), .dir = CDIR_BOTTOM},
	{.index = 18, .x = TX * 8 + (16 * 3), .y = TY * 8 + (16 * 5), .dir = CDIR_BOTTOM},
	{.index = 19, .x = TX * 8 + (16 * 2), .y = TY * 8 + (16 * 5), .dir = CDIR_BOTTOM},
	{.index = 20, .x = TX * 8 + (16 * 1), .y = TY * 8 + (16 * 5), .dir = CDIR_BOTTOM},
	{.index = 21, .x = TX * 8 + (16 * 0), .y = TY * 8 + (16 * 5), .dir = CDIR_BOTTOM},

	//LEFT LINE
	{.index = 22, .x = TX * 8 + (16 * 0), .y = TY * 8 + (16 * 4), .dir = CDIR_LEFT},
	{.index = 23, .x = TX * 8 + (16 * 0), .y = TY * 8 + (16 * 3), .dir = CDIR_LEFT},
	{.index = 24, .x = TX * 8 + (16 * 0), .y = TY * 8 + (16 * 2), .dir = CDIR_LEFT},
	{.index = 25, .x = TX * 8 + (16 * 0), .y = TY * 8 + (16 * 1), .dir = CDIR_LEFT},
#undef TX
#undef TY
};
/* clang-format on */

bool ShouldCellFlipH(const BoardCell *cell) {
    return cell->dir != CDIR_LEFT && cell->dir != CDIR_TOP;
}
