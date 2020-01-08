//
//  FieldView.h
//  myDeepSketch
//
//  Created by 外谷弘樹 on 2019/07/10.
//

#pragma once

#include "ofMain.h"
#include "ofxBox2d.h"
#include "MyContactListener.h"

#define MALLET_RADIUS 70

class Field {
public:
    
    void setup();
    void draw();
    void update();
    void makeBall(ofVec2f frc, float scale);
    void FieldDrawing();
    void drawStaticLines();
    void drawRightDirection(int n, int length, bool isDraw); // n: 破線の本数　length: 破線の長さ
    void drawleftDirection(int n, int length, bool isDraw);  // n: 破線の本数　length: 破線の長さ
    
    vector <ofPtr<ofxBox2dCircle> > circles;
    ofxBox2dCircle rightMallet;
    ofxBox2dCircle leftMallet;
    
private:
    
    ofxBox2d world2d;
    
    ofxBox2dRect wallUp;
    ofxBox2dRect wallU_R;
    ofxBox2dRect wallU_L;
    
    ofxBox2dRect wallDown;
    ofxBox2dRect wallD_R;
    ofxBox2dRect wallD_L;
    
    // 衝突感知のリスナー
    MyContactListener contacts;
    
};

