//
//  packet.h
//  musicVisualizer
//
//  Created by Ben Wiz on 10/14/19.
//

#pragma once

#include "ofxAudioAnalyzer.h"

class Packet {
public:
    Packet();
    void setup(ofxAudioAnalyzer *audioAnalyzer);

    float ms;
    float rmsL;
    float rmsR;
    float rms;
//    float power;
//    bool isOnset;
//    float centroidNorm;
//    float pitchSalience;
    vector<float> spectrum;
//    vector<float> melBands;
};
