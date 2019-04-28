//
//  canvas.cpp
//  of2DAudioVisual
//
//  Created by Ben Wiz on 4/27/19.
//

#include "canvas.h"

Canvas::Canvas() {}

void Canvas::setup(float w, float h) {
    this->w = w;
    this->h = h;

    // FFT
    spectrumMin = 999;
    spectrumMax = -999;
    
    // Ribbon
    minDistance = 10;
    leftMouseButtonPressed = false;
}

void Canvas::recordPacket(Packet packet) {
    // Append packet to vector
    packets.push_back(packet);
}

void Canvas::updateRibbon() {
    if (leftMouseButtonPressed) {
        ofVec2f mousePos(ofGetMouseX(), ofGetMouseY());
        if (lastPoint.distance(mousePos) >= minDistance) {
            // a.distance(b) calculates the Euclidean distance between point a and b.  It's
            // the length of the straight line distance between the points.
            currentPolyline.curveTo(mousePos.x, mousePos.y);
            lastPoint = mousePos;
        }
    }
}

void Canvas::update() {
    // Update the to align with the latest packet
    if (!packets.empty()) {
        Packet lastPacket = packets.back();
        
        // For now, we only care about the final packet. So we keep just the final
        // packet. Clearing then re-adding probably isn't the best way to do this. But whatever.
        packets.clear();
        packets.push_back(lastPacket);
        
        // Update ribbon
        updateRibbon();
    }
}

void Canvas::drawFFT() {
    float x = 0.1 * ofGetWidth();
    float step = 10;
    ofPath path;
    
    for (int i = 0; i < packets.back().spectrum.size(); i++) {
        float value = packets.back().spectrum[i];
        if (value < spectrumMin) {
            spectrumMin = value;
            if (spectrumMin < -18) {
                spectrumMin = -18;
            }
        }
        if (value > spectrumMax) {
            spectrumMax = value;
            if (spectrumMax > 10) {
                spectrumMax = 10;
            }
        }
        
        float y;
        if (value > -6.00001 && value < -5.99999) { // idk how to do float compare correctly
            y = 0;
        } else {
            y = ofMap(value, spectrumMin, spectrumMax, 0, ofGetHeight() / 2);
        }
        //cout << spectrumMin << "\tto\t" << spectrumMax << "\t|\t" << value << "\t->\t"  << y << endl;
        y = ofGetHeight() - y;
        
        if (i == 0) {
            path.moveTo(x, y);
        }
        path.lineTo(x, y);
        x += step;
    }
    path.setFilled(false);
    path.setStrokeColor(ofColor::black);
    path.setStrokeWidth(2);
    path.draw();
}

void Canvas::drawMelBands() {
    // TODO: Should be very similar to drawFFT().
}

void Canvas::drawRibbon() {
    ofBackground(255);
    ofSetColor(0);  // Black for saved polylines
    for (int i = 0; i < polylines.size(); i++) {
        ofPolyline polyline = polylines[i];
        polyline.draw();
    }
    ofSetColor(255,100,0);  // Orange color for active polyline
    currentPolyline.draw();
}

void Canvas::draw() {
    // Draw the fft spectrum for debugging
    drawFFT();
    
    // Draw the ribbon
    drawRibbon();
}

void Canvas::reset() {
    packets.clear();
    spectrumMin = 999;
    spectrumMax = -999;
}

void Canvas::mousePressed(int x, int y, int button) {
    if (button == OF_MOUSE_BUTTON_LEFT) {
        leftMouseButtonPressed = true;
        currentPolyline.curveTo(x, y);  // Remember that x and y are the location of the mouse
        currentPolyline.curveTo(x, y);  // Necessary duplicate for first control point
        lastPoint.set(x, y);  // Set the x and y
    }
}

void Canvas::mouseReleased(int x, int y, int button) {
    if (button == OF_MOUSE_BUTTON_LEFT) {
        leftMouseButtonPressed = false;
        currentPolyline.curveTo(x, y); // Necessary duplicate for last control point
        polylines.push_back(currentPolyline);
        currentPolyline.clear();  // Erase the vertices, allows us to start a new brush stroke
    }
}
