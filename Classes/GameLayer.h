//
//  GameLayer.h
//  SaveHostage
//
//  Created by Ke Peng on 4/9/14.
//
//

#ifndef PkGc_cocos2d_saveHostage_GAMELAYER_H_
#define PkGc_cocos2d_saveHostage_GAMELAYER_H_

#include "cocos2d.h"
#include "Hero.h"
#include "Enemy.h"
#include "Hostage.h"
#include "JoyStick.h"
#include "EnumUtil.h"
#include <math.h>
#include <PathGenerator.h>
#include "GameEndLayer.h"
#include "ImageHelper.h"
#include <cmath>
#include "TileNode.h"
#include "AppDef.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

/**
 *
 * GameLayer inherits from JoyStickDelegate in order to support touch control over stick pad.
 *
 */
class GameLayer : public cocos2d::Layer, public JoyStickDelegate {
public:
    GameLayer();
    ~GameLayer();
    virtual bool init();
    CREATE_FUNC(GameLayer);
    
    /** Load Hero, Hostage and Eneny and set to corresponding position
     */
    void loadCharactorAndScene();
    
    /** Generate UI, joy stick
     */
    void initGameControls();
    
    /** Routine function called per frame, check enemy state change, hero movement, etc
     */
    void update(float dt);
    
    /** For collision detection purpose, check the destination can be walked on or not
     */
    bool canGo(float x, float y);
    bool canGo(Point p);
    
    /** Cocos2d-x coordinate system is different from Tiled Map's, covert between both
     */
    Point tileCoordinate(float x, float y);
    Point tileCoordinate(Point p);
    Point tileCoordinate2Pixel(Point point);
    Point convertCoordinate2Pixel(int x, int y, int mapHeight);
    
    /** Button callback function
     */
    void rescueBtnPressed(CCObject* pSender);
    void toggleBtnPressed(Object* pSender);
    
    /** callback function of JoyStick
     */
    virtual void onJoyStickUpdate(Node* sender, float angle, Point direction,
                                  float power);
    
    /**
     * Function that can check whether the State should change, depends on the
     * Final State Machine.
     */
    void checkNewEvent();
    
    /** Routine function check the state of joystick to move the Hero
     */
    void checkJoysticker();
    
    /** Check the environment when Rescue button has been pressed
     */
    void checkRescueButton();
    
    void updateHeroHealthBar();
    
    /** Re-calculate the path which Enemy will follow
     */
    void recalculatePath(vector<Point>* directPath);
    
    /** Adjust Enemy's speed to high when find Hero 
     */
    void changeSpeed();
    
    /** Change the state symbol of Enemy
     */
    void changeSign();
    
    /** Utility function to retrieve the distance between two points
     */
    int distance(Point, Point);
    
    /** get the path from A to B if there is no block between them,
     *  return NULL if there is block, if path has 0 size, it is too close
     */
    vector<Point>* getStraightPath(Point from, Point to);
    
    void printPath(vector<Point>* path);
    
    /** Generate the path when Enemy is edle, it will loop among each hostage
     */
    vector<vector<Point>> generateLoop();
    
    /** Check if the game has come to an end
     */
    void checkGameEnded();
    
    
    
    
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
    
    static GameLevel game_level;
    
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

#endif  // end of PkGc_cocos2d_saveHostage_GAMELAYER_H_
