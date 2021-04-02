#include "clicker.h"

void SendClick(int button, Bool down) {
    Display *display = XOpenDisplay(nullptr);
    XTestFakeButtonEvent(display, button, down, CurrentTime);
    XFlush(display);
    XCloseDisplay(display);
}

void mouseClick(int button) {
    Display *display = XOpenDisplay(nullptr);

    XEvent event;
    if(display == nullptr)
    {
        fprintf(stderr, "Cannot initialize the display\n");
    }

    memset(&event, 0x00, sizeof(event));

    event.type = ButtonPress;
    event.xbutton.button = button;
    event.xbutton.same_screen = True;

    XQueryPointer(display, RootWindow(display, DefaultScreen(display)), &event.xbutton.root, &event.xbutton.window, &event.xbutton.x_root, &event.xbutton.y_root, &event.xbutton.x, &event.xbutton.y, &event.xbutton.state);

    event.xbutton.subwindow = event.xbutton.window;

    while(event.xbutton.subwindow)
    {
        event.xbutton.window = event.xbutton.subwindow;

        XQueryPointer(display, event.xbutton.window, &event.xbutton.root, &event.xbutton.subwindow, &event.xbutton.x_root, &event.xbutton.y_root, &event.xbutton.x, &event.xbutton.y, &event.xbutton.state);
    }

    if(XSendEvent(display, PointerWindow, True, 0xfff, &event) == 0) fprintf(stderr, "Error\n");

    XFlush(display);

    usleep(100000);

    event.type = ButtonRelease;
    event.xbutton.state = 0x100;

    if(XSendEvent(display, PointerWindow, True, 0xfff, &event) == 0) fprintf(stderr, "Error\n");

    XFlush(display);

    XCloseDisplay(display);
}

void click(Display *display, int button) {
    // Create and setting up the event
    XEvent event;
    memset(&event, 0, sizeof(event));
    event.xbutton.button = button;
    event.xbutton.same_screen = True;
    event.xbutton.subwindow = DefaultRootWindow(display);
    while (event.xbutton.subwindow) {
        event.xbutton.window = event.xbutton.subwindow;
        XQueryPointer(display, event.xbutton.window,
                      &event.xbutton.root, &event.xbutton.subwindow,
                      &event.xbutton.x_root, &event.xbutton.y_root,
                      &event.xbutton.x, &event.xbutton.y,
                      &event.xbutton.state);
    }
    // Press
    event.type = ButtonPress;
    if (XSendEvent(display, PointerWindow, True, ButtonPressMask, &event) == 0) {
        fprintf(stderr, "Error to send the event!\n");
    }
    XFlush(display);
    usleep(1);
    // Release
    event.type = ButtonRelease;
    if (XSendEvent(display, PointerWindow, True, ButtonReleaseMask, &event) == 0) {
        fprintf (stderr, "Error to send the event!\n");
    }
    XFlush(display);
    usleep(1);
}

void coords(Display *display, int *x, int *y) {
    XEvent event;
    XQueryPointer(display, DefaultRootWindow (display),
                  &event.xbutton.root, &event.xbutton.window,
                  &event.xbutton.x_root, &event.xbutton.y_root,
                  &event.xbutton.x, &event.xbutton.y,
                  &event.xbutton.state);
    *x = event.xbutton.x;
    *y = event.xbutton.y;
    //printf("%d %d \n", *x, *y);
}

void move(Display *display, int x, int y) {
    XWarpPointer(display, None, None, 0,0,0,0, x, y);
    XFlush(display);
    usleep(1);
}

void move_to(Display *display, int x, int y) {
    int cur_x, cur_y;
    coords(display, &cur_x, &cur_y);
    XWarpPointer(display, None, None, 0,0,0,0, -cur_x, -cur_y);
    XWarpPointer(display, None, None, 0,0,0,0, x, y);
    usleep(1);
}


void pixel_color(Display *display, int x, int y, XColor *color) {
    XImage *image;
    image = XGetImage(display, DefaultRootWindow (display), x, y, 1, 1, AllPlanes, XYPixmap);
    color->pixel = XGetPixel(image, 0, 0);
    XFree(image);
    XQueryColor(display, DefaultColormap(display, DefaultScreen(display)), color);
}

void press_move(Display *display, int x, int y, int button) {
    // Create and setting up the event
    XEvent event;
    memset(&event, 0, sizeof(event));
    event.xbutton.button = button;
    event.xbutton.same_screen = True;
    event.xbutton.subwindow = DefaultRootWindow(display);
    while (event.xbutton.subwindow) {
        event.xbutton.window = event.xbutton.subwindow;
        XQueryPointer(display, event.xbutton.window,
                      &event.xbutton.root, &event.xbutton.subwindow,
                      &event.xbutton.x_root, &event.xbutton.y_root,
                      &event.xbutton.x, &event.xbutton.y,
                      &event.xbutton.state);
    }
    // Press
    event.type = ButtonPress;
    if (XSendEvent(display, PointerWindow, True, ButtonPressMask, &event) == 0) {
        fprintf(stderr, "Error to send the event!\n");
    }
    XFlush(display);
    usleep(1);

    // Release
    event.type = ButtonRelease;
    if (XSendEvent(display, PointerWindow, True, ButtonReleaseMask, &event) == 0) {
        fprintf (stderr, "Error to send the event!\n");
    }

    event.type = ButtonPress;
    if (XSendEvent(display, PointerWindow, True, ButtonPressMask, &event) == 0) {
        fprintf(stderr, "Error to send the event!\n");
    }
    XFlush(display);
    usleep(1);

    XWarpPointer(display, None, None, 0,0,0,0, x, y);
    sleep(1);

    // Release
    event.type = ButtonRelease;
    if (XSendEvent(display, PointerWindow, True, ButtonReleaseMask, &event) == 0) {
        fprintf (stderr, "Error to send the event!\n");
    }

    XFlush(display);
    usleep(1);
}

