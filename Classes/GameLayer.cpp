//
//
//  SaveHostage
//
//  Created by Ke Peng on 4/9/14.
//
//

#include "GameLayer.h"

USING_NS_CC;
using namespace std;

#define SIGN 800

#define HERO 30,11
#define ENEMY 2, 2

#define UNLOCKBT 27,15
#define JOYSTICK 4,15

#define ROUTENUM 6
#define HOSTAGE0 1,1
#define WATCHHOSTAGE0 2,1
#define HOSTAGE1 1,11
#define WATCHHOSTAGE1 2,10
#define HOSTAGE2 20,9
#define WATCHHOSTAGE2 21,11
#define HOSTAGE3 20,1
#define WATCHHOSTAGE3 19,2
#define HOSTAGE4 12,7
#define WATCHHOSTAGE4 13,7

#define TAG_HEALTH 100
#define TAG_INVISIBLE 101
#define TAG_SPEED 102
#define TAG_UNBREAK 103

#define POTION1 16,4
#define POTION2 6,2
#define POTION3 7,10
#define POTION4 17,9

GameLevel GameLayer::game_level = GameLevel::MORTAL;

GameLayer::GameLayer() {
    
}

GameLayer::~GameLayer() {
    
}

void GameLayer::resetGameLayer() {
    map<Direction, vector<Rect>> rectsMap =
    ImageHelper::sharedImageHelper()->getWalkAnimationsRects();
    _hero->reset();
    for (int i = 0; i < hostages.size(); i++) {
        hostages[i]->reset();
    }
    _enemy->reset();
    positionAllRoles();
    joyStickerEnabled = true;
    GameSuspended = false;
    heroHealthBarTimer->setPercentage(100);
}

void GameLayer::restartGame() {
    resetGameLayer();
}

void GameLayer::resumeGmame() {
    GameSuspended = false;
    joyStickerEnabled = true;
}

void GameLayer::pauseGame() {
    GameSuspended = true;
    joyStickerEnabled = false;
}

void GameLayer::positionHero() {
    _hero->setPosition(tileCoordinate2Pixel(Point(HERO)));
    _hero->setCurrentNode(
                          tileCoordinate(_hero->getPositionX(), _hero->getPositionY()));
    _hero->setNextNode(
                       tileCoordinate(_hero->getPositionX(), _hero->getPositionY()));
}

void GameLayer::positionHostages() {
    _hostage0->setPosition(tileCoordinate2Pixel(Point(HOSTAGE0)));
    _hostage1->setPosition(tileCoordinate2Pixel(Point(HOSTAGE1)));
    _hostage2->setPosition(tileCoordinate2Pixel(Point(HOSTAGE2)));
    _hostage3->setPosition(tileCoordinate2Pixel(Point(HOSTAGE3)));
    _hostage4->setPosition(tileCoordinate2Pixel(Point(HOSTAGE4)));
}

void GameLayer::positionEnemies() {
    _enemy->setPosition(tileCoordinate2Pixel(Point(ENEMY)));
    _enemy->initialIdleMove();
}

void GameLayer::positionAllRoles() {
    positionHero();
    positionEnemies();
    positionHostages();
    for (int i = 0; i < potions.size(); i++) {
        potions[i]->setVisible(true);
    }
}

void GameLayer::initGameControls() {
    gameSticker = JoyStick::createJoyStick("control_bg.png", "joystick.png", 25,
                                           65, false, true, false, true);
    gameSticker->setPosition(tileCoordinate2Pixel(Point(JOYSTICK)));
    gameSticker->setDelegate(this);
    this->addChild(gameSticker, 2);
    
    saveBtn = MenuItemImage::create("key.png", "key2.png",
                                    CC_CALLBACK_1(GameLayer::saveBtnPressed, this));
    Menu* pMenu = Menu::create(saveBtn, NULL);
    pMenu->setPosition(tileCoordinate2Pixel(Point(UNLOCKBT)));
    this->addChild(pMenu, 2);
    
    Sprite* timerSprite = Sprite::create("hpblood.png");
    heroHealthBarTimer = ProgressTimer::create(timerSprite);
    heroHealthBarTimer->setType(ProgressTimer::Type::BAR);
    heroHealthBarTimer->setMidpoint(Point(0.0, 0.5));
    heroHealthBarTimer->setPercentage(100);
    heroHealthBarTimer->setZOrder(100);
    heroHealthBarTimer->setVisible(true);
    heroHealthBarTimer->setPosition(555.0f, 90.0f);
    addChild(heroHealthBarTimer, 1);
}

