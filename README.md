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

- Figure out how to make preload wait... or move data downloading into SETUP

- Function to consume the example data for one album
- Function to draw curve using consumed data and given property name (maybe a function of property names in the future)
- Configs
  - property (feature name)
  - line/stroke width
