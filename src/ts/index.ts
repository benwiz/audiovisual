import * as P5 from 'p5/lib/p5.min';
// import * as P5SVG from 'p5.js-svg';
// P5SVG(P5);
import SingleAudioFeatureSketch from './single-audio-feature-sketch';

const singleAudioFeatureSketch = (p5: P5) => {
  p5.preload = async () => {
    await SingleAudioFeatureSketch.preload(p5);
  };

  p5.setup = () => {
    SingleAudioFeatureSketch.setup(p5);
  };

  p5.draw = () => {
    SingleAudioFeatureSketch.draw(p5);
  };

  p5.mousePressed = () => {
    SingleAudioFeatureSketch.mousePressed(p5);
  };
};

const singleAudioFeatureCanvas = new P5(singleAudioFeatureSketch);
// new P5(singleAudioFeatureSketch);
