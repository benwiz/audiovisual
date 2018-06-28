package main

import (
	"fmt"
	"gocv.io/x/gocv"
)

func main() {
	webcam, _ := gocv.VideoCaptureDevice(0)
	window := gocv.NewWindow("Hello")
	img := gocv.NewMat()

	for {
		fmt.Println(&img)
		webcam.Read(&img)
		window.IMShow(img)
		window.WaitKey(1)
	}
}
