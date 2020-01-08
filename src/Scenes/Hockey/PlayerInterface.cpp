//
//  Player.cpp
//  myDeepSketch
//
//  Created by 外谷弘樹 on 2019/07/10.
//

#include <stdio.h>
#include "PlayerInterface.h"

void PlayerInterface::setup(){
    
    // kinect
    kinect.init();
    kinect.open();
    
    // GUI
#ifdef _USE_GUI
    gui.setup("myGUI", 0, 0, 360, 220);
    gui.addPanel("panel 1", 3);
    gui.setWhichColumn(0);
    gui.addSlider("depth near", "near", 60, 0, 255, true);
    gui.addSlider("depth far", "far", 255, 0, 255, true);
    gui.addSlider("Camera Tilt Angle", "angle", 0, -40, 40, true);
    gui.loadSettings("controlPanelSettings.xml");
#endif
    
    // ofxCv
    contourFinder.setMinAreaRadius(20);
    contourFinder.setMaxAreaRadius(200);
    
    rightPosition = Point2f(KINECT_WIDTH / 2, KINECT_HEIGHT / 2);
    leftPosition = Point2f(KINECT_WIDTH / 2, KINECT_HEIGHT / 2);
    mirrorRightPosition = rightPosition;
    mirrorLeftPosition = leftPosition;
    
    isRightPlayerExist = false;
    isLeftPlayerExist = false;
}

bool PlayerInterface::isFrameNew(){
    return kinect.isFrameNew();
}

void PlayerInterface::update(){
    
    kinect.update();
    
#ifdef _USE_GUI
    gui.update();
    kinect.setCameraTiltAngle(gui.getValueI("angle"));
#else
    kinect.setCameraTiltAngle(0);
#endif
    
    if(kinect.isFrameNew()) {
        colorImage.setFromPixels(kinect.getPixels().getData(), KINECT_WIDTH, KINECT_HEIGHT, OF_IMAGE_COLOR);
        depthImage.setFromPixels(kinect.getDepthPixels().getData(), KINECT_WIDTH, KINECT_HEIGHT, OF_IMAGE_GRAYSCALE);
        
        threshImage = depthImage;
        unsigned char * pix = threshImage.getPixels().getData();
        int numPixels = threshImage.getWidth() * threshImage.getHeight();
        
#ifdef _USE_GUI
        int near = gui.getValueI("near");
        int far = gui.getValueI("far");
#else
        int near = 60;// 本番環境
//        int near = 240;
        int far = 255;
#endif
        
        for(int i = 0; i < numPixels; i++){
            if(pix[i] < far && pix[i] > near) pix[i] = 255;
            else pix[i] = 0;
        }
        
        threshImage.setFromPixels(pix, KINECT_WIDTH, KINECT_HEIGHT, OF_IMAGE_GRAYSCALE);
        contourFinder.findContours(threshImage);
        
        isRightPlayerExist = false;
        isLeftPlayerExist = false;
        
        for(int i = 0; i < contourFinder.size() && contourFinder.size() != 0; i++){
            Point2f pos = contourFinder.getCenter(i);
            if (pos.x > KINECT_WIDTH / 2){
                isRightPlayerExist = true;
                rightPosition = pos;
            } else{
                isLeftPlayerExist = true;
                leftPosition = pos;
            }
        }
        
        if (!isRightPlayerExist) {
            mirrorRightPosition.x = KINECT_WIDTH - leftPosition.x;
            mirrorRightPosition.y = leftPosition.y;
        } else {
            mirrorRightPosition = rightPosition;
        }
        
        if (!isLeftPlayerExist){
            mirrorLeftPosition.x = KINECT_WIDTH - rightPosition.x;
            mirrorLeftPosition.y = rightPosition.y;
        } else {
            mirrorLeftPosition = leftPosition;
        }
        
        // 比率を更新
        rightPosition.x = rightPosition.x * ofGetWidth() / KINECT_WIDTH - 80;
        rightPosition.y = rightPosition.y * ofGetHeight() / KINECT_HEIGHT;
        leftPosition.x = leftPosition.x * ofGetWidth() / KINECT_WIDTH;
        leftPosition.y = leftPosition.y * ofGetHeight() / KINECT_HEIGHT;
        
        mirrorRightPosition.x = mirrorRightPosition.x * ofGetWidth() / KINECT_WIDTH;
        mirrorRightPosition.y = mirrorRightPosition.y * ofGetHeight() / KINECT_HEIGHT;
        mirrorLeftPosition.x = mirrorLeftPosition.x * ofGetWidth() / KINECT_WIDTH;
        mirrorLeftPosition.y = mirrorLeftPosition.y * ofGetHeight() / KINECT_HEIGHT;
    }
}

void PlayerInterface::draw(){
    
    ofSetColor(192, 192, 192);
    // 2値化した深度画像を表示
    threshImage.draw(0, 0, ofGetWidth(), ofGetHeight());
    ofPushMatrix();
    ofScale(ofGetWidth() / (float)KINECT_WIDTH,
            ofGetHeight() / (float)KINECT_HEIGHT);
    // 四角い輪郭を表示
    contourFinder.draw();
    ofPopMatrix();
    
#ifdef _USE_GUI
    gui.draw();
#endif
}

void PlayerInterface::saveImage() {
    
    string imgPath = "img/" + ofToString(ofGetYear()) + "/" + ofToString(ofGetMonth()) + "/" + ofToString(ofGetDay()) + "/" + ofToString(ofGetHours()) + "_" + ofToString(ofGetMinutes()) + "_" + ofToString(ofGetSeconds()) +".jpg";
    
    colorImage.save(imgPath);
}

void PlayerInterface::mouseDragged(int x, int y, int button){
#ifdef _USE_GUI
    gui.mouseDragged(x, y, button);
#endif
}

void PlayerInterface::mousePressed(int x, int y, int button){
#ifdef _USE_GUI
    gui.mousePressed(x, y, button);
#endif
}

void PlayerInterface::mouseReleased(int x, int y, int button){
#ifdef _USE_GUI
    gui.mouseReleased();
#endif
}
