#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

  ofBackground(34, 34, 34);
  ofSetFrameRate(60);

  int sampleRate = 44100;
  int bufferSize = 512;
  int outChannels = 0;
  int inChannels = 2;

  // setup the sound stream
  soundStream.setup(this, outChannels, inChannels, sampleRate, bufferSize, 3);

  //setup ofxAudioAnalyzer with the SAME PARAMETERS
  audioAnalyzer.setup(sampleRate, bufferSize, inChannels);

  // Init onset
  onset = false;
}

//--------------------------------------------------------------
void ofApp::update(){

  smooth = ofClamp(ofGetMouseX() / (float)ofGetWidth(), 0.0, 1.0);

  //get the analysis values
  rms_l = audioAnalyzer.getValue(RMS, 0, smooth);
  rms_r = audioAnalyzer.getValue(RMS, 1, smooth);

  // Onset
  onset = audioAnalyzer.getOnsetValue(0);
}

//--------------------------------------------------------------
void ofApp::draw(){

  ofSetColor(ofColor::cyan);

  float xpos = ofGetWidth() *.5;
  float ypos = ofGetHeight() - ofGetHeight() * rms_r;
  float radius = 5 + 100*rms_l;

  ofDrawCircle(xpos, ypos, radius);

  //----------------

  ofSetColor(225);
  ofDrawBitmapString("ofxAudioAnalyzer - RMS SMOOTHING INPUT EXAMPLE", 32, 32);


  string infoString = "RMS Left: " + ofToString(rms_l) +
  "\nRMS Right: " + ofToString(rms_r) +
  "\nSmoothing (mouse x): " + ofToString(smooth);

  ofDrawBitmapString(infoString, 32, 579);

  // Draw onset
  if (onset){
    ofSetColor(ofColor::cyan);
    ofDrawCircle(ofGetWidth()/4, ofGetHeight()/4, 200);
  }
}
//--------------------------------------------------------------
void ofApp::audioIn(ofSoundBuffer &inBuffer){
  //ANALYZE SOUNDBUFFER:

  float alpha = 0.5; // [0, 1.0]
  float silenceThreshold = 0.2; // [0, 1.0]
  float timeThreshold = 100.0; // [0, 1000.0]
  bool useTimeThreshold = false;
  audioAnalyzer.setOnsetsParameters(0, alpha, silenceThreshold, timeThreshold, useTimeThreshold);
  audioAnalyzer.analyze(inBuffer);
}

//--------------------------------------------------------------
void ofApp::exit(){
  ofSoundStreamStop();
  audioAnalyzer.exit();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
