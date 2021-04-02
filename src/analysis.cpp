#include "analysis.h"

void analysis(Mat src, std::vector<Point> *centerCoordinates) {
    Mat gray;
    // resize(src,src,Size(640,480));
    cvtColor(src, gray, COLOR_BGR2GRAY);
    // resize(src, src, Size(640,480)); (question to srceen)
    // Reduce the noise so we avoid false circle detection
    GaussianBlur(gray, gray, Size(9, 9), 2, 2);
    std::vector<Vec3f> circles;
    // Apply the Hough Transform to find the circles
    HoughCircles(gray, circles, CV_HOUGH_GRADIENT, 1, 30, 200, 50, 0, 0);
    // Draw the circles detected
    for(size_t i = 0; i < circles.size(); i++) {
        Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
        int radius = cvRound(circles[i][2]);
        circle(src, center, 3, Scalar(0,255,0), -1, 8, 0);// circle center
        circle(src, center, radius, Scalar(0,0,255), 3, 8, 0);// circle outline
        centerCoordinates->push_back(center);
        //cout << "center : " << center << "\nradius : " << radius << endl;

    }
}
