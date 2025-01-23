#pragma once
#include "common.h"

struct tile {
	u8 data[8][8];
};

struct tilemap {
	int number;
	tile tiles[32][32];
};


