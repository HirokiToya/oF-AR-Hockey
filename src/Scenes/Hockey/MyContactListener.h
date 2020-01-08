//
//  ContactListener.h
//  myDeepSketch
//
//  Created by 外谷弘樹 on 2019/07/08.
//

#pragma once

#include "ofMain.h"
#include "Sound.h"
#include "ofxBox2d.h"

// 衝突を検出するためのリスナー
class MyContactListener : public b2ContactListener {
    
public:
    MyContactListener();
    void BeginContact(b2Contact* contact);
    void EndContact(b2Contact* contact);
    
    // 効果音
    Sound sound;
};
