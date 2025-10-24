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

#include <unistd.h>     // for fork(), execlp()
#include <signal.h>     // for kill(), SIGTERM
#include <sys/wait.h>   // for waitpid()

pid_t sound_pid = -1;


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

// variables for BHARAT Movement
GLfloat translateX = -1.8f;
GLfloat posbX = 1.0f;

GLfloat poshX = -3.0f;
GLfloat poshY = 3.0f;

GLfloat posaX = -3.0f;
GLfloat posaY = -3.0f;

GLfloat posrX = -3.0f;
GLfloat posrY = 3.0f;

GLfloat posa1X = 3.0f;
GLfloat posa1Y = -3.0f;

GLfloat postX = 4.0f;

//speed
GLfloat speed = 0.002/2.0f;

//realted movement
Bool isMovingB = True;
Bool isMovingH = False;
Bool isMovingA = False;
Bool isMovingR = False;
Bool isMovingA1 = False;
Bool isMovingT = False;
GLfloat angle = 0.0f;

GLfloat planeTopAngle = 30.0f;

Bool moveMiddle = False;
Bool moveMiddleStaright = False;
Bool isMovingTop = False;
//Bool isTopStraight = False;
Bool isTopMiddle = False;
Bool isMovingExit = False;
Bool moveBottom = False;
Bool isBottomMiddle = False;
Bool isBottomExit = False;

GLfloat planeMiddleX = 10.0f;
GLfloat planeTopX = -10.0f, planeTopY = 10.0f;
GLfloat planeBottomX = -10.0f, planeBottomY = -10.0f;

GLfloat T_position_x = 0.6f;


int main(void)
{
    //function declarations
	void stopSound(void);
    void playSound(void);
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

   //sound
    playSound();

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
	 stopSound();
    return 0;
}


void playSound() {
    // Stop any previous sound
    if (sound_pid > 0) {
        kill(sound_pid, SIGTERM);
        waitpid(sound_pid, NULL, 0);
        sound_pid = -1;
    }

    sound_pid = fork();
    if (sound_pid == 0) {
        execlp("aplay", "aplay", "-q", "sound.wav", (char*)NULL);
        exit(1);
    }
}

