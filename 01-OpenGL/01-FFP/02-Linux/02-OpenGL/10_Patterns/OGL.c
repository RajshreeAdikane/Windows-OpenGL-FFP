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

//Rotation variables
GLfloat anglePyramid = 0.0f;
GLfloat angleCube = 0.0f;

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

void drawPattern_One(void) {
	glPointSize(5.0);
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_POINTS);
	for (float y = 0.6f; y >= -0.6f; y -= 0.4f) {
		for (float x = -0.6f; x <= 0.6f; x += 0.4f) {
			glVertex2f(x, y);
		}
	}
	glEnd();
}

void drawPattern_Two(void) {
	float startX = -0.6f;
	float startY = 0.6f;
	float step = 0.4f;

	glColor3f(1.0f, 1.0f, 1.0f); 
	glBegin(GL_LINES);
	for (float y = startY; y > -0.6f; y -= step) {
		for (float x = startX; x < 0.6f; x += step) {
			// Vertical line 
			glVertex2f(x, y);
			glVertex2f(x, y - step);

			// Diagonal line 
			glVertex2f(x, y - step);
			glVertex2f(x + step, y);

			// Horizontal line 
			glVertex2f(x, y);
			glVertex2f(x + step, y);
		}
	}
	glEnd();
}

void drawPattern_Three(void) {
	float startX = -0.6f;
	float startY = 0.6f;
	float step = 0.4f;

	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_LINES);

	// Vertical lines
	for (int i = 0; i <= 3; ++i) {
		float x = startX + i * step;
		glVertex2f(x, startY);     
		glVertex2f(x, startY - 3 * step);
	}

	// Horizontal lines 
	for (int i = 0; i <= 3; ++i) {
		float y = startY - i * step;
		glVertex2f(startX, y);        
		glVertex2f(startX + 3 * step, y); 
	}

	glEnd();
}

void drawPattern_Four(void) {
	float startX = -0.6f;
	float startY = 0.6f;
	float step = 0.4f;

	glColor3f(1.0f, 1.0f, 1.0f); 
	glBegin(GL_LINES);

	glBegin(GL_LINES);

	// Vertical lines 
	for (int i = 0; i <= 3; ++i) {
		float x = startX + i * step;
		glVertex2f(x, startY);         
		glVertex2f(x, startY - 3 * step); 
	}

	// Horizontal lines
	for (int i = 0; i <= 3; ++i) {
		float y = startY - i * step;
		glVertex2f(startX, y);         
		glVertex2f(startX + 3 * step, y); 
	}
	for (float y = startY; y > -0.6f; y -= step) {
		for (float x = startX; x < 0.6f; x += step) {
			
			glVertex2f(x, y - step);
			glVertex2f(x + step, y);
		}
	}

	glEnd();

}

void drawPattern_Five() {
	float startX = -0.6f;
	float startY = 0.6f;
	float width = 1.2f; 
	float step = 0.2f;

	glColor3f(1.0f, 1.0f, 1.0f); 

	glBegin(GL_LINES);

	// Draw square boundary
	glVertex2f(startX, startY);      
	glVertex2f(startX + width, startY);          
	glVertex2f(startX + width, startY);     
	glVertex2f(startX + width, startY - width);
	glVertex2f(startX + width, startY - width); 
	glVertex2f(startX, startY - width);         
	glVertex2f(startX, startY - width);      
	glVertex2f(startX, startY);              

	// Diagonal rays from top-left to bottom edge 
	for (float x = startX + 0.4f; x <= startX + width; x += 0.4f) {
		glVertex2f(startX, startY);  
		glVertex2f(x, startY - width); 
	}

	// Diagonal rays from top-left to right edge 
	for (float y = startY - 0.4f; y >= startY - width; y -= 0.4f) {
		glVertex2f(startX, startY);    
		glVertex2f(startX + width, y); 
	}

	glEnd();

}

