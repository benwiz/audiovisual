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

  // Save the original vertices
  for (auto vertex : mesh.getVertices()) {
    initialVertices.push_back(vertex); // ofVec3f(vertex.x, vertex.y, vertex.z)
  }
}

void Net::update(Packet packet) {
  for (int i = 0; i < mesh.getVertices().size(); i++) {
    ofVec3f vertex = mesh.getVertices()[i];
    ofVec3f initialVertex = initialVertices[i];

    // Calculate X-Y distance and maxDist to find distRatio
    float dist = center.distance(ofVec2f(vertex.x, vertex.y));
    float maxDist = sqrt(pow(center.x, 2) + pow(center.y, 2));
    float distRatio = dist / maxDist;

    // Select a melBand. We add one because the 0th band always has too extreme
    // a value.
    int melBandIndex = distRatio * packet.melBands.size() - 1;
    float normalizedMelBand = ofMap(packet.melBands[melBandIndex], -16 /* DB_MIN */, DB_MAX, 0.0, 1.0, true);

    // Primary movement is in the z-plane
    float multiplier = 200;
    float z = multiplier * normalizedMelBand;

    // Secondary movement is in the x- and y-planes. To do this, we move the
    // point toward the xy center based off the `normalizedMelBand` value.
    // Eventually, maybe we want to use some other metric for xy movement.
    //    float x = vertex.x;
    //    float y = vertex.y;
    float x = ofMap(normalizedMelBand, 0, 1.0, initialVertex.x, center.x);
    float y = ofMap(normalizedMelBand, 0, 1.0, initialVertex.y, center.y);

    // Update the vertex
    mesh.getVertices()[i] = ofVec3f(x, y, z);
  }
}

void Net::draw() {
  ofTranslate(-190, -190);
  mesh.drawWireframe();

  //  ofSetColor(ofColor::green);
  //  ofDrawSphere(0, 0, 20, 5);
}
