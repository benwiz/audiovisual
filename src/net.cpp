//
//  net.cpp
//  netAudioVisual
//
//  Created by Ben Wiz on 12/13/18.
//

#include "net.h"

Net::Net() {}

void Net::setup(int w, int h) {
  for (int i = 0; i < w; i++) {
    for (int j = 0; j < h; j++) {
      ofPoint point(i, j, 0);
      points.push_back(point);
    }
  }
}

// TODO: Eventually we want to remove the heavy lifting from the draw function.
void Net::draw(Packet packet) {
  ofSetColor(ofColor::black);

  // RMS sphere
  printf("%f\n", 100 * packet.rms);
  ofDrawSphere(0, 0, 100 * packet.rms);

  //  // Pitch Salience circle
  //  printf("%f\n", 100 * packet.pitchSalience);
  //  ofDrawSphere(0, 0, 100 * packet.pitchSalience);
}
