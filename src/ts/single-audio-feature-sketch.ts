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
let GRAPHICS: any;
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
  p5.createCanvas(w, h);
  const graphicsW = 8000;
  const graphicsH = heightRatio * graphicsW;
  GRAPHICS = p5.createGraphics(graphicsW, graphicsH);
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

const drawSurface = (surface: any): void => {
  // Do not set background color to keep it transparent

  // Get x- and y-values
  const n = ALBUM_AUDIO_FEATURES.length;
  const xValues = getXValues(surface, n);
  let yValues = getYValues(ALBUM_AUDIO_FEATURES);

  // Scale yValues
  yValues = yValues.map(y =>
    scale(y, Math.min(...yValues), Math.max(...yValues), 0, 1),
  );

  // Drawing configs
  surface.stroke(159, 137, 88); // Saints gold
  surface.strokeWeight(10);
  surface.noFill();

  // Set matrix to scale and translate so endpoints are visible
  surface.push();
  surface.scale(0.9);
  surface.translate(0.05 * surface.width, 0.03 * surface.height);

  // Draw line
  surface.beginShape();
  surface.curveVertex(xValues[0], yValues[0]);
  for (let i: number = 0; i < n; i++) {
    const x = xValues[i];
    const y = (1 - yValues[i]) * surface.height;
    surface.curveVertex(x, y);

    // Also draw point for debugging
    surface.ellipse(x, y, 10);
  }
  surface.curveVertex(xValues[n - 1], yValues[n - 1]);
  surface.endShape();

  // Unset matrix
  surface.pop();
};

const draw = (p5: any): void => {
  // Don't draw if no data
  if (!ALBUM_AUDIO_FEATURES) return;

  // Draw on the canvas by passing in p5
  drawSurface(p5);

  // Draw on the
  drawSurface(GRAPHICS);

  // Stop the loop
  p5.noLoop();
};

///////////
// Other //
///////////

const mousePressed = (_p5: any) => {
  GRAPHICS.save('out.png');
};

////////////
// Export //
////////////

export default { preload, setup, draw, mousePressed };
