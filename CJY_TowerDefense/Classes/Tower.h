//
//  Tower.h
//  CJY_TowerDefense
//
//  Created by CC on 14-1-23.
//
//

#ifndef __CJY_TowerDefense__Tower__
#define __CJY_TowerDefense__Tower__

#include <iostream>
#include "cocos2d.h"
#include "HelloWorldScene.h"

#define kTOWER_COST 300

class Enemy;

class Tower : public cocos2d::CCNode{

public:
    Tower();
    ~Tower();
    
    static Tower *nodeWithTheGame(HelloWorld *game,cocos2d::CCPoint location);
    bool initWithTheGame(HelloWorld *game,cocos2d::CCPoint location);
    
    void update(float dt);
    void draw(void);
    void attackEnemy();
    void shootWeapon(float dt);
    void chosenEnemyForAttack(Enemy *enemy);
    void damageEnemy();
    void removeBullet(cocos2d::CCSprite *bullet);
    void targetKilled();
    void lostSightOfEnemy();
    
    
    CC_SYNTHESIZE(HelloWorld *, _theGame, TheGame);
    CC_SYNTHESIZE(cocos2d::CCSprite *, _mySprite, MySprite);
    
private:
    int attackRange;
    int damage;
    float fireRate;
    
    bool attacking;
    Enemy *chosenEnemy;
};

#endif /* defined(__CJY_TowerDefense__Tower__) */






