bool GameLayer::init() {
    bool ret = false;
    do {
        CC_BREAK_IF(!Layer::init());
        _map = TMXTiledMap::create("basemap1.tmx");
        _bgLayer = _map->getLayer("background");
        _metaLayer = _map->getLayer("meta");
        _metaLayer->setVisible(false);
        this->addChild(_map, 0);
        
        loadCharactorAndScene();
        // Set the game level
        _enemy->setGameLevel();
        initGameControls();
        resetGameLayer();
        // The Save btn timer should be the child of GameLayer
        for (int i = 0; i < hostages.size(); i++) {
            hostages[i]->addSaveTimer(this);
        }
        this->schedule(schedule_selector(GameLayer::update), 1 / FPS);
        ret = true;
    } while (0);
    return ret;
}

void GameLayer::loadCharactorAndScene() {
    // Hero init
    _hero = Hero::create();
    this->addChild(_hero, 2);
    
    // Enemy init
    _enemy = Enemy::create();
    _enemy->setLoopRoute(generateLoop());
    _enemy->setTarget(_hero);
    _enemy->initialIdleMove();
    _enemy->reset();
    _enemy->setParentLayer(this);
    this->addChild(_enemy, 2);
    
    // Hostage init
    _hostage0 = Hostage::create();
    this->addChild(_hostage0, 1);
    _hostage1 = Hostage::create();
    this->addChild(_hostage1, 1);
    _hostage2 = Hostage::create();
    this->addChild(_hostage2, 1);
    _hostage3 = Hostage::create();
    this->addChild(_hostage3, 1);
    _hostage4 = Hostage::create();
    this->addChild(_hostage4, 1);
    
    hostages.push_back(_hostage0);
    hostages.push_back(_hostage1);
    hostages.push_back(_hostage2);
    hostages.push_back(_hostage3);
    hostages.push_back(_hostage4);
    
    
    hostagesWatch.push_back(Point(WATCHHOSTAGE0));
    hostagesWatch.push_back(Point(WATCHHOSTAGE1));
    hostagesWatch.push_back(Point(WATCHHOSTAGE2));
    hostagesWatch.push_back(Point(WATCHHOSTAGE3));
    hostagesWatch.push_back(Point(WATCHHOSTAGE4));
    
    vector<Sprite*> prisons;
    for (int i = 0; i < 5; i++) {
        prisons.push_back(Sprite::create("prison.png"));
        this->addChild(prisons[i], 2);
    }
    prisons[0]->setPosition(tileCoordinate2Pixel(Point(HOSTAGE0)));
    prisons[1]->setPosition(tileCoordinate2Pixel(Point(HOSTAGE1)));
    prisons[2]->setPosition(tileCoordinate2Pixel(Point(HOSTAGE2)));
    prisons[3]->setPosition(tileCoordinate2Pixel(Point(HOSTAGE3)));
    prisons[4]->setPosition(tileCoordinate2Pixel(Point(HOSTAGE4)));
    
    int rand1 = rand() % 4;
    int rand2 = (rand1 + 1) % 4;
    int rand3 = (rand2 + 1) % 4;
    int rand4 = (rand3 + 1) % 4;
    
    Sprite* tmp_potions[4];
    tmp_potions[0] = Sprite::create("potion_health.png");
    tmp_potions[0]->setTag(TAG_HEALTH);
    tmp_potions[1] = Sprite::create("potion_invisible.png");
    tmp_potions[1]->setTag(TAG_INVISIBLE);
    tmp_potions[2] = Sprite::create("potion_speed.png");
    tmp_potions[2]->setTag(TAG_SPEED);
    tmp_potions[3] = Sprite::create("potion_unbreak.png");
    tmp_potions[3]->setTag(TAG_UNBREAK);
    tmp_potions[rand1]->setPosition(tileCoordinate2Pixel(Point(POTION1)));
    tmp_potions[rand2]->setPosition(tileCoordinate2Pixel(Point(POTION2)));
    tmp_potions[rand3]->setPosition(tileCoordinate2Pixel(Point(POTION3)));
    tmp_potions[rand4]->setPosition(tileCoordinate2Pixel(Point(POTION4)));
    potions.push_back(tmp_potions[rand1]);
    potions.push_back(tmp_potions[rand2]);
    potions.push_back(tmp_potions[rand3]);
    potions.push_back(tmp_potions[rand4]);
    for (int i = 0; i < potions.size(); i++) {
        this->addChild(potions[i], 1);
    }
    
    pauseBtn = MenuItemImage::create(PIC_PAUSE, PIC_PAUSE_PRESSED,
                                     CC_CALLBACK_1(GameLayer::pausedGame, this));
    Menu* menu = Menu::create(pauseBtn,NULL);
    menu->setPosition(600,45);
    this->addChild(menu,7);
    
    MenuItemImage* soundOnBtn = MenuItemImage::create(PIC_SOUND_ON, PIC_SOUND_ON);
    MenuItemImage* soundOffBtn = MenuItemImage::create(PIC_SOUND_OFF, PIC_SOUND_OFF);
    
    MenuItemToggle* toggle = MenuItemToggle::createWithCallback(CC_CALLBACK_1(GameLayer::soundSwitch,this), soundOnBtn, soundOffBtn, NULL);
    Menu* menu1 = Menu::create();
    menu1->addChild(toggle);
    menu1->setPosition(550,45);
    addChild(menu1,7);
    
}

