//
//  scribe.cpp
//  clefChef
//
//  Created by Ben Wiz on 11/3/18.
//

#include "scribe.h"

Scribe::Scribe() {}

//--------------------------------------------------------------
void Scribe::setup(Canvas *canvas) {
  this->canvas = canvas;

  // Setup the sound stream. Idk why the proper way isn't working.
  int sampleRate = 44100;
  int bufferSize = 512;
  int outChannels = 0;
  int inChannels = 2;
  int numBuffers = 3;
  //  ofSoundStreamSettings soundStreamSettings;
  //  soundStreamSettings.numOutputChannels = outChannels;
  //  soundStreamSettings.numInputChannels = inChannels;
  //  soundStreamSettings.sampleRate = sampleRate;
  //  soundStreamSettings.bufferSize = bufferSize;
  //  soundStreamSettings.numBuffers = numBuffers;
  //  soundStream.setup(soundStreamSettings);
  //  soundStream.setup(this, outChannels, inChannels, sampleRate, bufferSize,
  //  numBuffers);
  ofSoundStreamSetup(outChannels, inChannels, sampleRate, bufferSize,
                     numBuffers);

  // Setup ofxAudioAnalyzer with the same parameters
  audioAnalyzer.setup(sampleRate, bufferSize, inChannels);

  // Init onset variable
  onset = false;
}

//--------------------------------------------------------------
// Run ofxAudioAnalyzer algorithms then pass to canvas.
void Scribe::update() {
  // Get the analysis values
  float smoothAmount = 0.2;
  rmsL = audioAnalyzer.getValue(RMS, 0, smoothAmount);
  rmsR = audioAnalyzer.getValue(RMS, 1, smoothAmount);
  rms = (rmsL + rmsR) / 2;

  // Onset
  onset = audioAnalyzer.getOnsetValue(0);

  // Centroid and pitchSalience
  int channel = 0;
  smoothAmount = 0.0; // [0, 1]
  centroid = audioAnalyzer.getValue(CENTROID, channel, smoothAmount, false);
  centroidNorm = audioAnalyzer.getValue(CENTROID, channel, smoothAmount, true);
  pitchSalience = audioAnalyzer.getValue(PITCH_SALIENCE, 0, smoothAmount);

  // Pass onset info to canvas
  if (onset) {
    canvas->recordOnset(rms, pitchSalience);
  }
}

//--------------------------------------------------------------
// Do any non-essential drawing
void Scribe::draw() {
  // Text
  ofSetColor(10);
  string infoString = "RMS Left: " + ofToString(rmsL) + "\nRMS Right: " +
                      ofToString(rmsR) + "\nRMS: " + ofToString(rms) +
                      "\nCentroid: " + ofToString(centroid) +
                      "\nCentroid Norm: " + ofToString(centroidNorm) +
                      "\nPitchSalience: " + ofToString(pitchSalience);
  ofDrawBitmapString(infoString, 32, 570);
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
