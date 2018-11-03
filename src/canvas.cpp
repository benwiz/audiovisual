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
  this->x = 0;
  this->y = 0;
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
  ofSetRectMode(OF_RECTMODE_CORNER);
  ofSetColor(ofColor::black);
  for (vector<float> &onset : onsets) {
    int ms = (int)onset[0];
    float magnitude = onset[1];
    float pitch = onset[2];

    // Starting off testing with 10s (10,000ms) to a line
    ms = ms % 10000;
    float xStep = ofMap(ms, 0, 1000, 0, w);
    x += xStep;
    if (x >= w) {
      x = 0;
    }
    if (x == 0) {
      // Increase by line height
      y += 16;
    }

    // Draw dot
    cout << x << "\t" << y << endl;
    ofDrawCircle(x, y, 4);
  }
}

void Canvas::draw() {
  // Translate
  ofPushMatrix();
  ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);

  // Draw blank canvas
  ofSetColor(ofColor::lightGoldenRodYellow);
  ofSetRectMode(OF_RECTMODE_CENTER);
  ofDrawRectangle(0, 0, w, h);

  // Draw all onsets (potential memory issue here)
  drawOnsets(onsets);

  // Untranslate
  ofPopMatrix();
}
