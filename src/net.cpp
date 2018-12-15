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

// TODO: Eventually we want to remove the heavy lifting from the draw function.
void Net::draw(Packet packet) {
  ofTranslate(20, 20);
  mesh.drawWireframe();
}
