//
//  TImer.cpp
//  myDeepSketch
//
//  Created by 外谷弘樹 on 2019/07/03.
//

#include <stdio.h>
#include "Timer.h"

Timer::Timer() {
    timerFont.load("font.ttf", 100);
    time = 0;
    timer = 0;
}

void Timer::set(int t) {
    timer = t;
    settedTimer = t;
}

void Timer::reset() {
    timer = settedTimer;
    time = 0;
    isStarted = false;
}

void Timer::stop() {
    isStarted = false;
}

void Timer::start() {
    isStarted = true;
}

void Timer::update() {
    if (isStarted) {
        time ++;
    }
}

int Timer::getTime() {
    return time;
}

bool Timer::isEnd() {
    if (timer - time / 60 <= 0) {
        return true;
    } else {
        return false;
    }
}

void Timer::drawTime() {
    ofSetColor(255, 255, 10);
    if(timer - time / 60 >= 0) {
        string t = to_string(timer - time / 60);
        float timerFontWidth = timerFont.stringWidth(t + "秒");
        timerFont.drawString(t + "秒", ofGetWidth() / 2 - timerFontWidth / 2, 200);
    } else {
        float timerFontWidth = timerFont.stringWidth("0秒");
        timerFont.drawString("0秒", ofGetWidth() / 2 - timerFontWidth / 2, 200);
    }
}

string Timer::strYear(){
    
    return ofToString(ofGetYear());
}

string Timer::strMonth(){
    
    return ofToString(ofGetMonth());
}

string Timer::strDay(){
    
    return ofToString(ofGetDay());
}

string Timer::strTime(){
    
    return ofToString(ofGetHours()) + "_" + ofToString(ofGetMinutes()) + "_" + ofToString(ofGetSeconds());
}
