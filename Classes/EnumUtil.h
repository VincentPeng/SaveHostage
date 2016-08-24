#ifndef PkGc_cocos2d_saveHostage_ENUMUTIL_H_
#define PkGc_cocos2d_saveHostage_ENUMUTIL_H_

#define FPS                 60
#define ENEMYSPEED          20      //how many steps to cover a block disance
#define HOSTAGESPEED        20
#define SAVINGCLOCKSNEEDED  100
#define TILESIZE            64
#define WIDTH_CENTER            240
#define HEIGHT_CENTER            160

#define ENEMYSPEED_H 20
#define ENEMYSPEED_M 25
#define ENEMYSPEED_L 40

#define DAMAGE_H 20
#define DAMAGE_M 10
#define DAMAGE_L 5

#define ATKRANGE_H 120
#define ATKRANGE_M 90
#define ATKRANGE_L 60

#define HEROSPEED_H 10
#define HEROSPEED_M 20

#define VISIONRANGE 270

#define MUSIC_BACKGROUND "music_background.mp3"

#define MUSIC_GAMEOVER "efct_gameover.mp3"
#define MUSIC_VICTORY "efct_victory.mp3"
#define EFCT_UNLOCK1 "efct_beginunlock.mp3"
#define EFCT_UNLOCK2 "efct_unlock.mp3"
#define EFCT_BTPRESS1 "efct_buttonpressed.mp3"
#define EFCT_SHOOT "efct_shoot.mp3"
#define EFCT_SPEED "efct_speed.mp3"
#define EFCT_UNBREAK "efct_unbreak.mp3"
#define EFCT_HEAL "efct_heal.mp3"
#define EFCT_INVISIBLE "efct_invisible.mp3"

#define PIC_GAMEOVER "gameover.png"
#define PIC_GAMEWIN "gamev.png"
#define PIC_RESUME "buttonResume.png"
#define PIC_RESUME_PRESSED "buttonResume_pressed.png"
#define PIC_RESTART "buttonRestart.png"
#define PIC_SETTINGS "buttonSetting.png"
#define PIC_PAUSE "buttonPause.png"
#define PIC_PAUSE_PRESSED "buttonPause_pressed.png"
#define PIC_SOUND_ON "buttonSound.png"
#define PIC_SOUND_OFF "buttonSoundOff.png"

#define BUFFTIME 800    // 60 -> 1s
enum State {
    IDLE, ALERT, ATTACK, LOST, LOOKAROUND, INSPECT
};
enum Event {
    FOUND_TARGET, LOST_TARGET, REACH_MISSPOINT, HOSTAGE_SECURE
};

enum Direction {
    STOP, UP, DOWN, LEFT, RIGHT, UL, UR, DL, DR
};

enum GameLevel {
    HEAVEN, MORTAL, HELL
};

enum Buff {
    SPEED, UNBREAK, INVISIBLE, NONE
};

#endif // end of PkGc_cocos2d_saveHostage_ENUMUTIL_H_
