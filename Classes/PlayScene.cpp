#include "PlayScene.h"
#include "Enemies.h"
#include "OverplayScene.h"
#include "Definition.h"
#include  <SimpleAudioEngine.h>

auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
USING_NS_CC;
using namespace std;


Scene* PlayScene::createScene()
{
    // 'scene' is an autorelease object
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setGravity(Vec2(0, 0));
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    
    // 'layer' is an autorelease object
    auto layer = PlayScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool PlayScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
	
	BlueUp = Sprite::createWithSpriteFrameName("arrowUp.png");
	BlueDown = Sprite::createWithSpriteFrameName("arrowDown.png");
	BlueRight = Sprite::createWithSpriteFrameName("arrowRight.png");
	BlueLeft = Sprite::createWithSpriteFrameName("arrowLeft.png");

	RedUp = Sprite::createWithSpriteFrameName("redUp.png");
	RedDown = Sprite::createWithSpriteFrameName("redDown.png");
	RedRight = Sprite::createWithSpriteFrameName("redRight.png");
	RedLeft = Sprite::createWithSpriteFrameName("redLeft.png");


	audio->preloadEffect("buble.wav");

     visibleSize = Director::getInstance()->getVisibleSize();
     origin = Director::getInstance()->getVisibleOrigin();

	 isEnd = false;
	 auto ground = Sprite::createWithSpriteFrameName("PlayBackground.png");
	
	 ground->setPosition(Point(origin.x + visibleSize.width / 2, origin.y + visibleSize.height/2));
	addChild(ground);
	//Score Line
	//Là đối tượng để mình tính điểm nếu Pixel đi qua nó
	auto scoreline = Node::create();
	scoreline->setPosition(Point(origin.x + visibleSize.width/2, origin.y + visibleSize.height/5));
	auto linebody = PhysicsBody::createBox(Size(visibleSize.width,1), PhysicsMaterial(0, 0, 0));
	linebody->setDynamic(false);

	linebody->setCategoryBitmask(eObjectBitmask::LINE);
	linebody->setCollisionBitmask(0);
	linebody->setContactTestBitmask(eObjectBitmask::ENEMIE);

	scoreline->setPhysicsBody(linebody);
	this->addChild(scoreline);


	score = 0;
	scoreLabel = LabelTTF::create("0", "fonts/Acid.ttf", 100);
	scoreLabel->setScale(0.3);
	scoreLabel->setColor(Color3B(255, 255, 255));
	scoreLabel->setPosition(origin.x + visibleSize.width / 2, origin.y + (visibleSize.height / 6) * 5);

	this->addChild(scoreLabel, 50);

	



	//m_left = CustomMenuSprite::create(Sprite::create("arrowLeft.png"), Sprite::create("arrowLeft.png"), Sprite::create("arrowLeft.png"), menu_selector(PlayScene::leftButtonTouch));
	//m_left->setScale(0.3);

	//m_up = CustomMenuSprite::create(Sprite::create("arrowUp.png"), Sprite::create("arrowUp.png"), Sprite::create("arrowUp.png"), menu_selector(PlayScene::upButtonTouch));
	//m_up->setScale(0.3);

	//m_down = CustomMenuSprite::create(Sprite::create("arrowDown.png"), Sprite::create("arrowDown.png"), Sprite::create("arrowDown.png"), menu_selector(PlayScene::downButtonTouch));
	//m_down->setScale(0.3);
	
	//m_right = CustomMenuSprite::create(Sprite::create("arrowRight.png"), Sprite::create("arrowRight.png"), Sprite::create("arrowRight.png"), menu_selector(PlayScene::rightButtonTouch));
	//m_right->setScale(0.3);



	m_left1 = MenuItemSprite::create(BlueLeft,BlueLeft, CC_CALLBACK_0(PlayScene::leftButtonTouch1, this));
	m_left1->setScale(0.3);



	m_up1 = MenuItemSprite::create(BlueUp, BlueUp, CC_CALLBACK_0(PlayScene::upButtonTouch1, this));
	m_up1->setScale(0.3);

	m_down1 = MenuItemSprite::create(BlueDown, BlueDown, CC_CALLBACK_0(PlayScene::downButtonTouch1, this));
	m_down1->setScale(0.3);

	m_right1 = MenuItemSprite::create(BlueRight, BlueRight, CC_CALLBACK_0(PlayScene::rightButtonTouch1, this));
	m_right1->setScale(0.3);
	
	
	
	_menu = Menu::create(m_left1, m_up1, m_down1, m_right1, nullptr);
	_menu->alignItemsHorizontallyWithPadding(10.0f);
	_menu->setPosition(Point(origin.x + visibleSize.width / 2, origin.y + m_left1->getContentSize().height /2));

	this->addChild(_menu);
	
	
	
	
	 auto contactListener = EventListenerPhysicsContact::create();
	 contactListener->onContactBegin = CC_CALLBACK_1(PlayScene::onContactBegin, this);
	 Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);


	 this->scheduleUpdate();
	 this->schedule(schedule_selector(PlayScene::createEnemies), 0.7f);
	 this->schedule(schedule_selector(PlayScene::changeButton), 30.0f);
	
    return true;
}

void PlayScene::reSetButton()
{
	changeImage(m_down1, Sprite::createWithSpriteFrameName("arrowDown.png"), Sprite::createWithSpriteFrameName("arrowDown.png"));
	changeImage(m_up1, Sprite::createWithSpriteFrameName("arrowUp.png"), Sprite::createWithSpriteFrameName("arrowUp.png"));
	changeImage(m_left1, Sprite::createWithSpriteFrameName("arrowLeft.png"), Sprite::createWithSpriteFrameName("arrowLeft.png"));
	changeImage(m_right1, Sprite::createWithSpriteFrameName("arrowRight.png"), Sprite::createWithSpriteFrameName("arrowRight.png"));
}

