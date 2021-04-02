#ifndef SCREENER_H
#define SCREENER_H

#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include <X11/extensions/XShm.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include <cstdio>
#include <cstring>

#include <opencv2/opencv.hpp>  // This includes most headers!

#include <ctime>
#define FPS(start) (CLOCKS_PER_SEC / (clock()-start))

struct ScreenShot {
    ScreenShot(uint x, uint y, uint width, uint height);

    void operator() (cv::Mat& cv_img);

    ~ScreenShot();

    Display* display;
    Window root;
    XWindowAttributes window_attributes;
    Screen* screen;
    XImage* ximg;
    XShmSegmentInfo shminfo;

    int x, y, width, height;

    bool init;
};
#endif  // SCREENER_H
