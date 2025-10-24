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

// #pragma comment(lib, "winmm.lib")

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

// variables for static bharat
GLfloat angle = 0.0f;


GLfloat translateX = -1.8f;


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

    // PlaySound(TEXT("sound2.wav"), NULL, SND_FILENAME | SND_ASYNC);

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
                    case 'f': case 'F':
                        toggleFullSCreen();
                        bFullScreen = !bFullScreen;
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

void LetterB(void)
{
	glPushMatrix();
	glTranslatef(translateX, 0.0f, -3.0f); 
	glScalef(0.25f, 0.25f, 0.0f); 

	// Left vertical bar 
	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.6f, 0.2f);
	glVertex3f(-0.98f, 1.0f, 0.0f);   
	glVertex3f(-0.3f, 0.557f, 0.0f); 
	glColor3f(1.0f, 1.0f, 1.0f);	
	glVertex3f(-0.3f, 0.22f, 0.0f);   
	glVertex3f(-0.98f, 0.22f, 0.0f);  
	glEnd();

	// Middle connecting part
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(-0.98f, 0.22f, 0.0f);
	glVertex3f(-0.3f, 0.22f, 0.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(-0.3f, -0.175f, 0.0f);
	glVertex3f(-0.98f, -0.175f, 0.0f);
	glEnd();

	// Lower vertical bar
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(-0.98f, -0.175f, 0.0f);
	glVertex3f(-0.3f, -0.175f, 0.0f);

	glColor3f(0.0754f, 0.563331f, 0.315f);
	glVertex3f(-0.3f, -0.595f, 0.0f);
	glVertex3f(-0.98f, -1.0f, 0.0f);

	glEnd();

	// Upper curved section
	glBegin(GL_QUADS);

	glColor3f(1.0f, 0.6f, 0.2f);
	glVertex3f(0.54f, 1.0f, 0.0f);
	glVertex3f(-0.98f, 1.0f, 0.0f);

	glColor3f(1.0f, 0.6f, 0.2f);	
	glVertex3f(-0.3f, 0.557f, 0.0f);
	glVertex3f(0.17f, 0.557f, 0.0f);
	glEnd();

	// Lower curved section
	glBegin(GL_QUADS);
	glColor3f(0.0754f, 0.563331f, 0.315f);
	glVertex3f(0.17f, -0.594f, 0.0f);
	glVertex3f(-0.3f, -0.594f, 0.0f);
	glColor3f(0.0754f, 0.563331f, 0.315f);
	glVertex3f(-0.98f, -0.99f, 0.0f);
	glVertex3f(0.54f, -0.99f, 0.0f);
	glEnd();

	// Top-right corner
	glBegin(GL_QUADS);

	glColor3f(1.0f, 0.6f, 0.2f);
	glVertex3f(0.17f, 0.567f, 0.0f);
	glVertex3f(0.54f, 1.0f, 0.0f);
	glColor3f(1.0f, 0.6f, 0.2f);
	glVertex3f(0.98f, 0.7f, 0.0f);
	glVertex3f(0.3f, 0.49f, 0.0f);
	glEnd();

	 //Top middle curve
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(0.98f, 0.7f, 0.0f);
	glVertex3f(0.98f, 0.49f, 0.0f);
	glVertex3f(0.3f, 0.3f, 0.0f);
	glVertex3f(0.98f, 0.2f, 0.0f);
	glEnd();

	 //Middle connecting part
	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.6f, 0.2f);
	glVertex3f(0.98f, 0.7f, 0.0f);
	glVertex3f(0.3f, 0.5f, 0.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(0.3f, 0.26f, 0.0f);
	glVertex3f(0.98f, 0.22f, 0.0f);
	glEnd();

	// Middle lower curve
	glBegin(GL_QUADS);
	glVertex3f(0.98f, 0.2f, 0.0f);
	glVertex3f(0.7f, 0.02f, 0.0f);
	glVertex3f(-0.1f, 0.02f, 0.0f);
	glVertex3f(0.3f, 0.3f, 0.0f);
	glEnd();

	// Lower rectangle inside B
	glBegin(GL_QUADS);
	glVertex3f(0.7f, 0.02f, 0.0f);
	glVertex3f(0.19f, 0.02f, 0.0f);
	glVertex3f(0.19f, -0.17f, 0.0f);
	glVertex3f(0.7f, -0.17f, 0.0f);
	glEnd();

	// Bottom left diagonal connection
	glBegin(GL_QUADS);
	glVertex3f(0.7f, 0.02f, 0.0f);
	glVertex3f(0.19f, -0.17f, 0.0f);
	glVertex3f(0.3f, -0.26f, 0.0f);
	glVertex3f(0.98f, -0.16f, 0.0f);
	glEnd();

	// Middle-bottom curve
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(0.98f, -0.16f, 0.0f);
	glVertex3f(0.3f, -0.26f, 0.0f);

	glColor3f(0.0754f, 0.563331f, 0.315f);
	glVertex3f(0.3f, -0.5f, 0.0f);
	glVertex3f(0.98f, -0.72f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.0754f, 0.563331f, 0.315f);
	glVertex3f(0.98f, -0.72f, 0.0f);
	glVertex3f(0.3f, -0.5f, 0.0f);
	glColor3f(0.0754f, 0.563331f, 0.315f);
	glVertex3f(0.17f, -0.595f, 0.0f);
	glVertex3f(0.54f, -0.99f, 0.0f);
	glEnd();

	// Middle bar 
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(0.19f, 0.22f, 0.0f);
	glVertex3f(-0.3f, 0.22f, 0.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(-0.3f, -0.175f, 0.0f);
	glVertex3f(0.19f, -0.175f, 0.0f);
	glEnd();

	glPopMatrix(); 
}

void LetterH(void)
{
	glPushMatrix();
	glTranslatef(translateX, 0.0f, -3.0f);
	glScalef(0.25f, 0.25f, 0.0f);

	// Left vertical bar - First half
	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.6f, 0.2f);
	glVertex3f(1.5f, 1.0f, 0.0f);
	glVertex3f(2.18f, 1.0f, 0.0f);

	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(2.18f, 0.0f, 0.0f);
	glVertex3f(1.5f, 0.0f, 0.0f);
	glEnd();

	// Left vertical bar - Second half
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(1.5f, 0.0f, 0.0f);
	glVertex3f(2.18f, 0.0f, 0.0f);

	glColor3f(0.0754f, 0.563331f, 0.315f);
	glVertex3f(2.18f, -1.0f, 0.0f);
	glVertex3f(1.5f, -1.0f, 0.0f);
	glEnd();

	// Right vertical bar - First half
	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.6f, 0.2f);
	glVertex3f(2.97f, 1.0f, 0.0f);
	glVertex3f(3.65f, 1.0f, 0.0f);

	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(3.65f, 0.0f, 0.0f);
	glVertex3f(2.97f, 0.0f, 0.0f);
	glEnd();

	// Right vertical bar - Second half
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(2.97f, 0.0f, 0.0f);
	glVertex3f(3.65f, 0.0f, 0.0f);

	glColor3f(0.0754f, 0.563331f, 0.315f);
	glVertex3f(3.65f, -1.0f, 0.0f);
	glVertex3f(2.97f, -1.0f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(2.18f, 0.3f, 0.0f); 
	glVertex3f(2.58f, 0.3f, 0.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(2.58f, -0.3f, 0.0f); 
	glVertex3f(2.18f, -0.3f, 0.0f);
	glEnd();

	// Middle bar - Second half
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(2.58f, 0.3f, 0.0f);
	glVertex3f(2.97f, 0.3f, 0.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(2.97f, -0.3f, 0.0f);
	glVertex3f(2.58f, -0.3f, 0.0f);
	glEnd();

	glPopMatrix();
}

void LetterA(void) {
	glPushMatrix();
	glTranslatef(translateX, 0.0f, -3.0f);
	glScalef(0.25f, 0.25f, 0.0f);

	glColor3f(0.5f, 0.5f, 0.5f);

	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(4.625f, 0.0f, 0.0f);	
	glVertex3f(5.351f, 0.0f, 0.0f);


	glColor3f(0.0754f, 0.563331f, 0.315f);
	glVertex3f(5.0f, -1.0f, 0.0f);
	glVertex3f(4.254f, -1.0f, 0.0f);

	glEnd();

	glBegin(GL_QUADS);
	
	glColor3f(1.0f, 0.6f, 0.2f);
	glVertex3f(5.0f, 1.0f, 0.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(5.39f, 0.11f, 0.0f);
	glVertex3f(5.351f, 0.0f, 0.0f);
	glVertex3f(4.625f, 0.0f, 0.0f);

	glColor3f(1.0f, 1.0f, 1.0f);

	glEnd();



	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.6f, 0.2f);
	glVertex3f(5.0f, 1.0f, 0.0f);
	glVertex3f(5.71f, 1.0f, 0.0f);

	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(5.39f, 0.11f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.6f, 0.2f);
	glVertex3f(5.39f, 1.0f, 0.0f);
	glVertex3f(6.25f, 1.0f, 0.0f);

	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(6.7f, 0.0f, 0.0f);
	glVertex3f(6.0f, 0.0f, 0.0f);

	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(6.0f, 0.0f, 0.0f);
	glVertex3f(6.7f, 0.0f, 0.0f);

	glColor3f(0.0754f, 0.563331f, 0.315f);
	glVertex3f(7.15f, -1.0f, 0.0f);
	glVertex3f(6.4f, -1.0f, 0.0f);

	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(5.43f, 0.22f, 0.0f);
	glVertex3f(5.28f, -0.19f, 0.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(6.07f, -0.19f, 0.0f);
	glVertex3f(5.90f, 0.22f, 0.0f);
	glEnd();


	glPopMatrix();
}

void LetterR(void) {

	glPushMatrix();
		glTranslatef(translateX - 0.03, 0.0f, -3.0f);
	glScalef(0.25f, 0.25f, 0.0f);

	glColor3f(0.5f, 0.5f, 0.5f);

	// Top Horizontal Part
	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.6f, 0.2f);
	glVertex3f(7.8f, 1.0f, 0.0f);   
	glVertex3f(8.37f, 1.0f, 0.0f);

	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(8.37f, 0.33f, 0.0f);
	glVertex3f(7.8f, 0.33f, 0.0f); 

	glEnd();

	 //Middle Horizontal Part
	glBegin(GL_QUADS);
	glVertex3f(7.8f, 0.33f, 0.0f);  
	glVertex3f(7.8f, -0.33f, 0.0f); 
	glVertex3f(8.37f, -0.33f, 0.0f);
	glVertex3f(8.37f, 0.33f, 0.0f); 
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(7.8f, -0.33f, 0.0f);
	glVertex3f(8.37f, -0.33f, 0.0f);

	glColor3f(0.0754f, 0.563331f, 0.315f);
	glVertex3f(8.37f, -1.0f, 0.0f);
	glVertex3f(7.8f, -1.0f, 0.0f);
	glEnd();


	glBegin(GL_QUADS);

	glColor3f(1.0f, 0.6f, 0.2f);
	glVertex3f(8.37f, 1.0f, 0.0f);
	glVertex3f(9.5f, 1.0f, 0.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(9.3f, 0.5f, 0.0f);
	glVertex3f(8.36f, 0.5f, 0.0f);

	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.6f, 0.2f);
	glVertex3f(9.5f, 1.0f, 0.0f);
	glVertex3f(9.92f, 0.63f, 0.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(9.5f, 0.25f, 0.0f);
	glVertex3f(9.3f, 0.5f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.6f, 0.2f);
	glVertex3f(9.92f, 0.63f, 0.0f);
	glVertex3f(9.92f, 0.19f, 0.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(9.5f, 0.1f, 0.0f);
	glVertex3f(9.5f, 0.25f, 0.0f);

	glEnd();

	glBegin(GL_QUADS);

	glVertex3f(9.92f, 0.19f, 0.0f);
	glVertex3f(9.6f, -0.35f, 0.0f);
	glVertex3f(9.2f, -0.19f, 0.0f);
	glVertex3f(9.5f, 0.2f, 0.0f);

	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(9.4f, -0.01f, 0.0f);
	glVertex3f(9.55f, -0.37f, 0.0f);
	glVertex3f(8.37f, -0.37f, 0.0f);
	glVertex3f(8.37f, -0.01f, 0.0f);

	glEnd();


	glBegin(GL_QUADS);
	glVertex3f(9.3f, -0.22f, 0.0f);
	glVertex3f(9.6f, 0.03f, 0.0f);
	glVertex3f(9.93f, -0.40f, 0.0f);
	glVertex3f(9.45f, -0.5f, 0.0f);

	glEnd();


	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(9.93f, -0.40f, 0.0f);
	glVertex3f(9.45f, -0.5f, 0.0f);
	glColor3f(0.0754f, 0.563331f, 0.315f);
	glVertex3f(9.45f, -1.0f, 0.0f);
	glVertex3f(9.93f, -1.0f, 0.0f);
	glEnd();	

	glPopMatrix();
}

void LetterA1(GLfloat x) {
	glPushMatrix();
	glTranslatef(x, 0.0f, -3.0f);
	glScalef(0.25f, 0.25f, 0.0f);

	glBegin(GL_QUADS);

	//glBegin(GL_QUADS);

	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(4.625f, 0.0f, 0.0f);
	glVertex3f(5.351f, 0.0f, 0.0f);

	glColor3f(0.0754f, 0.563331f, 0.315f);
	glVertex3f(5.0f, -1.0f, 0.0f);
	glVertex3f(4.254f, -1.0f, 0.0f);

	glEnd();

	glBegin(GL_QUADS);

	glColor3f(1.0f, 0.6f, 0.2f);
	glVertex3f(5.0f, 1.0f, 0.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(5.39f, 0.11f, 0.0f);
	glVertex3f(5.351f, 0.0f, 0.0f);
	glVertex3f(4.625f, 0.0f, 0.0f);

	glColor3f(1.0f, 1.0f, 1.0f);

	glEnd();



	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.6f, 0.2f);
	glVertex3f(5.0f, 1.0f, 0.0f);
	glVertex3f(5.71f, 1.0f, 0.0f);

	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(5.39f, 0.11f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.6f, 0.2f);
	glVertex3f(5.39f, 1.0f, 0.0f);
	glVertex3f(6.25f, 1.0f, 0.0f);

	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(6.7f, 0.0f, 0.0f);
	glVertex3f(6.0f, 0.0f, 0.0f);

	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(6.0f, 0.0f, 0.0f);
	glVertex3f(6.7f, 0.0f, 0.0f);

	glColor3f(0.0754f, 0.563331f, 0.315f);
	glVertex3f(7.15f, -1.0f, 0.0f);
	glVertex3f(6.4f, -1.0f, 0.0f);

	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(5.43f, 0.22f, 0.0f);
	glVertex3f(5.28f, -0.19f, 0.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(6.07f, -0.19f, 0.0f);
	glVertex3f(5.90f, 0.22f, 0.0f);
	glEnd();


	glPopMatrix();
}

void LetterT(GLfloat x) {
	glPushMatrix();
	glTranslatef(x, 0.0f, -3.0f);
	glScalef(0.25f, 0.25f, 0.0f);

	// Top bar - Left half
	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.6f, 0.2f);
	glVertex3f(7.0f, 1.0f, 0.0f);
	glVertex3f(8.25f, 1.0f, 0.0f);
	glColor3f(1.0f, 0.6f, 0.2f);
	glVertex3f(8.25f, 0.5f, 0.0f);
	glVertex3f(7.0f, 0.5f, 0.0f);
	glEnd();

	// Top bar - Right half
	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.6f, 0.2f);
	glVertex3f(8.25f, 1.0f, 0.0f);
	glVertex3f(9.5f, 1.0f, 0.0f);
	glColor3f(1.0f, 0.6f, 0.2f);
	glVertex3f(9.5f, 0.5f, 0.0f);
	glVertex3f(8.25f, 0.5f, 0.0f);
	glEnd();

	// Vertical bar - Upper half
	glBegin(GL_QUADS);

	glColor3f(1.0f, 0.6f, 0.2f);
	glVertex3f(8.0f, 0.68f, 0.0f);
	glVertex3f(8.6f, 0.68f, 0.0f);

	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(8.6f, 0.0f, 0.0f);
	glVertex3f(8.0f, 0.0f, 0.0f);
	glEnd();

	// Vertical bar - Lower half
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(8.0f, 0.0f, 0.0f);
	glVertex3f(8.6f, 0.0f, 0.0f);

	glColor3f(0.0754f, 0.563331f, 0.315f);
	glVertex3f(8.6f, -1.0f, 0.0f);
	glVertex3f(8.0f, -1.0f, 0.0f);
	glEnd();

	glPopMatrix();
}


void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glTranslatef(0.0f, 0.0f, -3.0f);

	glPushMatrix();

	//set matrix to model view mode
	glMatrixMode(GL_MODELVIEW);

	//set it to identity matrix
	glLoadIdentity();

	//drawBharat();
	//glTranslatef(-5.0f, 0.0f, -3.0f);
	LetterB();
	LetterH();
	LetterA();
	LetterR();
	LetterA1(-2.1f - translateX);
	LetterT(-2.09f - translateX);

	glPopMatrix();


    glXSwapBuffers(gpDisplay, window);
}

void update(void)
{
    /// code
	angle = angle + 2.0f;

	if (angle >= 360.0f)
	{
		angle = angle - 360.0f;
	}

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