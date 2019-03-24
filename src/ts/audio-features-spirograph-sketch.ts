// This file uses Spotify's Audio Features API to draw a spirograph based off
// the data returned in from the API.

import './interfaces';

namespace AudioFeaturesSpirographSketch {
  export interface Configs {
    album: string;
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
  }

  ///////////
  // Setup //
  ///////////

  setup = (p5: any): void => {
    console.log('setup');
  }

  //////////
  // Draw //
  //////////

  drawSurface = (surface: any): void => {
    // Do not set background color to keep it transparent
    surface.stroke('red');
    surface.fill('red');
    surface.ellipse(surface.width / 2, surface.height / 2, 50);
  }

  draw = (p5: any): void => {
    // Don't draw if no data
    if (!this.ALBUM_AUDIO_FEATURES) return;
    console.log('draw');

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
      // this.GRAPHICS.save(`${this.CONFIGS.album}.png`);
    }
  }
}

////////////
// Export //
////////////

export default AudioFeaturesSpirographSketch;
