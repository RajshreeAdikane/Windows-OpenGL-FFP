#include<stdio.h>
#include<stdlib.h>
#include<memory.h>

//xlib header files
#include<X11/Xlib.h>
#include<X11/Xutil.h>
#include<X11/XKBlib.h>

#define _USE_MATH_DEFINES 1 
#include <math.h>

//OPENGL RELATED HEADER FILES
#include<GL/gl.h>
#include<GL/glx.h>
#include <GL/glu.h>

//macros
#define WIN_WIDTH 800
#define WIN_HEIGHT 600

//GLOBAL VARIABLES
Display *gpDisplay = NULL;
XVisualInfo *visualInfo = NULL;
Window window;
Colormap colormap;
Bool bFullScreen = False;
Bool activeWindow = False;
GLXContext glxContext = NULL;

//variables related to the log file
char gszLogFileName[] = "Log.txt";
FILE *gpFile = NULL;

Bool gbCircle = False;
Bool gbGraph = False;
Bool gbTriangle = False;
Bool gbSquare = False;

int main(void)
{
    //function declarations
    void toggleFullSCreen(void);
    int initialize(void);
    void resize(int, int);
    void display(void);
    void update(void);
    void uninitialize(void);

    // variable declarations
    int defaultScreen;
    int defaultDepth;
    XSetWindowAttributes windowAtrributes;
    Atom windowManagerDeleteAtom;
    XEvent event;
    Screen *screen = NULL;
    int screenWidth, screenHeight;
    KeySym keySym;
    char keys[26];
    int frameBufferAttributes[] = {GLX_DOUBLEBUFFER, True, 
                                  GLX_RGBA, True,
                                  GLX_RED_SIZE, 8, 
                                  GLX_GREEN_SIZE, 8, 
                                  GLX_BLUE_SIZE, 8, 
                                  GLX_ALPHA_SIZE, 8, 
                                  GLX_DEPTH_SIZE, 24,
                                  None};
    Bool bDone = False;

    // create log file
    gpFile = fopen(gszLogFileName, "w");
    if(gpFile == NULL)
    {
        printf("Log file creation failed");
        exit(0);
    }
    else
    {
        fprintf(gpFile, "Program Started Successfully\n");
    }

    //code
    gpDisplay = XOpenDisplay(NULL);
    if(gpDisplay == NULL)
    {
        printf("Xopen display failed !!");
        uninitialize();
        exit(EXIT_FAILURE);
    }

    //create the default screen object
    defaultScreen = XDefaultScreen(gpDisplay);

    //get default depth
    defaultDepth = XDefaultDepth(gpDisplay, defaultScreen);

    visualInfo = glXChooseVisual(gpDisplay, defaultScreen, frameBufferAttributes);

    if(visualInfo == NULL)
    {
        printf("glxChooseVisual failed");
        uninitialize();
        exit(EXIT_FAILURE);
    }

    //set window attributes
    memset((void*)&windowAtrributes, 0, sizeof(XSetWindowAttributes));

    windowAtrributes.border_pixel = 0;
    windowAtrributes.background_pixmap = 0;
    windowAtrributes.background_pixel = XBlackPixel(gpDisplay, visualInfo->screen);
    windowAtrributes.colormap = XCreateColormap(gpDisplay,
                                                XRootWindow(gpDisplay, visualInfo->screen),
                                                visualInfo->visual,
                                                AllocNone
                                                );
    colormap = windowAtrributes.colormap;
    windowAtrributes.event_mask = KeyPressMask | ButtonPressMask | FocusChangeMask | StructureNotifyMask | ExposureMask;

    //create window
    window = XCreateWindow(gpDisplay,
                            XRootWindow(gpDisplay, visualInfo->screen),
                            0,
                            0,
                            WIN_WIDTH,
                            WIN_HEIGHT,
                            0,
                            visualInfo->depth,
                            InputOutput,
                            visualInfo->visual,
                            CWBorderPixel | CWBackPixel | CWEventMask | CWColormap,
                            &windowAtrributes
    );

    if(!window)
    {
        printf("WINDOW failed");
        uninitialize();
        exit(EXIT_FAILURE);
    }

    //create atom for windoe manager to destroy window
    windowManagerDeleteAtom = XInternAtom(gpDisplay, "WM_DELETE_WINDOW", True);
    XSetWMProtocols(gpDisplay, window, &windowManagerDeleteAtom, 1);

    //set window title
    XStoreName(gpDisplay, window, "RAJASHREE ADIKANE: XWINDOWS");

    //map window to show it
    XMapWindow(gpDisplay, window);

    //centering of window
    screen = XScreenOfDisplay(gpDisplay, visualInfo->screen);
    screenWidth = XWidthOfScreen(screen);
    screenHeight = XHeightOfScreen(screen);
    XMoveWindow(gpDisplay, window, screenWidth/2-WIN_WIDTH/2, screenHeight/2-WIN_HEIGHT/2);

    //initialize
    int iResult = initialize();
    if(iResult != 0)
    {
        uninitialize();
        exit(EXIT_FAILURE);
    }

    //game loop
    while(bDone == False)
    {
        while(XPending(gpDisplay))
        {
            XNextEvent(gpDisplay, &event);
            switch(event.type)
            {
                case MapNotify:
                break;

                case FocusIn:
                activeWindow = True;
                break;

                case FocusOut:
                activeWindow = False;
                break;

                case ConfigureNotify:
                resize(event.xconfigure.width, event.xconfigure.height);
                break;

                case KeyPress:
                keySym = XkbKeycodeToKeysym(gpDisplay, event.xkey.keycode, 0, 0);
                switch(keySym)
                {
                    case XK_Escape:
                    bDone = True;
                    break;

                    default:
                    break;
                }
                //for alphabatic keypress
                XLookupString(&event.xkey, keys, sizeof(keys), NULL, NULL);
                switch (keys[0])
                {
                    case 'g': case 'G':
                        gbGraph = !gbGraph; // Toggle graph visibility
                        break;

                    case 'c': case 'C':
                        gbCircle = !gbCircle; // Toggle circle visibility
                        break;

                    case 't': case 'T':
                        gbTriangle = !gbTriangle; // Toggle triangle visibility
                        break;

                    case 's': case 'S':
                        gbSquare = !gbSquare; // Toggle square visibility
                        break;

                    case 'f': case 'F':
                        toggleFullSCreen();
                        bFullScreen = !bFullScreen;
                        break;
                    case 'l': case 'L':
                        gbGraph = False;
                        gbCircle = False;
                        gbTriangle = False;
                        gbSquare = False;
                        break;

                    default:
                    break;
                }
                break;

                case ButtonPress:
                break;

                case Expose:
                break;

                case ClientMessage:
                    if (event.xclient.data.l[0] == windowManagerDeleteAtom)
                        bDone = True;
                break;

                default:
                break;
            }
        }
        //rendering
        if(activeWindow == True)
        {
            display();
            update();
        }
    }

    uninitialize();
    return 0;
}

