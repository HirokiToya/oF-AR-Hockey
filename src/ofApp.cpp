#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    
    baseScene * myApp = new EventController();
    scenes.push_back(myApp);
    
    currentScene = 0;
    scenes[currentScene] -> setup();
}

//--------------------------------------------------------------
void ofApp::update(){
    scenes[currentScene] -> update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    scenes[currentScene] -> draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch(key) {
        case ' ':
            // シーンの切り替え
            currentScene++;
            currentScene %= scenes.size();
            break;
            
        case 'f':
            ofToggleFullscreen();
            break;
        
        default:
            scenes[currentScene] -> keyPressed(key);
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    scenes[currentScene] -> keyReleased(key);
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    scenes[currentScene] -> mouseMoved(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    scenes[currentScene] -> mouseDragged(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    scenes[currentScene] -> mousePressed(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    scenes[currentScene] -> mouseReleased(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    scenes[currentScene] -> mouseEntered(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    scenes[currentScene] -> mouseExited(x, y);
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    scenes[currentScene] -> windowResized(w, h);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    scenes[currentScene] -> gotMessage(msg);
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    scenes[currentScene] -> dragEvent(dragInfo);
}
