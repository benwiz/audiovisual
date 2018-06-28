package main

import (
	"errors"
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

func decodeAudio(decoder *ffmpeg.AudioDecoder, packet av.Packet) (av.AudioFrame, error) {
	ok, frame, err := decoder.Decode(packet.Data)
	if err != nil {
		return frame, err
	}
	if !ok {
		return frame, errors.New("decode not ok")
	}

	return frame, nil
}

func readPacket(file av.DemuxCloser, streams []av.CodecData, decoder *ffmpeg.AudioDecoder, i int) error {
	packet, err := file.ReadPacket()
	if err != nil {
		return err
	}
	packetType := streams[packet.Idx].Type()
	fmt.Print("| packet:", i, packetType, "\t| len:", len(packet.Data), "\t| keyframe:", packet.IsKeyFrame, " ")

	if packetType.IsAudio() {
		frame, err := decodeAudio(decoder, packet)
		if err != nil {
			return err
		}
		fmt.Println("\t| frame:", frame.SampleCount)
	} else {
		fmt.Println("\t| ")
	}

	return nil
}

func readPackets(file av.DemuxCloser, streams []av.CodecData, decoder *ffmpeg.AudioDecoder) error {
	for i := 0; i < 7; i++ {
		err := readPacket(file, streams, decoder, i)
		if err != nil {
			return err
		}
	}

	return nil
}

func main() {
	fmt.Println("\n\n\t\t\t~~~~~~ \n\n ")

	var file av.DemuxCloser
	file, _ = avutil.Open("data/daft-punk.mp4")
	defer file.Close()

	// get streams and audio decoder
	streams, decoder, err := getStreamsAndAudioDecoder(file)
	if err != nil {
		fmt.Println("getStreamsAndAudioDecoder error:", err)
		return
	}
	defer decoder.Close()

	// read packets one by one
	err = readPackets(file, streams, decoder)
	if err != nil {
		fmt.Println("Error:", err)
		return
	}
}
