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

GLUquadric* quadric = NULL;

//GLfloat anglePyramid = 0.0f;
Bool blight = False;

//Light related variable
GLfloat lightAmbient0[] = {0.0f, 0.0f, 0.0f, 1.0f};
GLfloat lightDefuse0[] = { 1.0f, 0.0f, 0.0f, 1.0f };
GLfloat lightSpecular0[] = { 1.0f, 0.0f, 0.0f, 1.0f };
GLfloat lightPosition0[] = { 0.0f, 0.0f, 0.0f, 1.0f };//posiotnal light

GLfloat lightAmbient1[] = { 0.0f, 0.0f, 0.0f, 1.0f };
GLfloat lightDefuse1[] = { 0.0f, 1.0f, 0.0f, 1.0f };
GLfloat lightSpecular1[] = { 0.0f, 1.0f, 0.0f, 1.0f };
GLfloat lightPosition1[] = { 0.0f, 0.0f, 0.0f, 1.0f };//posiotnal light

GLfloat lightAmbient2[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
GLfloat lightDifuse2[]  = { 0.0f, 0.0f, 1.0f, 1.0f };  // Correct spelling: Diffuse
GLfloat lightSpecular2[] = { 0.0f, 0.0f, 1.0f, 1.0f };
GLfloat lightPosition2[] = { 0.0f, 0.0f, 0.0f, 1.0f };

GLfloat materialAmbient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
GLfloat materialDefuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat materialSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat materialShininess = 50.0f;

GLfloat lightAngle0 = 0.0f;
GLfloat lightAngle1 = 0.0f;
GLfloat lightAngle2 = 0.0f;

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
    int frameBufferAttributes[] = {GLX_DOUBLEBUFFER, GLX_RGBA, GLX_RED_SIZE, 8, GLX_GREEN_SIZE, 8, GLX_BLUE_SIZE, 8, GLX_ALPHA_SIZE, 8, GLX_DEPTH_SIZE, 24, None};
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
    XStoreName(gpDisplay, window,  "RAJASHREE ADIKANE: XWINDOWS");

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
                       
                    case 'L':
                    case 'l':
                        blight = !blight;
                        if(blight){
                            glEnable(GL_LIGHTING);
                        }
                        else{
                            glDisable(GL_LIGHTING);
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
    glxContext = glXCreateContext(gpDisplay, visualInfo, NULL, True);
    if(glxContext == NULL)
    {
        fprintf(gpFile, "glxcontex failed!!!!\n");
        return -1;
    }

    glXMakeCurrent(gpDisplay, window, glxContext);

    //clear color
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // state fuc

	// Depth related code
	glShadeModel(GL_SMOOTH); // for smoothness
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL); // glcleardepth madhlya 1.0 fragment value <=
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	// Initialize Quadric
	quadric = gluNewQuadric();

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


	// Light and Material Configuration
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient0); //float Vector array if their is value single then we could use only f
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDefuse0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular0);
	//glLightfv(GL_LIGHT0, GL_POSITION, lightPosition0);

	glEnable(GL_LIGHT0);

	// Light and Material Configuration
	glLightfv(GL_LIGHT1, GL_AMBIENT, lightAmbient1); //float Vector array if their is value single then we could use only f
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDefuse1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, lightSpecular1);
	//glLightfv(GL_LIGHT1, GL_POSITION, lightPosition1);
	glEnable(GL_LIGHT1);

	//glEnable(GL_LIGHT1);

	glLightfv(GL_LIGHT2, GL_AMBIENT, lightAmbient2); //float Vector array if their is value single then we could use only f
	glLightfv(GL_LIGHT2, GL_DIFFUSE, lightDifuse2);
	glLightfv(GL_LIGHT2, GL_SPECULAR, lightSpecular2);
	//glLightfv(GL_LIGHT2, GL_POSITION, lightPosition1);
	glEnable(GL_LIGHT2);

	//glEnable(GL_LIGHT1);

	glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDefuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular);
	//glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, materialSpecular);
	glMaterialf(GL_FRONT, GL_SHININESS, materialShininess);



	//warm up resize
	// resize(WIN_WIDTH, WIN_HEIGHT);

    return 0;
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
   
// Clear the color buffer.
	//glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// translate triangle backwords by z
	//glTranslatef(0.0f, 0.0f, -3.0f);

	//set matrix to model view mode
	glMatrixMode(GL_MODELVIEW);

	//set it to identity matrix
	glLoadIdentity();

	glPushMatrix();

	// red light rotation
	glPushMatrix();
	glRotatef(lightAngle0, 1.0f, 0.0f, 0.0f); //x, y, z, w
	lightPosition0[2] = lightAngle0; // x-axis rotation cause in matrix x would be zero and other two will me something
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition0);
	glPopMatrix();

	//Green Light roataion
	glPushMatrix();
	glRotatef(lightAngle1, 0.0f, 1.0f, 0.0f);
	lightPosition1[0] = lightAngle1;
	glLightfv(GL_LIGHT1, GL_POSITION, lightPosition1);
	glPopMatrix();

	//blue light roataion
	glPushMatrix();
	glRotatef(lightAngle2, 0.0f, 0.0f, 1.0f);
	lightPosition2[1] = lightAngle2;
	glLightfv(GL_LIGHT2, GL_POSITION, lightPosition2);
	glPopMatrix();
	
	// Do View Transformation
	gluLookAt(0.0, 0.0, 5.0,  // Eye
		0.0, 0.0, 0.0,  // center
		0.0, 1.0, 0.0); // up

	glPushMatrix();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	gluSphere(quadric, 1.5f, 60, 60); // (quadric object, radius, slices, stacks) vertical subdivin


	glPopMatrix();

    glXSwapBuffers(gpDisplay, window);
}

void update(void)
{
    // code

	//update red light angle
	lightAngle0 = lightAngle0 + 2.0f;

	if (lightAngle0 >= 360.0f)
	{
		lightAngle0 = lightAngle0 - 360.0f;
	}

	//update green light angle
	lightAngle1 = lightAngle1 + 2.0f;

	if (lightAngle1 >= 360.0f)
	{
		lightAngle1 = lightAngle1 - 360.0f;
	}

	//update blue light angle
	lightAngle2 = lightAngle2 + 2.0f;
	if (lightAngle2 >= 360.0f)
	{
		lightAngle2 = lightAngle2 - 360.0f;
	}

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



