package main

import (
	"errors"
	"fmt"
	"image"
	"io"
	"os"

	"github.com/hajimehoshi/go-mp3"
	"github.com/hajimehoshi/oto"
	"gocv.io/x/gocv"
)

func runAudio(filename string) error {
	f, err := os.Open(filename)
	if err != nil {
		return err
	}
	defer f.Close()

	d, err := mp3.NewDecoder(f)
	if err != nil {
		return err
	}
	defer d.Close()

	p, err := oto.NewPlayer(d.SampleRate(), 2, 2, 8192)
	if err != nil {
		return err
	}
	defer p.Close()

	fmt.Printf("Length: %d[bytes]\n", d.Length())

	if _, err := io.Copy(p, d); err != nil {
		return err
	}
	return nil
}

func runVideo(filename string) error {
	video, err := gocv.VideoCaptureFile(filename)
	if err != nil {
		fmt.Printf("Error opening video capture file: %s\n", filename)
		return err
	}
	defer video.Close()

	window := gocv.NewWindow("Track Window")
	defer window.Close()

	img := gocv.NewMat()
	defer img.Close()

	imgFG := gocv.NewMat()
	defer imgFG.Close()

	imgCleaned := gocv.NewMat()
	defer imgCleaned.Close()

	mog2 := gocv.NewBackgroundSubtractorMOG2()
	defer mog2.Close()

	for {
		if ok := video.Read(&img); !ok {
			fmt.Printf("Error cannot read file %s\n", filename)
			return errors.New("cannot read video file")
		}
		if img.Empty() {
			continue
		}

		// clean frame by removing background & eroding to eliminate artifacts
		mog2.Apply(img, &imgFG)
		kernel := gocv.GetStructuringElement(gocv.MorphRect, image.Pt(3, 3))
		gocv.Erode(imgFG, &imgCleaned, kernel)
		kernel.Close()

		// show frame
		window.IMShow(img)
		if window.WaitKey(1) >= 0 {
			break
		}
	}

	return nil
}

func main() {
	if len(os.Args) < 3 {
		fmt.Println("How to run:\n\tmain [videoFile] [audioFile]")
		return
	}
	fmt.Println(os.Args[0])
	videoFilename := os.Args[1]
	audioFilename := os.Args[2]

	go runAudio(audioFilename)
	runVideo(videoFilename)
}
