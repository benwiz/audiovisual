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

## Plan

- Create the following patterns using Audio Features data only. Have a new canvas and download button for each song in album.

## To Do

- Change repo name, because this is going to be the whole website
- Single feature plot
  - Configs
    - feature selector
    - PNG download size
    - stroke width
    - color
    - point display
