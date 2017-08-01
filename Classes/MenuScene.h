#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__

#include "cocos2d.h"

#include "HelloWorldScene.h"
#include "OptionLayer.h"

#define visibleSize Director::getInstance()->getVisibleSize()
#define MOVEBYDELAY 0.5f

USING_NS_CC;

enum e_Buttons
{
	START = 1,
	OPTION = 2,
	EXIT = 3
};

class MenuScene : public cocos2d::LayerColor
{
private:
	float mainBtnGoActionTime;
	bool isMainBtnTimer;
	bool isPossible;

private:
	MenuItemImage *startBtn;
	MenuItemImage *optionBtn;
	MenuItemImage *exitBtn;

private:
	MoveBy *action_00, *action_01, *action_02;
	EaseOut *action_11, *action_12, *action_13;
	Sequence *action_21, *action_22;

public:
	void InitVariables();

public:
	void update(float dt);
	void MenuCloseCallback(Ref *pSender);
	void ShowOption();

public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(MenuScene);
};

#endif // __MENU_SCENE_H__
