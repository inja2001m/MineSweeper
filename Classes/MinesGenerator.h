#ifndef __MINES_GENERATOR_H__
#define __MINES_GENERATOR_H__

#include <iostream>
#include <random>
#include <vector>

#include "cocos2d.h"

#include "Mine.h"

using namespace std;

enum e_Tile
{
	EMPTY = 0,
	MINE = 9
};

class MGenerator
{
public:
	int WIDTH, HEIGHT, MINECNT;
	int totalTileCnt;

private:
	inline void zeroSetMap() { for (int i = 0; i < HEIGHT; ++i) for (int j = 0; j < WIDTH; ++j) map[i][j].data = NULL; }
	void createMines(), createCntMines();

public:
	void createMap(int WIDTH, int HEIGHT, int MINECNT);
	
	Mine **map;
};

class CCMGenerator : public MGenerator
{
public:
	void drawMap(cocos2d::Node *parent);
	bool openSideTiles(int x, int y);
	bool openTile(int x, int y);
};

#endif