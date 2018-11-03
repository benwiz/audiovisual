#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
  ofBackground(ofColor::white);
  ofSetFrameRate(60);

  canvas.setup(ofGetWidth() * 0.9, ofGetHeight() * 0.9);
  scribe.setup(canvas);
}

//--------------------------------------------------------------
void ofApp::update() {
  scribe.update();
  canvas.update();
}

//--------------------------------------------------------------
void ofApp::draw() {
  scribe.draw();
  canvas.draw();
}

//--------------------------------------------------------------
void ofApp::exit() {
  scribe.exit();
}

//--------------------------------------------------------------
void ofApp::audioIn(ofSoundBuffer &inBuffer) {
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
