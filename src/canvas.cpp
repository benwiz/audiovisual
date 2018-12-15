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
  net.setup(10, 20);
}

void Canvas::recordPacket(Packet packet) {
  // Append packet to vector
  packets.push_back(packet);
}

void Canvas::draw() {
  // Draw the net with the most recent packet
  if (!packets.empty()) {
    Packet lastPacket = packets.back();
    net.draw(lastPacket);

    // For now, we only care about the final packet. So we keep just the final
    // packet. This probably isn't the best way to do this. But whatever.
    packets.clear();
    packets.push_back(lastPacket);
  }
}

void Canvas::reset() { packets.clear(); }