void GameLayer::saveBtnPressed(Object* pSender) {
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(EFCT_UNLOCK1);
}

void GameLayer::onJoyStickUpdate(Node*sender, float angle, Point direction,
                                 float power) {
    if (!joyStickerEnabled) {
        return;
    }
}

Point GameLayer::convertCoordinate2Pixel(int x, int y, int mapHeight) {
    return Point((x + 0.5) * BLKWIDTH, (mapHeight - y - 0.5) * BLKWIDTH);
}

void GameLayer::checkSaveButton() {
    int i = 0;
    for (; i < hostages.size(); i++) {
        if (!hostages[i]->isSaved()
            && distance(hostages[i]->getPosition(), _hero->getPosition())
            < 40.0) {
            saveBtn->setEnabled(true);
            break;
        }
    }
    if (i == hostages.size()) {
        saveBtn->setEnabled(false);
    }
    if (saveBtn->isSelected()) {
        joyStickerEnabled = false;
        if (_hero->getCurrentHostage()) {
            _hero->incrementSavingClock();
            _hero->getCurrentHostage()->setClockPassed(_hero->getSavingClock());
            return;
        }
        for (; i < hostages.size(); i++) {
            if (!hostages[i]->isSaved()
                && distance(hostages[i]->getPosition(),
                            _hero->getPosition()) < 40.0) {
                    _hero->setCurrentHostage(hostages[i]);
                    _hero->setTargetSavingClocks(
                                                 hostages[i]->getTotalClocksNeeded());
                    hostages[i]->showProgressTimer();
                    break;
                }
        }
    } else {
        if (_hero->getCurrentHostage())
            _hero->getCurrentHostage()->hideProgressTimer();
        _hero->setCurrentHostage(NULL);
        _hero->zeroSavingClock();
        joyStickerEnabled = true;
    }
}

void GameLayer::checkJoysticker() {
    float angle = gameSticker->getaAngle();
    if (joyStickerEnabled && gameSticker->getpPower() > 0.5) {
        Direction direction = STOP;
        Point nextNode;
        Point current = _hero->getCurrentNode();
        float e = 90.0 / 4;
        if (angle >= -e && angle < e) {
            direction = RIGHT;
            nextNode = Point(current.x + 1, current.y);
        }
        if (angle >= e && angle < 3 * e) {
            direction = UR;
            nextNode = Point(current.x + 1, current.y - 1);
        }
        if (angle >= 3 * e && angle < 5 * e) {
            direction = UP;
            nextNode = Point(current.x, current.y - 1);
        }
        if (angle >= 5 * e && angle < 7 * e) {
            direction = UL;
            nextNode = Point(current.x - 1, current.y - 1);
        }
        if (angle >= 7 * e || angle < -7 * e) {
            direction = LEFT;
            nextNode = Point(current.x - 1, current.y);
        }
        if (angle >= -7 * e && angle < -5 * e) {
            direction = DL;
            nextNode = Point(current.x - 1, current.y + 1);
        }
        if (angle >= -5 * e && angle < -3 * e) {
            direction = DOWN;
            nextNode = Point(current.x, current.y + 1);
        }
        if (angle >= -3 * e && angle < -e) {
            direction = DR;
            nextNode = Point(current.x + 1, current.y + 1);
        }
        
        Point pixelpos = convertCoordinate2Pixel(nextNode.x, nextNode.y,
                                                 _map->getMapSize().height);
        if (canGo(pixelpos.x, pixelpos.y)) {
            _hero->setNextNode(nextNode);
            _hero->setNextPosition(pixelpos);
            _hero->setNextDirection(direction);
        }
    }
}

