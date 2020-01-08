//
//  Timer.h
//  myDeepSketch
//
//  Created by 外谷弘樹 on 2019/07/03.
//

#pragma once

#include "ofMain.h"

class Timer {
public:
    
    Timer();
    void set(int t);
    void start();
    void stop();
    void reset();
    void update();
    bool isEnd();
    
    int getTime();
    void drawTime();
    
    string strYear();
    string strMonth();
    string strDay();
    string strTime();
    
private:
    bool isStarted;
    int time; // カウント
    int timer; // 制限時間設定
    int settedTimer; // はじめに設定された時間を保存しておく
    ofTrueTypeFont timerFont;
    
};
