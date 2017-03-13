#include "Enemies.h"
#include "Definition.h"

Enemies::Enemies(Layer* layer)
{
	isMoveFinished = false;
	origin = Director::getInstance()->getVisibleOrigin();
	visibleSize = Director::getInstance()->getVisibleSize();
	
	if (random(1, 10) <= 8)
	{
		normalArrow(); // create sprite
	}
	else
	{
		redArrow();
	}
		enemieSprite->setScale(0.2);
		enemieSprite->setPosition(Vec2(origin.x + random((int)enemieSprite->getContentSize().width / 2, (int)visibleSize.width - (int)enemieSprite->getContentSize().width / 2), origin.y + visibleSize.height + enemieSprite->getContentSize().height));
		EneMainBody = PhysicsBody::createBox(enemieSprite->getContentSize()/6);
		EneMainBody->setCategoryBitmask(eObjectBitmask::ENEMIE);
		EneMainBody->setContactTestBitmask(eObjectBitmask::LINE);
		enemieSprite->setPhysicsBody(EneMainBody);
		
		layer->addChild(enemieSprite);

		endPositionX = origin.y + enemieSprite->getContentSize().height / 2;
		
	
}

void Enemies::doAction()
{
	cocos2d::Vector<cocos2d::FiniteTimeAction*> actions;
	
	actions.pushBack(cocos2d::ScaleBy::create(0.5, 1.5));
	actions.pushBack(cocos2d::TintTo::create(0.2, 255, 255, 255));
	actions.pushBack(cocos2d::FadeTo::create(0.2, 30));
	actions.pushBack(CallFunc::create(CC_CALLBACK_0(Enemies::moveFinished,this)));
	
	auto sequence = cocos2d::Sequence::create(actions);
	enemieSprite->runAction(sequence);

}

void  Enemies::setVelocity(float velo)
{
	velocityX = velo;
}
int Enemies::getType()
{
	return enemieSprite->getTag();
}

void  Enemies::pubSetDynamic()
{
	EneMainBody->setCategoryBitmask(0);
	EneMainBody->setContactTestBitmask(0);
	enemieSprite->setPhysicsBody(EneMainBody);

}
void Enemies::moveFinished()
{
	//Khi mà di chuyển kết thúc, mình sẽ remove nó ra khỏi layer hiện tại
	enemieSprite->removeFromParent();
	isMoveFinished = true;
}

void Enemies::Fall()
{
	enemieSprite->runAction(Sequence::createWithTwoActions(MoveTo::create(visibleSize.height / velocityX, Point(enemieSprite->getPositionX(), endPositionX)), CallFunc::create(CC_CALLBACK_0(Enemies::moveFinished, this))));
}

void Enemies::normalArrow()
{ 
	switch (random(1, 4)) // RANDOM THE ARROW
	{
	case 1:
		{
				  enemieSprite = Sprite::createWithSpriteFrameName("arrowUp.png");
				  enemieSprite->setTag(1);
				  break;
		}
	case 2:
		{
				  enemieSprite = Sprite::createWithSpriteFrameName("arrowDown.png");
				  enemieSprite->setTag(2);
				  break;
		}
	case 3:
		{
				  enemieSprite = Sprite::createWithSpriteFrameName("arrowLeft.png");
				  enemieSprite->setTag(3);
				  break;
		}
	case 4:
		{
				  enemieSprite = Sprite::createWithSpriteFrameName("arrowRight.png");
				  enemieSprite->setTag(4);
				  break;
		}
	}
}

void Enemies::redArrow()
{ 
	switch (random(1, 4)) // RANDOM THE ARROW
	{
	case 1:
		{
				  enemieSprite = Sprite::createWithSpriteFrameName("redUp.png");
				  enemieSprite->setTag(2);
				break;
		}
	case 2:
		{
				  enemieSprite = Sprite::createWithSpriteFrameName("redDown.png");
				  enemieSprite->setTag(1);
				break;
		}
	case 3:
		{
				  enemieSprite = Sprite::createWithSpriteFrameName("redLeft.png");
				  enemieSprite->setTag(4);
				break;
		}
	case 4:
		{
				  enemieSprite = Sprite::createWithSpriteFrameName("redRight.png");
				  enemieSprite->setTag(3);
				break;
		}
	}
}

Enemies::~Enemies()
{

}
