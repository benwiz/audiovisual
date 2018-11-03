//
//  canvas.hpp
//  clefChef
//
//  Created by Ben Wiz on 11/3/18.
//

#include "ofMain.h"

class Canvas {
public:
  Canvas();

  void setup(float w, float h);
  void recordOnset(float magnitude, float pitch);
  void preprocess();
  void draw();

private:
  void drawOnsets();

  float w;
  float h;

  float x;
  float y;

  vector<vector<float>> onsets; // { [ms, magnitude, pitch], [...], ... }
};
