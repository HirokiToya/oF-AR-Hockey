//
//  hockey.cpp
//  myDeepSketch
//
//  Created by 外谷弘樹 on 2019/06/27.
//

#include <stdio.h>
#include "EventController.h"

void EventController::setup(){
    
    ofSetFrameRate(60);
    ofToggleFullscreen();
    
    player.setup();
    field.setup();
    
    // game control value
    initializeGameFlag();
    
    // fonts
    ofTrueTypeFont::setGlobalDpi(72);
    
    // timer
    timer.set(LIMIT_TIME);
    
    // sound
    endSound.load("mySound.mp3");
    waitingSound.load("waiting.mp3");
    setUpSound.load("setUp.mp3");
    startSetSound.load("startSet.mp3");
    startSound.load("startCountDown.mp3");
    playingSound.load("fightingSound.mp3");
    goalSound.load("billiard-pocket.mp3");
    finishSound.load("finishSound.mp3");
    sendOffSound.load("sendOffSoundShort.mp3");
    
    // img
    myImage.load("credit.jpg");
    
    ofAddListener(endSound.endEvent, this, &EventController::endSoundCallback);
    ofAddListener(startSetSound.endEvent, this, &EventController::startSetSoundCallback);
    ofAddListener(startSound.endEvent, this, &EventController::startCountDownSoundCallback);
    ofAddListener(goalSound.endEvent, this, &EventController::goalSoundCallback);
    ofAddListener(finishSound.endEvent, this, &EventController::endCountDownSoundCallback);
    ofAddListener(sendOffSound.endEvent, this, &EventController::sendOffSoundCallBack);
}

void EventController::update(){
    
    player.update();
    field.update();
    timer.update();
    endSound.update();
    startSetSound.update();
    startSound.update();
    goalSound.update();
    finishSound.update();
    sendOffSound.update();
    
    if(isGameStarted) {
        waitingSound.stop();
        // playerの位置を更新
        if(player.isFrameNew()) {
            field.rightMallet.setPosition(player.mirrorRightPosition.x - 150, player.mirrorRightPosition.y + 20);
            field.leftMallet.setPosition(player.mirrorLeftPosition.x + 60, player.mirrorLeftPosition.y);
        }
        
        // 座標のログ
        for(int i = 0; i < field.circles.size(); i++){
            ofLog(OF_LOG_NOTICE, "mr_x:%d, mr_y:%d, ml_x:%d, ml_y:%d, bx:%.f, by:%.f",
                  field.rightMallet.getPosition().x,
                  field.rightMallet.getPosition().y,
                  field.leftMallet.getPosition().x,
                  field.leftMallet.getPosition().y,
                  field.circles[0].get()->getPosition().x,
                  field.circles[0].get()->getPosition().y);}
        
        // ボールのゴール判定。→ インスタンス削除、効果音再生
        for(int i = 0; i < field.circles.size(); i++){
            if (field.circles[i].get()->getPosition().x > ofGetWidth()){
                score.leftPlayerPoint();
                field.circles.erase(field.circles.begin() + i);
                if(releaseDirection != VARIOUS) releaseDirection = RIGHT;
                if(isTimeOver) remainingBallCount --;
                goalSound.play();
            } else if(field.circles[i].get()->getPosition().x < 0) {
                score.rightPlayerPoint();
                field.circles.erase(field.circles.begin() + i);
                if(releaseDirection != VARIOUS) releaseDirection = LEFT;
                if(isTimeOver) remainingBallCount --;
                goalSound.play();
            }
        }
        
        if (timer.isEnd() && !isTimeOver) {
            timer.stop();
            if(!finishSound.isPlaying() && !startSound.isPlaying()){
                finishSound.play();
                isTimeOver = true;
                remainingBallCount = 0;
                
                for(int i = 0; i < field.circles.size(); i++){
                    remainingBallCount ++;
                }
            }
        }
        
        if(isTimeOver && remainingBallCount == 0) {
            gameEnd();
        }
        
    } else {
        if(!waitingSound.isPlaying()){
            ofLog(OF_LOG_NOTICE, timer.strTime() + "：待機中");
            waitingSound.play();
        }
            
        if(player.rightPosition.x < ofGetWidth() &&
           player.rightPosition.x > (ofGetWidth() - 300) &&
           player.rightPosition.y > (ofGetHeight()/2 - 300) &&
           player.rightPosition.y < (ofGetHeight()/2 + 300)) {
            rightStandingTime ++;
            isRightPlayerSetting = true;
            if (rightStandingTime / 60 > 5) {
                if(!isRightPlayerSetted) setUpSound.play();
                isRightPlayerSetting = false;
                isRightPlayerSetted = true;
                
                gameStart();
//                if (isLeftPlayerSetted) {
//                    isGameStarted = true;
//                    isSinglePlay = false;
//                    gameStart();
//                } else {
//                    if (rightStandingTime / 60 > 15) {
//                        isGameStarted = true;
//                        isSinglePlay = true;
//                        gameStart();
//                    }
//                }
            }
        } else {
            if(rightStandingTime > 0) {
                rightStandingTime --;
            }
        }
        
        if(player.leftPosition.x > 0 &&
           player.leftPosition.x < 300 &&
           player.leftPosition.y > (ofGetHeight()/2 - 300) &&
           player.leftPosition.y < (ofGetHeight()/2 + 300)) {
            leftStandingTime ++;
            isLeftPlayerSetting = true;
            if (leftStandingTime / 60 > 5) {
                if(!isLeftPlayerSetted) setUpSound.play();
                isLeftPlayerSetting = false;
                isLeftPlayerSetted = true;
                
                gameStart();
                
//                if (isRightPlayerSetted) {
//                    isGameStarted = true;
//                    isSinglePlay = false;
//                    gameStart();
//                } else {
//                    if (leftStandingTime / 60 > 15) {
//                        isGameStarted = true;
//                        isSinglePlay = true;
//                        gameStart();
//                    }
//                }
            }
        } else {
            if(leftStandingTime > 0) {
                leftStandingTime --;
            }
        }
    }
}

