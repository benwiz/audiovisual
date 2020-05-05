#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
  //  ofBackground(ofColor::white);
  //  ofSetFrameRate(60);

  canvas.setup(ofGetWidth(), ofGetHeight());
  listener.setup(&canvas);
}

//--------------------------------------------------------------
void ofApp::update() {
  listener.update();
  canvas.update();
}

//--------------------------------------------------------------
void ofApp::draw() {
  // Turn on camera
  glEnable(GL_DEPTH_TEST);
  cam.begin();

  canvas.draw();

  // Turn off camera
  cam.end();
}

//--------------------------------------------------------------
void ofApp::exit() { listener.exit(); }

//--------------------------------------------------------------
void ofApp::audioIn(ofSoundBuffer &inBuffer) { listener.audioIn(inBuffer); }

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
void ofApp::mouseEntered(int x, int y) {}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {}