void stopSound() {
    if (sound_pid > 0) {
        kill(sound_pid, SIGTERM);
        waitpid(sound_pid, NULL, 0);
        sound_pid = -1;
    }
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

void movingFunc(void) {
	if (isMovingB) {
		posbX -= speed;
		if (posbX <= 0.0f) {
			posbX = 0.0f;
			isMovingB = False;
			isMovingH = True; 
		}
	}
	else if (isMovingH) {
		poshX += speed;
		poshY -= speed; 

		if (poshX >= 0.0f && poshY <= 0.0f) {
			poshX = 0.0f;
			poshY = 0.0f;
			isMovingH = False;
			isMovingA = True;
		}
	}
	else if (isMovingA) {
		posaX += speed;
		posaY += speed;

		if (posaX >= 0.0f && posaY >= 0.0f) {
			posaX = 0.0f;
			posaX = 0.0f;
			isMovingA = False;
			isMovingR = True;
		}
	}
	else if (isMovingR) {
		posrX += speed;
		posrY -= speed; 

		if (posrX >= 0.0f && posrY <= 0.0f) {
			posrX = 0.0f;
			posrY = 0.0f;
			isMovingR = False;
			isMovingA1 = True;
		}
	}
	else if (isMovingA1) {
		posa1X -= speed; 
		posa1Y += speed; 

		if (posa1X <= 0.0f && posa1Y >= 0.0f) {
			posa1X = 0.0f;
			posa1Y = 0.0f;
			isMovingA1 = False;
			isMovingT = True;
		}
	}
	else if (isMovingT) {
		postX -= speed;
		if (postX <= 0.0f) {
			postX = 0.0f;
			isMovingT = False;
			moveMiddle = True;
			isMovingTop = True;
			moveBottom = True;
		}
	}
	if (moveMiddle) {
		planeMiddleX -= speed * 3.0;
		if (planeMiddleX <= 0.0f) {
			planeMiddleX = 0.0f;
			moveMiddle = False;
			moveMiddleStaright = True;
		}
	}

	if (moveMiddleStaright) {
		planeMiddleX -= speed * 3.0;
		if (planeMiddleX >= 0.0f) {
			planeMiddleX = 0.0f;
			//isMovingB = False;
		}
	}

	if (isMovingTop) {
		planeTopX += speed * 3.0f;

		if (planeTopX <= planeMiddleX) {
			planeTopY = 1.0f + (planeTopX * planeTopX) * 0.2f;
			planeTopAngle = 40.0f * (planeMiddleX - planeTopX) / (planeMiddleX - (-10.0f));
		}

		if (planeTopX >= planeMiddleX) {
			planeTopX = planeMiddleX;
			planeTopY = 1.0f;
			planeTopAngle = 0.0f; // Reset rotation
			isMovingTop = False;
			isTopMiddle = True;
		}
	}



	if (isTopMiddle) {
		planeTopX += speed * 3.0f;
		if (planeTopX >= 20.0f) {
			planeTopX = 20.0f;
			planeTopY = 1.0f;
			isTopMiddle = False;
			isMovingExit = True;
		}
	}

	if (isMovingExit)
	{
		planeTopX += speed * 3.0f;
		fprintf(gpFile, "speed1: %.2f\n", planeBottomX);
		if (planeTopX <= 30.0f)
		{
			float t = (planeTopX - 7.0f) / (20.0f - 7.0f);
			planeTopY = 1.0f + (1.0f - t) * (1.0f - t) * 9.0f;
			planeTopAngle = 30.0f * (1.0f - t);

		}
	}

	if (moveBottom)
	{
		planeBottomX += speed * 3.0f;
		if (planeBottomX <= planeMiddleX)
		{
			planeBottomY = 1.0f + (planeBottomX * planeBottomX) * 0.2f;
			planeTopAngle = 40.0f * (planeMiddleX - planeTopX) / (planeMiddleX - (-10.0f));
		}
		if (planeBottomX >= planeMiddleX) {
			planeBottomX = planeMiddleX;
			planeBottomY = 1.0f;
			moveBottom = False;
			isBottomMiddle = True;
		}
	}

	if (isBottomMiddle) {
		planeBottomX += speed * 3.0f;
		if (planeBottomX >= 20.0f) {
			planeBottomX = 20.0f;
			planeBottomY = 1.0f;
			isBottomMiddle = False;
			isBottomExit = True;
		}
	}
	if (isBottomExit)
	{
		planeBottomX += speed * 3.0f;

		fprintf(gpFile, "speed2: %.2f\n", planeBottomX);
		if (planeBottomX <= 30.0f)
		{
			float t = (planeBottomX - 7.0f) / (20.0f - 7.0f);
			planeBottomY = 1.0f + (1.0f - t) * (1.0f - t) * 9.0f;
		}
	}

}

void LetterB(void)
{
	movingFunc();
	glPushMatrix();
	glTranslatef(translateX-posbX, 0.0f, -3.0f);
	glScalef(0.25f, 0.25f, 0.0f); 

	
	GLfloat grayColor[] = { 0.5f, 0.5f, 0.5f };
	GLfloat leftColor[] = { 1.0f, 0.6f, 0.2f };    // Saffron
	GLfloat middleColor[] = { 1.0f, 1.0f, 1.0f };  // White
	GLfloat rightColor[] = { 0.0754f, 0.5633f, 0.315f }; // Green

	// Determine active colors
	GLfloat* saffron = grayColor;
	GLfloat* white = grayColor;
	GLfloat* green = grayColor;

	if (planeMiddleX <= -2.0f) {
		// Use original colors when planeMiddleX > 2
		saffron = leftColor;
		white = middleColor;
		green = rightColor;
	}
	/*fprintf(gpFile, "x = %f", planeMiddleX);*/
	// Left vertical bar 
	glBegin(GL_QUADS);
	 glColor3fv(saffron);
	glVertex3f(-0.98f, 1.0f, 0.0f);   
	glVertex3f(-0.3f, 0.557f, 0.0f); 
	 glColor3fv(white);
	glVertex3f(-0.3f, 0.22f, 0.0f);   
	glVertex3f(-0.98f, 0.22f, 0.0f);  
	glEnd();

	// Middle connecting part
	glBegin(GL_QUADS);
	 glColor3fv(white);
	glVertex3f(-0.98f, 0.22f, 0.0f);
	glVertex3f(-0.3f, 0.22f, 0.0f);
	 glColor3fv(white);
	glVertex3f(-0.3f, -0.175f, 0.0f);
	glVertex3f(-0.98f, -0.175f, 0.0f);
	glEnd();

	// Lower vertical bar
	glBegin(GL_QUADS);
	 glColor3fv(white);
	glVertex3f(-0.98f, -0.175f, 0.0f);
	glVertex3f(-0.3f, -0.175f, 0.0f);

	 glColor3fv(green);
	glVertex3f(-0.3f, -0.595f, 0.0f);
	glVertex3f(-0.98f, -1.0f, 0.0f);

	glEnd();

	// Upper curved section
	glBegin(GL_QUADS);

	 glColor3fv(saffron);
	glVertex3f(0.54f, 1.0f, 0.0f);
	glVertex3f(-0.98f, 1.0f, 0.0f);

	 glColor3fv(saffron);
	glVertex3f(-0.3f, 0.557f, 0.0f);
	glVertex3f(0.17f, 0.557f, 0.0f);
	glEnd();

	// Lower curved section
	glBegin(GL_QUADS);
	 glColor3fv(green);
	glVertex3f(0.17f, -0.594f, 0.0f);
	glVertex3f(-0.3f, -0.594f, 0.0f);
	 glColor3fv(green);
	glVertex3f(-0.98f, -0.99f, 0.0f);
	glVertex3f(0.54f, -0.99f, 0.0f);
	glEnd();

	// Top-right corner
	glBegin(GL_QUADS);

	 glColor3fv(saffron);
	glVertex3f(0.17f, 0.567f, 0.0f);
	glVertex3f(0.54f, 1.0f, 0.0f);
	 glColor3fv(saffron);
	glVertex3f(0.98f, 0.7f, 0.0f);
	glVertex3f(0.3f, 0.49f, 0.0f);
	glEnd();

	 //Top middle curve
	glBegin(GL_QUADS);
	 glColor3fv(white);
	glVertex3f(0.98f, 0.7f, 0.0f);
	glVertex3f(0.98f, 0.49f, 0.0f);
	glVertex3f(0.3f, 0.3f, 0.0f);
	glVertex3f(0.98f, 0.2f, 0.0f);
	glEnd();

	 //Middle connecting part
	glBegin(GL_QUADS);
	 glColor3fv(saffron);
	glVertex3f(0.98f, 0.7f, 0.0f);
	glVertex3f(0.3f, 0.5f, 0.0f);
	 glColor3fv(white);
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
	 glColor3fv(white);
	glVertex3f(0.98f, -0.16f, 0.0f);
	glVertex3f(0.3f, -0.26f, 0.0f);

	 glColor3fv(green);
	glVertex3f(0.3f, -0.5f, 0.0f);
	glVertex3f(0.98f, -0.72f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	 glColor3fv(green);
	glVertex3f(0.98f, -0.72f, 0.0f);
	glVertex3f(0.3f, -0.5f, 0.0f);
	 glColor3fv(green);
	glVertex3f(0.17f, -0.595f, 0.0f);
	glVertex3f(0.54f, -0.99f, 0.0f);
	glEnd();

	// Middle bar 
	glBegin(GL_QUADS);
	 glColor3fv(white);
	glVertex3f(0.19f, 0.22f, 0.0f);
	glVertex3f(-0.3f, 0.22f, 0.0f);
	 glColor3fv(white);
	glVertex3f(-0.3f, -0.175f, 0.0f);
	glVertex3f(0.19f, -0.175f, 0.0f);
	glEnd();

	glPopMatrix(); 
}

void LetterH(void)
{
	movingFunc();
	glPushMatrix();
	glTranslatef(translateX+poshX, poshY, -3.0f);
	glScalef(0.25f, 0.25f, 0.0f);

	GLfloat grayColor[] = { 0.5f, 0.5f, 0.5f };
	GLfloat leftColor[] = { 1.0f, 0.6f, 0.2f };    // Saffron
	GLfloat middleColor[] = { 1.0f, 1.0f, 1.0f };  // White
	GLfloat rightColor[] = { 0.0754f, 0.5633f, 0.315f }; // Green

	// Determine active colors
	GLfloat* saffron = grayColor;
	GLfloat* white = grayColor;
	GLfloat* green = grayColor;

	if (planeMiddleX <= -5.0f) {
		// Use original colors when planeMiddleX > 2
		saffron = leftColor;
		white = middleColor;
		green = rightColor;
	}
	/*fprintf(gpFile, "x = %f", planeMiddleX);*/


	// Left vertical bar - First half
	glBegin(GL_QUADS);
	glColor3fv(saffron);
	glVertex3f(1.5f, 1.0f, 0.0f);
	glVertex3f(2.18f, 1.0f, 0.0f);

	glColor3fv(white);
	glVertex3f(2.18f, 0.0f, 0.0f);
	glVertex3f(1.5f, 0.0f, 0.0f);
	glEnd();

	// Left vertical bar - Second half
	glBegin(GL_QUADS);
	glColor3fv(white);
	glVertex3f(1.5f, 0.0f, 0.0f);
	glVertex3f(2.18f, 0.0f, 0.0f);

	glColor3fv(green);
	glVertex3f(2.18f, -1.0f, 0.0f);
	glVertex3f(1.5f, -1.0f, 0.0f);
	glEnd();

	// Right vertical bar - First half
	glBegin(GL_QUADS);
	glColor3fv(saffron);
	glVertex3f(2.97f, 1.0f, 0.0f);
	glVertex3f(3.65f, 1.0f, 0.0f);

	glColor3fv(white);
	glVertex3f(3.65f, 0.0f, 0.0f);
	glVertex3f(2.97f, 0.0f, 0.0f);
	glEnd();

	// Right vertical bar - Second half
	glBegin(GL_QUADS);
	glColor3fv(white);
	glVertex3f(2.97f, 0.0f, 0.0f);
	glVertex3f(3.65f, 0.0f, 0.0f);

	glColor3fv(green);
	glVertex3f(3.65f, -1.0f, 0.0f);
	glVertex3f(2.97f, -1.0f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3fv(white);
	glVertex3f(2.18f, 0.3f, 0.0f); 
	glVertex3f(2.58f, 0.3f, 0.0f);
	glColor3fv(white);
	glVertex3f(2.58f, -0.3f, 0.0f); 
	glVertex3f(2.18f, -0.3f, 0.0f);
	glEnd();

	// Middle bar - Second half
	glBegin(GL_QUADS);
	glColor3fv(white);
	glVertex3f(2.58f, 0.3f, 0.0f);
	glVertex3f(2.97f, 0.3f, 0.0f);
	glColor3fv(white);
	glVertex3f(2.97f, -0.3f, 0.0f);
	glVertex3f(2.58f, -0.3f, 0.0f);
	glEnd();

	glPopMatrix();
}

void LetterA(void) {
	movingFunc();
	glPushMatrix();
	glTranslatef(translateX+posaX, posaY, -3.0f);
	glScalef(0.25f, 0.25f, 0.0f);

	GLfloat grayColor[] = { 0.5f, 0.5f, 0.5f };
	GLfloat leftColor[] = { 1.0f, 0.6f, 0.2f };    // Saffron
	GLfloat middleColor[] = { 1.0f, 1.0f, 1.0f };  // White
	GLfloat rightColor[] = { 0.0754f, 0.5633f, 0.315f }; // Green

	// Determine active colors
	GLfloat* saffron = grayColor;
	GLfloat* white = grayColor;
	GLfloat* green = grayColor;

	if (planeMiddleX <= -9.0f) {
		saffron = leftColor;
		white = middleColor;
		green = rightColor;
	}
	/*fprintf(gpFile, "x = %f", planeMiddleX);*/

	glBegin(GL_QUADS);
	glColor3fv(white);
	glVertex3f(4.625f, 0.0f, 0.0f);	
	glVertex3f(5.351f, 0.0f, 0.0f);


	glColor3fv(green);
	glVertex3f(5.0f, -1.0f, 0.0f);
	glVertex3f(4.254f, -1.0f, 0.0f);

	glEnd();

	glBegin(GL_QUADS);
	
	glColor3fv(saffron);
	glVertex3f(5.0f, 1.0f, 0.0f);
	glColor3fv(white);
	glVertex3f(5.39f, 0.11f, 0.0f);
	glVertex3f(5.351f, 0.0f, 0.0f);
	glVertex3f(4.625f, 0.0f, 0.0f);

	glColor3fv(white);

	glEnd();



	glBegin(GL_TRIANGLES);
	glColor3fv(saffron);
	glVertex3f(5.0f, 1.0f, 0.0f);
	glVertex3f(5.71f, 1.0f, 0.0f);

	glColor3fv(white);
	glVertex3f(5.39f, 0.11f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3fv(saffron);
	glVertex3f(5.39f, 1.0f, 0.0f);
	glVertex3f(6.25f, 1.0f, 0.0f);

	glColor3fv(white);
	glVertex3f(6.7f, 0.0f, 0.0f);
	glVertex3f(6.0f, 0.0f, 0.0f);

	glEnd();

	glBegin(GL_QUADS);
	glColor3fv(white);
	glVertex3f(6.0f, 0.0f, 0.0f);
	glVertex3f(6.7f, 0.0f, 0.0f);

	glColor3fv(green);
	glVertex3f(7.15f, -1.0f, 0.0f);
	glVertex3f(6.4f, -1.0f, 0.0f);

	glEnd();

	glBegin(GL_QUADS);
	glColor3fv(white);
	glVertex3f(5.43f, 0.22f, 0.0f);
	glVertex3f(5.28f, -0.19f, 0.0f);
	glColor3fv(white);
	glVertex3f(6.07f, -0.19f, 0.0f);
	glVertex3f(5.90f, 0.22f, 0.0f);
	glEnd();


	glPopMatrix();
}

void LetterR(void) {
	movingFunc();
	glPushMatrix();
	glTranslatef((translateX- 0.03)-posrX, posrY, -3.0f);
	//glTranslatef(translateX - poshX - 0.03, poshY, -3.0f);
	glScalef(0.25f, 0.25f, 0.0f);

	GLfloat grayColor[] = { 0.5f, 0.5f, 0.5f };
	GLfloat leftColor[] = { 1.0f, 0.6f, 0.2f };    // Saffron
	GLfloat middleColor[] = { 1.0f, 1.0f, 1.0f };  // White
	GLfloat rightColor[] = { 0.0754f, 0.5633f, 0.315f }; // Green

	// Determine active colors
	GLfloat* saffron = grayColor;
	GLfloat* white = grayColor;
	GLfloat* green = grayColor;

	if (planeMiddleX <= -13.0f) {
		// Use original colors when planeMiddleX > 2
		saffron = leftColor;
		white = middleColor;
		green = rightColor;
	}

	fprintf(gpFile, "x = %f", planeMiddleX);

	// Top Horizontal Part
	glBegin(GL_QUADS);
	glColor3fv(saffron);
	glVertex3f(7.8f, 1.0f, 0.0f);   
	glVertex3f(8.37f, 1.0f, 0.0f);

	glColor3fv(white);
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
	glColor3fv(white);
	glVertex3f(7.8f, -0.33f, 0.0f);
	glVertex3f(8.37f, -0.33f, 0.0f);

	glColor3fv(green);
	glVertex3f(8.37f, -1.0f, 0.0f);
	glVertex3f(7.8f, -1.0f, 0.0f);
	glEnd();


	glBegin(GL_QUADS);

	glColor3fv(saffron);
	glVertex3f(8.37f, 1.0f, 0.0f);
	glVertex3f(9.5f, 1.0f, 0.0f);
	glColor3fv(white);
	glVertex3f(9.3f, 0.5f, 0.0f);
	glVertex3f(8.36f, 0.5f, 0.0f);

	glEnd();

	glBegin(GL_QUADS);
	glColor3fv(saffron);
	glVertex3f(9.5f, 1.0f, 0.0f);
	glVertex3f(9.92f, 0.63f, 0.0f);
	glColor3fv(white);
	glVertex3f(9.5f, 0.25f, 0.0f);
	glVertex3f(9.3f, 0.5f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3fv(saffron);
	glVertex3f(9.92f, 0.63f, 0.0f);
	glVertex3f(9.92f, 0.19f, 0.0f);
	glColor3fv(white);
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
	glColor3fv(white);
	glVertex3f(9.93f, -0.40f, 0.0f);
	glVertex3f(9.45f, -0.5f, 0.0f);
	glColor3fv(green);
	glVertex3f(9.45f, -1.0f, 0.0f);
	glVertex3f(9.93f, -1.0f, 0.0f);
	glEnd();	

	glPopMatrix();
}

void LetterA1(GLfloat x) {
	movingFunc();
	glPushMatrix();
	glTranslatef(x + posa1X, posa1Y, -3.0f);
	glScalef(0.25f, 0.25f, 0.0f);

	GLfloat grayColor[] = { 0.5f, 0.5f, 0.5f };
	GLfloat leftColor[] = { 1.0f, 0.6f, 0.2f };    // Saffron
	GLfloat middleColor[] = { 1.0f, 1.0f, 1.0f };  // White
	GLfloat rightColor[] = { 0.0754f, 0.5633f, 0.315f }; // Green

	// Determine active colors
	GLfloat* saffron = grayColor;
	GLfloat* white = grayColor;
	GLfloat* green = grayColor;

	if (planeMiddleX <= -15.55f) {
		// Use original colors when planeMiddleX > 2
		saffron = leftColor;
		white = middleColor;
		green = rightColor;
	}
	//fprintf(gpFile, "x = %f", planeMiddleX);

	glBegin(GL_QUADS);

	//glBegin(GL_QUADS);

	glColor3fv(white);
	glVertex3f(4.625f, 0.0f, 0.0f);
	glVertex3f(5.351f, 0.0f, 0.0f);

	glColor3fv(green);
	glVertex3f(5.0f, -1.0f, 0.0f);
	glVertex3f(4.254f, -1.0f, 0.0f);

	glEnd();

	glBegin(GL_QUADS);

	glColor3fv(saffron);
	glVertex3f(5.0f, 1.0f, 0.0f);
	glColor3fv(white);
	glVertex3f(5.39f, 0.11f, 0.0f);
	glVertex3f(5.351f, 0.0f, 0.0f);
	glVertex3f(4.625f, 0.0f, 0.0f);

	glColor3f(1.0f, 1.0f, 1.0f);

	glEnd();



	glBegin(GL_TRIANGLES);
	glColor3fv(saffron);
	glVertex3f(5.0f, 1.0f, 0.0f);
	glVertex3f(5.71f, 1.0f, 0.0f);

	glColor3fv(white);
	glVertex3f(5.39f, 0.11f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3fv(saffron);
	glVertex3f(5.39f, 1.0f, 0.0f);
	glVertex3f(6.25f, 1.0f, 0.0f);

	glColor3fv(white);
	glVertex3f(6.7f, 0.0f, 0.0f);
	glVertex3f(6.0f, 0.0f, 0.0f);

	glEnd();

	glBegin(GL_QUADS);
	glColor3fv(white);
	glVertex3f(6.0f, 0.0f, 0.0f);
	glVertex3f(6.7f, 0.0f, 0.0f);

	glColor3fv(green);
	glVertex3f(7.15f, -1.0f, 0.0f);
	glVertex3f(6.4f, -1.0f, 0.0f);

	glEnd();

	glBegin(GL_QUADS);
	glColor3fv(white);
	glVertex3f(5.43f, 0.22f, 0.0f);
	glVertex3f(5.28f, -0.19f, 0.0f);
	glColor3fv(white);
	glVertex3f(6.07f, -0.19f, 0.0f);
	glVertex3f(5.90f, 0.22f, 0.0f);
	glEnd();


	glPopMatrix();
}

void LetterT(GLfloat x) {
	glPushMatrix();
	glTranslatef(x + postX, 0.0f, -3.0f);
	glScalef(0.25f, 0.25f, 0.0f);

	GLfloat grayColor[] = { 0.5f, 0.5f, 0.5f };
	GLfloat leftColor[] = { 1.0f, 0.6f, 0.2f };    // Saffron
	GLfloat middleColor[] = { 1.0f, 1.0f, 1.0f };  // White
	GLfloat rightColor[] = { 0.0754f, 0.5633f, 0.315f }; // Green

	// Determine active colors
	GLfloat* saffron = grayColor;
	GLfloat* white = grayColor;
	GLfloat* green = grayColor;
	if (planeMiddleX <= -17.88f) {
		// Use original colors when planeMiddleX > 2
		saffron = leftColor;
		white = middleColor;
		green = rightColor;
	}

	fprintf(gpFile, "x = %f", planeMiddleX);

	// Top bar - Left half
	glBegin(GL_QUADS);
	glColor3fv(saffron);
	glVertex3f(7.0f, 1.0f, 0.0f);
	glVertex3f(8.25f, 1.0f, 0.0f);
	glColor3fv(saffron);
	glVertex3f(8.25f, 0.5f, 0.0f);
	glVertex3f(7.0f, 0.5f, 0.0f);
	glEnd();

	// Top bar - Right half
	glBegin(GL_QUADS);
	glColor3fv(saffron);
	glVertex3f(8.25f, 1.0f, 0.0f);
	glVertex3f(9.5f, 1.0f, 0.0f);
	glColor3fv(saffron);
	glVertex3f(9.5f, 0.5f, 0.0f);
	glVertex3f(8.25f, 0.5f, 0.0f);
	glEnd();

	// Vertical bar - Upper half
	glBegin(GL_QUADS);

	glColor3fv(saffron);
	glVertex3f(8.0f, 0.68f, 0.0f);
	glVertex3f(8.6f, 0.68f, 0.0f);

	glColor3fv(white);
	glVertex3f(8.6f, 0.0f, 0.0f);
	glVertex3f(8.0f, 0.0f, 0.0f);
	glEnd();

	// Vertical bar - Lower half
	glBegin(GL_QUADS);
	glColor3fv(white);
	glVertex3f(8.0f, 0.0f, 0.0f);
	glVertex3f(8.6f, 0.0f, 0.0f);

	glColor3fv(green);
	glVertex3f(8.6f, -1.0f, 0.0f);
	glVertex3f(8.0f, -1.0f, 0.0f);
	glEnd();

	glPopMatrix();
}

void DrawIAFInsignia() {
	int segments = 100;
	float radius[] = { 0.12f, 0.08f, 0.04f };

	float colors[3][3] = {
		{1.0f, 0.5f, 0.0f},   // Orange
		{1.0f, 1.0f, 1.0f},   // White
		{0.0f, 0.6f, 0.0f}    // Green
	};

	for (int i = 0; i < 3; i++) {
		glColor3f(colors[i][0], colors[i][1], colors[i][2]);
		glBegin(GL_TRIANGLE_FAN);
		glVertex2f(0.0f, 0.0f);
		for (int j = 0; j <= segments; j++) {
			float angle = 2.0f * M_PI * j / segments;
			glVertex2f(cos(angle) * radius[i], sin(angle) * radius[i]);
		}
		glEnd();
	}
}


void DrawPlane() {
		movingFunc();
		glPushMatrix();
		glScalef(0.025f/2, 0.025f/2, 0.0f);

		// Translate by x and y passed in from animation logic
		glTranslatef(-(planeMiddleX + 10.0f) * 10, 0.0f, 0.0f);
		//glTranslatef(translateX - posbX, 0.0f, -3.0f);


		glColor3f(173.0f / 256.0f, 216.0f / 256.0f, 230.0f / 256.0f);
		glBegin(GL_POLYGON);
		glVertex3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0.0f, -1.0f, 0.0f);
		glVertex3f(-2.75f, -4.8f, 0.0f);
		glVertex3f(-4.77f, -4.8f, 0.0f);
		glVertex3f(-4.77f, 4.8f, 0.0f);
		glVertex3f(-2.75f, 4.8f, 0.0f);

		glEnd();


		glColor3f(70.0f / 256.0f, 130.0f / 256.0f, 180.0f / 256.0f);
		glBegin(GL_POLYGON);
		glVertex3f(-5.5f, 1.0f, 0.0f);
		glVertex3f(2.0f, 1.0f, 0.0f);
		glVertex3f(5.0f, 0.0f, 0.0f);
		glVertex3f(2.0f, -1.0f, 0.0f);
		glVertex3f(-5.5f, -1.0f, 0.0f);
		glEnd();

		glColor3f(0.6f, 0.6f, 0.7f);
		glBegin(GL_QUADS);
		glVertex3f(-2.75f, -4.5f, 0.0f);
		glVertex3f(-0.75f, -5.3f, 0.0f);
		glVertex3f(-4.77f, -5.0f, 0.0f);
		glVertex3f(-4.77f, -4.5f, 0.0f);

		glEnd();

		glColor3f(0.6f, 0.6f, 0.7f);
		glBegin(GL_QUADS);
		glVertex3f(-4.77f, 4.5f, 0.0f);
		glVertex3f(-2.75f, 4.5f, 0.0f);
		glVertex3f(-0.8f, 5.3f, 0.0f);
		glVertex3f(-4.77f, 5.0f, 0.0f);
		glEnd();

		glColor3f(0.6f, 0.6f, 0.7f);
		glBegin(GL_POLYGON);
		glVertex3f(-5.5f, 0.71f, 0.0f);
		glVertex3f(-5.5f, -0.71f, 0.0f);
		glColor3f(1.0f, 1.0f, 1.0f);	
		glVertex3f(-9.0f, -0.71f, 0.0f);
		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex3f(-12.0f, 0.0f, 0.0f);
		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex3f(-9.0f, 0.71f, 0.0f);
		glEnd();

		glColor3f(173.0f / 256.0f, 216.0f / 256.0f, 230.0f / 256.0f);
		glBegin(GL_POLYGON);
		glVertex3f(-9.0f, 0.71f, 0.0f);
		glVertex3f(-9.5f, 1.0f, 0.0f);
		glVertex3f(-9.5f, 3.2f, 0.0f);
		glVertex3f(-8.0f, 3.1f, 0.0f);
		//glVertex3f(-10.0f, 0.0f, 0.0f);
		glVertex3f(-5.6f, 0.71f, 0.0f);
		glEnd();

		glColor3f(173.0f / 256.0f, 216.0f / 256.0f, 230.0f / 256.0f);
		glBegin(GL_POLYGON);
		glVertex3f(-9.0f, -0.71f, 0.0f);
		glVertex3f(-9.5f, -1.0f, 0.0f);
		glVertex3f(-9.5f, -3.2f, 0.0f);
		glVertex3f(-8.0f, -3.1f, 0.0f);
		//glVertex3f(-10.0f, 0.0f, 0.0f);
		glVertex3f(-5.6f, -0.71f, 0.0f);
		glEnd();
		glTranslatef(-4.2f, 0.0f, 0.01f);  // adjust position
		glScalef(8.0f, 8.0f, 1.0f);     // upscale only the insignia
		DrawIAFInsignia();

		glPopMatrix();
	}
void DrawPlane1() {
	movingFunc();
	glPushMatrix();
	glScalef(0.025f / 2, 0.025f / 2, 0.0f);

	// Translate by x and y passed in from animation logic
	//glTranslatef((planeTopX + 10.0f) * 10, planeTopY*10, 0.0f);
	glTranslatef((planeTopX - 10.0f) * 10.0f, planeTopY * 10.0f, -3.0f);
	glRotatef(-planeTopAngle, 0.0f, 0.0f, 1.0f);

	//glTranslatef(-(planeMiddleX + 10.0f) * 10, 0.0f, 0.0f);
	//glTranslatef(translateX - posbX, 0.0f, -3.0f);


	glColor3f(173.0f / 256.0f, 216.0f / 256.0f, 230.0f / 256.0f);
	glBegin(GL_POLYGON);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, -1.0f, 0.0f);
	glVertex3f(-2.75f, -4.8f, 0.0f);
	glVertex3f(-4.77f, -4.8f, 0.0f);
	glVertex3f(-4.77f, 4.8f, 0.0f);
	glVertex3f(-2.75f, 4.8f, 0.0f);

	glEnd();


	glColor3f(70.0f / 256.0f, 130.0f / 256.0f, 180.0f / 256.0f);
	glBegin(GL_POLYGON);
	glVertex3f(-5.5f, 1.0f, 0.0f);
	glVertex3f(2.0f, 1.0f, 0.0f);
	glVertex3f(5.0f, 0.0f, 0.0f);
	glVertex3f(2.0f, -1.0f, 0.0f);
	glVertex3f(-5.5f, -1.0f, 0.0f);
	glEnd();

	glColor3f(0.6f, 0.6f, 0.7f);
	glBegin(GL_QUADS);
	glVertex3f(-2.75f, -4.5f, 0.0f);
	glVertex3f(-0.75f, -5.3f, 0.0f);
	glVertex3f(-4.77f, -5.0f, 0.0f);
	glVertex3f(-4.77f, -4.5f, 0.0f);

	glEnd();

	glColor3f(0.6f, 0.6f, 0.7f);
	glBegin(GL_QUADS);
	glVertex3f(-4.77f, 4.5f, 0.0f);
	glVertex3f(-2.75f, 4.5f, 0.0f);
	glVertex3f(-0.8f, 5.3f, 0.0f);
	glVertex3f(-4.77f, 5.0f, 0.0f);
	glEnd();

	glColor3f(0.6f, 0.6f, 0.7f);
	glBegin(GL_POLYGON);
	glVertex3f(-5.5f, 0.71f, 0.0f);
	glVertex3f(-5.5f, -0.71f, 0.0f);
	glColor3f(1.0f, 0.6f, 0.2f);
	glVertex3f(-9.0f, -0.71f, 0.0f);
	glColor3f(1.0f, 0.6f, 0.2f);
	glVertex3f(-12.0f, 0.0f, 0.0f);
	glColor3f(1.0f, 0.6f, 0.2f);
	glVertex3f(-9.0f, 0.71f, 0.0f);
	glEnd();

	glColor3f(173.0f / 256.0f, 216.0f / 256.0f, 230.0f / 256.0f);
	glBegin(GL_POLYGON);
	glVertex3f(-9.0f, 0.71f, 0.0f);
	glVertex3f(-9.5f, 1.0f, 0.0f);
	glVertex3f(-9.5f, 3.2f, 0.0f);
	glVertex3f(-8.0f, 3.1f, 0.0f);
	//glVertex3f(-10.0f, 0.0f, 0.0f);
	glVertex3f(-5.6f, 0.71f, 0.0f);
	glEnd();

	glColor3f(173.0f / 256.0f, 216.0f / 256.0f, 230.0f / 256.0f);
	glBegin(GL_POLYGON);
	glVertex3f(-9.0f, -0.71f, 0.0f);
	glVertex3f(-9.5f, -1.0f, 0.0f);
	glVertex3f(-9.5f, -3.2f, 0.0f);
	glVertex3f(-8.0f, -3.1f, 0.0f);
	//glVertex3f(-10.0f, 0.0f, 0.0f);
	glVertex3f(-5.6f, -0.71f, 0.0f);
	glEnd();
	glTranslatef(-4.2f, 0.0f, 0.01f);  // adjust position
	glScalef(8.0f, 8.0f, 1.0f);     // upscale only the insignia
	DrawIAFInsignia();

	glPopMatrix();
}
void DrawPlane2() {
	movingFunc();
	glPushMatrix();
	glScalef(0.025f / 2, 0.025f / 2, 0.0f);
	//glTranslatef(planeBottomX, planeBottomY, 0.0f);
	glTranslatef((planeBottomX - 10.0f) * 10.0f, -planeBottomY * 10.0f, -3.0f);
	glRotatef(planeTopAngle, 0.0f, 0.0f, 1.0f);

	glColor3f(173.0f / 256.0f, 216.0f / 256.0f, 230.0f / 256.0f);
	glBegin(GL_POLYGON);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, -1.0f, 0.0f);
	glVertex3f(-2.75f, -4.8f, 0.0f);
	glVertex3f(-4.77f, -4.8f, 0.0f);
	glVertex3f(-4.77f, 4.8f, 0.0f);
	glVertex3f(-2.75f, 4.8f, 0.0f);

	glEnd();

	glColor3f(70.0f / 256.0f, 130.0f / 256.0f, 180.0f / 256.0f);
	glBegin(GL_POLYGON);
	glVertex3f(-5.5f, 1.0f, 0.0f);
	glVertex3f(2.0f, 1.0f, 0.0f);
	glVertex3f(5.0f, 0.0f, 0.0f);
	glVertex3f(2.0f, -1.0f, 0.0f);
	glVertex3f(-5.5f, -1.0f, 0.0f);
	glEnd();

	glColor3f(0.6f, 0.6f, 0.7f);
	glBegin(GL_QUADS);
	glVertex3f(-2.75f, -4.5f, 0.0f);
	glVertex3f(-0.75f, -5.3f, 0.0f);
	glVertex3f(-4.77f, -5.0f, 0.0f);
	glVertex3f(-4.77f, -4.5f, 0.0f);

	glEnd();

	glColor3f(0.6f, 0.6f, 0.7f);
	glBegin(GL_QUADS);
	glVertex3f(-4.77f, 4.5f, 0.0f);
	glVertex3f(-2.75f, 4.5f, 0.0f);
	glVertex3f(-0.8f, 5.3f, 0.0f);
	glVertex3f(-4.77f, 5.0f, 0.0f);
	glEnd();

	glColor3f(0.6f, 0.6f, 0.7f);
	glBegin(GL_POLYGON);
	glVertex3f(-5.5f, 0.71f, 0.0f);
	glVertex3f(-5.5f, -0.71f, 0.0f);
	glColor3f(0.0754f, 0.563331f, 0.315f);
	glVertex3f(-9.0f, -0.71f, 0.0f);
	glColor3f(0.0754f, 0.563331f, 0.315f);
	glVertex3f(-12.0f, 0.0f, 0.0f);
	glColor3f(0.0754f, 0.563331f, 0.315f);
	glVertex3f(-9.0f, 0.71f, 0.0f);
	glEnd();

	glColor3f(173.0f / 256.0f, 216.0f / 256.0f, 230.0f / 256.0f);
	glBegin(GL_POLYGON);
	glVertex3f(-9.0f, 0.71f, 0.0f);
	glVertex3f(-9.5f, 1.0f, 0.0f);
	glVertex3f(-9.5f, 3.2f, 0.0f);
	glVertex3f(-8.0f, 3.1f, 0.0f);
	//glVertex3f(-10.0f, 0.0f, 0.0f);
	glVertex3f(-5.6f, 0.71f, 0.0f);
	glEnd();

	glColor3f(173.0f / 256.0f, 216.0f / 256.0f, 230.0f / 256.0f);
	glBegin(GL_POLYGON);
	glVertex3f(-9.0f, -0.71f, 0.0f);
	glVertex3f(-9.5f, -1.0f, 0.0f);
	glVertex3f(-9.5f, -3.2f, 0.0f);
	glVertex3f(-8.0f, -3.1f, 0.0f);
	//glVertex3f(-10.0f, 0.0f, 0.0f);
	glVertex3f(-5.6f, -0.71f, 0.0f);
	glEnd();
	glTranslatef(-4.2f, 0.0f, 0.01f);  
	glScalef(8.0f, 8.0f, 1.0f);     
	DrawIAFInsignia();

	glPopMatrix();
}


void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glTranslatef(0.0f, 0.0f, -3.0f);

	glPushMatrix();

	glMatrixMode(GL_MODELVIEW);

	//set it to identity matrix
	glLoadIdentity();

	LetterB();
	LetterH();
	LetterA();
	LetterR();
	LetterA1(-2.1f - translateX);
	LetterT(-2.0f - translateX);

	DrawPlane();
	DrawPlane1();
	DrawPlane2();

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