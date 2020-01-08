//
//  Score.cpp
//  myDeepSketch
//
//  Created by 外谷弘樹 on 2019/07/03.
//

#include <stdio.h>
#include "Score.h"

Score::Score() {
    scoreFont.load("font.ttf", 200);
    rightPlayerScore = 0;
    leftPlayerScore = 0;
}

void Score::rightPlayerPoint(){
    rightPlayerScore ++;
}

void Score::leftPlayerPoint(){
    leftPlayerScore ++;
}

void Score::draw(){
    ofSetColor(30, 200, 200);
    string leftScore = to_string(leftPlayerScore);
    string rightScore = to_string(rightPlayerScore);
    float scoreFontWidth = scoreFont.stringWidth(leftScore + " - " + rightScore);
    
    ofPushMatrix();
    ofTranslate(ofGetWidth(), ofGetHeight());
    ofRotateZDeg(180);
    scoreFont.drawString(rightScore + " - " + leftScore,
                         ofGetWidth() / 2 - scoreFontWidth / 2,
                         ofGetHeight() / 2  - 200);
    
    ofPopMatrix();
}

void Score::reset() {
    rightPlayerScore = 0;
    leftPlayerScore = 0;
}

int Score::getRightPoint(){
    return rightPlayerScore;
}

int Score::getLeftPoint(){
    return leftPlayerScore;
}
