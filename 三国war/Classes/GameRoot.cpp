#include "GameRoot.h"
#include "Tower.h"
static GameRoot* _shareGameRoot = NULL;
static SceneStart* _SceneStart = NULL;
 static SceneSelect* _SceneSelect = NULL;
static SceneGame* _SceneGame = NULL;
static SceneOver* _SceneOver = NULL;
float ScaleX =0;
float ScaleY = 0;
GameRoot::~GameRoot(){
    CC_SAFE_RELEASE_NULL(_SceneStart);
    CC_SAFE_RELEASE_NULL(_SceneGame);
    CC_SAFE_RELEASE_NULL(_SceneOver);
    CC_SAFE_RELEASE_NULL(_SceneSelect);
    CC_SAFE_RELEASE_NULL(_actorArrL);
    CC_SAFE_RELEASE_NULL(_actorArrR);
    CC_SAFE_RELEASE_NULL(_TowerArrR);
    CC_SAFE_RELEASE_NULL(_TowerArrL);
}
GameRoot* GameRoot::shareGameRoot()
{
    if (_shareGameRoot==NULL) {
        _shareGameRoot = new GameRoot();
       _shareGameRoot->init();
        _shareGameRoot->InitializeResource();
    }
    return _shareGameRoot;
}
bool GameRoot::init()
{
    bool bRet = false;
    do {
        InitializeResource();
        _actorArrL = CCArray::create();
        _actorArrL->retain();
        _actorArrR = CCArray::create();
        _actorArrR->retain();
        _TowerArrL = CCArray::create();
        _TowerArrL->retain();
        _TowerArrR = CCArray::create();
        _TowerArrR->retain();
        _spriteTag = 10;
        bRet = true;
    } while (0);
    return bRet;
}
void GameRoot::InitializeResource()
{
	CCSpriteFrameCache* cache = 
			CCSpriteFrameCache::sharedSpriteFrameCache();
	cache->addSpriteFramesWithFile("GameUI01.plist", "GameUI01.png");
	cache->addSpriteFramesWithFile("GameUI02.plist", "GameUI02.png");
	cache->addSpriteFramesWithFile("ActorsPack1.plist", "ActorsPack1.png");
}
void  GameRoot::addSpriteTag()
{
    _spriteTag++;
}
void GameRoot::startGame()
{
    CCObject* _obj;
    CCARRAY_FOREACH( _actorArrL, _obj)
    {
        ActorBase* actor = (ActorBase*)_obj;
        actor->start();
    }
    CCARRAY_FOREACH( _actorArrR, _obj)
    {
        ActorBase* actor = (ActorBase*)_obj;
        actor->start();
    }
}
int GameRoot::getLiveActors(int var)
{
    CCArray* checkArr;
    if (var==1) {
        checkArr = _actorArrL;
    }else
        checkArr = _actorArrR;
    CCObject* _obj;
    int count = 0;
    CCARRAY_FOREACH(checkArr, _obj)
    {
        ActorBase* actor = (ActorBase*)_obj;
        if (actor->getActorData()->getblood()>0) {
            count++;
        }
    }
    return count;
}

int GameRoot::getLiveTowers(int var)
{
    CCArray* checkArr;
    if (var==1) {
        checkArr = _TowerArrL;
    }else
        checkArr = _TowerArrR;
    CCObject* _obj;
    int count = 0;
    CCARRAY_FOREACH(checkArr, _obj)
    {
        Tower* tower = (Tower*)_obj;
        if (tower->getBlood()>0) {
            count++;
        }
    }
    return count;
}
SceneStart* GameRoot::getSceneStart()
{
	if (_SceneStart == NULL){
		_SceneStart =(SceneStart*)SceneStart::Scene();
        _SceneStart->retain();
    }
	return _SceneStart;
}

SceneSelect* GameRoot::getSceneSelect()
{
	if (_SceneSelect == NULL){
		_SceneSelect = (SceneSelect*)SceneSelect::Scene();
        _SceneSelect->retain();
    }
	return _SceneSelect;
}

SceneGame* GameRoot::getSceneGame()
{
	if (_SceneGame == NULL){
		_SceneGame = (SceneGame*) SceneGame::Scene();
        _SceneGame->retain();
    }
	return _SceneGame;
}
bool GameRoot:: resetSceneGame()
{
    if (_SceneGame) {
        CC_SAFE_RELEASE_NULL(_SceneGame);
        return true;
    }
    return false;
}
SceneOver* GameRoot::getSceneOver()
{
	if (_SceneOver == NULL){
		_SceneOver = (SceneOver*) SceneOver::Scene();
        _SceneOver->retain();
    }
	return _SceneOver;
}