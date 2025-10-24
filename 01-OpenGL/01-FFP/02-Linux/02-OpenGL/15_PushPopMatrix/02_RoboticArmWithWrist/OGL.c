#include<stdio.h>
#include<stdlib.h>
#include<memory.h>

//xlib header files
#include<X11/Xlib.h>
#include<X11/Xutil.h>
#include<X11/XKBlib.h>

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

//robotic arm related 
int elbow = 0;
int shoulder = 0;
int palm = 0;
GLboolean palmForward = True;
GLUquadric* quadric =  NULL;

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
    int frameBufferAttributes[] = {GLX_DOUBLEBUFFER, GLX_RGBA, GLX_RED_SIZE, 8, GLX_GREEN_SIZE, 8, GLX_BLUE_SIZE, 8, GLX_ALPHA_SIZE, 8, None};
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
    if(iResult == -1)
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
                    case 'f':
                    case 'F':
                    if(bFullScreen == False)
                    {
                        toggleFullSCreen();
                        bFullScreen = True;
                    }
                    else
                    {
                        toggleFullSCreen();
                        bFullScreen = False;
                    }
                    break;
                    case 'S':
			shoulder = (shoulder + 3) % 360;
			break;
		case 's':
			shoulder = (shoulder - 3) % 360;
			break;

		case 'E':
			elbow = (elbow + 3) % 360;
			break;
		case 'e':
			elbow = (elbow - 3) % 360;
			break;

		case 'P':  
		case 'p':
			if (palmForward)
			{
				palm += 3;
				if (palm >= 30)
					palmForward = False;
			}
			else
			{
				palm -= 3;
				if (palm <= -30)
					palmForward = True;
			}
			break;


                    default:
                    break;
                }
                break;

                case ButtonPress:
                break;

                case Expose:
                break;

                case 33:
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
    Atom windowManagerNormalStateAtom = XInternAtom(gpDisplay, "_NET_WM_STATE", False);
    Atom windowManagerFullScreenStateAtom = XInternAtom(gpDisplay, "_NET_WM_STATE_FULLSCREEN", False);
    XEvent event;
    memset((void*)&event, 0, sizeof(XEvent));
    event.type = ClientMessage;
    event.xclient.window = window;
    event.xclient.message_type = windowManagerNormalStateAtom;
    event.xclient.format = 32;
    event.xclient.data.l[0] = bFullScreen?0:1;
    event.xclient.data.l[1] = windowManagerFullScreenStateAtom;

    //sent above event to Xserver
    XSendEvent(gpDisplay, XRootWindow(gpDisplay, visualInfo->screen), False, SubstructureNotifyMask, &event);
}

int initialize(void)
{
	// Function declarations
	void printGLInfo(void);
	void resize(int, int);

	// Attributes for visual
	static int visual_attribs[] = {
		GLX_RGBA,
		GLX_DEPTH_SIZE, 24,
		GLX_DOUBLEBUFFER,
		None
	};

	// Get a matching visual
	XVisualInfo *vi = glXChooseVisual(gpDisplay, 0, visual_attribs);
	if (vi == NULL) {
		fprintf(gpFile, "glXChooseVisual() failed\n");
		exit(1);
	}

	// Create GLX context
	glxContext = glXCreateContext(gpDisplay, vi, NULL, GL_TRUE);
	if (glxContext == NULL) {
		fprintf(gpFile, "glXCreateContext() failed\n");
		exit(2);
	}

	// Make the context current
	if (!glXMakeCurrent(gpDisplay, window, glxContext)) {
		fprintf(gpFile, "glXMakeCurrent() failed\n");
		exit(3);
	}

	// Print OpenGL info
	printGLInfo();

	// OpenGL initialization
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glShadeModel(GL_SMOOTH);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    
    quadric = gluNewQuadric();   

	// Initial resize
	resize(WIN_WIDTH, WIN_HEIGHT);
}




void printGLInfo(void)
{
	// code

	// Print OpenGL Information
	fprintf(gpFile, "OPENGL INFORMATION\n");
	fprintf(gpFile, "***********************\n");
	fprintf(gpFile, "OpenGL Vendor : %s\n", glGetString(GL_VENDOR));
	fprintf(gpFile, "OpenGL Renderer : %s\n", glGetString(GL_RENDERER));
	fprintf(gpFile, "OpenGL Version : %s\n", glGetString(GL_VERSION));
	fprintf(gpFile, "***********************\n");

}

void resize(int width, int height)
{
	// code
	// if height by accident is less than 0 make it 1
	if (height < 0)
	{
		height = 1;
	}
	// set the view port
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);

	//set matrix projection mode
	glMatrixMode(GL_PROJECTION);

	//set identity to matrix
	glLoadIdentity();

	//Do perspective projection
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);

}


void display(void)
{
	// code

	// Clear the color and depth buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Set matrix mode and reset to identity
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Set the camera/view
	gluLookAt(0.0, 0.0, 5.0,   // Eye position
		0.0, 0.0, 0.0,   // Look-at point
		0.0, 1.0, 0.0);  // Up vector

	// Translate whole model backward (simulate depth)
	glTranslatef(0.0f, 0.0f, -12.0f);

	// Set polygon mode (filled)
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// --- Draw Arm and Forearm ---
	glPushMatrix();  // Save world matrix

	// Rotate shoulder
	glRotatef((GLfloat)shoulder, 0.0f, 0.0f, 1.0f);
	glTranslatef(1.0f, 0.0f, 0.0f);  // Move to middle of upper arm

	// Draw arm (upper)
	glPushMatrix(); // Save transformation for forearm
	glScalef(2.1f, 0.6f, 1.0f);
	glColor3f(0.5f, 0.35f, 0.05f); // brownish
	gluSphere(quadric, 0.5f, 10, 10);
	glPopMatrix();

	// Move to elbow joint
	glTranslatef(1.0f, 0.0f, 0.0f);
	glRotatef((GLfloat)elbow, 0.0f, 0.0f, 1.0f);
	glTranslatef(1.0f, 0.0f, 0.0f);

	// Draw forearm (lower)
	glPushMatrix();
	glScalef(2.1f, 0.6f, 1.0f);
	glColor3f(0.5f, 0.35f, 0.05f);
	gluSphere(quadric, 0.5f, 10, 10);
	glPopMatrix();

	glTranslatef(0.4f, 0.0f, 0.0f);
	glRotatef((GLfloat)palm, 0.0f, 0.0f, 1.0f);
	glTranslatef(1.0f, 0.0f, 0.0f);
	// draw palm 
	glPushMatrix();
	glColor3f(0.90f, 0.76f, 0.671f);
	gluSphere(quadric, 0.5f, 10, 10);
	glPopMatrix();

	glPopMatrix(); // Restore world matrix


	// Swap the buffers
  glXSwapBuffers(gpDisplay, window);

}

void update(void)
{
	// code

}



void uninitialize(void)
{

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
    if(gpFile)
    {
        fprintf(gpFile, "Program terminated Successfully\n");
        fclose(gpFile);
        gpFile = NULL;
    }
    GLXContext currenctContext = glXGetCurrentContext();
    if(currenctContext && currenctContext == glxContext)
    {
        glXMakeCurrent(gpDisplay, 0, 0);
    }
    if(glxContext)
    {
        glXDestroyContext(gpDisplay, glxContext);
        glxContext = NULL;
    }
    if(visualInfo)
    {
        free(visualInfo);
        visualInfo = NULL;
    }

}



