#ifndef CLICKER_H
#define CLICKER_H

#include <cstdio>
#include <cstring>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/extensions/XTest.h>
#include <unistd.h>

//Clicker
void click(Display *display, int button);
//Clicker wia FakeClicks (for all windows)
void SendClick(int button, Bool down);
//Clicker prototip click
void mouseClick(int button);
//Get coords of cursor
void coords(Display *display, int *x, int *y);
//Move cursor relative to current position (curx+x;cury+y)
void move(Display *display, int x, int y);
//Move cursor relative from absolute zero point (0+x;0+y)
void move_to(Display *display, int x, int y);
//Get pixel colour at x;y *EXTRA FUNCTION*
void pixel_color(Display *display, int x, int y, XColor *color);
//Pressed cursor movement to x;y (curx+x;cury+y)
void press_move(Display *display, int x, int y, int button);

#endif  // CLICKER_H

