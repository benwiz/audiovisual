// TODO: File description

import * as P5 from 'p5/lib/p5.min';
import * as Dat from 'dat.gui';
import AudioFeaturesWavesSketch from './audio-features-wave-sketch';
import AudioFeaturesSpirographsSketch from './audio-features-spirograph-sketch';

/////////////
// Dat.GUI //
/////////////

const gui = new Dat.GUI();

/////////////////
// Album Waves //
/////////////////

const wavesSketch = (p5: P5, configs: AudioFeaturesWavesSketch.Configs) => {
  const sketch = new AudioFeaturesWavesSketch(configs);

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

const createWaves = (configs: AudioFeaturesWavesSketch.Configs) => {
  // Check to see if the #album-waves div exists, if so delete it
  const id = 'album-waves';
  const oldContainer = document.querySelector(`#${id}`);
  if (oldContainer) {
    oldContainer.remove();
  }

  // Create the div for holding all the album waves
  const body = document.querySelector('body');
  const container: HTMLElement = document.createElement('div');
  container.id = id;
  body.appendChild(container);

  // Title
  const title = document.createElement('h2');
  title.innerHTML = 'Album Waves';
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
    new P5((p5: P5) => wavesSketch(p5, clone), 'album-waves');
  }
};

// Album Waves dat.gui
const wavesDatGUI = (configs: AudioFeaturesWavesSketch.Configs) => {
  const wavesChange = (_value: number) => {
    createWaves(configs);
  };
  const wavesFolder = gui.addFolder('Album Waves');
  // wavesFolder.open();
  wavesFolder
    .add(configs, 'feature', [
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
  wavesFolder.addColor(configs, 'color').onChange(wavesChange);
  wavesFolder
    .add(configs, 'strokeWeight', 1, 250)
    .step(1)
    .onChange(wavesChange);
  wavesFolder.add(configs, 'drawPoint').onChange(wavesChange);
  wavesFolder.add(configs, 'exportImageWidth').onChange(wavesChange);
};

///////////////////////
// Spirograph Sketch //
///////////////////////

const spirographSketch = (
  p5: P5,
  configs: AudioFeaturesSpirographsSketch.Configs,
) => {
  const sketch = new AudioFeaturesSpirographsSketch(configs);

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

const createSpirographs = (configs: AudioFeaturesSpirographsSketch.Configs) => {
  // Check to see if the #audio-features-spirographs div exists, if so delete it
  const id = 'audio-features-spirographs';
  const oldContainer = document.querySelector(`#${id}`);
  if (oldContainer) {
    oldContainer.remove();
  }

  // Create the div for holding all the spirographs
  const body = document.querySelector('body');
  const container: HTMLElement = document.createElement('div');
  container.id = id;
  body.appendChild(container);

  // Title
  const title = document.createElement('h2');
  title.innerHTML = 'Track Spirographs';
  title.style.textDecoration = 'underline';
  container.appendChild(title);

  // Actually run the sketches
  const albums = [
    { name: 'vital-signs', numTracks: 12 },
    // { name: 'city-of-sound', numTracks: 10 },
    // { name: 'men-amongst-mountains', numTracks: 14 },
    // { name: 'take-good-care', numTracks: 14 },
  ];
  for (const album of albums) {
    // Album Title
    const albumTitle = document.createElement('h3');
    albumTitle.innerHTML = album.name;
    albumTitle.style.textDecoration = 'underline';
    container.appendChild(albumTitle);

    // Create div for album
    const albumContainer: HTMLElement = document.createElement('div');
    const albumContainerID = `audio-features-spirographs-${album.name}`;
    albumContainer.id = albumContainerID;
    albumContainer.style.display = 'grid';
    albumContainer.style.gridTemplateColumns = 'auto auto auto';
    container.appendChild(albumContainer);

    // Start the sketch
    for (let i: number = 0; i < album.numTracks; i++) {
      const clone = Object.assign({}, configs);
      clone.album = album.name;
      clone.trackIndex = i;
      new P5(
        (p5: P5) => spirographSketch(p5, clone),
        `audio-features-spirographs-${album.name}`,
      );
    }
  }
};

////////////////
// Executions //
////////////////

// Album Waves
const wavesConfigs: AudioFeaturesWavesSketch.Configs = {
  feature: 'energy',
  album: null,
  color: '#000000',
  strokeWeight: 10,
  drawPoint: false,
  exportImageWidth: 8000,
};
createWaves(wavesConfigs);
wavesDatGUI(wavesConfigs);

// Audio Features Spirograph Sketch
const spirographsConfigs: AudioFeaturesSpirographsSketch.Configs = {
  album: null,
  trackIndex: 0,
  exportImageWidth: 4000,
};
createSpirographs(spirographsConfigs);
