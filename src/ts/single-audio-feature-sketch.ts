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

class SingleAudioFeatureSketch {
  /////////////////
  // Class Setup //
  /////////////////

  ALBUM: string;
  CANVAS: any;
  GRAPHICS: any;
  ALBUM_AUDIO_FEATURES: AudioFeatures[];

  constructor(album: string) {
    this.ALBUM = album;
  }

  //////////
  // Util //
  //////////

  range = (start: number, stop: number, step: number = 1) =>
    Array(Math.ceil((stop - start) / step))
      .fill(start)
      .map((x, y) => x + y * step)

  scale = (
    num: number,
    inMin: number,
    inMax: number,
    outMin: number,
    outMax: number,
  ): number => ((num - inMin) * (outMax - outMin)) / (inMax - inMin) + outMin

  /////////////
  // Preload //
  /////////////

  async api<T>(url: string): Promise<T> {
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

  preload = async (p5: any): Promise<void> => {
    // Get audio features for one album
    const audioFeaturesResponse: {
      audio_features: AudioFeatures[];
    } = await this.api(`/data/${this.ALBUM}.json`);
    const albumAudioFeatures: AudioFeatures[] =
      audioFeaturesResponse.audio_features;

    // Save in global variable
    this.ALBUM_AUDIO_FEATURES = albumAudioFeatures;
  }

  ///////////
  // Setup //
  ///////////

  setup = (p5: any): void => {
    // Write the album name
    const body = document.querySelector('body');
    const title = document.createElement('h3');
    title.innerHTML = this.ALBUM;
    body.appendChild(title);

    // Create canvas for web page visual
    const widthRatio = 0.9;
    const heightRatio = 0.25 * widthRatio;
    const w = widthRatio * p5.windowWidth;
    const h = heightRatio * w;
    this.CANVAS = p5.createCanvas(w, h);

    // Create graphics for PNG download
    const graphicsW = 8000;
    const graphicsH = heightRatio * graphicsW;
    this.GRAPHICS = p5.createGraphics(graphicsW, graphicsH);
  }

  //////////
  // Draw //
  //////////

  getXValues = (p5: any, n: number) => {
    const values: number[] = this.range(0, n);
    const scaledValues = values.map(x => (x / (n - 1)) * p5.width);
    return scaledValues;
  }

  getYValues = (albumAudioFeatures: AudioFeatures[]) => {
    const result: number[] = [];
    for (const trackAudioFeature of albumAudioFeatures) {
      const feature: number = trackAudioFeature.energy; // TODO: Generalize
      result.push(feature);
    }
    return result;
  }

  drawSurface = (surface: any): void => {
    // Do not set background color to keep it transparent

    // Get x- and y-values
    const n = this.ALBUM_AUDIO_FEATURES.length;
    const xValues = this.getXValues(surface, n);
    let yValues = this.getYValues(this.ALBUM_AUDIO_FEATURES);

    // Scale yValues
    yValues = yValues.map(y =>
      this.scale(y, Math.min(...yValues), Math.max(...yValues), 0, 1),
    );

    // Drawing configs
    surface.stroke(159, 137, 88); // Saints gold
    surface.strokeWeight(10);
    surface.noFill();

    // Set matrix to scale and translate so endpoints are visible
    surface.push();
    surface.scale(0.95, 0.8);
    surface.translate(0.025 * surface.width, 0.1 * surface.height);

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
  }

  draw = (p5: any): void => {
    // Don't draw if no data
    if (!this.ALBUM_AUDIO_FEATURES) return;

    // Draw on the canvas by passing in p5
    this.drawSurface(p5);

    // Draw on the
    this.drawSurface(this.GRAPHICS);

    // Stop the loop
    p5.noLoop();
  }

  ///////////
  // Other //
  ///////////

  mousePressed = (p5: any) => {
    if (
      p5.mouseX >= 0 &&
      p5.mouseX <= p5.width &&
      p5.mouseY >= 0 &&
      p5.mouseY <= p5.height
    ) {
      this.GRAPHICS.save(`${this.ALBUM}.png`);
    }
  }
}

////////////
// Export //
////////////

export default SingleAudioFeatureSketch;
