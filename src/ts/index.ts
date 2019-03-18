import * as P5 from 'p5/lib/p5.min';
import * as Dat from 'dat.gui';
import AlbumRiversSketch from './audio-features-album-rivers-sketch';

/////////////
// Dat.GUI //
/////////////

const gui = new Dat.GUI();

//////////////////
// Album Rivers //
//////////////////

const albumRiversSketch = (p5: P5, configs: AlbumRiversSketch.Configs) => {
  const sketch = new AlbumRiversSketch(configs);

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

const createAlbumRivers = (configs: AlbumRiversSketch.Configs) => {
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
    new P5((p5: P5) => albumRiversSketch(p5, clone), 'album-rivers');
  }
};

// Call all creation functions
const albumRiversConfigs: AlbumRiversSketch.Configs = {
  feature: 'energy',
  album: null,
  color: '#000000',
  strokeWeight: 10,
  drawPoint: false,
  exportImageWidth: 8000,
};
createAlbumRivers(albumRiversConfigs);

// Album Rivers dat.gui
const albumRiversChange = (_value: number) => {
  createAlbumRivers(albumRiversConfigs);
};
const albumRiversFolder = gui.addFolder('Album Rivers');
albumRiversFolder.open();
albumRiversFolder
  .add(albumRiversConfigs, 'feature', [
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
  .onChange(albumRiversChange);
albumRiversFolder
  .addColor(albumRiversConfigs, 'color')
  .onChange(albumRiversChange);
albumRiversFolder
  .add(albumRiversConfigs, 'strokeWeight', 1, 250)
  .step(1)
  .onChange(albumRiversChange);
albumRiversFolder
  .add(albumRiversConfigs, 'drawPoint')
  .onChange(albumRiversChange);
albumRiversFolder
  .add(albumRiversConfigs, 'exportImageWidth')
  .onChange(albumRiversChange);
