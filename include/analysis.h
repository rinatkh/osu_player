#ifndef ANALYSIS_H
#define ANALYSIS_H

#include <iostream>
#include <stdio.h>
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
using namespace cv;
using namespace std;

void analysis(Mat src, std::vector<Point> *centerCoordinates);

#endif  // ANALYSIS_H
