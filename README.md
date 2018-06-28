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

## Notes

### Figure out frame rate of mp4

- Open it in VLC
- CMD+I (Media Information)
- Codec Details
- Frame Rate (daft-punk.mp4 is 23.976024)

## To Do

- Figure out how to AudioDecode or video Demux the packets
- Then figure out how to re-encode and re-mux them and hopefully play/display in real time (probably via a streaming server)
- Decide if I have to switch to C 
  - https://batchloaf.wordpress.com/2017/02/10/a-simple-way-to-read-and-write-audio-and-video-files-in-c-using-ffmpeg/
  - https://batchloaf.wordpress.com/2017/02/12/a-simple-way-to-read-and-write-audio-and-video-files-in-c-using-ffmpeg-part-2-video/
