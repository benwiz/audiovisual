//
//  canvas.cpp
//  clefChef
//
//  Created by Ben Wiz on 11/3/18.
//

#include "canvas.h"

Canvas::Canvas() {}

void Canvas::setup(float w, float h) {
  this->w = w;
  this->h = h;
}

void Canvas::recordOnset(float magnitude, float pitch) {
  float ms = ofGetElapsedTimeMillis();
  vector<float> onset{ms, magnitude, pitch};
  onsets.push_back(onset);
}

void Canvas::recordSpectrum(vector<float> spectrum) {
  this->spectrum = spectrum;
}

void Canvas::recordMelBands(vector<float> melBands) {
  this->melBands = melBands;
}

void Canvas::preprocess() {
  // Here is where any preprocessing would happen. If any preprocessing is done,
  // we should create a new vector causing draw() to need to be updated.
}

void Canvas::drawOnsets(vector<vector<float>> onsets) {
  if (onsets.size() == 0) {
    return;
  }

  int firstMs = (int)onsets[0][0];
  for (vector<float> &onset : onsets) {
    int ms = (int)onset[0] - firstMs;
    float magnitude = onset[1];
    float pitch = onset[2];

    // Calculate the position
    int msPerRow = 10000;
    int rowHeight = 40;
    int xPos = ms % msPerRow;
    float x = ofMap(xPos, 0, msPerRow, 0, 0.9 * w); // 0.9 because dots must lie within the yellow
    float y = ms / msPerRow * rowHeight + pitch * rowHeight;

    // Calculate radius
    float r = ofMap(magnitude, 0.2, 0.9, 1, 5);

    // Draw dot
    ofDrawCircle(x, y, r);
  }
}

void Canvas::drawSpectrum(vector<float> spectrum) {
  float w = ofGetWidth() / 2;
  float x = 0;
  float y = ofGetHeight();
  float yOffset = 100;
  float step = w / spectrum.size();
  float spectrumMultiplier = 10;

  ofPath path;
  path.moveTo(x, y - yOffset);
  for (int i = 0; i < spectrum.size(); i++) {
    y = ofGetHeight() - yOffset - abs(spectrum[i]) * spectrumMultiplier;
    path.lineTo(x, y);
    x += step;
  }

  path.setFilled(false);
  path.setStrokeColor(ofColor::black);
  path.setStrokeWidth(2);
  path.draw();
}

void Canvas::drawMelBands(vector<float> melBands) {
  float w = ofGetWidth() / 2;
  float x = ofGetWidth() / 2;
  float y = ofGetHeight();
  float yOffset = 100;
  float step = w / melBands.size();
  float bandMultiplier = 20;

  ofPath path;
  path.moveTo(x, y - yOffset);
  for (int i = 0; i < melBands.size(); i++) {
    y = ofGetHeight() - yOffset - abs(melBands[i]) * bandMultiplier;
    path.lineTo(x, y);
    x += step;
  }

  path.setFilled(false);
  path.setStrokeColor(ofColor::black);
  path.setStrokeWidth(2);
  path.draw();
}

void Canvas::draw() {
  ofPushMatrix();

  // Draw blank canvas
  ofSetColor(ofColor::lightGoldenRodYellow);
  ofSetRectMode(OF_RECTMODE_CENTER);
  ofDrawRectangle(ofGetWidth() / 2, ofGetHeight() / 2, w, h);

  // Draw all onsets (potential memory issue here depending how large onsets is)
  ofSetColor(ofColor::black);
  ofSetRectMode(OF_RECTMODE_CORNER);
  float x = (ofGetWidth() - w) / 2 + 0.05 * w;
  float y = (ofGetHeight() - h) / 2 + 0.05 * h;
  ofTranslate(x, y);
  drawOnsets(onsets);

  ofPopMatrix();

  // Draw spectrum and mel bands
  drawSpectrum(spectrum);
  drawMelBands(melBands);
}

void Canvas::reset() { onsets.clear(); }
