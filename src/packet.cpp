//
//  packet.cpp
//  netAudioVisual
//
//  Created by Ben Wiz on 12/13/18.
//

#include "packet.h"

Packet::Packet(ofxAudioAnalyzer *audioAnalyzer) {
  // Get ellapsed ms
  ms = ofGetElapsedTimeMillis();

  // Get the rms values
  float smoothAmount = 0.2;
  rmsL = audioAnalyzer->getValue(RMS, 0, smoothAmount);
  rmsR = audioAnalyzer->getValue(RMS, 1, smoothAmount);
  rms = (rmsL + rmsR) / 2;

  // Get power
  power = audioAnalyzer->getValue(POWER, 0, smoothAmount);

  // Onset
  isOnset = audioAnalyzer->getOnsetValue(0);

  // Centroid and pitchSalience
  int channel = 0;
  smoothAmount = 0.1; // [0, 1]
  bool doNormalize = true;
  centroidNorm =
      audioAnalyzer->getValue(CENTROID, channel, smoothAmount, doNormalize);
  pitchSalience = audioAnalyzer->getValue(
      PITCH_SALIENCE, channel, smoothAmount); // Normalized by default

  // Spectrum and melBands
  smoothAmount = 0.4;
  spectrum = audioAnalyzer->getValues(SPECTRUM, channel, smoothAmount);
  melBands = audioAnalyzer->getValues(MEL_BANDS, channel, smoothAmount);
}

