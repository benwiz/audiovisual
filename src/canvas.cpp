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
//    net.setup(20, 20);
}

void Canvas::recordPacket(Packet packet) {
    // Append packet to vector
    packets.push_back(packet);
}

void Canvas::update() {
    // Update the to align with the latest packet
    if (!packets.empty()) {
        Packet lastPacket = packets.back();
        
        // For now, we only care about the final packet. So we keep just the final
        // packet. Clearing then re-adding probably isn't the best way to do this. But whatever.
        packets.clear();
        packets.push_back(lastPacket);
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
    // TODO: Should be very similar to drawFF().
}

void Canvas::drawRibbon() {
    
}

void Canvas::draw() {
    // Draw the fft spectrum for debugging
    drawFFT();
}

void Canvas::reset() {
    packets.clear();
    spectrumMin = 999;
    spectrumMax = -999;
}
