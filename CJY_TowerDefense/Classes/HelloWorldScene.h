#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::CCLayer
{
public:
    HelloWorld();
    ~HelloWorld();
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);

    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(HelloWorld);
    
    /*add*/
    void loadTowerPosition();
    void addWaypoints();
    bool canBuyTower();
    bool collisionWithCircle(cocos2d::CCPoint circlePoint,float radius,cocos2d::CCPoint circlePointTwo,float radiusTwo);
    void enemyGotKilled();
    void getHpDamage();
    bool loadWave();
    void doGameOver();
    void awardGold(int gold);
    
    virtual void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    
    
    CC_SYNTHESIZE(cocos2d::CCArray*, _towers, Towers);
    CC_SYNTHESIZE(cocos2d::CCArray*, _waypoints, Waypoints);
    CC_SYNTHESIZE(cocos2d::CCArray*, _enemies, Enemies);
private:
    cocos2d::CCArray* towerBases;
    int wave;
    cocos2d::CCLabelBMFont *ui_wave_lbl;
    int playerHp;
    cocos2d::CCLabelBMFont *ui_hp_lbl;
    bool gameEnded;
    int playerGold;
    cocos2d::CCLabelBMFont *ui_gold_lbl;
    
};

#endif // __HELLOWORLD_SCENE_H__






























