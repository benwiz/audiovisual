package main

import (
	"fmt"
	// "reflect"

	"github.com/nareix/joy4/av"
	"github.com/nareix/joy4/av/avutil"
	"github.com/nareix/joy4/cgo/ffmpeg"
	"github.com/nareix/joy4/format"
)

func init() {
	format.RegisterAll()
}

func getStreamsAndAudioDecoder(file av.DemuxCloser) ([]av.CodecData, *ffmpeg.AudioDecoder, error) {
	var decoder *ffmpeg.AudioDecoder

	fmt.Println()
	streams, _ := file.Streams()
	for _, stream := range streams {
		if stream.Type().IsAudio() {
			audioStream := stream.(av.AudioCodecData)
			var err error
			decoder, err = ffmpeg.NewAudioDecoder(stream.(av.AudioCodecData))
			if err != nil {
				return nil, nil, err
			}
			fmt.Println("Audio Stream:", audioStream.Type(), audioStream.SampleRate(), audioStream.SampleFormat(), audioStream.ChannelLayout())
		} else if stream.Type().IsVideo() {
			videoStream := stream.(av.VideoCodecData)
			fmt.Println("Video Stream:", videoStream.Type(), videoStream.Width(), videoStream.Height())
		}
	}
	fmt.Println()

	return streams, decoder, nil
}

func readPackets(file av.DemuxCloser, streams []av.CodecData, decoder *ffmpeg.AudioDecoder) error {
	for i := 0; i < 7; i++ {
		var pkt av.Packet
		pkt, err := file.ReadPacket()
		if err != nil {
			return err
		}
		fmt.Println("| pkt:", i, streams[pkt.Idx].Type(), "\t| len:", len(pkt.Data), "\t| keyframe:", pkt.IsKeyFrame)
		// fmt.Println(pkt.Data)

		// b, frame, err := av.AudioDecoder.Decode(pkt.Data)
		// if err != nil {
		// 	return err
		// }
		// defer av.AudioDecoder.Close()
	}

	return nil
}

func main() {
	var file av.DemuxCloser
	file, _ = avutil.Open("data/daft-punk.mp4")
	defer file.Close()

	// get streams and audio decoder
	streams, decoder, err := getStreamsAndAudioDecoder(file)
	if err != nil {
		fmt.Println("getStreamsAndAudioDecoder error:", err)
	}

	// read packets one by one
	err = readPackets(file, streams, decoder)
	if err != nil {
		fmt.Println("Error:", err)
	}
}
