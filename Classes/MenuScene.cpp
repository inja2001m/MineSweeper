#include "MenuScene.h"

Scene* MenuScene::createScene()
{
	auto scene = Scene::create();

	auto layer = MenuScene::create();

	scene->addChild(layer);

	return scene;
}

bool MenuScene::init()
{
	if (!LayerColor::initWithColor(Color4B(119, 255, 148, 255)))
	{
		return false;
	}

	InitVariables();

	startBtn = MenuItemImage::create(
											"UI/StartBtnNormal.png",
											"UI/StartBtnSelected.png",
											CC_CALLBACK_1(MenuScene::MenuCloseCallback, this));
	startBtn->setPosition(visibleSize.width + startBtn->getContentSize().width, 
		visibleSize.height / 2 + startBtn->getContentSize().height / 1.5);
	startBtn->setTag(e_Buttons::START);
	optionBtn = MenuItemImage::create(
											"UI/OptionBtnNormal.png",
											"UI/OptionBtnSelected.png",
											CC_CALLBACK_1(MenuScene::MenuCloseCallback, this));
	optionBtn->setPosition(visibleSize.width + optionBtn->getContentSize().width,
		visibleSize.height / 2 - optionBtn->getContentSize().height / 1.5);
	optionBtn->setTag(e_Buttons::OPTION);
	exitBtn = MenuItemImage::create(
											"UI/ExitBtnNormal.png",
											"UI/ExitBtnSelected.png",
											CC_CALLBACK_1(MenuScene::MenuCloseCallback, this));
	exitBtn->setPosition(visibleSize.width + exitBtn->getContentSize().width,
		visibleSize.height / 2 - exitBtn->getContentSize().height / 0.5);
	exitBtn->setTag(e_Buttons::EXIT);

	Menu *menu = Menu::create(startBtn, optionBtn, exitBtn, NULL);
	menu->setPosition(0, -300);
	this->addChild(menu);

	float posX = -(startBtn->getContentSize().width * 1.5 + 10);

	action_00 = MoveBy::create(MOVEBYDELAY, Vec2(posX, 0));
	action_01 = MoveBy::create(MOVEBYDELAY, Vec2(posX, 0));
	action_02 = MoveBy::create(MOVEBYDELAY, Vec2(posX, 0));

	action_11 = EaseOut::create(action_00, 3.0f);
	action_12 = EaseOut::create(action_01, 3.0f);
	action_13 = EaseOut::create(action_02, 3.0f);

	DelayTime *delay1 = DelayTime::create(MOVEBYDELAY * 0.9);
	DelayTime *delay2 = DelayTime::create(MOVEBYDELAY * 0.9 * 2);
	
	action_21 = Sequence::create(delay1, action_12, NULL);
	action_22 = Sequence::create(delay2, action_13, NULL);

	startBtn->runAction(action_11);
	optionBtn->runAction(action_21);
	exitBtn->runAction(action_22);

	return true;
}

void MenuScene::update(float dt)
{
	//if (isMainBtnTimer)
	//{
	//	mainBtnGoActionTime += dt;
	//
	//	if (mainBtnGoActionTime >= MOVEBYDELAY * 2 )
	//	{
	//		//exitBtn->runAction(action_4);
	//		isMainBtnTimer = false;
	//	}
	//	else if (mainBtnGoActionTime >= MOVEBYDELAY && isPossible)
	//	{
	//		//optionBtn->runAction(action_3);
	//		isPossible = false;
	//	}
	//}
}

void MenuScene::MenuCloseCallback(Ref *pSender)
{
	MenuItemImage *node = dynamic_cast <MenuItemImage *>(pSender);

	switch (node->getTag())
	{
	case e_Buttons::START:
		Director::getInstance()->replaceScene(TransitionCrossFade::create(1.0f, HelloWorld::createScene()));
		break;
	case e_Buttons::OPTION:
		ShowOption();
		break;
	case e_Buttons::EXIT:
		Director::getInstance()->end();
		break;
	default:
		break;
	}
}

void MenuScene::ShowOption()
{
	CCLOG("In the ShowOption funcion");
}

void MenuScene::InitVariables()
{
	mainBtnGoActionTime = 0;
	isMainBtnTimer = true;
	isPossible = true;
}