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

// Globals
let CANVAS: any;
let ALBUM_AUDIO_FEATURES: AudioFeatures[];

//////////
// Util //
//////////

const range = (start: number, stop: number, step: number = 1) =>
  Array(Math.ceil((stop - start) / step))
    .fill(start)
    .map((x, y) => x + y * step);

export const scale = (
  num: number,
  inMin: number,
  inMax: number,
  outMin: number,
  outMax: number,
): number => ((num - inMin) * (outMax - outMin)) / (inMax - inMin) + outMin;

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
  const widthRatio = 0.8;
  const heightRatio = 0.25 * widthRatio;
  // const w = widthRatio * p5.windowWidth;
  const w = 1000;
  const h = heightRatio * w;
  CANVAS = p5.createCanvas(w, h);
};

//////////
// Draw //
//////////

const getXValues = (p5: any, n: number) => {
  const values: number[] = range(0, n);
  const scaledValues = values.map(x => (x / (n - 1)) * p5.width);
  return scaledValues;
};

const getYValues = (albumAudioFeatures: AudioFeatures[]) => {
  const result: number[] = [];
  for (const trackAudioFeature of albumAudioFeatures) {
    const feature: number = trackAudioFeature.energy; // TODO: Generalize
    result.push(feature);
  }
  return result;
};

const draw = (p5: any): void => {
  // Don't draw if no data
  if (!ALBUM_AUDIO_FEATURES) return;

  // Do not set background color to keep it transparent

  // Get x- and y-values
  const n = ALBUM_AUDIO_FEATURES.length;
  const xValues = getXValues(p5, n);
  let yValues = getYValues(ALBUM_AUDIO_FEATURES);

  // Scale yValues
  yValues = yValues.map(y =>
    scale(y, Math.min(...yValues), Math.max(...yValues), 0, 1),
  );

  // Drawing configs
  p5.stroke(159, 137, 88); // Saints gold
  p5.strokeWeight(10);
  p5.noFill();

  // Set matrix to scale and translate so endpoints are visible
  p5.push();
  p5.scale(0.9);
  p5.translate(0.05 * p5.width, 0.03 * p5.height);

  // Draw line
  p5.beginShape();
  p5.curveVertex(xValues[0], yValues[0]);
  for (let i: number = 0; i < n; i++) {
    const x = xValues[i];
    const y = (1 - yValues[i]) * p5.height;
    p5.curveVertex(x, y);

    // Also draw point for debugging
    p5.ellipse(x, y, 10);
  }
  p5.curveVertex(xValues[n - 1], yValues[n - 1]);
  p5.endShape();

  // Unset matrix
  p5.pop();

  // Stop the loop
  p5.noLoop();
  // Save
  // p5.save(CANVAS, 'out.png');
};

////////////
// Export //
////////////

export default { preload, setup, draw };
