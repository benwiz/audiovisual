//
//  scribe.cpp
//  clefChef
//
//  Created by Ben Wiz on 11/3/18.
//

#include "scribe.h"

Scribe::Scribe() {}

//--------------------------------------------------------------
void Scribe::setup() {

  ofBackground(34, 34, 34);
  ofSetFrameRate(60);

  int sampleRate = 44100;
  int bufferSize = 512;
  int outChannels = 0;
  int inChannels = 2;

  // Setup the sound stream. Idk why the proper way isn't working.
  //  ofSoundStreamSettings soundStreamSettings;
  //  soundStreamSettings.numOutputChannels = outChannels;
  //  soundStreamSettings.numInputChannels = inChannels;
  //  soundStreamSettings.sampleRate = sampleRate;
  //  soundStreamSettings.bufferSize = bufferSize;
  //  soundStreamSettings.numBuffers = 3;
  //  soundStream.setup(soundStreamSettings);
  //  soundStream.setup(this, outChannels, inChannels, sampleRate, bufferSize, 3);
  ofSoundStreamSetup(outChannels, inChannels, sampleRate, bufferSize, 3);

  // Setup ofxAudioAnalyzer with the SAME PARAMETERS
  audioAnalyzer.setup(sampleRate, bufferSize, inChannels);

  // Init onset
  onset = false;
}

//--------------------------------------------------------------
void Scribe::update() {

  smooth = ofClamp(ofGetMouseX() / (float)ofGetWidth(), 0.0, 1.0);

  // Get the analysis values
  rms_l = audioAnalyzer.getValue(RMS, 0, smooth);
  rms_r = audioAnalyzer.getValue(RMS, 1, smooth);

  // Onset
  onset = audioAnalyzer.getOnsetValue(0);

  // Centroid and pitchSalience
  int channel = 0;
  float smoothAmount = 0.0; // [0, 1]
  centroid = audioAnalyzer.getValue(CENTROID, channel, smoothAmount, false);
  centroidNorm = audioAnalyzer.getValue(CENTROID, channel, smoothAmount, true);
  pitchSalience = audioAnalyzer.getValue(PITCH_SALIENCE, 0, smoothAmount);
}

//--------------------------------------------------------------
void Scribe::draw() {
  // Bouncing circle
  ofSetColor(ofColor::cyan);
  float xpos = ofGetWidth() * .5;
  float ypos = ofGetHeight() - ofGetHeight() * rms_r;
  float radius = 5 + 100 * rms_l;
  ofDrawCircle(xpos, ypos, radius);

  // Text
  ofSetColor(225);
  ofDrawBitmapString("ofxAudioAnalyzer - RMS SMOOTHING INPUT EXAMPLE", 32, 32);
  string infoString =
      "RMS Left: " + ofToString(rms_l) + "\nRMS Right: " + ofToString(rms_r) +
      "\nSmoothing (mouse x): " + ofToString(smooth) + "\nCentroid: " +
      ofToString(centroid) + "\nCentroid Norm: " + ofToString(centroidNorm) +
      "\nPitchSalience: " + ofToString(pitchSalience);

  ofDrawBitmapString(infoString, 32, 570);

  // Onset
  if (onset) {
    ofSetColor(ofColor::cyan);
    ofDrawCircle(ofGetWidth() / 4, ofGetHeight() / 4, 200);
  }
}
//--------------------------------------------------------------
void Scribe::audioIn(ofSoundBuffer &inBuffer) {
  int channel = 0;
  float alpha = 0.5;            // [0, 1.0]
  float silenceThreshold = 0.2; // [0, 1.0]
  float timeThreshold = 100.0;  // [0, 1000.0]
  bool useTimeThreshold = false;
  audioAnalyzer.setOnsetsParameters(channel, alpha, silenceThreshold,
                                    timeThreshold, useTimeThreshold);
  audioAnalyzer.analyze(inBuffer);
}

//--------------------------------------------------------------
void Scribe::exit() {
  ofSoundStreamStop();
  audioAnalyzer.exit();
}
