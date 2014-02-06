OpenCV autocrop
===============

This program will crop arbitrary background from input image.

Example:

Input:

![alttext](https://github.com/EndPointCorp/opencv_autocrop/blob/master/images/input.png "")

Output:

![alttext](https://github.com/EndPointCorp/opencv_autocrop/blob/master/images/output.png "")


Requirements
============
* opencv
  apt-get install libopencv-highgui-dev libopencv-dev

* compiler

Compilation
===========

g++ -o autocrop autocrop.cpp `pkg-config opencv --cflags --libs`
chmod +x autocrop

Usage
=====

autocrop <input_image_path> <output_image_path>

Example:
./autocrop input.png output.png
