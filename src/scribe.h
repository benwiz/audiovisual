//
//  scribe.hpp
//  clefChef
//
//  Created by Ben Wiz on 11/3/18.
//

#include "ofMain.h"
#include "ofxAudioAnalyzer.h"

class Scribe {
public:
  Scribe();

  void setup();
  void update();
  void draw();
  void exit();

  void audioIn(ofSoundBuffer &inBuffer);

private:
  ofSoundStream soundStream;
  ofxAudioAnalyzer audioAnalyzer;

  float rmsL, rmsR;
  float smooth;

  bool onset;
  float centroid;
  float centroidNorm;
  float pitchSalience;
};


