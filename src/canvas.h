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
  void reset();

private:
  void drawOnsets(vector<vector<float>> onsets);

  float w;
  float h;

  vector<vector<float>> onsets; // { [ms, magnitude, pitch], [...], ... }
};
