#ifndef __MINE_H__
#define __MINE_H__

#include "cocos2d.h"

class Mine : public cocos2d::Sprite
{
public:
	bool isOpen;
	bool isFlag;

public:
	int data;
	int x, y;

public:
	static Mine* create();
	virtual bool init();
};

#endif