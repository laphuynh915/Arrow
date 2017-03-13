#pragma once
#ifndef _ENEMIES_
#define _ENEMIES_
#include "cocos2d.h"
USING_NS_CC;

class Enemies
{
	public:
		Enemies(Layer* layer);
		void Fall();
		void moveFinished();
		int getType();
		void doAction();
		void setVelocity(float velo);
		void pubSetDynamic();
		~Enemies();
	private:
		void normalArrow();
		void redArrow();

		Sprite* enemieSprite;
		PhysicsBody * enemiePhysics;
		Size visibleSize;
		Vec2 origin;
		PhysicsBody* EneMainBody;
		bool isMoveFinished;
		float endPositionX;
		float velocityX;
};

#endif 