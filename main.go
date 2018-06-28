package main

import (
	"fmt"
	// "reflect"

	"github.com/nareix/joy4/av"
	"github.com/nareix/joy4/av/avutil"
	"github.com/nareix/joy4/format"
)

func init() {
	format.RegisterAll()
}

func probeStreams(file av.DemuxCloser) []av.CodecData {
	fmt.Println()
	streams, _ := file.Streams()
	for _, stream := range streams {
		if stream.Type().IsAudio() {
			audioStream := stream.(av.AudioCodecData)
			fmt.Println("Audio Stream:", audioStream.Type(), audioStream.SampleRate(), audioStream.SampleFormat(), audioStream.ChannelLayout())
		} else if stream.Type().IsVideo() {
			videoStream := stream.(av.VideoCodecData)
			fmt.Println("Video Stream:", videoStream.Type(), videoStream.Width(), videoStream.Height())
		}
	}
	fmt.Println()

	return streams
}

func readPackets(file av.DemuxCloser, streams []av.CodecData) {
	for i := 0; i < 7; i++ {
		var pkt av.Packet
		pkt, err := file.ReadPacket()
		if err != nil {
			break
		}
		fmt.Println("| pkt:", i, streams[pkt.Idx].Type(), "\t| len:", len(pkt.Data), "\t| keyframe:", pkt.IsKeyFrame)
		// fmt.Println(pkt.Data)
	}
}

func main() {
	var file av.DemuxCloser
	file, _ = avutil.Open("data/daft-punk.mp4")
	defer file.Close()

	streams := probeStreams(file)
	readPackets(file, streams)
}
