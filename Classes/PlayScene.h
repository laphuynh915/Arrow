#ifndef __PLAY_SCENE_H__
#define __PLAY_SCENE_H__

#include "cocos2d.h"
#include "MainObject.h"
#include "Enemies.h"
#include "custommenusprite.h"
#include <vector>
using namespace std;
class PlayScene : public cocos2d::Layer
{
private:
	Sprite* BlueUp;
	Sprite* BlueDown;
	Sprite* BlueLeft;
	Sprite* BlueRight;

	Sprite* RedUp;
	Sprite* RedDown;
	Sprite* RedLeft;
	Sprite* RedRight;


	LabelTTF* scoreLabel;
	int score;
	Size visibleSize ;
	Vec2 origin ;
	void createEnemies(float dt);
	
	bool isEnd;

	void leftButtonTouch1();
	void rightButtonTouch1();
	void upButtonTouch1();
	void downButtonTouch1();

	void changeButton(float dt);
	void changeImage(MenuItemSprite* itemImage, Node*  normal, Node* disable);
	void reSetButton();
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
	bool onContactBegin(PhysicsContact &contact);
	vector <Enemies*> arraySprite;
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
	//Vector <int> index;
	void update(float dt);

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
	
	MenuItemSprite * m_left1;
	MenuItemSprite * m_right1;
	MenuItemSprite * m_down1;
	MenuItemSprite * m_up1;

	Menu* _menu;
    // implement the "static create()" method manually
    CREATE_FUNC(PlayScene);
};

#endif // __PlayScene_SCENE_H__
