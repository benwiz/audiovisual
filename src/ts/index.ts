import * as P5 from 'p5/lib/p5.min';
import * as Dat from 'dat.gui';
import WavesSketch from './audio-features-wave-sketch';

/////////////
// Dat.GUI //
/////////////

const gui = new Dat.GUI();

//////////////////
// Album Rivers //
//////////////////

const wavesSketch = (p5: P5, configs: WavesSketch.Configs) => {
  const sketch = new WavesSketch(configs);

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

const createWaves = (configs: WavesSketch.Configs) => {
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
    new P5((p5: P5) => wavesSketch(p5, clone), 'album-rivers');
  }
};

// Call all creation functions
const wavesConfigs: WavesSketch.Configs = {
  feature: 'energy',
  album: null,
  color: '#000000',
  strokeWeight: 10,
  drawPoint: false,
  exportImageWidth: 8000,
};
createWaves(wavesConfigs);

// Album Rivers dat.gui
const wavesChange = (_value: number) => {
  createWaves(wavesConfigs);
};
const wavesFolder = gui.addFolder('Album Rivers');
wavesFolder.open();
wavesFolder
  .add(wavesConfigs, 'feature', [
    'danceability',
    'energy',
    'key',
    'loudness',
    'mode',
    'speechiness',
    'acousticness',
    'instrumentalness',
    'liveness',
    'valence',
    'tempo',
  ])
  .onChange(wavesChange);
wavesFolder.addColor(wavesConfigs, 'color').onChange(wavesChange);
wavesFolder
  .add(wavesConfigs, 'strokeWeight', 1, 250)
  .step(1)
  .onChange(wavesChange);
wavesFolder.add(wavesConfigs, 'drawPoint').onChange(wavesChange);
wavesFolder.add(wavesConfigs, 'exportImageWidth').onChange(wavesChange);
