import * as P5 from 'p5/lib/p5.min';
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
};

new P5(singleAudioFeatureSketch);
// new P5(singleAudioFeatureSketch);
