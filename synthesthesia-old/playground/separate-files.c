#include <math.h>
#include <stdint.h>
#include <stdio.h>

/*
 * separate-files.c
 *
 * This file consumes an audio file (or audio from a video file) and
 * a video file. It transforms the data from each and outputs each separately.
 * This could be valuable if I really am getting data from two separate
 * sources and want to output to two separate sources.
 *
 * TODO:
 * - Command line arguments for inputs configus (filename, sample rate, video size, etc.)
 */

// Video resolution
#define W 1280
#define H 720

// Allocate a buffer to store one video frame
unsigned char video_frame[H][W][3] = {0};

int main()
{
    // Audio pipes
    FILE *audio_pipein = popen("ffmpeg -i data/daft-punk.mp3 -f s16le -ac 1 -", "r");
    FILE *audio_pipeout = popen("ffmpeg -y -f s16le -ar 44100 -ac 1 -i - out/daft-punk.mp3", "w");

    // Video pipes
    FILE *video_pipein = popen("ffmpeg -i data/daft-punk.mp4 -f image2pipe -vcodec rawvideo -pix_fmt rgb24 -", "r");
    FILE *video_pipeout = popen("ffmpeg -y -f rawvideo -vcodec rawvideo -pix_fmt rgb24 -s 1280x720 -r 25 -i - -f mp4 -q:v 5 -an -vcodec mpeg4 out/daft-punk.mp4", "w");

    // Audio vars
    int16_t audio_sample;
    int audio_count;
    int audio_n = 0;

    // Video vars
    int x = 0;
    int y = 0;
    int video_count;

    // Read, modify, and write one audio_sample and video_frame at a time
    while (1)
    {
        // Audio
        audio_count = fread(&audio_sample, 2, 1, audio_pipein); // read one 2-byte audio_sample
        if (audio_count == 1)
        {
            ++audio_n;
            audio_sample = audio_sample * sin(audio_n * 5.0 * 2 * M_PI / 44100.0);
            fwrite(&audio_sample, 2, 1, audio_pipeout);
        }

        // Video
        video_count = fread(video_frame, 1, H * W * 3, video_pipein); // Read a frame from the input pipe into the buffer
        if (video_count == H * W * 3)                                 // Only modify and write if frame exists
        {
            for (y = 0; y < H; ++y)
                for (x = 0; x < W; ++x)
                {
                    // Invert each colour component in every pixel
                    video_frame[y][x][0] = 255 - video_frame[y][x][0]; // red
                    video_frame[y][x][1] = 255 - video_frame[y][x][1]; // green
                    video_frame[y][x][2] = 255 - video_frame[y][x][2]; // blue
                }
            // Write this frame to the output pipe
            fwrite(video_frame, 1, H * W * 3, video_pipeout);
        }

        // Break if both complete
        if (audio_count != 1 && video_count != H * W * 3)
            break;
    }

    // Close audio pipes
    pclose(audio_pipein);
    pclose(audio_pipeout);

    // Close video pipes
    fflush(video_pipein);
    fflush(video_pipeout);
    pclose(video_pipein);
    pclose(video_pipeout);

    return 0;
}
