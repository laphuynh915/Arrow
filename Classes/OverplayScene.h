#ifndef __OVER_SCENE_H__
#define __OVER_SCENE_H__
#include "PlayScene.h"
#include "MenuScene.h"
#include "cocos2d.h"

class OverPlayScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(OverPlayScene);

	void setScore(int _score);

private:
	void gotoMenuScene();
	void gotoPlayScene();
	int score;
	LabelTTF* scoreLabel;
	//LabelTTF* scoreLabel;
};

#endif // __OverPlayScene_SCENE_H__