void drawPattern_Six(void) {
	float startX = -0.6f;
	float startY = 0.6f;
	float step = 0.4f;

	// Drawing the grid lines
	glColor3f(1.0f, 1.0f, 1.0f); 
	glBegin(GL_LINES);

	// Vertical lines
	for (int i = 0; i <= 3; ++i) {
		float x = startX + i * step;
		glVertex2f(x, startY);          
		glVertex2f(x, startY - 3 * step); 
	}

	// Horizontal lines 
	for (int i = 0; i <= 3; ++i) {
		float y = startY - i * step;
		glVertex2f(startX, y);         
		glVertex2f(startX + 3 * step, y); 
	}

	glEnd();

	// Fill left vertical blocks (Red)
	glColor3f(1.0f, 0.01f, 0.01f); // Red
	glBegin(GL_QUADS);
	glVertex2f(startX + 0.01f, startY - 0.01f);                // Top-left
	glVertex2f(startX + step - 0.01f, startY - 0.01f);          // Top-right
	glVertex2f(startX + step - 0.01f, startY - step + 0.01f);    // Bottom-right
	glVertex2f(startX + 0.01f, startY - step + 0.01f);           // Bottom-left

	glVertex2f(startX + 0.01f, startY - step - 0.01f);          // Second row top-left
	glVertex2f(startX + step - 0.01f, startY - step - 0.01f);    // Second row top-right
	glVertex2f(startX + step - 0.01f, startY - 2 * step + 0.01f); // Second row bottom-right
	glVertex2f(startX + 0.01f, startY - 2 * step + 0.01f);       // Second row bottom-left

	glVertex2f(startX + 0.01f, startY - 2 * step - 0.01f);      // Third row top-left
	glVertex2f(startX + step - 0.01f, startY - 2 * step - 0.01f); // Third row top-right
	glVertex2f(startX + step - 0.01f, startY - 3 * step + 0.01f); // Third row bottom-right
	glVertex2f(startX + 0.01f, startY - 3 * step + 0.01f);       // Third row bottom-left
	glEnd();

	// Fill middle vertical blocks (Green)
	glColor3f(0.01f, 1.0f, 0.01f); // Green
	glBegin(GL_QUADS);
	glVertex2f(startX + step + 0.01f, startY - 0.01f);                // Top-left
	glVertex2f(startX + 2 * step - 0.01f, startY - 0.01f);             // Top-right
	glVertex2f(startX + 2 * step - 0.01f, startY - step + 0.01f);       // Bottom-right
	glVertex2f(startX + step + 0.01f, startY - step + 0.01f);           // Bottom-left

	glVertex2f(startX + step + 0.01f, startY - step - 0.01f);          // Second row top-left
	glVertex2f(startX + 2 * step - 0.01f, startY - step - 0.01f);       // Second row top-right
	glVertex2f(startX + 2 * step - 0.01f, startY - 2 * step + 0.01f);    // Second row bottom-right
	glVertex2f(startX + step + 0.01f, startY - 2 * step + 0.01f);       // Second row bottom-left

	glVertex2f(startX + step + 0.01f, startY - 2 * step - 0.01f);      // Third row top-left
	glVertex2f(startX + 2 * step - 0.01f, startY - 2 * step - 0.01f);   // Third row top-right
	glVertex2f(startX + 2 * step - 0.01f, startY - 3 * step + 0.01f);   // Third row bottom-right
	glVertex2f(startX + step + 0.01f, startY - 3 * step + 0.01f);      // Third row bottom-left
	glEnd();

	// Fill right vertical blocks (Blue)
	glColor3f(0.01f, 0.01f, 1.0f); // Blue
	glBegin(GL_QUADS);
	glVertex2f(startX + 2 * step + 0.01f, startY - 0.01f);                // Top-left
	glVertex2f(startX + 3 * step - 0.01f, startY - 0.01f);                 // Top-right
	glVertex2f(startX + 3 * step - 0.01f, startY - step + 0.01f);           // Bottom-right
	glVertex2f(startX + 2 * step + 0.01f, startY - step + 0.01f);           // Bottom-left

	glVertex2f(startX + 2 * step + 0.01f, startY - step - 0.01f);          // Second row top-left
	glVertex2f(startX + 3 * step - 0.01f, startY - step - 0.01f);           // Second row top-right
	glVertex2f(startX + 3 * step - 0.01f, startY - 2 * step + 0.01f);       // Second row bottom-right
	glVertex2f(startX + 2 * step + 0.01f, startY - 2 * step + 0.01f);       // Second row bottom-left

	glVertex2f(startX + 2 * step + 0.01f, startY - 2 * step - 0.01f);      // Third row top-left
	glVertex2f(startX + 3 * step - 0.01f, startY - 2 * step - 0.01f);       // Third row top-right
	glVertex2f(startX + 3 * step - 0.01f, startY - 3 * step + 0.01f);       // Third row bottom-right
	glVertex2f(startX + 2 * step + 0.01f, startY - 3 * step + 0.01f);       // Third row bottom-left
	glEnd();
}


void display(void)
{
	// Clear OpenGL buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Get current window size
	int windowWidth, windowHeight;
	Window root;
	int x, y;
	unsigned int borderWidth, depth;

	XGetGeometry(gpDisplay, window, &root, &x, &y, 
	             (unsigned int *)&windowWidth, 
	             (unsigned int *)&windowHeight, 
	             &borderWidth, &depth);

	// Define grid layout
	const int columns = 3;
	const int rows = 2;

	// Calculate cell size
	int cellWidth = windowWidth / columns;
	int cellHeight = windowHeight / rows;

	// Loop through all 6 cells
	for (int patternIndex = 0; patternIndex < 6; patternIndex++)
	{
		int col = patternIndex % columns;
		int row = patternIndex / columns;

		// Flip Y-axis (OpenGL origin is bottom-left)
		int viewportX = col * cellWidth;
		int viewportY = (rows - 1 - row) * cellHeight;

		// Set viewport for this cell
		glViewport(viewportX, viewportY, cellWidth, cellHeight);

		// Set up projection
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(-1.0, 1.0, -1.0, 1.0);  // 2D orthographic

		// Set modelview matrix
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		// Draw the corresponding pattern
		switch (patternIndex)
		{
		case 0: drawPattern_One();   break;
		case 1: drawPattern_Two();   break;
		case 2: drawPattern_Three(); break;
		case 3: drawPattern_Four();  break;
		case 4: drawPattern_Five();  break;
		case 5: drawPattern_Six();   break;
		}
	}

	// Swap buffers
	glXSwapBuffers(gpDisplay, window);
}


void update(void)
{
	// code

	anglePyramid = anglePyramid + 2.0f;

	if (anglePyramid >= 360.0f)
	{
		anglePyramid = anglePyramid - 360.0f;
	}

	angleCube = angleCube - 2.0f;
	if (angleCube <= 0)
	{
		angleCube = angleCube + 360.0f;
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



