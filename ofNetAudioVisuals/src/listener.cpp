//
//  audioAnalyzer.cpp
//  netAudioVisual
//
//  Created by Ben Wiz on 12/13/18.
//

#include "listener.h"

Listener::Listener() {}

//--------------------------------------------------------------
void Listener::setup(Canvas *canvas) {
  this->canvas = canvas;

  // Setup the sound stream. Idk why the proper way isn't working using
  // soundStreamSettings.
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
}

//--------------------------------------------------------------
void Listener::update() {
  Packet packet(&audioAnalyzer);
  canvas->recordPacket(packet);
}

//--------------------------------------------------------------
void Listener::audioIn(ofSoundBuffer &inBuffer) {
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
void Listener::exit() {
  ofSoundStreamStop();
  audioAnalyzer.exit();
}


