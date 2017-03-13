#include "MenuScene.h"
#include "PlayScene.h"
USING_NS_CC;

Scene* MenuScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MenuScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MenuScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto menuBackground = Sprite::createWithSpriteFrameName("MenuBackground.png");
	menuBackground->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
	this->addChild(menuBackground);
	

	//Button
	auto playBtn = MenuItemSprite::create(Sprite::createWithSpriteFrameName("PlayBtn.png"), Sprite::createWithSpriteFrameName("PlayBtn.png"), CC_CALLBACK_0(MenuScene::gotoPlayScene, this));
	playBtn->setScale(0.3);
	auto menu = Menu::create(playBtn, nullptr);
	menu->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 - 10);
	this->addChild(menu);
  
    
    return true;
}

void MenuScene::gotoPlayScene()
{
	auto playscene = PlayScene::createScene();
	Director::getInstance()->replaceScene(playscene);
}

void MenuScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
