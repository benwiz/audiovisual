//
//  canvas.hpp
//  of2DAudioVisual
//
//  Created by Ben Wiz on 4/27/19.
//

#pragma once

#include "ofMain.h"
#include "packet.h"

class Canvas {
public:
    Canvas();
    
    void setup(float w, float h);
    void recordPacket(Packet packet);
    void update();
    void draw();
    void reset();
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    
private:
    void updateRibbon();
    void drawFFT();
    void drawMelBands();
    void drawRibbon();
    
    // Essentials
    float w;
    float h;
    vector<Packet> packets;
    
    // FFT
    float spectrumMin;
    float spectrumMax;
    
    // Ribbon
    ofPolyline currentPolyline;
    bool leftMouseButtonPressed;
    ofVec2f lastPoint;
    float minDistance;
    vector<ofPolyline> polylines;
};