void GameLayer::checkGameEnded() {
    int endType = 0;
    if (_hero->isDead()) {
        
        GameSuspended = true;
        endType = 0;
    } else if (_hero->getCurrentNode() == Point(30, 1)) {
        bool saved = true;
        for (int i = 0; i < hostages.size(); i++) {
            if (hostages[i]->isSaved() == false) {
                saved = false;
            }
        }
        if (saved) {
            // CCLOG("Game ends You win!");
            GameSuspended = true;
            endType = 1;
        }
    }
    if (GameSuspended == true) {
        GameEndLayer* gendlayer = GameEndLayer::create();
        gendlayer->setGameEndLayerType(endType);
        gendlayer->setParentGameLayer(this);
        this->addChild(gendlayer, 4);
        joyStickerEnabled = false;
    }
}

void GameLayer::updateHeroHealthBar() {
    heroHealthBarTimer->setPercentage(_hero->getHealth());
}

void GameLayer::update(float dt) {
    if (GameSuspended) {
        return;
    }
    checkNewEvent();
    _hero->doAction();
    if (_hero->getCurBuff() != Buff::NONE) {
        _hero->buffCountdown();
        if (_hero->getBufftime() <= 0) {
            _hero->setCurBuff(Buff::NONE);
        }
    }
    if (_hero->getPosition() == tileCoordinate2Pixel(Point(POTION1))
        || _hero->getPosition() == tileCoordinate2Pixel(Point(POTION2))
        || _hero->getPosition() == tileCoordinate2Pixel(Point(POTION3))
        || _hero->getPosition() == tileCoordinate2Pixel(Point(POTION4))) {
        Point hpoint = _hero->getPosition();
        for (int i = 0; i < potions.size(); i++) {
            if (potions[i]->isVisible()
                && potions[i]->getPosition() == hpoint) {
                int tag = potions[i]->getTag();
                switch (tag) {
                    case TAG_HEALTH:
                        _hero->setHealth(100);
                        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(
                                                                                    EFCT_HEAL);
                        break;
                    case TAG_INVISIBLE:
                        _hero->setCurBuff(Buff::INVISIBLE);
                        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(
                                                                                    EFCT_INVISIBLE);
                        break;
                    case TAG_SPEED:
                        _hero->setCurBuff(Buff::SPEED);
                        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(
                                                                                    EFCT_SPEED);
                        break;
                    case TAG_UNBREAK:
                        _hero->setCurBuff(Buff::UNBREAK);
                        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(
                                                                                    EFCT_UNBREAK);
                        break;
                }
                potions[i]->setVisible(false);
                break;
            }
        }
        
    }
    _enemy->doAction();
    for (int i = 0; i < hostages.size(); i++) {
        hostages[i]->doAction();
    }
}

Point GameLayer::tileCoordinate(float x, float y) {
    int newx = x / _map->getTileSize().width;
    int newy = (_map->getMapSize().height * _map->getTileSize().height - y)
    / _map->getTileSize().height;
    return Point(newx, newy);
}

Point GameLayer::tileCoordinate(Point p) {
    int newx = p.x / _map->getTileSize().width;
    int newy = (_map->getMapSize().height * _map->getTileSize().height - p.y)
    / _map->getTileSize().height;
    return Point(newx, newy);
}

Point GameLayer::tileCoordinate2Pixel(Point point) {
    return Point((point.x + 0.5) * BLKWIDTH,
                 (_map->getMapSize().height - point.y - 0.5) * BLKWIDTH);
}

bool GameLayer::canGo(float x, float y) {
    bool ret = true;
    int gid = _metaLayer->getTileGIDAt(tileCoordinate(x, y));
    unordered_map<string, Value> kmap =
    _map->getPropertiesForGID(gid).asValueMap();
    if (kmap.empty()) {
        LOGE("kmap is null!!");
    } else {
        Value str = kmap.at("Collidable");
        if (str.asString().compare("true") == 0) {
            return false;
        }
    }
    
    return ret;
}

