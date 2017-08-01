#include "Mine.h"

USING_NS_CC;

Mine* Mine::create()
{
	Mine *mine = new Mine();
	if (mine && mine->init())
	{
		mine->autorelease();
		return mine;
	}

	CC_SAFE_DELETE(mine);
	return mine;
}

bool Mine::init()
{
	this->initWithFile("UI/Mine.png");

	isOpen = false;
	isFlag = false;
	x = y = NULL;

	return true;
}