interface AudioFeatures {
  [key: string]: number | string;
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
  analysisUrl: string;
  trackHref: string;
  durationMs: number;
  timeSignature: number;
}
