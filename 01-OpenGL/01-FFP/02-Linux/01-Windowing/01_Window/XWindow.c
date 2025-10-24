// stadard header files
#include <stdio.h> // for printf
#include <stdlib.h> // for exit
#include <memory.h> // for memset

// XLib related header files
#include <X11/Xlib.h> // just like for xlib apis windows.h
#include <X11/Xutil.h> // 

// macros
#define WIN_WIDTH 800
#define WIN_HEIGHT 600

// global variables
Display *gpDisplay = NULL; // it's structure which is midiator of xserver and xclient 
XVisualInfo visualInfo; // it's like of Divice Context not like Handle to device context
Window window;          // its a object of window
Colormap colormap;      // in graphics card memory color aranged in certain way its called Colormap

int main(void)
{
    // function declarations
    void uninitialize(void);

    // variables declarations
    int defaultScreen;
    int defaultDepth;
    Status status;
    XSetWindowAttributes windowAttributes;
    Atom windowManagerDeleteAtom;
    XEvent event;

    // code
    // Step-1 : Open the connection between the XServer
    gpDisplay = XOpenDisplay(NULL); // NULL means i didn't provide my display name take display number instead of that
    if(gpDisplay == NULL)
    {
        printf("XOpenDisplay() : failed to connect with the XServer\n");
        uninitialize();
        exit (EXIT_FAILURE);
    }
    // Step-2 : Create the default screen object 
    defaultScreen = XDefaultScreen(gpDisplay); 

    // step-3 : Get default depth
    defaultDepth = XDefaultDepth(gpDisplay, defaultScreen);

    // step-4 get visual info
    memset((void *)&visualInfo, 0, sizeof(XVisualInfo));
    status = XMatchVisualInfo(gpDisplay, defaultScreen, defaultDepth, TrueColor, &visualInfo);
    if(status == 0)
    {
        printf("XMatchVisualInfo() : failed\n");
        uninitialize();
        exit(EXIT_FAILURE);
    }
    // step-5 : Set Window atributes
    memset(&windowAttributes, 0, sizeof(XSetWindowAttributes));
    windowAttributes.border_pixel = 0;
    windowAttributes.background_pixmap = 0;
    windowAttributes.background_pixel = XBlackPixel(gpDisplay, visualInfo.screen);// we have two default screen visualinfo.screen and defaultScreen
    windowAttributes.colormap = XCreateColormap(gpDisplay, 
                                                XRootWindow(gpDisplay, visualInfo.screen), visualInfo.visual, AllocNone);

    // color map assign to global colorMap
    colormap = windowAttributes.colormap;

    window = XCreateWindow(gpDisplay, XRootWindow(gpDisplay, visualInfo.screen),
                            0,
                            0,
                            WIN_WIDTH,
                            WIN_HEIGHT,
                            0,
                            visualInfo.depth,
                            InputOutput,
                            visualInfo.visual,
                            CWBorderPixel | CWBackPixel | CWEventMask | CWColormap,
                            &windowAttributes);

    if(!window)
    {
        printf("XCreateWindow() : Failed\n");
        uninitialize();
        exit(EXIT_FAILURE);
    }

    // Create atom for wondow manager to distroy the window
    windowManagerDeleteAtom = XInternAtom(gpDisplay, "WM_DELETE_WINDOW", True);

    XSetWMProtocols(gpDisplay, window, &windowManagerDeleteAtom, 1);

    // set window title
    XStoreName(gpDisplay, window, "RAJASHREE ADIKANE: XWindow");

    // map the window to show it
    XMapWindow(gpDisplay, window);

    // Message Loop
    while(1)
    {
        XNextEvent(gpDisplay, &event);
        switch(event.type)
        {
            case 33:
                uninitialize();
                exit(EXIT_SUCCESS);
            break;
            default:
                break;
        }
    }
    uninitialize();

    return (0);
}

void uninitialize(void)
{
    //code
    if(window)
    {
        XDestroyWindow(gpDisplay, window);
    }
    if(colormap)
    {
        XFreeColormap(gpDisplay, colormap);
    }
    if(gpDisplay)
    {
        XCloseDisplay(gpDisplay);
        gpDisplay = NULL;
    }
}
