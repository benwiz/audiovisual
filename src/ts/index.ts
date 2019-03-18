import * as P5 from 'p5/lib/p5.min';
import * as Dat from 'dat.gui';
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

const createAlbumRivers = (configs: SingleAudioFeatureSketch.Configs) => {
  // Check to see if the #album-rivers div exists, if so delete it
  const id = 'album-rivers';
  const oldContainer = document.querySelector(`#${id}`);
  if (oldContainer) {
    oldContainer.remove();
  }

  // Create the div for holding all the album rivers
  const body = document.querySelector('body');
  const container: HTMLElement = document.createElement('div');
  container.id = id;
  body.appendChild(container);

  // Title
  const title = document.createElement('h2');
  title.innerHTML = 'Album Rivers';
  title.style.textDecoration = 'underline';
  container.appendChild(title);

  // Actually run the sketches
  const albums = [
    'vital-signs',
    'city-of-sound',
    'men-amongst-mountains',
    'take-good-care',
  ];
  for (const album of albums) {
    const clone = Object.assign({}, configs);
    clone.album = album;
    new P5((p5: P5) => singleAudioFeatureSketch(p5, clone), 'album-rivers');
  }
};

// Call all creation functions
const albumRiversConfigs: SingleAudioFeatureSketch.Configs = {
  album: null,
  color: '#000000',
  strokeWeight: 2,
};
createAlbumRivers(albumRiversConfigs);

// Dat.GUI
const gui = new Dat.GUI();

// Album Rivers dat.gui
const albumRiversChange = (_value: number) => {
  createAlbumRivers(albumRiversConfigs);
};
const albumRiversFolder = gui.addFolder('Album Rivers');
albumRiversFolder.open();
albumRiversFolder
  .addColor(albumRiversConfigs, 'color')
  .onChange(albumRiversChange);
albumRiversFolder
  .add(albumRiversConfigs, 'strokeWeight', 1, 20)
  .step(1)
  .onChange(albumRiversChange);
