//
//  net.cpp
//  netAudioVisual
//
//  Created by Ben Wiz on 12/13/18.
//

#include "net.h"

Net::Net() {}

void Net::setup(int w, int h) {
  int multiplier = 20;

  // Set primitive to triangles // OF_PRIMITIVE_TRIANGLES
  mesh.setMode(OF_PRIMITIVE_TRIANGLES);

  // Add vertices to mesh
  for (int y = 0; y < h; y++) {
    for (int x = 0; x < w; x++) {
      ofPoint point(x * multiplier, y * multiplier, 0);
      mesh.addVertex(point);
      mesh.addColor(ofColor::black);
    }
  }

  for (int y = 0; y < h - 1; y++) {
    for (int x = 0; x < w - 1; x++) {
      mesh.addIndex(x + y * w);       // 0
      mesh.addIndex((x + 1) + y * w); // 1
      mesh.addIndex(x + (y + 1) * w); // 10

      mesh.addIndex((x + 1) + y * w);       // 1
      mesh.addIndex((x + 1) + (y + 1) * w); // 11
      mesh.addIndex(x + (y + 1) * w);       // 10
    }
  }
}

void Net::update(Packet packet) {
  for (auto &vertex : mesh.getVertices()) {

    // TODO: zOffset should calculate the distance from center of mesh then use
    // that distance as a fraction of radius (max distance from center) to
    // select a FrequencyBand or a MelBand to warp with.

    float zOffset = 10 * (0.5 - ofRandomuf());
    ofPoint offset(0, 0, zOffset);
    vertex += offset;
  }
}

void Net::draw() {
  ofTranslate(-45, -45);
  mesh.drawWireframe();
}
