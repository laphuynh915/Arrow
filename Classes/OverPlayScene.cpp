#include "OverPlayScene.h"

USING_NS_CC;


// on "init" you need to initialize your instance
bool OverPlayScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//Background gameover
	auto overPanel = Sprite::createWithSpriteFrameName("Gameover.png");
	overPanel->setPosition(Point(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 1.5));

	this->addChild(overPanel);

	//Score
	//Tạo LabelTTF
	scoreLabel = LabelTTF::create("0", "fonts/Acid.ttf", 120);
	scoreLabel->setScale(0.3);
	scoreLabel->setPosition(origin.x + visibleSize.width / 2, overPanel->getPositionY() - 20);

	this->addChild(scoreLabel);

	//Button
	//Tương tự như Play Button, mình tạo 2 nút menu, replay và gắn nó vô menu thôi
	auto menuBtn = MenuItemSprite::create(Sprite::createWithSpriteFrameName("MenuBtn.png"), Sprite::createWithSpriteFrameName("MenuBtn_Selected.png"), CC_CALLBACK_0(OverPlayScene::gotoMenuScene, this));
	auto replayBtn = MenuItemSprite::create(Sprite::createWithSpriteFrameName("ReplayBtn.png"), Sprite::createWithSpriteFrameName("ReplayBtn_Selected.png"), CC_CALLBACK_0(OverPlayScene::gotoPlayScene, this));

	auto menu = Menu::create(menuBtn, replayBtn, nullptr);
	//Chỉnh align cho mấy cái nút, cách nhau 50
	menu->alignItemsHorizontallyWithPadding(50);

	menu->setPosition(origin.x + visibleSize.width / 2, overPanel->getPositionY());

	this->addChild(menu);
    
    return true;
}

void OverPlayScene::gotoMenuScene()
{
	auto menuscene = MenuScene::createScene();
	Director::getInstance()->replaceScene(TransitionMoveInT::create(0.25f, menuscene));
}

void OverPlayScene::gotoPlayScene()
{
	auto playscene = PlayScene::createScene();
	Director::getInstance()->replaceScene(playscene);
}
void OverPlayScene::setScore(int _score)
{
	score = _score;
	scoreLabel->setString(String::createWithFormat("%d", score)->getCString());
}
void OverPlayScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
