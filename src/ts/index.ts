import * as P5 from 'p5/lib/p5.min';
import SingleAudioFeatureSketch from './single-audio-feature-sketch';

const singleAudioFeatureSketch = (p5: P5, album: string) => {
  const sketch = new SingleAudioFeatureSketch(album);

  p5.preload = async () => {
    await sketch.preload(p5);
  };

  p5.setup = () => {
    sketch.setup(p5);
  };

  p5.draw = () => {
    sketch.draw(p5);
  };

  p5.mousePressed = () => {
    sketch.mousePressed(p5);
  };
};

new P5((p5: P5) => singleAudioFeatureSketch(p5, 'vital-signs'));
new P5((p5: P5) => singleAudioFeatureSketch(p5, 'city-of-sound'));
new P5((p5: P5) => singleAudioFeatureSketch(p5, 'men-amongst-mountains'));
new P5((p5: P5) => singleAudioFeatureSketch(p5, 'take-good-care'));
