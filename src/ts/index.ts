import * as P5 from 'p5/lib/p5.min';
import SingleAudioFeatureSketch from './single-audio-feature-sketch';

////////////////////
// Sketch Configs //
////////////////////

const singleAudioFeatureSketch = (
  p5: P5,
  configs: SingleAudioFeatureSketch.Configs,
) => {
  const sketch = new SingleAudioFeatureSketch(configs);

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
  //
  // Create the div for holding all the album rivers
  //
  const body = document.querySelector('body');
  const container: HTMLElement = document.createElement('div');
  container.id = 'album-rivers';
  body.appendChild(container);

  //
  // Create the UI for configs
  //
  // Title
  const title = document.createElement('h2');
  title.innerHTML = 'Album Rivers';
  title.style.textDecoration = 'underline';
  container.appendChild(title);
  //

  // Set up configs
  const configs: SingleAudioFeatureSketch.Configs = {
    album: null,
  };

  //
  // Actually run the sketches
  //
  configs.album = 'vital-signs';
  new P5((p5: P5) => singleAudioFeatureSketch(p5, configs), 'album-rivers');

  configs.album = 'city-of-sound';
  new P5((p5: P5) => singleAudioFeatureSketch(p5, configs), 'album-rivers');

  configs.album = 'men-amongst-mountains';
  new P5((p5: P5) => singleAudioFeatureSketch(p5, configs), 'album-rivers');

  configs.album = 'take-good-care';
  new P5((p5: P5) => singleAudioFeatureSketch(p5, configs), 'album-rivers');
};

// Call all creation functions
createAlbumRivers();
