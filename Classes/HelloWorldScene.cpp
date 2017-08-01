#include "HelloWorldScene.h"

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    
    auto layer = HelloWorld::create();

    scene->addChild(layer);

    return scene;
}

bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

	InitListener();

	// Background Sprite setting
	mineBG = Sprite::create("UI/MineBG.png");
	mineBG->setPosition(visibleSize / 2);
	this->addChild(mineBG);
	Sprite *TopBG = Sprite::create("UI/TopBG.png");
	TopBG->setPosition(visibleSize.width / 2, visibleSize.height - TopBG->getContentSize().height / 1.7);
	this->addChild(TopBG);

	// Button Sprite setting
	flagBtn = Sprite::create("UI/LongBtn.png");
	flagBtn->setPosition(flagBtn->getContentSize() / 2);
	this->addChild(flagBtn);
	spoonBtn = Sprite::create("UI/LongBtn.png");
	spoonBtn->setPosition(visibleSize.width - spoonBtn->getContentSize().width / 2, 
		spoonBtn->getContentSize().height / 2);
	this->addChild(spoonBtn);
	selectBtn = Sprite::create("UI/ShortBtn.png");
	selectBtn->setPosition(flagBtn->getBoundingBox().getMaxX() + selectBtn->getContentSize().width / 2,
		selectBtn->getContentSize().height / 2);
	this->addChild(selectBtn);

	// Label setting
	LabelTTF *Lflag = LabelTTF::create("FLAG", "Arial", 32);
	Lflag->setColor(Color3B::BLACK);
	Lflag->setPosition(flagBtn->getContentSize() / 2);
	flagBtn->addChild(Lflag);
	LabelTTF *LspoonUp = LabelTTF::create("SPOON UP", "Arial", 32);
	LspoonUp->setColor(Color3B::BLACK);
	LspoonUp->setPosition(flagBtn->getContentSize() / 2);
	spoonBtn->addChild(LspoonUp);

	// CCMGenerator object setting
	const Sprite *mineSize = Sprite::create("UI/Mine.png");
	mapWidth = mineBG->getContentSize().width / mineSize->getContentSize().width;
	mapHeight = mineBG->getContentSize().height / mineSize->getContentSize().height;
	totalMineCnt = 100;
	mineMap.createMap(mapWidth, mapHeight, totalMineCnt);
	mineMap.drawMap(mineBG);

	// The first OutLine setting
	Sprite *InitOutLine = Sprite::create("UI/MineOutline.png");
	InitOutLine->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	InitOutLine->setTag(e_ChildObjTag::OUTLINE);
	tempMine = Mine::create();
	tempMine = &mineMap.map[0][0];
	tempMine->addChild(InitOutLine);

	// Temp object color setting for original sprite
	tempMineColor = mineSize->getColor();
	tempBtnColor = flagBtn->getColor();

	// Switch object setting for button
	swBtnPush = 0;
	swPushType = true;
	flagBtn->setColor(ccc3(90, 90, 90));

	isClear = false;

    return true;
}

void HelloWorld::InitListener()
{
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

bool HelloWorld::onTouchBegan(Touch *touch, Event *event)
{
	if (tempMine->getChildrenCount())
		tempMine->removeChildByTag(e_ChildObjTag::OUTLINE, true);

	Vec2 touchPos = touch->getLocation();
	bool isMinePush = MineTouchProcess(touchPos);

	if (!isMinePush)
	{
		if (flagBtn->getBoundingBox().containsPoint(touchPos))
		{
			flagBtn->setColor(ccc3(40, 40, 40));
			swBtnPush = 0;
		}
		else if (spoonBtn->getBoundingBox().containsPoint(touchPos))
		{
			spoonBtn->setColor(ccc3(40, 40, 40));
			swBtnPush = 1;
		}
		else if (selectBtn->getBoundingBox().containsPoint(touchPos))
		{
			selectBtn->setColor(ccc3(40, 40, 40));
			swBtnPush = 2;
		}
	}

	return true;
}
void HelloWorld::onTouchEnded(Touch *touch, Event *event)
{
	MineTouchEndedProcess();
	BtnTouchEndedProcess(touch->getLocation());

	if (isClear)
		CCLOG("CLEAR !! :)");
}

bool HelloWorld::MineTouchProcess(Vec2 touchPos)
{
	for (int i = 0; i < mineMap.HEIGHT; ++i)
	{
		for (int j = 0; j < mineMap.WIDTH; ++j)
		{
			if (mineMap.map[i][j].getBoundingBox().containsPoint(mineBG->convertToNodeSpace(touchPos)) &&
				!mineMap.map[i][j].isOpen)
			{
				tempMine = &mineMap.map[i][j];
				tempMine->x = j;
				tempMine->y = i;
				tempMine->setColor(ccc3(50, 50, 50));

				return true;
			}
		}
	}
	
	return false;
}
void HelloWorld::MineTouchEndedProcess()
{
	if (tempMine->isOpen)
		return;

	tempMine->setColor(tempMineColor);

	Sprite *outLine = Sprite::create("UI/MineOutline.png");
	outLine->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	outLine->setTag(e_ChildObjTag::OUTLINE);
	tempMine->addChild(outLine);
}
void HelloWorld::BtnTouchEndedProcess(Vec2 touchPos)
{
	if (swBtnPush == 0 && flagBtn->getBoundingBox().containsPoint(touchPos))
	{
		swPushType = true;
		flagBtn->setColor(ccc3(90, 90, 90));
		spoonBtn->setColor(tempBtnColor);
	}
	else if (swBtnPush == 1&& spoonBtn->getBoundingBox().containsPoint(touchPos))
	{
		swPushType = false;
		spoonBtn->setColor(ccc3(90, 90, 90));
		flagBtn->setColor(tempBtnColor);
	}
	else if (swBtnPush == 2 && selectBtn->getBoundingBox().containsPoint(touchPos))
	{
		switch (swPushType)
		{
		case true: FlagTouchPush(); break;
		case false: SpoonUpTouchPush(); break;
		default: break;
		}
	}

	selectBtn->setColor(tempBtnColor);
}

void HelloWorld::FlagTouchPush()
{
	if (tempMine->isOpen)
		return;

	if (!tempMine->isFlag)
	{
		Sprite *flag = Sprite::create("UI/Flag.png");
		flag->setPosition(tempMine->getContentSize() / 2);
		flag->setTag(e_ChildObjTag::FLAG);
		tempMine->addChild(flag);
		tempMine->isFlag = true;
	}
	else
	{
		tempMine->removeChildByTag(3, true);
		tempMine->isFlag = false;
	}
}
void HelloWorld::SpoonUpTouchPush()
{
	if (tempMine->isFlag || tempMine->isOpen)
		return;

	if (tempMine->data == e_Tile::MINE)
	{
		for (int i = 0; i < mineMap.HEIGHT; ++i)
		{
			for (int j = 0; j < mineMap.WIDTH; ++j)
			{
				if (!mineMap.map[i][j].isOpen)
				{
					if (mineMap.map[i][j].isFlag)
						mineMap.map[i][j].removeChildByTag(e_ChildObjTag::FLAG, true);
					
					mineMap.openTile(j, i);
				}
			}
		}

		CCLOG("Fail!! :(");
	}
	else if (tempMine->data == e_Tile::EMPTY)
		isClear = mineMap.openSideTiles(tempMine->x, tempMine->y);
	else
		isClear = mineMap.openTile(tempMine->x, tempMine->y);

	CCLOG("Total: %d, nTile: %d", mapWidth * mapHeight, mineMap.totalTileCnt);
}