void toggleFullSCreen(void)
{
    Atom windowManagerState = XInternAtom(gpDisplay, "_NET_WM_STATE", False);
    Atom windowManagerFullScreen = XInternAtom(gpDisplay, "_NET_WM_STATE_FULLSCREEN", False);

    XEvent xev;
    memset(&xev, 0, sizeof(xev));
    
    xev.type = ClientMessage;
    xev.xclient.window = window;
    xev.xclient.message_type = windowManagerState;
    xev.xclient.format = 32;
    xev.xclient.data.l[0] = bFullScreen ? 0 : 1; // 0 = off, 1 = on
    xev.xclient.data.l[1] = windowManagerFullScreen;
    xev.xclient.data.l[2] = 0;

    XSendEvent(gpDisplay,
               XRootWindow(gpDisplay, visualInfo->screen),
               False,
               SubstructureRedirectMask | SubstructureNotifyMask,
               &xev);
}

int initialize(void)
{
    glxContext = glXCreateContext(gpDisplay, visualInfo, NULL, GL_TRUE);
    if(glxContext == NULL)
    {
        fprintf(gpFile, "glxcontex failed!!!!\n");
        return -1;
    }

    if (!glXMakeCurrent(gpDisplay, window, glxContext)) 
    {
        fprintf(gpFile, "glXMakeCurrent failed\n");
        return -1;
    }

    //clear color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // Enable depth testing
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    return 0;
}

