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
  void recordSpectrum(vector<float> spectrum);
  void recordMelBands(vector<float> melBands);
  void preprocess();
  void draw();
  void reset();

private:
  void drawOnsets(vector<vector<float>> onsets);
  void drawSpectrum(vector<float> spectrum);
  void drawMelBands(vector<float> melBands);

  float w;
  float h;

  vector<vector<float>> onsets; // { [ms, magnitude, pitch], [...], ... }
  vector<float> spectrum;
  vector<float> melBands;
};
