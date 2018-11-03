//
//  scribe.hpp
//  clefChef
//
//  Created by Ben Wiz on 11/3/18.
//

#include "ofMain.h"
#include "canvas.h"
#include "ofxAudioAnalyzer.h"

class Scribe {
public:
  Scribe();

  void setup(Canvas *canvas);
  void update();
  void draw();
  void exit();

  void audioIn(ofSoundBuffer &inBuffer);

private:
  Canvas *canvas;

  ofSoundStream soundStream;
  ofxAudioAnalyzer audioAnalyzer;

  float rmsL, rmsR, rms;
  bool onset;
  float centroid;
  float centroidNorm;
  float pitchSalience;
};


