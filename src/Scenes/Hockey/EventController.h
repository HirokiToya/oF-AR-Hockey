//
//  hockey.h
//  myDeepSketch
//
//  Created by 外谷弘樹 on 2019/06/27.
//
#pragma once

#include <string>
#include "ofMain.h"
#include "baseScene.h"
#include "Timer.h"
#include "Score.h"
#include "Sound.h"
#include "Field.h"
#include "PlayerInterface.h"

#define LIMIT_TIME 60
#define PUCK_SPEED 20

class EventController : public baseScene {
    
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    enum NEXT_RELEASE_DIRECTION {RIGHT, LEFT, VARIOUS};
    bool isGameStarted;
    bool isTimeOver;
    
private:
    
    NEXT_RELEASE_DIRECTION releaseDirection;
    void initializeGameFlag();
    void drawNextBallDirection();
    bool isdrawNextBallDirection;
    void endSoundCallback();
    void startSetSoundCallback();
    void startCountDownSoundCallback();
    void goalSoundCallback();
    void endCountDownSoundCallback();
    void sendOffSoundCallBack();
    void gameStart();
    bool isSinglePlay;
    void gameEnd();
    bool isDrawFieldMessage;
    
    // timer
    Timer timer;
    
    // score
    Score score;
    
    // sound
    Sound waitingSound;
    Sound setUpSound;
    Sound startSetSound;
    Sound goalSound;
    Sound startSound;
    Sound playingSound;
    Sound finishSound;
    Sound sendOffSound;
    Sound endSound;
    
    ofImage myImage;
    
    // fieldView
    Field field;
    PlayerInterface player;
    
    // player
    int rightStandingTime;
    int leftStandingTime;
    
    bool isRightPlayerSetting;
    bool isLeftPlayerSetting;
    
    bool isRightPlayerSetted;
    bool isLeftPlayerSetted;
    
    int remainingBallCount;
    
    bool isAppearMyImage;
    
};