void PlayScene::changeButton(float dt)
{
	if (score < 50)
	{
		switch (random(1, 2))
		{
			case 1:
				
				changeImage(m_down1, Sprite::createWithSpriteFrameName("redUp.png"), Sprite::createWithSpriteFrameName("redUp.png"));
				changeImage(m_up1, Sprite::createWithSpriteFrameName("redDown.png"), Sprite::createWithSpriteFrameName("redDown.png"));
				break;
			case 2:
				changeImage(m_left1, Sprite::createWithSpriteFrameName("redRight.png"), Sprite::createWithSpriteFrameName("redRight.png"));
				changeImage(m_right1, Sprite::createWithSpriteFrameName("redLeft.png"), Sprite::createWithSpriteFrameName("redLeft.png"));
				break;
		}
	}
	else
	{
		changeImage(m_down1, Sprite::createWithSpriteFrameName("redUp.png"), Sprite::createWithSpriteFrameName("redUp.png"));
		changeImage(m_up1, Sprite::createWithSpriteFrameName("redDown.png"), Sprite::createWithSpriteFrameName("redDown.png"));
		changeImage(m_left1, Sprite::createWithSpriteFrameName("redRight.png"), Sprite::createWithSpriteFrameName("redRight.png"));
		changeImage(m_right1, Sprite::createWithSpriteFrameName("redLeft.png"), Sprite::createWithSpriteFrameName("redLeft.png"));
	}
}

void  PlayScene::changeImage(MenuItemSprite* itemImage, Node*  normal, Node* disable)
{
	itemImage->setNormalImage(normal);
	itemImage->setSelectedImage(disable);
}
void PlayScene::update(float dt)
{
	
	if (score % 20 == 0)
	{
		reSetButton();
	}
	else
	{
		//
	}
}

bool PlayScene::onContactBegin(PhysicsContact &contact)

{ 
	isEnd = true;
	for (int i = 0; i < arraySprite.size(); ++i)
	{ 
		arraySprite[i]->moveFinished();
	}
	this->pause();
	OverPlayScene* overlayer = OverPlayScene::create();

	
	overlayer->setScore(score);
	this->addChild(overlayer, 110);
	return true;

}



void PlayScene::createEnemies(float dt)
{
	Enemies* a =  new Enemies(this);
	a->setVelocity(30.0f + score/5);
	

	arraySprite.push_back(a);
	a->Fall();
	

}



void PlayScene::leftButtonTouch1()
{

	cocos2d::Vector<cocos2d::FiniteTimeAction*> actions;

	actions.pushBack(cocos2d::ScaleTo::create(0.05, 0.5));
	actions.pushBack(cocos2d::ScaleBy::create(0.05, 0.5));

	auto sequence = cocos2d::Sequence::create(actions);
	m_left1->runAction(sequence);
	if (!isEnd)
	if (arraySprite.size() >= 1 && arraySprite[0]->getType() == 3)
	{
		audio->playEffect("buble.wav");
		arraySprite[0]->pubSetDynamic();
		score++;
		scoreLabel->setString(String::createWithFormat("%d", score)->getCString());
		arraySprite[0]->doAction();
		arraySprite.erase(arraySprite.begin());
	}
}
void PlayScene::rightButtonTouch1()
{
	cocos2d::Vector<cocos2d::FiniteTimeAction*> actions;

	actions.pushBack(cocos2d::ScaleTo::create(0.05, 0.5));
	actions.pushBack(cocos2d::ScaleBy::create(0.05, 0.5));

	auto sequence = cocos2d::Sequence::create(actions);
	m_right1->runAction(sequence);

	if (!isEnd)
	if (arraySprite.size() >= 1 && arraySprite[0]->getType() == 4)
	{
		audio->playEffect("buble.wav");
		arraySprite[0]->pubSetDynamic();
		score++;
		scoreLabel->setString(String::createWithFormat("%d", score)->getCString());
		arraySprite[0]->doAction();
		arraySprite.erase(arraySprite.begin());
	}
}
void PlayScene::upButtonTouch1()
{
	cocos2d::Vector<cocos2d::FiniteTimeAction*> actions;

	actions.pushBack(cocos2d::ScaleTo::create(0.05, 0.5));
	actions.pushBack(cocos2d::ScaleBy::create(0.05, 0.5));
	
	auto sequence = cocos2d::Sequence::create(actions);
	m_up1->runAction(sequence);


	if (!isEnd)
	if (arraySprite.size() >= 1 && arraySprite[0]->getType() == 1)
	{
		audio->playEffect("buble.wav");
		arraySprite[0]->pubSetDynamic();
		score++;
		scoreLabel->setString(String::createWithFormat("%d", score)->getCString());
		arraySprite[0]->doAction();
		arraySprite.erase(arraySprite.begin());
	}
}
void PlayScene::downButtonTouch1()
{

	cocos2d::Vector<cocos2d::FiniteTimeAction*> actions;

	actions.pushBack(cocos2d::ScaleTo::create(0.05, 0.5));
	actions.pushBack(cocos2d::ScaleBy::create(0.05, 0.5));

	auto sequence = cocos2d::Sequence::create(actions);
	m_down1->runAction(sequence);
	if (!isEnd)
	if (arraySprite.size() >= 1 && arraySprite[0]->getType() == 2)
	{
		audio->playEffect("buble.wav");
		score++;
		arraySprite[0]->pubSetDynamic();
		scoreLabel->setString(String::createWithFormat("%d", score)->getCString());
		arraySprite[0]->doAction();
		arraySprite.erase(arraySprite.begin());
	}
}
void PlayScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
