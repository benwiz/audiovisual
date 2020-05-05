//
//  canvas.cpp
//  netAudioVisual
//
//  Created by Ben Wiz on 12/13/18.
//

#include "canvas.h"

Canvas::Canvas() {}

void Canvas::setup(float w, float h) {
  this->w = w;
  this->h = h;
  net.setup(20, 20);
}

void Canvas::recordPacket(Packet packet) {
  // Append packet to vector
  packets.push_back(packet);
}

void Canvas::update() {
  // Update the to align with the latest packet
  if (!packets.empty()) {
    Packet lastPacket = packets.back();
    net.update(lastPacket);

    // For now, we only care about the final packet. So we keep just the final
    // packet. This probably isn't the best way to do this. But whatever.
    packets.clear();
    packets.push_back(lastPacket);
  }
}

void Canvas::draw() {
  // Draw the net
  net.draw();

  //  // Draw the fft spectrum for debugging
  //  float x = -1000;
  //  float y = -500;
  //  float step = 10;
  //  ofPath path;
  //  path.moveTo(x, y);
  //  for (int i = 0; i < packets.back().spectrum.size(); i++) {
  //    y = ofGetHeight() - abs(packets.back().spectrum[i]) * 200;
  //    path.lineTo(x, y);
  //    x += step;
  //  }
  //  path.setFilled(false);
  //  path.setStrokeColor(ofColor::black);
  //  path.setStrokeWidth(2);
  //  path.draw();
}

void Canvas::reset() { packets.clear(); }
