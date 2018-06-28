# synthesthesia

Sound, audio, and maybe location all interact and blur to output something new.

## Idea

The idea is to take a video feed and an audio feed (either from that same video source or a separate source) and cause them to interact. Hopefully location can be integrated into this since I plan to use travel footage, travel audio, and local music as inputs.

## Plan

Services:

- Consume Video File
  - Inputs: video file, [consume audio flag]
  - Outputs: video frame stream, [audio frame stream]
- Consume Audio File
  - Inputs: audio file
  - Outputs: audio frame stream
- (many services) Audio mutates video
- (many services) Video mutates audio

## To Do

- Create video file consumer service using [GoCV](https://gocv.io/)
