#ifndef PkGc_cocos2d_saveHostage_ENUMUTIL_H_
#define PkGc_cocos2d_saveHostage_ENUMUTIL_H_

enum State {
    IDLE, ALERT, LOST, LOOKAROUND, INSPECT
};
enum Event {
    FOUND_TARGET, LOST_TARGET, REACH_MISSPOINT, HOSTAGE_SECURE
};

enum Direction {
    UP,DOWN,LEFT,RIGHT,STOP
};

#endif // end of PkGc_cocos2d_saveHostage_ENUMUTIL_H_
