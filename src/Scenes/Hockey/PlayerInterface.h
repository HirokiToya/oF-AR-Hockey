//
//  PlayerInterface.h
//  myDeepSketch
//
//  Created by 外谷弘樹 on 2019/07/10.
//

#pragma once

#include "ofMain.h"
#include "ofxKinect.h"
#include "ofxCv.h"
#include "ofxControlPanel.h"

//#define _USE_GUI
#define KINECT_WIDTH 640
#define KINECT_HEIGHT 480

using namespace cv;
using namespace ofxCv;

// ユーザーからの情報をkinectを介して取得して、コントローラが使いやすいデータにして渡す役割。
class PlayerInterface {
public:
    
    void setup();
    void update();
    void draw();
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    bool isFrameNew();
    void saveImage();
    
    Point2f rightPosition, leftPosition;
    Point2f mirrorRightPosition, mirrorLeftPosition;
    
    bool isRightPlayerExist;
    bool isLeftPlayerExist;
    
private:
    
    // GUI
    ofxControlPanel gui;
    
    // kinect
    ofxKinect kinect;
    
    ofImage colorImage;
    ofImage depthImage;
    ofImage threshImage;
    
    // openCV
    ContourFinder contourFinder;
    
    
    
    
};
