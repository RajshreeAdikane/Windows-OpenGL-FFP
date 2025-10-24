#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/XKBlib.h>

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

Display *gpDisplay = NULL;
Window window;
Colormap colormap;
XVisualInfo visualInfo;
Bool bFullScreen = False;
GC gc;
XGCValues gcValues;
XFontStruct *PFontStruct = NULL;

Screen *screen = NULL;
int screenWidth, screenHeight;

int winWidth = WIN_WIDTH;
int winHeight = WIN_HEIGHT;

char str[] = "Hello World";

int main(void)
{
    //function declarations
    void uninitialize(void);
    void toggleFullScreen(void);

    //varibale declaration
    int defaultScreen;
    int defaultDepth;
    Status status;
    XSetWindowAttributes windowAttributes;
    Atom windowManagerDeleteAtom;
    XEvent event;
    
    XColor color;
    int strLen = strlen(str);
    int strWidth, fontHeight, x, y;

    gpDisplay = XOpenDisplay(NULL);
    if (gpDisplay == NULL)
    {
        printf("Failed to open X display.\n");
        exit(EXIT_FAILURE);
    }

    defaultScreen = XDefaultScreen(gpDisplay);
    defaultDepth = XDefaultDepth(gpDisplay, defaultScreen);

    status = XMatchVisualInfo(gpDisplay, defaultScreen, defaultDepth, TrueColor, &visualInfo);
    if (!status)
    {
        printf("No matching visual info.\n");
        uninitialize();
        exit(EXIT_FAILURE);
    }

    memset(&windowAttributes, 0, sizeof(XSetWindowAttributes));
    windowAttributes.border_pixel = 0;
    windowAttributes.background_pixel = BlackPixel(gpDisplay, defaultScreen);
    windowAttributes.colormap = XCreateColormap(gpDisplay, RootWindow(gpDisplay, defaultScreen), visualInfo.visual, AllocNone);
    colormap = windowAttributes.colormap;
    windowAttributes.event_mask = ExposureMask | KeyPressMask | StructureNotifyMask;

    window = XCreateWindow(gpDisplay,
                           RootWindow(gpDisplay, defaultScreen),
                           0, 0, WIN_WIDTH, WIN_HEIGHT,
                           0,
                           visualInfo.depth,
                           InputOutput,
                           visualInfo.visual,
                           CWBorderPixel | CWBackPixel | CWColormap | CWEventMask,
                           &windowAttributes);

    if (!window)
    {
        printf("Failed to create window.\n");
        uninitialize();
        exit(EXIT_FAILURE);
    }

    windowManagerDeleteAtom = XInternAtom(gpDisplay, "WM_DELETE_WINDOW", False);
    XSetWMProtocols(gpDisplay, window, &windowManagerDeleteAtom, 1);

    XStoreName(gpDisplay, window, "Hello World XWindow");
    XMapWindow(gpDisplay, window);

    // Load font once here
    PFontStruct = XLoadQueryFont(gpDisplay, "fixed");
    if (!PFontStruct)
    {
        printf("Failed to load font.\n");
        uninitialize();
        exit(EXIT_FAILURE);
    }

    gc = XCreateGC(gpDisplay, window, 0, &gcValues);
    XSetFont(gpDisplay, gc, PFontStruct->fid);

    while (1)
    {
        XNextEvent(gpDisplay, &event);
        switch (event.type)
        {
            case Expose:
                // Get window width/height from event or use global
                winWidth = event.xexpose.width;
                winHeight = event.xexpose.height;

                if (!XAllocNamedColor(gpDisplay, colormap, "green", &color, &color))
                {
                    printf("Failed to allocate color.\n");
                    color.pixel = WhitePixel(gpDisplay, defaultScreen);
                }

                XSetForeground(gpDisplay, gc, color.pixel);

                strWidth = XTextWidth(PFontStruct, str, strLen);
                fontHeight = PFontStruct->ascent + PFontStruct->descent;
                x = (winWidth - strWidth) / 2;
                y = (winHeight + fontHeight) / 2;

                XClearWindow(gpDisplay, window); // Clear before drawing
                XDrawString(gpDisplay, window, gc, x, y, str, strLen);
                break;

            case KeyPress:
            {
                KeySym keysym = XkbKeycodeToKeysym(gpDisplay, event.xkey.keycode, 0, 0);
                if (keysym == XK_Escape)
                {
                    uninitialize();
                    exit(0);
                }
                break;
            }

            case ClientMessage:
                if ((Atom)event.xclient.data.l[0] == windowManagerDeleteAtom)
                {
                    uninitialize();
                    exit(0);
                }
                break;

            case ConfigureNotify:
                winWidth = event.xconfigure.width;
                winHeight = event.xconfigure.height;
                break;

            default:
                break;
        }
    }

    return 0;
}

void uninitialize(void)
{
    if (gc)
    {
        XFreeGC(gpDisplay, gc);
        gc = 0;
    }
    if (PFontStruct)
    {
        XUnloadFont(gpDisplay, PFontStruct->fid);
        PFontStruct = NULL;
    }
    if (window)
    {
        XDestroyWindow(gpDisplay, window);
        window = 0;
    }
    if (colormap)
    {
        XFreeColormap(gpDisplay, colormap);
        colormap = 0;
    }
    if (gpDisplay)
    {
        XCloseDisplay(gpDisplay);
        gpDisplay = NULL;
    }
}
