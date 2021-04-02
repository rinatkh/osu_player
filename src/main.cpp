#include "screener.h"
#include "analysis.h"
#include "clicker.h"

#include <thread>
#include <X11/Xlib.h>

#include <cstdio>
#include <unistd.h>

auto func = [](Display *display, int x, int y)
{
    sleep(3);
    move_to(display, x, y);
    SendClick(1, true);   // press lmb
    SendClick(1, false);  // release lmb
};


int main() {

    int starting = 3;
    int x = 0;
    int y = 0;
    int l = 20;
    XColor color;

    // Open X isplay
    Display *display = XOpenDisplay(0);
    if (display == nullptr) {
        fprintf(stderr, "Can't open display!\n");
        return -1;
    }

    Window root = DefaultRootWindow(display);

    // Wait 3 seconds to start
    printf("Starting in   ");
    fflush(stdout);
    while (starting > 0) {
        printf("\b\b\b %d...", starting);
        fflush(stdout);
        sleep(1);
        starting--;
    }
    printf("\n");
    vector<Point> usedCenterCoordinates;

    while(true) {
        ScreenShot screen(0, 0, 1920, 1080);
        cv::Mat img;

        for (uint i;; ++i) {
            double start = clock();

            screen(img);

            if (!(i & 0b111111)) {
                printf("fps %4.f  spf %.4f\n", FPS(start), 1 / FPS(start));
            }
            break;

        }


        vector<Point> centerCoordinates;
        analysis(img, &centerCoordinates);
        //cout << centerCoordinates.size() << endl;
        for (int k = 0; k < centerCoordinates.size(); k++ ) {
            std::cout << "vhod " << centerCoordinates[k].x << " " << centerCoordinates[k].y << std::endl;
            std::cout << "   " << usedCenterCoordinates.size() << std::endl;
            std::thread thread(func, display, centerCoordinates[k].x, centerCoordinates[k].y);
            thread.join();
            for (int j = 0; j < usedCenterCoordinates.size(); j++) {
                if (centerCoordinates[k] == usedCenterCoordinates[j]) {
                    std::cout << "delete " << centerCoordinates[j].x << " " << centerCoordinates[j].y;
                    centerCoordinates.erase(centerCoordinates.begin() + k);
                    usedCenterCoordinates.erase(usedCenterCoordinates.begin() + j);
                }
            }
        }
        //move_to(display, centerCoordinates[0].x, centerCoordinates[0].y);
        usedCenterCoordinates.clear();
        for (int j = 0; j < centerCoordinates.size(); j++) {
            Point temp = centerCoordinates[j];
            usedCenterCoordinates.push_back(temp);
            std::cout << "new " << usedCenterCoordinates[j].x << " " << usedCenterCoordinates[j].y;
        }
        l--;
        sleep(1);
    }

    /*for (size_t i = 0; i < centerCoordinates.size(); i++) {
        std::cout << "Coordinates: " << i << centerCoordinates[i] << std::endl;
        sleep(1);
        move_to(display, centerCoordinates[i].x, centerCoordinates[i].y);
    }

    namedWindow("Hough Circle Transform Demo", WINDOW_AUTOSIZE);
    imshow("Hough Circle Transform Demo", img);
    waitKey(0);*/

    //cv::imshow("img", img);
    //cv::waitKey(0);

    // Start
    //while (i) {
        //coords (display, &x, &y);
        //printf("%d %d\n", x, y);
        //pixel_color(display, x, y, &color);
        //printf("%lu %lu %lu\n", color.red, color.green, color.blue);
        //printf("%lu \n", color.pixel);
        //move(display, 10, 10);
        //move_to(display, x, y);
        //click (display, Button1);
        //SendClick(1, true);   // press lmb
        //move(display, 10, 10);
        //SendClick(1, false);  // release lmb
        //mouseClick(Button1);
        //press_move(display, 0, 60, Button1);
        //sleep(1);
        //i--;
    //}

    // Close X display and exit
    XCloseDisplay(display);

    return 0;
}

