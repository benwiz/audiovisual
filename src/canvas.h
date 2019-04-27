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
    
private:
    float w;
    float h;
    vector<Packet> packets;
    float spectrumMin = 999;
    float spectrumMax = -999;
    
    void drawFFT();
    void drawMelBands();
    void drawRibbon();
};