bool GameLayer::canGo(Point p) {
    bool ret = true;
    int gid = _metaLayer->getTileGIDAt(p);
    unordered_map<string, Value> kmap =
    _map->getPropertiesForGID(gid).asValueMap();
    if (kmap.empty()) {
        LOGE("kmap is null!!");
    } else {
        Value str = kmap.at("Collidable");
        if (str.asString().compare("true") == 0) {
            return false;
        }
    }
    
    return ret;
    
}

void GameLayer::onWalk(int direction) {
    
}

void GameLayer::onStop() {
    // CCLOG("GameLayer onStop");
    tempstate = 0;
}

/**
 *  Function that can check whether the State should change, depends on the Final State Machine.
 */
void GameLayer::checkNewEvent() {
    checkGameEnded();
    int dist = distance(_hero->getPosition(), _enemy->getPosition());
    vector<Point>* directPath = getStraightPath(
                                                tileCoordinate(_enemy->getPosition()),
                                                tileCoordinate(_hero->getPosition()));
    bool stateChanged = false;
    
    switch (_enemy->getState()) {
        case State::IDLE:
            // path is fixed, generated by generator
            if (directPath != NULL) { // no direct path
                if (_enemy->canAttack(_hero)) { // enter attack state
                    LOGV("checkNewEvent: IDLE -> ATTACK state");
                    stateChanged = true;
                    _enemy->setState(State::ATTACK);
                    break;
                } else if (_enemy->canSee(_hero)) { // enter alert state
                    LOGV("checkNewEvent: IDLE -> ALERT state");
                    stateChanged = true;
                    _enemy->setState(State::ALERT);
                    break;
                }
            }
            break;
        case State::ALERT:
            // path is dynamic, straight line
            if (directPath == NULL || !_enemy->canSee(_hero)) { // no direct path or cannot see
                LOGV("checkNewEvent: ALERT -> LOST state");
                stateChanged = true;
                _enemy->setState(State::LOST);
            } else if (_enemy->canAttack(_hero)) { // enter attack state
                LOGV("checkNewEvent: ALERT -> ATTACK state");
                stateChanged = true;
                _enemy->setState(State::ATTACK);
            } else { // maintain current state and recalculate the path.
                recalculatePath(directPath);
            }
            break;
        case State::ATTACK:
            // path is dynamic, straight line
            if (directPath == NULL || !_enemy->canSee(_hero)) { // no direct path or cannot see
                LOGV("checkNewEvent: ATTACK -> LOST state");
                stateChanged = true;
                _enemy->setState(State::LOST);
            } else if (!_enemy->canAttack(_hero)) { // can see but cannot attack, enter alert state
                LOGV("checkNewEvent: ATTACK -> ALERT state");
                stateChanged = true;
                _enemy->setState(State::ALERT);
            } else { // maintain current state and recalculate the path.
                recalculatePath(directPath);
            }
            break;
        case State::LOST:
            // path is fixed, straight line
            if (directPath != NULL) { // have direct path
                if (_enemy->canAttack(_hero)) {
                    LOGV("checkNewEvent: LOST -> ATTACK state");
                    stateChanged = true;
                    _enemy->setState(State::ATTACK);
                    break;
                } else if (_enemy->canSee(_hero)) { // enter alert state
                    LOGV("checkNewEvent: LOST -> ALERT state");
                    stateChanged = true;
                    _enemy->setState(State::ALERT);
                    break;
                }
            }
            if (_enemy->ifStoped()) {
                stateChanged = true;
                _enemy->setState(State::INSPECT);
            }
            break;
        case State::LOOKAROUND:
            // path is fixed, generated by generator
            //TODO: search the hero for a while, if no new events happen in timeout, go into INSPECT
            break;
        case State::INSPECT:
            if (directPath != NULL) { // have direct path
                if (_enemy->canAttack(_hero)) {
                    LOGV("checkNewEvent: INSPECT -> ATTACK state");
                    stateChanged = true;
                    _enemy->setState(State::ATTACK);
                    break;
                } else if (_enemy->canSee(_hero)) { // enter alert state
                    LOGV("checkNewEvent: INSPECT -> ALERT state");
                    stateChanged = true;
                    _enemy->setState(State::ALERT);
                    break;
                }
            }
            if (tileCoordinate(_enemy->getInspectTarget())
                == tileCoordinate(_enemy->getPosition())) { // already return to hostage stop, begin IDLE state
                LOGV("checkNewEvent: INSPECT -> IDLE state");
                stateChanged = true;
                int i;
                for (i = 0; i < hostagesWatch.size(); i++) {
                    if (hostagesWatch[i]
                        == tileCoordinate(_enemy->getInspectTarget())) {
                        break;
                    }
                }
                LOGV("debug i:%d", i);
                _enemy->idleMoveFrom(i);
                _enemy->setState(State::IDLE);
            }
            break;
    }
    
    if (stateChanged) {
        recalculatePath(directPath);
        changeSpeed();
        changeSign();
    }
    
    checkSaveButton();
    checkJoysticker();
    updateHeroHealthBar();
}

