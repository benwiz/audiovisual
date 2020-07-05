# synthesthesia

Sound, audio, and maybe location all interact and blur to output something new.

## Idea

The idea is to take a video feed and an audio feed (either from that same video source or a separate source) and cause them to interact. Hopefully location can be integrated into this since I plan to use travel footage, travel audio, and local music as inputs.

## Requirements

- ffmpeg
- vlc or ffplay?

## Notes

### Figure out frame rate of mp4

- Open it in VLC
- CMD+I (Media Information)
- Codec Details
- Frame Rate (daft-punk.mp4 is 23.976024)

### Build and execute C program

https://stackoverflow.com/questions/51139736/error-inclunding-libavformat-avformat-h-in-ffmpeg-project-on-a-mac-using-clang#51139809

```bash
cc -o filename.out filepath.c -lavformat
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

### Potentially Useful Notes and Links

- https://wiki.videolan.org/Uncommon_uses/
- https://stackoverflow.com/questions/10126715/how-to-encode-a-video-file-for-real-time-streaming-and-deliver-it-through-udp-da
- http://nullprogram.com/blog/2017/11/03/
- MUXING! https://github.com/FFmpeg/FFmpeg/blob/master/doc/examples/remuxing.c
- `ffmpeg -i input.avi <options> -f matroska - | ffplay -`
- https://stackoverflow.com/questions/40677951/how-to-merge-audio-to-video-through-ffmpeg-c-api
- http://dranger.com/ffmpeg/tutorial01.html

## To Do

- Use [this example](https://github.com/FFmpeg/FFmpeg/blob/master/doc/examples/decode_video.c#L158-L173) to get frames
