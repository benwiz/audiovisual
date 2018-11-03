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

void Canvas::update() {
  // Here is where any preprocessing would happen. If any preprocessing is done
  // here, it should create a new vector causing draw() to need to be updated.
}

void Canvas::drawOnsets() {
  ofSetRectMode(OF_RECTMODE_CORNER);
  for (vector<float> &onset : onsets) {
    cout << "draw onset" << endl;
    float ms = onset[0];
    float magnitude = onset[1];
    float pitch = onset[2];
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

  // Draw all onsets (if this turns out to take up too much memory, we will
  // need to not overwrite everything but trim the onsets vector as we go)
  drawOnsets();

  // Untranslate
  ofPopMatrix();
}
