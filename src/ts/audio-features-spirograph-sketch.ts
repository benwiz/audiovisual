// This file uses Spotify's Audio Features API to draw a spirograph based off
// the data returned in from the API.

import './interfaces';

namespace AudioFeaturesSpirographSketch {
  export interface Configs {
    album: string;
    trackIndex: number;
    exportImageWidth: number;
  }
}

class AudioFeaturesSpirographSketch {
  /////////////////
  // Class Setup //
  /////////////////

  CONFIGS: AudioFeaturesSpirographSketch.Configs;
  CANVAS: any;
  GRAPHICS: any;
  ALBUM_AUDIO_FEATURES: AudioFeatures[];
  TRACK_AUDIO_FEATURES: AudioFeatures;
  SINES: number[];

  constructor(configs: AudioFeaturesSpirographSketch.Configs) {
    this.CONFIGS = configs;
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
    } = await this.api(`/data/${this.CONFIGS.album}.json`);
    const albumAudioFeatures: AudioFeatures[] =
      audioFeaturesResponse.audio_features;

    // Save in global variable
    this.ALBUM_AUDIO_FEATURES = albumAudioFeatures;

    // Save track audio features
    this.TRACK_AUDIO_FEATURES = albumAudioFeatures[this.CONFIGS.trackIndex];

    // TODO: Need to include track name
    this.TRACK_AUDIO_FEATURES.name = this.TRACK_AUDIO_FEATURES.uri;
  }

  ///////////
  // Setup //
  ///////////

  setupSines = (p5: any, n: number): number[] => {
    const sines: number[] = new Array(n);
    for (let i: number = 0; i < sines.length; i++) {
      sines[i] = p5.PI; // start all sines facing NORTH
    }
    return sines;
  }

  setup = (p5: any): void => {};

  runSetup = (p5: any): void => {
    // Create container
    const albumContainer = document.querySelector(
      `#audio-features-spirographs-${this.CONFIGS.album}`,
    );
    const container: HTMLElement = document.createElement('div');
    container.id = `audio-features-spirographs-${this.CONFIGS.album}-${
      this.TRACK_AUDIO_FEATURES.name
    }`;
    albumContainer.appendChild(container);

    // Write the track title, if no track name yet
    const title = document.createElement('h5');
    title.innerHTML = <string>this.TRACK_AUDIO_FEATURES.name;
    container.appendChild(title);

    // Create canvas for web page visual
    const ratio = 0.25;
    const w = ratio * p5.windowWidth;
    const h = w;
    this.CANVAS = p5.createCanvas(w, h);
    this.CANVAS.parent(container.id);

    // Create graphics for PNG download
    const graphicsW = this.CONFIGS.exportImageWidth;
    const graphicsH = graphicsW;
    this.GRAPHICS = p5.createGraphics(graphicsW, graphicsH);

    // Create the sines (circles) for the spirograph
    this.SINES = this.setupSines(p5, 10);
  }

  //////////
  // Draw //
  //////////

  drawSurface = (surface: any, sines: number[]): void => {
    // Some configs
    const fund = 0.005; // the speed of the central sine
    const ratio = 1; // what multiplier for speed is each additional sine?
    const alpha = 50; // how opaque is the tracing system

    // Some "globals"
    const rad = surface.height / 4; // compute radius for central circle

    surface.push();
    surface.translate(surface.width / 2, surface.height / 2);

    for (let i: number = 0; i < sines.length; i++) {
      let erad = 0; // radius for small "point" within circle... this is the 'pen' when tracing
      surface.stroke(0, 0, 255 * (surface.float(i) / sines.length), alpha); // blue
      surface.fill(0, 0, 255, alpha / 2); // also, um, blue
      erad = 5.0 * (1.0 - surface.float(i) / sines.length); // pen width will be related to which sine
      const radius = rad / (i + 1); // radius for circle itself
      surface.rotate(sines[i]); // rotate circle

      surface.push(); // go up one level
      surface.translate(0, radius); // move to sine edge
      surface.ellipse(0, 0, erad, erad); // draw with erad
      surface.pop(); // go down one level

      surface.translate(0, radius); // move into position for next sine
      sines[i] = (sines[i] + (fund + fund * i * ratio)) % surface.TWO_PI; // update angle based on fundamental
    }

    surface.pop();
  }

  draw = (p5: any): void => {
    // Don't draw if no data
    if (!this.TRACK_AUDIO_FEATURES) return;

    // Run setup if not run yet... running here because setup isn't waiting for preload
    if (!this.CANVAS) {
      this.runSetup(p5);
    }

    const energy = this.TRACK_AUDIO_FEATURES.energy;
    const iterations: number = this.scale(energy, 0, 1, 300, 1200);
    for (let i: number = 0; i < iterations; i++) {
      // Draw on the canvas by passing in p5
      this.drawSurface(p5, this.SINES);

      // Draw on the
      this.drawSurface(this.GRAPHICS, [...this.SINES]);
    }

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
      this.GRAPHICS.save(`${this.TRACK_AUDIO_FEATURES.name}.png`);
    }
  }
}

////////////
// Export //
////////////

export default AudioFeaturesSpirographSketch;
