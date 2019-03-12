import * as P5 from 'p5/lib/p5.min';
import Sketch from './sketch';

const sketch = function(p5: P5) {
  p5.preload = () => {
    Sketch.preload(p5);
  };

  p5.setup = () => {
    Sketch.setup(p5);
  };

  p5.draw = () => {
    Sketch.setup(p5);
  };
};

new P5(sketch);
