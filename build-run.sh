#!/bin/bash

cc playground/remuxing.c -lavformat && ./a.out data/daft-punk-short.mp4 out/out.mp4
