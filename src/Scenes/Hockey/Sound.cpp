//
//  Sound.cpp
//  myDeepSketch
//
//  Created by 外谷弘樹 on 2019/07/04.
//

#include <stdio.h>
#include "Sound.h"

Sound::Sound() {
    isPlayed = false;
}

void Sound::load(string name) {
    sound.load(name);
}

void Sound::play () {
    isPlayed = true;
    sound.play();
}

void Sound::stop(){
    sound.stop();
}

void Sound::update() {
    if (isPlayed && !isPlaying()) {
        ofNotifyEvent(endEvent);
        isPlayed = false;
    }
}

bool Sound::isPlaying(){
    return sound.isPlaying();
}
