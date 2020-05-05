//
//  canvas.hpp
//  netAudioVisual
//
//  Created by Ben Wiz on 12/13/18.
//

#pragma once

#include "ofMain.h"
#include "packet.h"
#include "net.h"

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
  Net net;
};

