//
//  Score.h
//  myDeepSketch
//
//  Created by 外谷弘樹 on 2019/07/03.
//

#pragma once

#include "ofMain.h"

class Score {
public:
    
    Score();
    void rightPlayerPoint();
    void leftPlayerPoint();
    void draw();
    void reset();
    int getRightPoint();
    int getLeftPoint();
    
private:
    ofTrueTypeFont scoreFont;
    
    int rightPlayerScore;
    int leftPlayerScore;
};