void EventController::draw(){
    
    player.draw();
    field.drawStaticLines();
    drawNextBallDirection();
    score.draw();
    timer.drawTime();
//    field.draw(isSinglePlay);
    bool isSingle = player.isLeftPlayerExist && player.isRightPlayerExist;
    field.draw(!isSingle);
    
    if(isLeftPlayerSetting) {
        field.drawLeftPlayerSetting();
    }
    
    if(isRightPlayerSetting) {
        field.drawRightPlayerSetting();
    }
    
    if(isRightPlayerSetted) {
        field.drawRightPlayerSetted();
    }
    
    if(isLeftPlayerSetted) {
        field.drawLeftPlayerSetted();
    }
    
    if(isDrawFieldMessage) {
        field.drawMessage("次のお友達と交代してね。");
    }
    
    if(isAppearMyImage) {
        ofSetColor(255, 255, 255);
        myImage.draw(0, 0);
    }
}

void EventController::initializeGameFlag() {
    
    string logPath = "log/" + timer.strYear() + "/" + timer.strMonth() + "/" + timer.strDay() + "/" + "log.txt";
    
    ofLogToFile(logPath, true);
    
    releaseDirection = RIGHT;
    isdrawNextBallDirection = false;
    isGameStarted = false;
    isTimeOver = false;
    remainingBallCount = 0;
    isSinglePlay = false;
    isRightPlayerSetting = false;
    isLeftPlayerSetting = false;
    isRightPlayerSetted = false;
    isLeftPlayerSetted = false;
    rightStandingTime = 0;
    leftStandingTime = 0;
    isDrawFieldMessage = false;
//    isAppearMyImage = false;
    
    timer.reset();
    score.reset();
}

void EventController::gameStart() {
    
    string logPath = "log/" + timer.strYear() + "/" + timer.strMonth() + "/" + timer.strDay() + "/" + timer.strTime() + ".txt";
    
    ofLogToFile(logPath, true);
    
    ofLog(OF_LOG_NOTICE, timer.strTime() + "：ゲーム開始");
    
    isGameStarted = true;
    
    if(isSinglePlay) {
        ofLog(OF_LOG_NOTICE, "ゲーム人数：1人");
    } else {
        ofLog(OF_LOG_NOTICE, "ゲーム人数：2人");
    }
    
    player.saveImage();
    startSetSound.play();
    
}

void EventController::keyPressed(int key){
    
}

void EventController::mouseDragged(int x, int y, int button){
    player.mouseDragged(x, y, button);
}

void EventController::mousePressed(int x, int y, int button){
    player.mousePressed(x, y, button);
}

void EventController::mouseReleased(int x, int y, int button){
    player.mouseReleased(x, y, button);
}

void EventController::drawNextBallDirection() {
    
    switch (releaseDirection) {
        case RIGHT:
            if(isdrawNextBallDirection) field.drawRightDirection(5, 30);
            break;
            
        case LEFT:
            if(isdrawNextBallDirection) field.drawLeftDirection(5, 30);
            break;
            
        case VARIOUS:
            // あらゆる方向に矢印を表示する
            break;
    }
}

void EventController::gameEnd() {
    
    isDrawFieldMessage = true;
    isRightPlayerSetted = false;
    isLeftPlayerSetted = false;
    playingSound.stop();
    
    if(!sendOffSound.isPlaying()){
        player.saveImage();
        sendOffSound.play();
    }
}

void EventController::startSetSoundCallback() {
    
    if(!isTimeOver && isGameStarted){
        playingSound.play();
        startSound.play();
    }
    
    isdrawNextBallDirection = true;
}

void EventController::startCountDownSoundCallback(){
    
    timer.start();
    isdrawNextBallDirection = false;
    
    if (!timer.isEnd()){
        switch (releaseDirection) {
            case RIGHT:
                field.makeBall(ofPoint(PUCK_SPEED, 0), 1);
                break;
                
            case LEFT:
                field.makeBall(ofPoint(-PUCK_SPEED, 0), 1);
                break;
                
            case VARIOUS:
                for(int i =0; i < 10; i++){
                    field.makeBall(ofPoint(ofRandom(-PUCK_SPEED, PUCK_SPEED), ofRandom(-PUCK_SPEED, PUCK_SPEED)), 1);
                }
                break;
        }
    }
}

void EventController::goalSoundCallback() {
    
    if (!isTimeOver && isGameStarted){
        startSound.play();
        isdrawNextBallDirection = true;
    }
}

void EventController::endCountDownSoundCallback(){
    
}

void EventController::sendOffSoundCallBack() {
    
    ofLog(OF_LOG_NOTICE, "得点結果：右 %d点, 左 %d点", score.getRightPoint(), score.getLeftPoint());
    ofLog(OF_LOG_NOTICE, timer.strTime() + "：ゲーム終了");
    
    isAppearMyImage = true;
    initializeGameFlag();
    field.rightMallet.setPosition(ofGetWidth() / 2 + 80, ofGetHeight() / 2);
    field.leftMallet.setPosition(ofGetWidth() / 2 - 80, ofGetHeight() / 2);
    
    endSound.play();
}

void EventController::endSoundCallback(){
    isAppearMyImage = false;
}

