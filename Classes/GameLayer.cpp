#include "GameLayer.h"
#include "EnumUtil.h"
#include <math.h>

USING_NS_CC;
using namespace std;

GameLayer::GameLayer() {

}

GameLayer::~GameLayer() {

}

bool GameLayer::init() {
    bool ret = false;
    do {
        CC_BREAK_IF(!Layer::init());

        _map = TMXTiledMap::create("basemap1.tmx");

        CCLOG("map size:%f,%f", _map->getTileSize().width, _map->getTileSize().height);
        _bgLayer = _map->getLayer("background");
        _metaLayer = _map->getLayer("meta");
        _metaLayer->setVisible(false);
        if (_map == nullptr)
            CCLOG("err: GameLayer::init 4");
        else
            CCLOG("cr GameLayer::init 4");
        this->addChild(_map, 0);

        _hero = Hero::create();
        CCLOG("GameLayer: %f, %f, %f, %f", _map->getMapSize().width, _map->getTileSize().width, _map->getMapSize().height, _map->getTileSize().height);
        _hero->setPosition(
                Point(
                        (_map->getMapSize().width-1) * _map->getTileSize().width/2
                                ,
                        (_map->getMapSize().height-1) * _map->getTileSize().height/2
                                ));
        this->addChild(_hero,1);

        _enemy = Enemy::create();
        _enemy->setPosition(Point(
                _map->getMapSize().width * _map->getTileSize().width/2,
                _map->getMapSize().height * _map->getTileSize().height/2));
        this->addChild(_enemy,1);


        _hostage1 = Hostage::create();
        _hostage1->setPosition(Point(_map->getTileSize().width*2 - _map->getTileSize().width / 2,
                _map->getTileSize().height*17 - _map->getTileSize().height / 2));
        this->addChild(_hostage1,1);

        _hostage2 = Hostage::create();
        _hostage2->setPosition(Point(_map->getTileSize().width*12 - _map->getTileSize().width / 2,
                _map->getTileSize().height*2 - _map->getTileSize().height / 2));
        this->addChild(_hostage2,1);

        this->schedule(schedule_selector(GameLayer::update), 0.1f);
        ret = true;
    } while (0);
    return ret;
}

void GameLayer::update(float dt) {
    //            CCLOG("%f",dt);
    _hero->doAction();
    _enemy->doAction();

    checkNewEvent();
//    if()
//    if (tempstate == 1) {
//
//
//    } else {
//        //_hero->setPositionX(_hero->getPositionX()+1);
//    }
}

Point GameLayer::tileCoordinate(float x, float y) {
    int newx = x/_map->getTileSize().width;
    int newy = (_map->getMapSize().height*_map->getTileSize().height-y)/_map->getTileSize().height;
    return Point(newx,newy);
}

bool GameLayer::canGo(float x, float y) {
    bool ret = true;
    int gid = _metaLayer->getTileGIDAt(tileCoordinate(x,y));
    CCLOG("gid is :%d", gid);
    unordered_map<string,Value> kmap = _map->getPropertiesForGID(gid).asValueMap();
    if(kmap.empty()) {
        CCLOG("err: kmap is null!!");
    } else {
        Value str = kmap.at("Collidable");
        CCLOG("%s",str.asString().c_str());
        if(str.asString().compare("true") == 0) {
            return false;
        }
    }

    return ret;

}

void GameLayer::onWalk(int direction) {
    CCLOG("GameLayer onWalk");
//    _hero->setState(Direction::)
    tempstate = 1;
    tempdirect = direction;
    int newx, newy;
        switch (tempdirect) {
                case 0: //up
                    newx = _hero->getPositionX();
                    newy = _hero->getPositionY() + _map->getTileSize().height;
                    if (canGo(newx, newy)) {
                        _hero->setPositionY(
                                _hero->getPositionY() + _map->getTileSize().height);
                    }
                    break;
                case 1: //down
                    newx = _hero->getPositionX();
                    newy = _hero->getPositionY() - _map->getTileSize().height;;
                    if (canGo(newx, newy)) {
                        _hero->setPositionY(
                                _hero->getPositionY() - _map->getTileSize().height);
                    }
                    break;
                case 2: //left
                    newx = _hero->getPositionX() - _map->getTileSize().width;
                    newy = _hero->getPositionY();
                    if (canGo(newx, newy)) {
                        _hero->setPositionX(
                                _hero->getPositionX() - _map->getTileSize().width);
                    }
                    break;
                case 3: //right
                    newx = _hero->getPositionX() + _map->getTileSize().width;
                    newy = _hero->getPositionY();
                    if (canGo(newx, newy)) {
                        _hero->setPositionX(
                                _hero->getPositionX() + _map->getTileSize().width);
                    }
                    break;
                }
}

void GameLayer::onStop() {
    CCLOG("GameLayer onStop");
    tempstate = 0;
}

void GameLayer::checkNewEvent() {
    int dist = distance(_hero->getPosition(), _enemy->getPosition());
    if (dist < 150) {
        CCLOG("I see you and attacking!");
    } else if (dist < 300){
        CCLOG("I see you!");
    } else {
        CCLOG("CANNOT see..");
    }
}

int GameLayer::distance(Point a, Point b) {
    int x = (int)(a.x - b.x);
    int y = (int)(a.y - b.y);

    return (int)sqrt(x*x + y*y);
}
