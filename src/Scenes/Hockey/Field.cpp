//
//  Field.cpp
//  myDeepSketch
//
//  Created by 外谷弘樹 on 2019/07/10.
//

#include <stdio.h>
#include "Field.h"

void Field::setup() {
    
    ofTrueTypeFontSettings settings("arial.ttf", 64);
    settings.addRanges(ofAlphabet::Latin);
    settings.addRanges(ofAlphabet::Japanese);
    message.load(settings);
    
    ofSetLineWidth(5.0);
    
    world2d.init();
    world2d.setFPS(60.0);
    world2d.registerGrabbing();
    world2d.setGravity(0.0, 0.0);
    world2d.getWorld()->SetContactListener(&contacts);
    
    rightMallet.setup(world2d.getWorld(), ofGetWidth() / 2 + 80, ofGetHeight() / 2, MALLET_RADIUS);
    leftMallet.setup(world2d.getWorld(), ofGetWidth() / 2 - 80, ofGetHeight() / 2, MALLET_RADIUS);
    
    wallUp.setup(world2d.getWorld(), 0, 0, ofGetWidth() * 2, 20);
    wallU_L.setup(world2d.getWorld(), 0, 0, 20, ofGetHeight() / 3);
    wallU_R.setup(world2d.getWorld(), ofGetWidth(), 0, 20, ofGetHeight() / 3);
    wallDown.setup(world2d.getWorld(), 0, ofGetHeight(), ofGetWidth() * 2, 20);
    wallD_L.setup(world2d.getWorld(), 0, ofGetHeight(), 20, ofGetHeight() / 3);
    wallD_R.setup(world2d.getWorld(), ofGetWidth(), ofGetHeight(), 20, ofGetHeight() / 3);
}

void Field::update() {
    world2d.update();
}

void Field::draw(bool isSinglePlay) {
    ofSetColor(0, 255, 0);
    wallUp.draw();
    wallU_L.draw();
    wallU_R.draw();
    wallDown.draw();
    wallD_L.draw();
    wallD_R.draw();
    
    if(isSinglePlay) {
        ofSetColor(255, 0, 0);
        rightMallet.draw();
        leftMallet.draw();
    } else {
        ofSetColor(255, 0, 0);
        rightMallet.draw();
        
        ofSetColor(0, 0, 255);
        leftMallet.draw();
    }
    
    ofSetColor(255, 255, 255);
    for(int i = 0; i < circles.size(); i++){
        circles[i].get()->draw();
    }
}

void Field::makeBall(ofVec2f frc, float scale){
    ofPtr<ofxBox2dCircle> circle = ofPtr<ofxBox2dCircle>(new ofxBox2dCircle);
    circle.get()-> setPhysics(0.01, 1.0, 0.0);
    circle.get()-> setup(world2d.getWorld(), ofGetWidth() / 2, ofGetHeight() / 2, 20);
    circle.get()-> addForce(frc, scale);
    circles.push_back(circle);
}

void Field::drawStaticLines(){
    ofSetColor(192, 192, 192);
    // 中央ラインの描画
    ofDrawLine(ofGetWidth() / 2, 0, ofGetWidth() / 2, ofGetHeight());
    ofNoFill();
    ofSetCircleResolution(128);
    // 真ん中の円の描画
    ofDrawCircle(ofGetWidth()/2, ofGetHeight()/2, 300);
    // 左右の半円の描画（実際は円）
    ofDrawCircle(0, ofGetHeight()/2, 300);
    ofDrawCircle(ofGetWidth(), ofGetHeight()/2, 300);
    ofFill();
}

void Field::drawRightPlayerSetting(){
    ofSetLineWidth(10.0);
    ofSetColor(255, 255, 0);
    ofNoFill();
    ofDrawCircle(ofGetWidth(), ofGetHeight()/2, 300);
    ofFill();
}

void Field::drawLeftPlayerSetting(){
    ofSetLineWidth(10.0);
    ofSetColor(255, 255, 0);
    ofNoFill();
    ofDrawCircle(0, ofGetHeight()/2, 300);
    ofFill();
}

void Field::drawRightPlayerSetted(){
    ofSetLineWidth(5.0);
    ofSetColor(192, 192, 192);
    ofNoFill();
    ofDrawCircle(ofGetWidth(), ofGetHeight()/2, 300);
    ofFill();
}

void Field::drawLeftPlayerSetted(){
    ofSetLineWidth(5.0);
    ofSetColor(192, 192, 192);
    ofNoFill();
    ofDrawCircle(0, ofGetHeight()/2, 300);
    ofFill();
}

// 右向きの破線の矢印を描画します。
void Field::drawRightDirection(int n, int length){
    for(int i = 0; i < n; i++){
        ofDrawLine(ofGetWidth() /2 + length * 2 * i,
                   ofGetHeight()/2,
                   ofGetWidth() /2 + length * 2 * i + length,
                   ofGetHeight()/2);
    }
    
    ofDrawLine(ofGetWidth() /2 + length * (2 * n - 1),
               ofGetHeight()/2,
               ofGetWidth() /2 + length * (2 * n - 1) + length,
               ofGetHeight()/2);
    ofDrawLine(ofGetWidth() /2 + length * (2 * n - 1) + length,
               ofGetHeight()/2,
               ofGetWidth() /2 + length * (2 * n - 1) - length,
               ofGetHeight()/2 + length);
    ofDrawLine(ofGetWidth() /2 + length * (2 * n - 1) + length,
               ofGetHeight()/2,
               ofGetWidth() /2 + length * (2 * n - 1) - length,
               ofGetHeight()/2 - length);
}

// 左向きの破線の矢印を描画します。
void Field::drawLeftDirection(int n, int length){
    for(int i = 0; i < 5; i++){
        ofDrawLine(ofGetWidth() /2 - length * 2 * i,
                   ofGetHeight()/2,
                   ofGetWidth() /2 - length * 2 * i - length,
                   ofGetHeight()/2);
    }
    ofDrawLine(ofGetWidth() /2 - length * (2 * n - 1),
               ofGetHeight()/2,
               ofGetWidth() /2 - length * (2 * n - 1) - 30,
               ofGetHeight()/2);
    ofDrawLine(ofGetWidth() /2 - length * (2 * n - 1) - length,
               ofGetHeight()/2,
               ofGetWidth() /2 - length * (2 * n - 1) + length,
               ofGetHeight()/2 + length);
    ofDrawLine(ofGetWidth() /2 - length * (2 * n - 1) - length,
               ofGetHeight()/2,
               ofGetWidth() /2 - length * (2 * n - 1) + length,
               ofGetHeight()/2 - length);
}

void Field::drawMessage(string msg) {
    ofSetColor(30, 200, 30);
    float fontWidth = message.stringWidth(msg);
    message.drawString(msg, ofGetWidth() / 2 - fontWidth / 2, ofGetHeight() / 2);
}

