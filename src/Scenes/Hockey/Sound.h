//
//  Sound.h
//  myDeepSketch
//
//  Created by 外谷弘樹 on 2019/07/04.
//

#pragma once

#include "ofMain.h"

class Sound {
public:
    
    Sound();
    void load(string name);
    void play();
    void update();
    void stop();
    bool isPlaying();
    
    ofEvent <void> endEvent;
    
private:
    ofSoundPlayer sound;
    bool isPlayed;
};
