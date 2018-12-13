//
//  net.cpp
//  netAudioVisual
//
//  Created by Ben Wiz on 12/13/18.
//

#include "net.h"

Net::Net() {}

void Net::setup(int w, int h) {
  int multiplier = 10;
  for (int i = 0; i < w; i++) {
    for (int j = 0; j < h; j++) {
      ofPoint point(i * multiplier, j * multiplier, 0);
      points.push_back(point);
      mesh.addVertex(point);
    }
  }
}

// TODO: Eventually we want to remove the heavy lifting from the draw function.
void Net::draw(Packet packet) {
  ofSetColor(ofColor::black);

  for (ofPoint point : points) {
    ofDrawSphere(point.x, point.y, point.z, packet.rms);
  }

  //  mesh.draw();
}
