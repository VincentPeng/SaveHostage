#ifndef PkGc_cocos2d_saveHostage_GAMELAYER_H_
#define PkGc_cocos2d_saveHostage_GAMELAYER_H_

#include "cocos2d.h"
#include "Hero.h"
#include "Enemy.h"
#include "Hostage.h"
#include "JoyStick.h"
#include "EnumUtil.h"

USING_NS_CC;

class GameLayer: public cocos2d::Layer, public JoyStickDelegate //public OptionDelegate
{
public:
    GameLayer();
    ~GameLayer();
    virtual bool init();
    void loadCharactorAndScene();
    void initGameControls();
    CREATE_FUNC(GameLayer);
    void update(float dt);
    bool canGo(float x, float y);
    bool canGo(Point p);
    Point tileCoordinate(float x, float y);
    Point tileCoordinate(Point p);
    Point tileCoordinate2Pixel(Point point);
    Point convertCoordinate2Pixel (int x, int y, int mapHeight);
    void saveBtnPressed(CCObject* pSender);
	  void toggleBtnPressed(Object* pSender);
    virtual void onJoyStickUpdate(Node*sender, float angle, Point direction,
            float power);

    void onWalk(int direction);
    void onStop();

    void checkNewEvent();
    void checkJoysticker();
    void checkSaveButton();
    void updateHeroHealthBar();
    void recalculatePath(vector<Point>* directPath);
    void changeSpeed();
    void changeSign();
    int distance(Point, Point);

    vector<Point>* getStraightPath(Point from, Point to);
    void printPath(vector<Point>* path);

    vector<vector<Point>> generateLoop();
    void checkGameEnded();
    static GameLevel game_level;
    
    void resetGameLayer();
    void positionHero();
    void positionHostages();
    void positionEnemies();
    void positionAllRoles();
    
    void resumeGmame();
    void restartGame();
    void pauseGame();

    void pausedGame(Object* pSender);
    void soundSwitch(Object* pSender);

private:
    Hero* _hero;
    Enemy* _enemy;
    Sprite* _enemysign;
    Hostage* _hostage0;
    Hostage* _hostage1;
    Hostage* _hostage2;
    Hostage* _hostage3;
    Hostage* _hostage4;
    vector<Sprite*> potions;

    vector<Hostage*> hostages;
    vector<Point> hostagesWatch;
    int tempstate = 0;
    int tempdirect = 0;
    TMXTiledMap* _map;
    TMXLayer* _bgLayer;
    TMXLayer* _metaLayer;

    ProgressTimer* heroHealthBarTimer;
    JoyStick* gameSticker;
    MenuItemImage* saveBtn;
    bool joyStickerEnabled;
    bool GameSuspended;

    MenuItemImage* pauseBtn;
};

#endif // end of PkGc_cocos2d_saveHostage_GAMELAYER_H_