void resize(int width, int height)
{
    if (height == 0)
        height = 1;

    glViewport(0, 0, (GLsizei)width, (GLsizei)height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);
}

void DrawGraph(void)
{
    if (gbGraph)
    {
        glLineWidth(1.0f);
        glBegin(GL_LINES);

        for (int i = -40; i <= 40; i++) {
            float y = i * 0.05f;
            float x = i * 0.05f;

            // Horizontal grid lines
            glColor3f((i == 0) ? 1.0f : 0.0f, 0.0f, (i == 0) ? 0.0f : 1.0f);
            glVertex3f(-2.0f, y, 0.0f);
            glVertex3f(2.0f, y, 0.0f);

            // Vertical grid lines
            glColor3f(0.0f, (i == 0) ? 1.0f : 0.0f, (i == 0) ? 0.0f : 1.0f);
            glVertex3f(x, -2.0f, 0.0f);
            glVertex3f(x, 2.0f, 0.0f);
        }

        glEnd();
    }
}

void DrawCircle(void)
{
    if (gbCircle) { 
        const int num_segments = 100;
        const float radius = 0.5f;

        glLineWidth(2.0f);
        glBegin(GL_LINE_LOOP);
        glColor3f(1.0f, 1.0f, 0.0f);
        for (int i = 0; i < num_segments; ++i) {
            float theta = 2.0f * M_PI * i / num_segments;
            glVertex2f(radius * cosf(theta), radius * sinf(theta));
        }
        glEnd();
    }
}

void Triangle(void)
{
    if (gbTriangle)
    {
        glLineWidth(2.0f);
        glBegin(GL_LINE_LOOP);
        glColor3f(1.0f, 1.0f, 0.0f);

        glVertex2f(0.0f, 0.5f);
        glVertex2f(-0.5f, -0.5f);
        glVertex2f(0.5f, -0.5f);
        glEnd();
    }
}

void Square(void)
{
    if (gbSquare)
    {
        glLineWidth(2.0f);
        glBegin(GL_LINE_LOOP);
        glColor3f(1.0f, 1.0f, 0.0f);

        glVertex3f(-0.5f, 0.5f, 0.0f);
        glVertex3f(0.5f, 0.5f, 0.0f);
        glVertex3f(0.5f, -0.5f, 0.0f);
        glVertex3f(-0.5f, -0.5f, 0.0f);
        glEnd();
    }
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -3.0f);

    DrawGraph();
    DrawCircle();
    Triangle();
    Square();

    glXSwapBuffers(gpDisplay, window);
}

void update(void)
{
    // Animation or other updates can go here
}

void uninitialize(void)
{
    if(glxContext)
    {
        if(glXGetCurrentContext() == glxContext)
        {
            glXMakeCurrent(gpDisplay, 0, 0);
        }
        glXDestroyContext(gpDisplay, glxContext);
        glxContext = NULL;
    }

    if(window)
    {
        XDestroyWindow(gpDisplay, window);
    }

    if(colormap)
    {
        XFreeColormap(gpDisplay, colormap);
    }

    if(visualInfo)
    {
        free(visualInfo);
        visualInfo = NULL;
    }

    if(gpDisplay)
    {
        XCloseDisplay(gpDisplay);
        gpDisplay = NULL;
    }

    if(gpFile)
    {
        fprintf(gpFile, "Program terminated Successfully\n");
        fclose(gpFile);
        gpFile = NULL;
    }
}