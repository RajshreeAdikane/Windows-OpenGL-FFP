#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/XKBlib.h>

//OpenGL related Header Files
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glx.h>

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

Display *gpDisplay = NULL;
Window window;
Colormap colormap;
XVisualInfo *visualInfo = NULL;
Bool bFullScreen = False;

Bool bActiveWindow = False;

GC gc;
XGCValues gcValues;
XFontStruct *PFontStruct = NULL;

//OpenGL related Varibales
GLXContext glxContext = NULL; 

FILE *gpFile = NULL;

int main(void)
{
    // Function declarations
    int initialize(void);
    void resize(int, int);
    void display(void);
    void uninitialize(void);
    void toggleFullScreen(void);

    // Variable declarations
    int defaultScreen;
    int defaultDepth;
    Status status;
    XSetWindowAttributes windowAttributes;
    Atom windowManagerDeleteAtom;
    XEvent event;
    XColor color;
    int strWidth, fontHeight, x, y;
    Bool bDone = False;
    Bool bActiveWindow = False;

    int framebufferAttributes[] = {
        GLX_DOUBLEBUFFER, 
        GLX_RGBA,
        GLX_RED_SIZE, 8,
        GLX_GREEN_SIZE, 8,
        GLX_BLUE_SIZE, 8,
        GLX_ALPHA_SIZE, 8,
        None
    };

    // int strLen = strlen(str);  // Ensure 'str' is defined globally or locally
    gpDisplay = XOpenDisplay(NULL);
    if (gpDisplay == NULL)
    {
        fprintf(stderr, "Failed to open X display.\n");
        exit(EXIT_FAILURE);
    }

    gpFile = fopen("log.txt", "w");
    if (gpFile == NULL)
    {
        fprintf(stderr, "Log file creation failed!\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        fprintf(gpFile, "Program started successfully!\n");
    }

    defaultScreen = XDefaultScreen(gpDisplay);
    defaultDepth = XDefaultDepth(gpDisplay, defaultScreen);

    visualInfo = glXChooseVisual(gpDisplay, defaultScreen, framebufferAttributes);
    if (visualInfo == NULL)
    {
        fprintf(stderr, "glXChooseVisual failed.\n");
        uninitialize();
        exit(EXIT_FAILURE);
    }

    windowAttributes.border_pixel = 0;
    windowAttributes.background_pixel = BlackPixel(gpDisplay, defaultScreen);
    windowAttributes.colormap = XCreateColormap(gpDisplay, RootWindow(gpDisplay, defaultScreen), visualInfo->visual, AllocNone);
    colormap = windowAttributes.colormap;
    windowAttributes.event_mask = ExposureMask | KeyPressMask | StructureNotifyMask | FocusChangeMask;

    window = XCreateWindow(gpDisplay,
                           RootWindow(gpDisplay, defaultScreen),
                           0, 0, WIN_WIDTH, WIN_HEIGHT,
                           0,
                           visualInfo->depth,
                           InputOutput,
                           visualInfo->visual,
                           CWBorderPixel | CWBackPixel | CWColormap | CWEventMask,
                           &windowAttributes);

    if (!window)
    {
        fprintf(stderr, "Window creation failed.\n");
        uninitialize();
        exit(EXIT_FAILURE);
    }

    windowManagerDeleteAtom = XInternAtom(gpDisplay, "WM_DELETE_WINDOW", False);
    XSetWMProtocols(gpDisplay, window, &windowManagerDeleteAtom, 1);

    XStoreName(gpDisplay, window, "Rajashree Adikane:XWindows");
    XMapWindow(gpDisplay, window);

    PFontStruct = XLoadQueryFont(gpDisplay, "fixed");
    if (!PFontStruct)
    {
        fprintf(stderr, "Failed to load font.\n");
        uninitialize();
        exit(EXIT_FAILURE);
    }

    gc = XCreateGC(gpDisplay, window, 0, &gcValues);
    XSetFont(gpDisplay, gc, PFontStruct->fid);

    if (initialize() == -1)
    {
        uninitialize();
        exit(EXIT_FAILURE);
    }
    else
    {
        fprintf(gpFile, "Initialization succeeded.\n");
    }

    // Main loop
    while (bDone == False)
    {
        while (XPending(gpDisplay) > 0)
        {
            XNextEvent(gpDisplay, &event);
            switch (event.type)
            {
                case FocusIn:
                    bActiveWindow = True;
                    break;

                case FocusOut:
                    bActiveWindow = False;
                    break;

                case Expose:
                    break;

                case ConfigureNotify:
                    // winWidth = event.xconfigure.width;
                    // winHeight = event.xconfigure.height;
                    resize(event.xconfigure.width, event.xconfigure.height);
                    break;

                case KeyPress:
                {
                    KeySym keysym = XkbKeycodeToKeysym(gpDisplay, event.xkey.keycode, 0, 0);
                    if (keysym == XK_Escape)
                    {
                        bDone = True;
                    }
                    break;

                    
                }
                

                case ClientMessage:
                    if ((Atom)event.xclient.data.l[0] == windowManagerDeleteAtom)
                    {
                        bDone = True;
                    }
                    break;
            }
        }

        if (bActiveWindow == True)
        {
            display();          // Render your scene here
            glXSwapBuffers(gpDisplay, window);  // Swap the buffers
        }
    }

    uninitialize();
    return 0;
}


int initialize(void)
{
    // Create OpenGL Rendering Context
    glxContext = glXCreateContext(gpDisplay, visualInfo, NULL, GL_TRUE); // last param = direct rendering
    if (glxContext == NULL)
    {
        fprintf(gpFile, "glXCreateContext failed.\n");
        return -1;
    }
    else
    {
        fprintf(gpFile, "glXCreateContext succeeded.\n");
    }

    // Make the context current
    if (glXMakeCurrent(gpDisplay, window, glxContext) == False)
    {
        fprintf(gpFile, "glXMakeCurrent failed.\n");
        return -1;
    }

    // Set the clear color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Blue screen

    return 0;
}


void resize(int width, int height)
{
    //code
    if (height < 0)
	{
		height = 1;
	}
	// set the view port
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);

}

void display(void)
{
    //code
    // clear OpenGL buffers
	glClear(GL_COLOR_BUFFER_BIT);//state

    glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.0f, 0.0f);        // Red vertex
	glVertex3f(0.0f, 1.0f, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);        // Green vertex
	glVertex3f(-1.0f, -1.0f, 0.0f);

	glColor3f(0.0f, 0.0f, 1.0f);        // Blue vertex
	glVertex3f(1.0f, -1.0f, 0.0f);
	glEnd();
    
    glXSwapBuffers(gpDisplay,window);



}

void update(void)
{
    //code
}

void uninitialize(void)
{
    if (glxContext)
    {
        if (glXGetCurrentContext() == glxContext)
        {
            glXMakeCurrent(gpDisplay, None, NULL);
        }

        glXDestroyContext(gpDisplay, glxContext);
        glxContext = NULL;
    }
    if(visualInfo)
    {
        free(visualInfo);
        visualInfo = NULL;
    }
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
     if (gpFile) {
        fprintf(gpFile, "Program terminated Successfully!.\n");
        fclose(gpFile);
        gpFile = NULL;
    }

}
