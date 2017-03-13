#pragma once
#ifndef _MAIN_OBJECT_
#define _MAIN_OBJECT_
#include "cocos2d.h"
USING_NS_CC;

class MainObject
{
	public:
		MainObject(Layer* layer);
		void Update();
		bool isDead;

	private:
		Sprite* MainTexture;
		PhysicsBody* MainBody;

		Size visibleSize;
		Vec2 origin;
};

#endif