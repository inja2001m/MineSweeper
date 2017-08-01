#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

#include "MinesGenerator.h"
#include "FailLayer.h"

#define visibleSize Director::getInstance()->getVisibleSize()

USING_NS_CC;

enum e_ChildObjTag
{
	FLAG = 3,
	OUTLINE = 4
};

class HelloWorld : public cocos2d::Layer
{
private:
	Sprite *mineBG;
	Sprite *flagBtn, *spoonBtn, *selectBtn;

private:
	int mapWidth, mapHeight;
	int totalMineCnt;
	int tempI, tempJ;
	int swBtnPush;
	bool swPushType;

private:
	bool isClear;

private:
	CCMGenerator mineMap;
	Mine *tempMine;
	Color3B tempMineColor, tempBtnColor;

private:
	void InitListener();
	
	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);

private:
	bool MineTouchProcess(Vec2);
	void MineTouchEndedProcess();
	void BtnTouchEndedProcess(Vec2);
	
	void FlagTouchPush();
	void SpoonUpTouchPush();

public:
    static cocos2d::Scene* createScene();

    virtual bool init();
        
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
