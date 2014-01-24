#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "Tower.h"
#include "Waypoint.h"
#include "Enemy.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

HelloWorld::HelloWorld(){


}
HelloWorld::~HelloWorld(){

    towerBases->release();
    _towers->release();
    _waypoints->release();
    _enemies->release();
}
CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    /*add background*/
    bool bRet = false;
    do{
    
        CC_BREAK_IF(!CCLayer::init());
        /*init*/
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        this->setTouchEnabled(true);
        CCSprite *background = CCSprite::create("Bg.png");
        this->addChild(background);
        background->setPosition(ccp(background->getContentSize().width / 2,background->getContentSize().height / 2));
        
        this->loadTowerPosition();
        this->addWaypoints();
        
        _towers = CCArray::create();
        _towers->retain();
        
        wave = 0;
        ui_wave_lbl = CCLabelBMFont::create(CCString::createWithFormat("WAVE:%d",wave)->getCString(),"font_red_14.fnt");
        this->addChild(ui_wave_lbl,10);
        ui_wave_lbl->setPosition(ccp(400, background->getContentSize().height - 12));
        ui_wave_lbl->setAnchorPoint(ccp(0, 0.5));
        
        _enemies = CCArray::create();
        _enemies->retain();
        
        this->loadWave();
        
        gameEnded = false;
        playerHp = 5;
        ui_hp_lbl = CCLabelBMFont::create(CCString::createWithFormat("HP: %d", playerHp)->getCString(), "font_red_14.fnt");
        this->addChild(ui_hp_lbl, 10);
        ui_hp_lbl->setPosition(ccp(35, background->getContentSize().height - 12));
        
        playerGold = 1000;
        ui_gold_lbl = CCLabelBMFont::create(CCString::createWithFormat("GOLD: %d", playerGold)->getCString(), "font_red_14.fnt");
        this->addChild(ui_gold_lbl, 10);
        ui_gold_lbl->setPosition(ccp(135, background->getContentSize().height - 12));
        ui_gold_lbl->setAnchorPoint(ccp(0, 0.5));
        
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("8bitDungeonLevel.mp3", true);
        
        bRet = true;
        
        
    }while(0);
    
    return bRet;
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}


void HelloWorld::loadTowerPosition(){

    CCArray *towerPositions = CCArray::createWithContentsOfFile("TowersPosition.plist");
    towerBases = CCArray::createWithCapacity(10);
    towerBases->retain();
    
    CCObject *pObject = NULL;
    CCARRAY_FOREACH(towerPositions, pObject){
    
        CCDictionary *towerPos = (CCDictionary *)pObject;
        CCSprite *towerBase = CCSprite::create("open_spot.png");
        this->addChild(towerBase);
        
        /*translate position*/
        int posX = ((CCString *)towerPos->objectForKey("x"))->intValue();
        int posY = ((CCString *)towerPos->objectForKey("y"))->intValue();
        
        towerBase->setPosition(ccp(posX,posY));
        towerBases->addObject(towerBase);
        
    }
    
}

bool HelloWorld::canBuyTower(){

    if (playerGold - kTOWER_COST >= 0)
    {
        return true;
    }
    return false;
}

void HelloWorld::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent){

    CCSetIterator iter = pTouches->begin();
    for (; iter != pTouches->end(); iter++)
    {
        CCTouch* pTouch = (CCTouch*)(*iter);
        CCPoint location = pTouch->getLocation();
        
        CCObject *pObject = NULL;
        CCARRAY_FOREACH(towerBases, pObject)
        {
            CCSprite *tb = (CCSprite*)pObject;
            if (this->canBuyTower() && tb->boundingBox().containsPoint(location) && !tb->getUserData())
            {
                //We will spend our gold later.
                playerGold -= kTOWER_COST;
                ui_gold_lbl->setString(CCString::createWithFormat("GOLD: %d", playerGold)->getCString());
                
                Tower* tower = Tower::nodeWithTheGame(this, tb->getPosition());
                _towers->addObject(tower);
                tb->setUserData(tower);
                
                CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("tower_place.wav");
                
            }
        }
    }
}

