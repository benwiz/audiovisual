#include <math.h>
#include <stdint.h>
#include <stdio.h>

int main()
{
    // Launch two instances of FFmpeg, one to read the original WAV
    // file and another to write the modified WAV file. In each case,
    // data passes between this program and FFmpeg through a pipe.
    FILE *pipein;
    FILE *pipeout;
    pipein = popen("ffmpeg -i data/daft-punk.mp3 -f s16le -ac 1 -", "r");
    pipeout = popen("ffmpeg -y -f s16le -ar 44100 -ac 1 -i - out/daft-punk.mp3", "w");

    // Read, modify and write one sample at a time
    int16_t sample;
    int count, n = 0;
    while (1)
    {
        count = fread(&sample, 2, 1, pipein); // read one 2-byte sample
        if (count != 1)
            break;
        ++n;
        sample = sample * sin(n * 5.0 * 2 * M_PI / 44100.0);
        fwrite(&sample, 2, 1, pipeout);
    }

    // Close input and output pipes
    pclose(pipein);
    pclose(pipeout);

    return 1;
}