int GameLayer::distance(Point a, Point b) {
    int x = (int) (a.x - b.x);
    int y = (int) (a.y - b.y);
    
    return (int) sqrt(x * x + y * y);
}

// get the path from A to B if there is no block between them,
// return NULL if there is block, if path has 0 size, it is too close.
vector<Point>* GameLayer::getStraightPath(Point from, Point to) {
    vector<Point>* path = new vector<Point>();
    if (from == to) {
        return path;
    }
    
    int step = 0;
    float x = 0.0, y = 0.0;
    if (from.x != to.x && from.y != to.y) {
        float k = (from.y - to.y) / (from.x - to.x);
        float b = from.y - k * from.x;
        // count on the longer edge
        if (abs(from.x - to.x) < abs(from.y - to.y)) {
            from.y > to.y ? step = -1 : step = 1;
            for (int i = from.y + step; i != to.y; i += step) {
                x = (i - b) / k;
                if (x - (int) x <= 0.5) {
                    // (int(x),i) and (int(x)-1,i) will be check
                    if (!canGo(Point(int(x), i))) {
                        return NULL;
                    }
                    path->push_back(tileCoordinate2Pixel(Point(int(x), i)));
                } else {
                    if (!canGo(Point(int(x) + 1, i))) {
                        return NULL;
                    }
                    path->push_back(tileCoordinate2Pixel(Point(int(x) + 1, i)));
                }
            }
        } else {
            from.x > to.x ? step = -1 : step = 1;
            for (int i = from.x + step; i != to.x; i += step) {
                y = k * i + b;
                if (y - int(y) <= 0.5) {
                    // (i,int(y)) and (i,int(y)-1) will be check
                    if (!canGo(Point(i, int(y)))) {
                        return NULL;
                    }
                    path->push_back(tileCoordinate2Pixel(Point(i, int(y))));
                } else {
                    // (x,y) and (x,int(y)+1) will be check
                    if (!canGo(Point(i, int(y) + 1))) {
                        return NULL;
                    }
                    path->push_back(tileCoordinate2Pixel(Point(i, int(y) + 1)));
                }
            }
            
        }
    } else if (from.x == to.x) {
        from.y <= to.y ? step = 1 : step = -1;
        for (int i = from.y + step; i != to.y; i += step) {
            if (!canGo(Point(from.x, i)))
                return NULL;
            path->push_back(tileCoordinate2Pixel(Point(from.x, i)));
        }
    } else { // from.y == to.y
        from.x <= to.x ? step = 1 : step = -1;
        for (int i = from.x + step; i != to.x; i += step) {
            if (!canGo(Point(i, from.y)))
                return NULL;
            path->push_back(tileCoordinate2Pixel(Point(i, from.y)));
        }
    }
    return path;
}

void GameLayer::printPath(vector<Point>* path) {
    for (int i = 0; i < path->size(); i++) {
        LOGV("element %d:(%f, %f)", i, (*path)[i].x, (*path)[i].y);
    }
}

