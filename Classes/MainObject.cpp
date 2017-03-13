#include "MainObject.h"


MainObject::MainObject(Layer* layer)
{
	//Mình sẽ lấy các giá trị của màn hình
	origin = Director::getInstance()->getVisibleOrigin();
	visibleSize = Director::getInstance()->getVisibleSize();

	//Tạo sprite cho MainObject, và set vị trí cho nó
	MainTexture = Sprite::create("MainObject.png");
	MainTexture->setPosition(origin.x + visibleSize.width / 2, MainTexture->getContentSize().height/2);
	MainBody = PhysicsBody::createBox(MainTexture->getContentSize());
	//Cuối cùng là gán body cho Sprite thôi :p
	MainTexture->setPhysicsBody(MainBody);

	//Mình sẽ add nó vào layer hiện tại, cho index cỡ 100 để nó trên tất cả các cái khác
	layer->addChild(MainTexture, 100);

	//Các giá trị mặc định cho các biến
	
	isDead = false;
}


