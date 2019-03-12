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

const main = async (): Promise<void> => {
  // Get audio features for one data file
  const audioFeaturesResponse: { audio_features: AudioFeatures } = await api(
    '/data/vital-signs.json',
  );
  const audioFeatures: AudioFeatures = audioFeaturesResponse.audio_features;
  console.log(audioFeatures);
};

main();
