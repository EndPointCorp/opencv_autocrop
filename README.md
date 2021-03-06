OpenCV autocrop
===============

This program will crop arbitrary background from input image.

Example:

Input:

![alttext](https://github.com/EndPointCorp/opencv_autocrop/blob/master/images/input.png?raw=true "")

Output:

![alttext](https://github.com/EndPointCorp/opencv_autocrop/blob/master/images/output.png?raw=true "")


Requirements
============
* opencv
  `apt-get install libopencv-highgui-dev libopencv-dev`

* compiler
  `apt-get install build-essential`

Building
===========

* set you pkg flags:

PKG_FLAGS=`pkg-config opencv --cflags --libs`

* run compilation
`g++ -o autocrop autocrop.cpp $PKG_FLAGS ; chmod +x autocrop`

Usage
=====

`autocrop <input_image_path> <output_image_path>`

Example:
`./autocrop input.png output.png`
