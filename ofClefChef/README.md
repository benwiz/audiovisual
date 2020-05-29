#  clefChef

## What

OpenFrameworks (C++) based audio visualizer. Intended to plot a single song or audioclip to a static image that is inspired by sheet music. Should be able to be printed out.

## How

Using the "packet" configuring seen in my other OpenFrameworks projects. Some audio frames are consumed, analyzed, then sent to the game loop.

## Status

Inactive.

### Retrospective

As much as I'd rather use another tool OpenFrameworks is excellent.

## To Do

- Figure out the right way to organize the code base to explore different approaches

- Approaches to try:
  - Draw onsets with pitch (current setup)
  - Draw melBands as if there were a staff and `if onset == true` emphasize it some way

