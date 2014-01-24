//
//  Waypoint.h
//  CJY_TowerDefense
//
//  Created by CC on 14-1-23.
//
//

#ifndef __CJY_TowerDefense__Waypoint__
#define __CJY_TowerDefense__Waypoint__

#include <iostream>
#include "cocos2d.h"
#include "HelloWorldScene.h"

class Waypoint : public cocos2d::CCNode
{
public:
    Waypoint(void);
    ~Waypoint(void);
    
    static Waypoint* nodeWithTheGame(HelloWorld* game, cocos2d::CCPoint location);
    bool initWithTheGame(HelloWorld* game, cocos2d::CCPoint location);
    
    void draw(void);
    
    CC_SYNTHESIZE(cocos2d::CCPoint, _myPosition, MyPosition);
    CC_SYNTHESIZE(Waypoint*, _nextWaypoint, NextWaypoint);
    
private:
    HelloWorld* theGame;
};
#endif /* defined(__CJY_TowerDefense__Waypoint__) */