void GameLayer::recalculatePath(vector<Point>* directPath) {
    switch (_enemy->getState()) {
        case State::IDLE:
            // path is fixed, generated by generator
            
            break;
        case State::ALERT:
        case State::ATTACK:
            // path is dynamic, straight line
            _enemy->setPath(*directPath);
            _enemy->takeAction();
            break;
        case State::LOST:
            // path is fixed, straight line
            break;
        case State::LOOKAROUND:
            //TODO: search the hero for a while, if no new events happen in timeout, go into INSPECT
            break;
        case State::INSPECT:
            // go to the nearest hostage
            int min = 100000;
            vector<Point>* tmppath;
            vector<Point>* path;
            for (int i = 0; i < hostagesWatch.size(); i++) {
                tmppath = PathGenerator::sharePathGenerator(_map)->generatePath(
                                                                                tileCoordinate(_enemy->getPosition()), hostagesWatch[i]);
                if (tmppath->size() < min) {
                    min = tmppath->size();
                    path = tmppath;
                }
            }
            
            _enemy->setInspectTarget((*path)[path->size() - 1]);
            LOGV(
                 "%f %f", _enemy->getInspectTarget().x, _enemy->getInspectTarget().y);
            _enemy->setPath(*path);
            _enemy->takeAction();
            break;
    }
}

void GameLayer::changeSpeed() {
    switch (_enemy->getState()) {
        case State::IDLE:
        case State::ATTACK:
        case State::LOST:
        case State::LOOKAROUND:
            _enemy->useNormalSpeed();
            break;
        case State::ALERT:
        case State::INSPECT:
            _enemy->useHighSpeed();
            break;
        default:
            _enemy->useNormalSpeed();
            break;
            
    }
}

void GameLayer::changeSign() {
    switch (_enemy->getState()) {
        case State::IDLE:
            _enemysign = Sprite::create(PIC_ENEMY_IDLE);
            break;
        case State::ALERT:
            _enemysign = Sprite::create("state_alert.png");
            break;
        case State::ATTACK:
            _enemysign = Sprite::create("state_attack.png");
            break;
        case State::LOST:
            _enemysign = Sprite::create("state_lost.png");
            break;
        case State::LOOKAROUND:
            //TODO: search the hero for a while, if no new events happen in timeout, go into INSPECT
            _enemysign = Sprite::create("state_lookaround.png");
            break;
        case State::INSPECT:
            _enemysign = Sprite::create("state_inspect.png");
            break;
        default:
            _enemysign = Sprite::create("CloseNormal.png");
            break;
    }
    _enemy->setSign(_enemysign);
}

vector<vector<Point>> GameLayer::generateLoop() {
    vector < vector < Point >> loopRoute;
    vector<Point>* path0 =
    PathGenerator::sharePathGenerator(_map)->generatePath(
                                                          Point(WATCHHOSTAGE0), Point(WATCHHOSTAGE1));
    loopRoute.push_back(*path0);
    path0 = PathGenerator::sharePathGenerator(_map)->generatePath(
                                                                  Point(WATCHHOSTAGE1), Point(WATCHHOSTAGE2));
    loopRoute.push_back(*path0);
    path0 = PathGenerator::sharePathGenerator(_map)->generatePath(
                                                                  Point(WATCHHOSTAGE2), Point(WATCHHOSTAGE3));
    loopRoute.push_back(*path0);
    path0 = PathGenerator::sharePathGenerator(_map)->generatePath(
                                                                  Point(WATCHHOSTAGE3), Point(WATCHHOSTAGE4));
    loopRoute.push_back(*path0);
    path0 = PathGenerator::sharePathGenerator(_map)->generatePath(
                                                                  Point(WATCHHOSTAGE4), Point(WATCHHOSTAGE0));
    loopRoute.push_back(*path0);
    return loopRoute;
}

void GameLayer::pausedGame(Object* pSender) {
    LOGV("GameLayer::pausedGame");
    Director::getInstance()->pause();
    Size sz = Director::getInstance()->getWinSize();
    
    RenderTexture* rendertexture =  RenderTexture::create(sz.width, sz.height);
    
    //    // An object that has not been addChild needs to be retain, otherwise it will be auto released.
    rendertexture->retain();
    Scene* sene = Director::getInstance()->getRunningScene();
    rendertexture->begin();
    sene->visit();
    rendertexture->end();
    GameEndLayer* geLayer = GameEndLayer::getLayerWithTexture(rendertexture);
    geLayer->setParentGameLayer(this);
    addChild(geLayer,9999);
}

void GameLayer::soundSwitch(Object* obj) {
    LOGV("soundSwitch");
    if(CocosDenshion::SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying()) {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
    } else {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
    }
}
