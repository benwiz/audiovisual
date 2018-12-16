






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
  center = ofVec2f((w - 1) * multiplier / 2.0, (h - 1) * multiplier / 2.0);

  // Save the original vertices
  for (auto vertex : mesh.getVertices()) {
    initialVertices.push_back(vertex);
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

    // NOTE: I decided to switch to frequency.
    //    // Select a melBand. We add one because the 0th band always has too
    //    extreme
    //    // a value.
    //    int melBandIndex = distRatio * packet.melBands.size() + 1;
    //    float normalizedMelBand = ofMap(packet.melBands[melBandIndex], -16 /*
    //    DB_MIN */, DB_MAX, 0.0, 1.0, true);

    // Select a frequency from spectrum
    int spectrumIndex = distRatio * (packet.spectrum.size() - 1);
    float frequency =
        ofMap(packet.spectrum[spectrumIndex], DB_MIN, DB_MAX, 0.0, 1.0, true);

    // Primary movement is in the z-plane
    float z = 200 * frequency;

    // Secondary movement is in the x- and y-planes

    // Create line from initial vertex location to center
    // TODO: Figure out how to bubble out the mesh
    ofPolyline line;
    //line.addVertex(initialVertex.x, initialVertex.y);
    line.addVertex(2*initialVertex.x-center.x, 2*initialVertex.y-center.y); // This extends the line twice as far away from center as target point
    line.addVertex(center.x, center.y);
    float percent = ofMap(packet.power, 0, 10, 0, 1);
    percent *= 1 - distRatio;
    percent *= 100;
    percent = 1 - percent;
    cout << percent << endl;
    ofPoint point = line.getPointAtPercent(percent);
    float x = point.x;
    float y = point.y;

    // Update the vertex's position
    mesh.getVertices()[i] = ofVec3f(x, y, z);
  }
}

void Net::draw() {
  ofTranslate(-190, -190);
  mesh.drawWireframe();

  //  ofSetColor(ofColor::green);
  //  ofDrawCircle(center.x, center.y, 282.843);

  //  ofSetColor(ofColor::blue);
  //  ofDrawCircle(center.x, center.y, 1, 20);

  ofSetColor(ofColor::lightGreen);
  ofDrawRectangle(0, 0, -1, 380, 380);

  ofSetColor(ofColor::red);
  ofDrawCircle(initialVertices[100].x, initialVertices[100].y, 1, 5);
  ofDrawCircle(center.x, center.y, 1, 5);
  ofDrawCircle(2*initialVertices[100].x - center.x, 2*initialVertices[100].y - center.y, 1, 5);
}
