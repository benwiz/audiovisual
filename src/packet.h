//
//  packet.hpp
//  netAudioVisual
//
//  Created by Ben Wiz on 12/13/18.
//

#pragma once

#include "ofxAudioAnalyzer.h"

class Packet {
public:
  Packet(ofxAudioAnalyzer *audioAnalyzer);

  // Since this is a data class, I'm just keeping the data public, no need for
  // getters and setters.
  float ms;
  float rmsL;
  float rmsR;
  float rms;
  float power;
  bool isOnset;
  float centroidNorm;
  float pitchSalience;
  vector<float> spectrum;
  vector<float> melBands;
};

