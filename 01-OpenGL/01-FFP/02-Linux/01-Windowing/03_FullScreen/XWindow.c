#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <stdbool.h>    

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/XKBlib.h>

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

Display *gpDisplay = NULL;
XVisualInfo *visualInfo = NULL;
Window window;
Colormap colormap;
bool bFullScreen = false;
bool bDone = false;

Screen *screen = NULL;
int screenWidth, screenHeight;

int main(void)
{
    void uninitialize(void);
    void toggleFullScreen(void);

    int defaultScreen;
    int defaultDepth;
    Status status;
    XSetWindowAttributes windowAttributes;
    Atom windowManagerDeleteAtom;
    XEvent event;

    gpDisplay = XOpenDisplay(NULL);
    if (gpDisplay == NULL)
    {
        printf("XOpenDisplay() : failed to connect with the XServer\n");
        uninitialize();
        exit(EXIT_FAILURE);
    }

    defaultScreen = XDefaultScreen(gpDisplay);
    defaultDepth = XDefaultDepth(gpDisplay, defaultScreen);

    visualInfo = (XVisualInfo *)malloc(sizeof(XVisualInfo));
    status = XMatchVisualInfo(gpDisplay, defaultScreen, defaultDepth, TrueColor, visualInfo);
    if (status == 0)
    {
        printf("XMatchVisualInfo() : failed\n");
        uninitialize();
        exit(EXIT_FAILURE);
    }

    memset(&windowAttributes, 0, sizeof(XSetWindowAttributes));
    windowAttributes.border_pixel = 0;
    windowAttributes.background_pixmap = 0;
    windowAttributes.background_pixel = XBlackPixel(gpDisplay, visualInfo->screen);
    windowAttributes.colormap = XCreateColormap(gpDisplay,
                                                XRootWindow(gpDisplay, visualInfo->screen),
                                                visualInfo->visual, AllocNone);
    colormap = windowAttributes.colormap;
    windowAttributes.event_mask = KeyPressMask | ButtonPressMask | FocusChangeMask | ExposureMask | StructureNotifyMask;

    window = XCreateWindow(gpDisplay, XRootWindow(gpDisplay, visualInfo->screen),
                           0, 0, WIN_WIDTH, WIN_HEIGHT, 0,
                           visualInfo->depth,
                           InputOutput,
                           visualInfo->visual,
                           CWBorderPixel | CWBackPixel | CWEventMask | CWColormap,
                           &windowAttributes);

    if (!window)
    {
        printf("XCreateWindow() : Failed\n");
        uninitialize();
        exit(EXIT_FAILURE);
    }

    windowManagerDeleteAtom = XInternAtom(gpDisplay, "WM_DELETE_WINDOW", True);
    XSetWMProtocols(gpDisplay, window, &windowManagerDeleteAtom, 1);

    XStoreName(gpDisplay, window, "RAJASHREE ADIKANE: XWindow");
    XMapWindow(gpDisplay, window);

    screen = XScreenOfDisplay(gpDisplay, visualInfo->screen);
    screenWidth = XWidthOfScreen(screen);
    screenHeight = XHeightOfScreen(screen);
    XMoveWindow(gpDisplay, window, screenWidth / 2 - WIN_WIDTH / 2, screenHeight / 2 - WIN_HEIGHT / 2);

    char keys[26];

    while (!bDone)
    {
        XNextEvent(gpDisplay, &event);
        switch (event.type)
        {
        case KeyPress:
        {
            KeySym keysym = XkbKeycodeToKeysym(gpDisplay, event.xkey.keycode, 0, 0);
            if (keysym == XK_Escape)
            {
                bDone = true;
            }

            XLookupString(&event.xkey, keys, sizeof(keys), NULL, NULL);
            switch (keys[0])
            {
            case 'F':
            case 'f':
                toggleFullScreen();
                bFullScreen = !bFullScreen;
                break;
            }
            break;
        }

        case ClientMessage:
            if ((Atom)event.xclient.data.l[0] == windowManagerDeleteAtom)
            {
                bDone = true;
            }
            break;
        }
    }

    uninitialize();
    return 0;
}

void toggleFullScreen(void)
{
    Atom wmState = XInternAtom(gpDisplay, "_NET_WM_STATE", False);
    Atom wmFullscreen = XInternAtom(gpDisplay, "_NET_WM_STATE_FULLSCREEN", False);

    XEvent event;
    memset(&event, 0, sizeof(event));

    event.type = ClientMessage;
    event.xclient.window = window;
    event.xclient.message_type = wmState;
    event.xclient.format = 32;
    event.xclient.data.l[0] = bFullScreen ? 0 : 1;
    event.xclient.data.l[1] = wmFullscreen;

    XSendEvent(gpDisplay,
               XRootWindow(gpDisplay, visualInfo->screen),
               False,
               SubstructureNotifyMask,
               &event);
}

void uninitialize(void)
{
    if (window)
        XDestroyWindow(gpDisplay, window);
    if (colormap)
        XFreeColormap(gpDisplay, colormap);
    if (visualInfo)
    {
        free(visualInfo);
        visualInfo = NULL;
    }
    if (gpDisplay)
    {
        XCloseDisplay(gpDisplay);
        gpDisplay = NULL;
    }
}
