#!/bin/bash

avconv -f video4linux2 -s 640x480 -i /dev/video1 -ss 0:0:5 -frames 1 E1_data/images/pic_"$1".jpg
