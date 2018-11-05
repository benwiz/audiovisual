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

void Canvas::preprocess() {
  // Here is where any preprocessing would happen. If any preprocessing is done,
  // we should create a new vector causing draw() to need to be updated.
}

void Canvas::drawOnsets(vector<vector<float>> onsets) {
  if (onsets.size() == 0) {
    return;
  }

  ofSetRectMode(OF_RECTMODE_CORNER);
  ofSetColor(ofColor::black);
  int firstMs = (int)onsets[0][0];
  for (vector<float> &onset : onsets) {
    int ms = (int)onset[0] - firstMs;
    float magnitude = onset[1];
    float pitch = onset[2];

    // Calculate the step
    int msPerRow = 10000;
    int rowHeight = 16;
    int xPos = ms % msPerRow;
    float x = ofMap(xPos, 0, msPerRow, 0, 0.9 * w); // 0.9 because dots must lie within the yellow
    float y = ms / msPerRow * rowHeight;

    // Draw dot
    ofDrawCircle(x, y, 4);
  }
}

void Canvas::draw() {
  ofPushMatrix();

  // Draw blank canvas
  ofSetColor(ofColor::lightGoldenRodYellow);
  ofSetRectMode(OF_RECTMODE_CENTER);
  ofDrawRectangle(ofGetWidth() / 2, ofGetHeight() / 2, w, h);

  // Draw all onsets (potential memory issue here depending how large onsets is)
  float x = (ofGetWidth() - w) / 2 + 0.05 * w;
  float y = (ofGetHeight() - h) / 2 + 0.05 * h;
  ofTranslate(x, y);
  drawOnsets(onsets);

  ofPopMatrix();
}

void Canvas::reset() { onsets.clear(); }
