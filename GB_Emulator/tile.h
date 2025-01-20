#pragma once
#include "common.h"
#include "memory.h"

struct tile {
	u8 data[8][8];
};

struct tilemap {
	int number;
	tile tiles[32][32];
};


