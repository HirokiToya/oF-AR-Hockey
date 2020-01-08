//
//  ContactListener.cpp
//  myDeepSketch
//
//  Created by 外谷弘樹 on 2019/07/08.
//

#include <stdio.h>
#include "MyContactListener.h"

MyContactListener::MyContactListener(){
    sound.load("billiard-ball.mp3");
}

void MyContactListener::BeginContact(b2Contact* contact){
    sound.play();
}

void MyContactListener::EndContact(b2Contact* contact){
    
}
