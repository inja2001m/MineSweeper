#include "MinesGenerator.h"

USING_NS_CC;

void MGenerator::createMap(int mapWidth, int mapHeight, int nMine)
{
	WIDTH = mapWidth;
	HEIGHT = mapHeight;
	MINECNT = nMine;
	totalTileCnt = WIDTH * HEIGHT;

	map = new Mine*[HEIGHT];
	for (int i = 0; i < HEIGHT; i++)
		map[i] = new Mine[WIDTH];

	zeroSetMap();
	createMines();
	createCntMines();
}

void MGenerator::createMines()
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> widthDist(0, WIDTH - 1);
	uniform_int_distribution<> heightDist(0, HEIGHT - 1);

	int width, height, nMine = MINECNT;

	while (nMine)
	{
		do
		{
			width = widthDist(gen);
			height = heightDist(gen);
		} while (map[height][width].data == e_Tile::MINE);

		map[height][width].data = e_Tile::MINE;

		--nMine;
	}
}

// 瘤汾 林函 积己 内靛
void MGenerator::createCntMines()
{
	for (int i = 0; i < HEIGHT; ++i)
	{
		for (int j = 0; j < WIDTH; ++j)
		{
			if (map[i][j].data == 0)
			{
				if (i != 0)
					if (map[i - 1][j].data == e_Tile::MINE) ++map[i][j].data;

				if (j != 0)
				{
					if (i != 0 && map[i - 1][j - 1].data == e_Tile::MINE) ++map[i][j].data;
					if (map[i][j - 1].data == e_Tile::MINE) ++map[i][j].data;
					if (i != HEIGHT - 1 && map[i + 1][j - 1].data == e_Tile::MINE) ++map[i][j].data;
				}

				if (j != WIDTH - 1)
				{
					if (i != 0 && map[i - 1][j + 1].data == e_Tile::MINE) ++map[i][j].data;
					if (map[i][j + 1].data == e_Tile::MINE) ++map[i][j].data;
					if (i != HEIGHT - 1 && map[i + 1][j + 1].data == e_Tile::MINE) ++map[i][j].data;
				}

				if (i != HEIGHT - 1)
					if (map[i + 1][j].data == e_Tile::MINE) ++map[i][j].data;
			}
		}
	}
}


void CCMGenerator::drawMap(Node *parent)
{
	for (int i = 0; i < HEIGHT; ++i)
	{
		for (int j = 0; j < WIDTH; ++j)
		{
			map[i][j].init();
			map[i][j].setPosition(j * map[i][j].getContentSize().width + map[i][j].getContentSize().width / 2,
				i * map[i][j].getContentSize().height + map[i][j].getContentSize().height / 2);
			parent->addChild((&map[i][j]));
		}
	}
}
bool CCMGenerator::openSideTiles(int x, int y)
{
	if (map[y][x].isFlag)
		return false;

	if (map[y][x].data != 0)
	{
		openTile(x, y);
		return false;
	}

	--totalTileCnt;
	map[y][x].isOpen = true;
	map[y][x].setColor(Color3B::BLACK);

	if (y > 0          && !map[y - 1][x].isOpen) openSideTiles(x, y - 1);  // Top
	if (x > 0          && !map[y][x - 1].isOpen) openSideTiles(x - 1, y);  // Left
	if (x < WIDTH - 1  && !map[y][x + 1].isOpen) openSideTiles(x + 1, y);  // Right
	if (y < HEIGHT - 1 && !map[y + 1][x].isOpen) openSideTiles(x, y + 1);  // Bottom

	if (totalTileCnt == MINECNT)
		return true;

	return false;
}
bool CCMGenerator::openTile(int x, int y)
{
	--totalTileCnt;

	map[y][x].isOpen = true;
	map[y][x].setColor(Color3B::BLACK);

	if (map[y][x].data == e_Tile::EMPTY)
		return false;
	else if (map[y][x].data == e_Tile::MINE)
	{
		LabelTTF *numLabel = LabelTTF::create("B", "Arial", 24);
		numLabel->setPosition(map[y][x].getContentSize() / 2);
		map[y][x].addChild(numLabel);
		
		return false;
	}

	char *bufferNum = new char();
	sprintf(bufferNum, "%d", map[y][x].data);
	LabelTTF *numLabel = LabelTTF::create(bufferNum, "Arial", 24);
	numLabel->setPosition(map[y][x].getContentSize() / 2);
	switch (map[y][x].data)
	{
	case 1: numLabel->setColor(Color3B::WHITE);   break;
	case 2: numLabel->setColor(Color3B::GRAY);    break;
	case 3:	numLabel->setColor(Color3B::ORANGE);  break;
	case 4: numLabel->setColor(Color3B::GREEN);   break;
	case 5: numLabel->setColor(Color3B::BLUE);    break;
	case 6: numLabel->setColor(Color3B::YELLOW);  break;
	case 7: numLabel->setColor(Color3B::MAGENTA); break;
	case 8: numLabel->setColor(Color3B::RED);     break;
	default: break;
	}
	map[y][x].addChild(numLabel);

	if (totalTileCnt == MINECNT)
		return true;

	return false;
}