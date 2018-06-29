# synthesthesia

Sound, audio, and maybe location all interact and blur to output something new.

## Idea

The idea is to take a video feed and an audio feed (either from that same video source or a separate source) and cause them to interact. Hopefully location can be integrated into this since I plan to use travel footage, travel audio, and local music as inputs.

## Requirements

- ffmpeg
- ffplay?

## Notes

### Figure out frame rate of mp4

- Open it in VLC
- CMD+I (Media Information)
- Codec Details
- Frame Rate (daft-punk.mp4 is 23.976024)

### Build and execute C program

```bash
cc -o filename.out filepath.c
```

```bash
./filename.out
```

Or

```bash
./build-run.sh
```

### Play audio file

```bash
afplay filename.mp3
```

### Sources

- Video file provides video and audio
- Video file and audio file

### Initial Research

- https://batchloaf.wordpress.com/2017/02/10/a-simple-way-to-read-and-write-audio-and-video-files-in-c-using-ffmpeg/
- https://batchloaf.wordpress.com/2017/02/12/a-simple-way-to-read-and-write-audio-and-video-files-in-c-using-ffmpeg-part-2-video/

## To Do

- separate-files.c
  - Take command line arguments where appropriate
- separate-streams.c
  - Make a copy of `separate-files.c` to handle input and output to streams. It will probably be easiest to output first in real time. Then figure out inputs.
