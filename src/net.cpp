//
//  net.cpp
//  netAudioVisual
//
//  Created by Ben Wiz on 12/13/18.
//

#include "net.h"

Net::Net() {}

void Net::setup(int w, int h) {
  // TODO: Consider other shape options, it may make more sense to have a
  // circle or even a sphere (or any shape?)

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

  // Connect vertices with indices
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

  // Save the center location of the mesh for later. Just X and Y, not Z.
  center = ofVec2f(w * multiplier / 2, h * multiplier / 2);
}

void Net::update(Packet packet) {
  for (auto &vertex : mesh.getVertices()) {

    // TODO: zOffset should calculate the X-Y (not X-Y-Z) distance from center
    // of mesh then use that distance as a fraction of radius (max distance
    // from center) to select a FrequencyBand or a MelBand to warp with.

    // Calculate X-Y distance and maxDist to find distRatio
    float dist = center.distance(ofVec2f(vertex.x, vertex.y));
    float maxDist = sqrt(pow(center.x, 2) + pow(center.y, 2));
    float distRatio = dist / maxDist;

    // Select a melBand
    int melBandIndex = distRatio * packet.melBands.size();
    cout << melBandIndex << ":\t" << packet.melBands[melBandIndex] << endl;

    // Calculate z value
    float z = 10 * abs(packet.melBands[melBandIndex]) - 6;

    // Update the vertex
    //  float zOffset = melBandValue;
    //  ofPoint offset(0, 0, zOffset);
    //  vertex += offset;
    vertex = ofVec3f(vertex.x, vertex.y, z);
  }
}

void Net::draw() {
  ofTranslate(-45, -45);
  mesh.drawWireframe();

  //  ofSetColor(ofColor::green);
  //  ofDrawSphere(center.x, center.y, 0, 5);
}
