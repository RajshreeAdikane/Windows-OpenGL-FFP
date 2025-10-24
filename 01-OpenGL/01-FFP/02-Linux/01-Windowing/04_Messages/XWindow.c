// stadard header files
#include <stdio.h> // for printf
#include <stdlib.h> // for exit
#include <memory.h> // for memset

// XLib related header files
#include <X11/Xlib.h> // just like for xlib apis windows.h
#include <X11/Xutil.h> // 
#include <X11/XKBlib.h>

// macros
#define WIN_WIDTH 800
#define WIN_HEIGHT 600

// global variables
Display *gpDisplay= NULL; // it's structure which is midiator of xserver and xclient 
XVisualInfo visualInfo; // it's like of Divice Context not like Handle to device context
Window window;          // its a object of window
Colormap colormap;      // in graphics card memory color aranged in certain way its called Colormap
Bool bFullScreen = False;


Screen *screen = NULL;
int screenWidth, screenHeight;


int main(void)
{
    // function declaration
    void uninitialize(void);

    // variable declarations
    int defaultScreen;
    int defaultDepth;
    Status status;
    XSetWindowAttributes windowAttributes;
    Atom windowManagerDeleteAtom;
    XEvent event;

    Screen *screen = NULL;
    int screenWidth, screenHeight;


    // code
    
    // open the connection with the xserver
    gpDisplay= XOpenDisplay(NULL); // first xlib API, client server sobt connection open krto
    if(gpDisplay== NULL)
    {
        printf("XOpenDisplay() failed to connect with the xserver..\n");
        uninitialize();
        exit(EXIT_FAILURE);
    }

    // create the default screen object
    defaultScreen = XDefaultScreen(gpDisplay); // open kelelya display la vichart, xserver ani xclient mdhli ji default screen ahe ti return kr ani tyacha no mla de
    
    // get default depth
    defaultDepth = XDefaultDepth(gpDisplay, defaultScreen); // 

    // get visual info
    memset((void*)&visualInfo, 0, sizeof(XVisualInfo));
    status = XMatchVisualInfo(gpDisplay, defaultScreen, defaultDepth, TrueColor, &visualInfo); // true color ya visual class la match krnara visual info majhya rikamya visual info mdhye bhrun de
    if(status == 0)
    {
        printf("XMatchVisualInfo() failed..\n");
        uninitialize();
        exit(EXIT_FAILURE);
    }
    
    //  set window attributes
    memset((void*)&windowAttributes, 0, sizeof(XSetWindowAttributes));
    windowAttributes.border_pixel = 0; // default border pixel gheil
    windowAttributes.background_pixmap = 0;
    windowAttributes.background_pixel = XWhitePixel(gpDisplay, visualInfo.screen); // black color denyasathi xlib cha API vaprl
    windowAttributes.colormap = XCreateColormap(gpDisplay, 
                                                XRootWindow(gpDisplay, visualInfo.screen), 
                                                visualInfo.visual, AllocNone);

    windowAttributes.event_mask =   KeyPressMask | ButtonPressMask | FocusChangeMask | StructureNotifyMask | ExposureMask;
                                               

    colormap = windowAttributes.colormap;

    // create the window
    window = XCreateWindow( gpDisplay,
                            XRootWindow(gpDisplay, visualInfo.screen),
                            0,
                            0,
                            WIN_WIDTH,
                            WIN_HEIGHT,
                            0,
                            visualInfo.depth,
                            InputOutput, 
                            visualInfo.visual,
                            CWBorderPixel | CWBackPixel |  CWEventMask | CWColormap,
                            &windowAttributes    
                        );
    if(!window)
    {
        printf("xwindow failed.\n");
        exit(EXIT_FAILURE);
    }

    // create atom for window manager to destroy the window
    windowManagerDeleteAtom = XInternAtom(gpDisplay, "WM_DELETE_WINDOW", True);

    XSetWMProtocols(gpDisplay, window, &windowManagerDeleteAtom, 1);
    
    // set window title
    XStoreName(gpDisplay, window, "RAJASHREE ADIKANE: XWindow");
    
    // Map the window to show it
    XMapWindow(gpDisplay, window);

    // centering of window
    screen = XScreenOfDisplay(gpDisplay, visualInfo.screen);

    // changing x&y in cw_usedefault in win32 will not work here because the initial pos of the window is governed by window manager like GNOME, KDE, PLASMA
    // so let the window manager decide the position, later we will center it by using XMoveWindow() xlib api
    screenWidth = XWidthOfScreen(screen);
    screenHeight  = XHeightOfScreen(screen);
    
    XMoveWindow(gpDisplay, window, (screenWidth / 2) - (WIN_WIDTH / 2), (screenHeight / 2) - (WIN_HEIGHT / 2));
    

    // message loop
    while(1)
    {
        XNextEvent(gpDisplay, &event);
        switch(event.type)
        {
            case MapNotify:
                printf("Map Notify Event is Received\n");
                break;

            case FocusIn:
                printf("WindowsGotFocused\n");
                break;

            case FocusOut:
               printf("Window Lost Focus\n");
               break;
               
            case ConfigureNotify:
                printf("Window is resized\n");
                break;
            
            case KeyPress:
               printf("Key is pressed\n");
               break;

            case ButtonPress:
                switch(event.xbutton.button)
                {
                    case 1:
                        printf("Left mouse button is clicked\n");    
                        break;
                    
                    case 2:
                        printf("Middle Mouse Button Is Clicked\n");
                        break;

                    case 3:
                        printf("Right Mouse Button Is Clicked\n");
                        break;

                    default:
                        break;
                    
                }
                break;
            
            case Expose:
                break;                
              
            // 33 mhnje windows mdhla WM_DESTROY aahe, window manager neutral msg no aahe haa
            case 33:
                uninitialize();
                exit(EXIT_SUCCESS);
                break;
        
            default:
                break;
        }

    }

    return 0;
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
        gpDisplay= NULL;
    }
}
