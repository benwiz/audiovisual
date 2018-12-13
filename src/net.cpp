//
//  net.cpp
//  netAudioVisual
//
//  Created by Ben Wiz on 12/13/18.
//

#include "net.h"

Net::Net() {}

// TODO: Eventually we want to remove the heavy lifting from the draw function.
void Net::draw(Packet packet) {
  ofSetColor(ofColor::black);

//  // RMS circle
//  printf("%f\n", 100 * packet.rms);
//  ofDrawCircle(0, 0, 100 * packet.rms);

  // Pitch Salience circle
  printf("%f\n", 100 * packet.pitchSalience);
  ofDrawCircle(0, 0, 100 * packet.pitchSalience);
}
