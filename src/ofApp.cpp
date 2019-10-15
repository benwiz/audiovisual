#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    // Output devices
    soundStream.printDeviceList();
    
    // Drawing setup
    ofSetVerticalSync(true);
    ofSetCircleResolution(80);
    ofBackground(54, 54, 54);
    
    // Setup audio streaming
    ofSoundStreamSettings settings;
    
    auto devices = soundStream.getMatchingDevices("default");
    if(!devices.empty()){
        settings.setInDevice(devices[0]);
    }
    
    settings.setInListener(this);
    settings.sampleRate = 44100;
    settings.numOutputChannels = 0;
    settings.numInputChannels = 2;
    settings.bufferSize = 256;
    soundStream.setup(settings);
    
    // Set up audio analyzer
    audioAnalyzer.setup(settings.sampleRate, settings.bufferSize, settings.numInputChannels);
    
    // Set up shader
    vertShaderPath = "shaders/default.vert";
    fragShaderPath = "shaders/color-organ-1.frag";
    shader.load(vertShaderPath, fragShaderPath);

}

//--------------------------------------------------------------
void ofApp::update(){
    // Update packet
    packet.setup(&audioAnalyzer);
}

//--------------------------------------------------------------
void ofApp::draw(){

    // NOTE: Drawings will appear behind transparent shader
//    // Draw rms circle
//    ofSetColor(245, 58, 135);
//    ofFill();
//    ofDrawCircle(ofGetWidth() / 2, ofGetHeight() / 2, packet.rms * 150.0f);

    ofSetColor(255);
    shader.begin();
    
    // Setup
    shader.setUniform1f("iWidth", ofGetWidth());
    shader.setUniform1f("iHeight", ofGetHeight());
    
    // Audio data
    shader.setUniform1f("iRMS", packet.rms);
    
    // Screen
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
    
    shader.end();
}

//--------------------------------------------------------------
void ofApp::audioIn(ofSoundBuffer & input){
    
    // Audio Analyzer
    int channel = 0;
    float alpha = 0.5;            // [0, 1.0]
    float silenceThreshold = 0.2; // [0, 1.0]
    float timeThreshold = 100.0;  // [0, 1000.0]
    bool useTimeThreshold = false;
    audioAnalyzer.setOnsetsParameters(channel, alpha, silenceThreshold, timeThreshold, useTimeThreshold);
    audioAnalyzer.analyze(input);

}

//--------------------------------------------------------------
void ofApp::keyPressed  (int key){
    if( key == 's' ){
        soundStream.start();
    }
    
    if( key == 'e' ){
        soundStream.stop();
    }
    
    if( key == 'r' ){
        shader.load(vertShaderPath, fragShaderPath);
    }
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
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
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

