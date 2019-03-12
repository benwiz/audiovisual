# spotify-album-curves

Create curves (lines) based on a single audio feature for a set of songs (album). Export the result as a SVG. Allow some configuration like min/max y-values and thickness of the curve and possibly selection of audio feature property.

## Development Notes

To develop in two shells run the following two NPM scripts

```sh
npm run webpack
```

```sh
npm start
```

To deploy just push all changes to GitHub.

## To Do

- Create a prototype for The Revialists using Gimp

- The line shape is missing two points
- Figure out how to make background transparent, default is black when exported as PNG
- Download as svg... maybe look into how canvas-sketch exports large PNGs

- Configs
  - property (feature name)
  - line/stroke width
