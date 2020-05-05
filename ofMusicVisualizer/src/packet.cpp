//
//  packet.cpp
//  musicVisualizer
//
//  Created by Ben Wiz on 10/14/19.
//

#include "packet.h"

Packet::Packet() {}

void Packet::setup(ofxAudioAnalyzer *audioAnalyzer) {
    // Get ellapsed ms
    ms = ofGetElapsedTimeMillis();
    
    int channel = 0;
    
    // Get the rms values
    float smoothAmount = 0.2;
    rmsL = audioAnalyzer->getValue(RMS, 0, smoothAmount);
    rmsR = audioAnalyzer->getValue(RMS, 1, smoothAmount);
    rms = (rmsL + rmsR) / 2;
    
    //    // Get power
    //    smoothAmount = 0.4;
    //    power = audioAnalyzer->getValue(POWER, 0, smoothAmount);
    //
    //    // Onset
    //    isOnset = audioAnalyzer->getOnsetValue(0);
    //
    //    // Centroid and pitchSalience
    //    smoothAmount = 0.1; // [0, 1]
    //    bool doNormalize = true;
    //    centroidNorm = audioAnalyzer->getValue(CENTROID, channel, smoothAmount, doNormalize);
    //    pitchSalience = audioAnalyzer->getValue(PITCH_SALIENCE, channel, smoothAmount); // Normalized by default
    
        // Spectrum and melBands
        smoothAmount = 0.3;
        spectrum = audioAnalyzer->getValues(SPECTRUM, channel, smoothAmount);
    //    melBands = audioAnalyzer->getValues(MEL_BANDS, channel, smoothAmount);
}
