//
//  Enemy.h
//  CJY_TowerDefense
//
//  Created by CC on 14-1-23.
//
//

#ifndef __CJY_TowerDefense__Enemy__
#define __CJY_TowerDefense__Enemy__

#include <iostream>
#include "cocos2d.h"
#include "HelloWorldScene.h"
#include "Waypoint.h"
#include "Tower.h"

class Enemy : public cocos2d::CCNode{

public:
    Enemy(void);
    ~Enemy(void);
    
    static Enemy* nodeWithTheGame(HelloWorld *game);
    bool initWithTheGame(HelloWorld *game);
    void doActivate(float dt);
    void getRemoved();
    
    void update(float dt);
    void draw(void);
    void getAttacked();
    void getAttacked(Tower* attacker);
    void gotLostSight(Tower* attacker);
    void getDamaged(int damage);
    
    CC_SYNTHESIZE(HelloWorld*, _theGame, TheGame);
    CC_SYNTHESIZE(cocos2d::CCSprite*, _mySprite, MySprite);
    
private:
    cocos2d::CCPoint myPosition;
    int maxHp;
    int currentHp;
    float walkingSpeed;
    Waypoint *destinationWaypoint;
    bool active;
    cocos2d::CCArray *attackedBy;
};


#endif /* defined(__CJY_TowerDefense__Enemy__) */








































