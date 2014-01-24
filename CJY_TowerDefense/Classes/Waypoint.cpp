//
//  Waypoint.cpp
//  CJY_TowerDefense
//
//  Created by CC on 14-1-23.
//
//

#include "Waypoint.h"
using namespace cocos2d;

Waypoint::Waypoint(void)
{
    _nextWaypoint = NULL;
}

Waypoint::~Waypoint(void)
{
}

Waypoint* Waypoint::nodeWithTheGame(HelloWorld *game, cocos2d::CCPoint location){

    Waypoint *pRet = new Waypoint();
    if (pRet && pRet->initWithTheGame(game, location)) {
        return pRet;
    }else{
    
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

bool Waypoint::initWithTheGame(HelloWorld *game, cocos2d::CCPoint location){

    bool bRet = false;
    do{
    
        theGame = game;
        _myPosition = location;
        
        this->setPosition(CCPointZero);
        theGame->addChild(this);
        bRet = true;
    }while(0);
    return bRet;
}

void Waypoint::draw(){

#ifdef COCOS2D_DEBUG
    ccDrawColor4F(0, 255, 0, 255);
    ccDrawCircle(_myPosition, 6, 360, 30, false);
    ccDrawCircle(_myPosition, 2, 360, 30, false);

    if (_nextWaypoint) {
        ccDrawLine(_myPosition, _nextWaypoint->_myPosition);
    }
#endif
    
    CCNode::draw();
}



