void HelloWorld::addWaypoints(){

    _waypoints = CCArray::create();
    _waypoints->retain();
    
    Waypoint *waypoint1 = Waypoint::nodeWithTheGame(this, ccp(420,35));
    _waypoints->addObject(waypoint1);
    
    Waypoint *waypoint2 = Waypoint::nodeWithTheGame(this, ccp(35, 35));
    _waypoints->addObject(waypoint2);
    waypoint2->setNextWaypoint(waypoint1);
    
    Waypoint *waypoint3 = Waypoint::nodeWithTheGame(this, ccp(35, 130));
    _waypoints->addObject(waypoint3);
    waypoint3->setNextWaypoint(waypoint2);
    
    Waypoint *waypoint4 = Waypoint::nodeWithTheGame(this, ccp(445, 130));
    _waypoints->addObject(waypoint4);
    waypoint4->setNextWaypoint(waypoint3);
    
    Waypoint *waypoint5 = Waypoint::nodeWithTheGame(this, ccp(445, 220));
    _waypoints->addObject(waypoint5);
    waypoint5->setNextWaypoint(waypoint4);
    
    Waypoint *waypoint6 = Waypoint::nodeWithTheGame(this, ccp(-40, 220));
    _waypoints->addObject(waypoint6);
    waypoint6->setNextWaypoint(waypoint5);
}

bool HelloWorld::collisionWithCircle(cocos2d::CCPoint circlePoint, float radius, cocos2d::CCPoint circlePointTwo, float radiusTwo){

    float xdif = circlePoint.x - circlePointTwo.x;
    float ydif = circlePoint.y - circlePointTwo.y;
    
    float distance = sqrtf(xdif * xdif + ydif * ydif);
    if (distance <= radius + radiusTwo) {
        return true;
    }else{
        return false;
    }
}

void HelloWorld::enemyGotKilled(){

    if (_enemies->count() <= 0) {
        if (!this->loadWave()) {
            CCLOG("You win!");
            CCDirector::sharedDirector()->replaceScene(CCTransitionSplitCols::create(1, HelloWorld::scene()));
        }
    }
}
bool HelloWorld::loadWave(){
    
    CCArray *waveDate = CCArray::createWithContentsOfFile("Waves.plist");
    if (wave >= waveDate->count()) {
        return false;
    }
    CCArray *currentWaveData = (CCArray*)waveDate->objectAtIndex(wave);
    CCObject *pObject = NULL;
    CCARRAY_FOREACH(currentWaveData, pObject){
    
        CCDictionary *enemyData = (CCDictionary*)pObject;
        Enemy *enemy = Enemy::nodeWithTheGame(this);
        _enemies->addObject(enemy);
        enemy->schedule(schedule_selector(Enemy::doActivate), ((CCString *)enemyData->objectForKey("spawnTime"))->floatValue());
        
        
    }
    wave++;
    ui_wave_lbl->setString(CCString::createWithFormat("WAVE:%d",wave)->getCString());
    
    return true;
}

void HelloWorld::getHpDamage()
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("life_lose.wav");
    playerHp--;
    ui_hp_lbl->setString(CCString::createWithFormat("HP: %d", playerHp)->getCString());
    if (playerHp <= 0)
    {
        this->doGameOver();
    }
}

void HelloWorld::doGameOver()
{
    if (!gameEnded)
    {
        gameEnded = true;
        CCDirector::sharedDirector()->replaceScene(CCTransitionRotoZoom::create(1, HelloWorld::scene()));
    }
}


void HelloWorld::awardGold(int gold)
{
    playerGold += gold;
    ui_gold_lbl->setString(CCString::createWithFormat("GOLD: %d", playerGold)->getCString());
}


















































