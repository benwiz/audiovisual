#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
  ofBackground(34, 34, 34);
  ofSetFrameRate(60);

  // Scribe
  scribe.setup();
}

//--------------------------------------------------------------
void ofApp::update() {
  // Scribe
  scribe.update();
}

//--------------------------------------------------------------
void ofApp::draw() {
  // Scribe
  scribe.draw();
}

//--------------------------------------------------------------
void ofApp::exit() {
  // Scribe
  scribe.exit();
}

//--------------------------------------------------------------
void ofApp::audioIn(ofSoundBuffer &inBuffer) {
  // Scribe
  scribe.audioIn(inBuffer);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {}
