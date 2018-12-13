//
//  net.hpp
//  netAudioVisual
//
//  Created by Ben Wiz on 12/13/18.
//

#pragma once

#include "packet.h"

class Net {
public:
  Net();

  void setup(int w, int h);
  void draw(Packet packet);

private:
  vector<ofPoint> points;
};
