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

let ALBUM_AUDIO_FEATURES: AudioFeatures[];

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
  // Get audio features for one album
  const audioFeaturesResponse: { audio_features: AudioFeatures[] } = await api(
    '/data/vital-signs.json',
  );
  const albumAudioFeatures: AudioFeatures[] =
    audioFeaturesResponse.audio_features;

  // Save in global variable
  ALBUM_AUDIO_FEATURES = albumAudioFeatures;
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

// Extract single feature from audioFeatures
const getData = (albumAudioFeatures: AudioFeatures[]) => {
  const result: number[] = [];
  for (const trackAudioFeature of albumAudioFeatures) {
    const feature: number = trackAudioFeature.energy; // TODO: Generalize
    result.push(feature);
  }
  return result;
};

const draw = (p5: any): void => {
  if (!ALBUM_AUDIO_FEATURES) return;

  p5.background(200);

  // Extract data from from AUDIO_FEATURES using given property
  const data = getData(ALBUM_AUDIO_FEATURES);
};

////////////
// Export //
////////////

export default { preload, setup, draw };
