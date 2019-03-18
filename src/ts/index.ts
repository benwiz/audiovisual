import * as P5 from 'p5/lib/p5.min';
import SingleAudioFeatureSketch from './single-audio-feature-sketch';

////////////////////
// Sketch Configs //
////////////////////

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

////////////////////////
// Creation Functions //
////////////////////////

const createAlbumRivers = () => {
  const body = document.querySelector('body');

  // Create the div for holding all the album rivers
  const container: HTMLElement = document.createElement('div');
  container.id = 'album-rivers';
  body.appendChild(container);

  // Create the UI for configs
  const title = document.createElement('h2');
  title.innerHTML = 'Album Rivers';
  title.style.textDecoration = 'underline';
  container.appendChild(title);

  // Actually run the sketches
  new P5(
    (p5: P5) => singleAudioFeatureSketch(p5, 'vital-signs'),
    'album-rivers',
  );
  new P5(
    (p5: P5) => singleAudioFeatureSketch(p5, 'city-of-sound'),
    'album-rivers',
  );
  new P5(
    (p5: P5) => singleAudioFeatureSketch(p5, 'men-amongst-mountains'),
    'album-rivers',
  );
  new P5(
    (p5: P5) => singleAudioFeatureSketch(p5, 'take-good-care'),
    'album-rivers',
  );
};

// Call all creation functions
createAlbumRivers();
