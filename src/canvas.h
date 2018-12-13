//
//  canvas.hpp
//  netAudioVisual
//
//  Created by Ben Wiz on 12/13/18.
//

#pragma once

#include "ofMain.h"
#include "packet.h"

class Canvas {
public:
  Canvas();

  void setup(float w, float h);
  void recordPacket(Packet packet);
  void draw();
  void reset();

private:
  void drawNet(Packet packet);

  float w;
  float h;

  vector<Packet> packets;
};

