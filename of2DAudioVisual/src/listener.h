//
//  listener.hpp
//  of2DAudioVisual
//
//  Created by Ben Wiz on 4/27/19.
//

#pragma once

#include "ofMain.h"
#include "canvas.h"
#include "packet.h"

class Listener {
public:
    Listener();
    
    void setup(Canvas *canvas);
    void update();
    void exit();
    
    void audioIn(ofSoundBuffer &inBuffer);
    
private:
    Canvas *canvas;
    
    ofSoundStream soundStream;
    ofxAudioAnalyzer audioAnalyzer;
};
