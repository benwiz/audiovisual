interface AudioFeatures {
  // TODO: Put ranges or options in here in comments
  danceability: number;
  energy: number;
  key: number;
  loudness: number;
  mode: number;
  speechiness: number;
  acousticness: number;
  instrumentalness: number;
  liveness: number;
  valence: number;
  tempo: number;
  type: string;
  id: string;
  uri: string;
  trackHref: string;
  analysisUrl: string;
  durationMs: number;
  timeSignature: number;
}

const ALBUM_AUDIO_FEATURES: AudioFeatures[] = [];

/////////////
// Preload //
/////////////

async function api<T>(url: string): Promise<T> {
  return fetch(url)
    .then(response => {
      if (!response.ok) {
        throw new Error(response.statusText);
      }
      return response.json().then(data => data as T);
    })
    .catch((error: Error) => {
      throw error;
    });
}

const preload = async (p5: any): Promise<void> => {
  // Get audio features for one album and add to the global variable
  const audioFeaturesResponse: { audio_features: AudioFeatures } = await api(
    '/data/vital-signs.json',
  );
  const audioFeatures: AudioFeatures = audioFeaturesResponse.audio_features;
  ALBUM_AUDIO_FEATURES.push(audioFeatures);
};

///////////
// Setup //
///////////

const setup = (p5: any): void => {
  p5.createCanvas(0.8 * p5.windowWidth, 0.8 * p5.windowHeight);
};

//////////
// Draw //
//////////

const draw = (p5: any): void => {
  p5.background(200);

  // For each set of songs (album) draw a line using the provided property
  // as the y-value.
};

////////////
// Export //
////////////

export default { preload, setup, draw };
