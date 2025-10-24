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

// Variable
GLUquadric* quadric = NULL;

// Light
Bool blight = False;
GLfloat lightAmbient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
GLfloat lightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat lightPosition[] = { 0.0f, 0.0f, 0.0f, 1.0f };

GLfloat angleForXRotation = 0.0f;
GLfloat angleForYRotation = 0.0f;
GLfloat angleForZRotation = 0.0f;
GLuint keyPressed = 0;

int main(void)
{
    //function declarations
    void toggleFullSCreen(void);
    int initialize(void);
    void resize(int, int);
    void display(void);
    void update(void);
    void uninitialize(void);
	void CenterWindow(Display *display, Window window);
	

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

	CenterWindow(gpDisplay, window);
	
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
                        case 'X':
		case 'x':
			keyPressed = 1;
			angleForXRotation = 0.0f;	// Reset
			break;

		case 'Y':
		case 'y':
			keyPressed = 2;
			angleForYRotation = 0.0f;	// Reset
			break;

		case 'Z':
		case 'z':
			keyPressed = 3;
			angleForZRotation = 0.0f;	// Reset
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

// Centering of Window
void CenterWindow(Display *display, Window window)
{
    XWindowAttributes attr;
    XGetWindowAttributes(display, window, &attr);

    int windowWidth  = attr.width;
    int windowHeight = attr.height;

    int screenWidth  = XDisplayWidth(display, DefaultScreen(display));
    int screenHeight = XDisplayHeight(display, DefaultScreen(display));

    int x = (screenWidth - windowWidth) / 2;
    int y = (screenHeight - windowHeight) / 2;

    XMoveWindow(display, window, x, y);
    XFlush(display); // Apply changes immediately
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

   glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// Depth related code
	glShadeModel(GL_SMOOTH); // for smoothness
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	// Light
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
	glEnable(GL_LIGHT0);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	quadric = gluNewQuadric();

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

	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);


}



void display(void)
{
   
// Variable declarations
	GLfloat materialAmbient[4];
	GLfloat materialDiffuse[4];
	GLfloat materialSpecular[4];
	GLfloat materialShininess;

	// code

	// Clear the color and depth buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Set the matrix mode to model-view
	glMatrixMode(GL_MODELVIEW);
  	glLoadIdentity();
	//glPushMatrix();
	glTranslatef(-7.0f, -7.0f, -30.0f); // Initial view translation

	glPushMatrix(); 

	// Animation
	if (keyPressed == 1)
	{

		glRotatef(angleForXRotation, 1.0f, 0.0f, 0.0f);
		lightPosition[2] = angleForXRotation;
	}

	if (keyPressed == 2)
	{

		glRotatef(angleForYRotation, 0.0f, 1.0f, 0.0f);
		lightPosition[0] = angleForYRotation;
	}

	if (keyPressed == 3)
	{

		glRotatef(angleForZRotation, 0.0f, 0.0f, 1.0f);
		lightPosition[1] = angleForZRotation;
	}

	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	glPopMatrix();


	//////// First Column : Precious Stones

	//// 1. Emerald Material
	materialAmbient[0] = 0.0215f;
	materialAmbient[1] = 0.1745f;
	materialAmbient[2] = 0.0215f;
	materialAmbient[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient);

	materialDiffuse[0] = 0.07568f;
	materialDiffuse[1] = 0.61424f;
	materialDiffuse[2] = 0.07568f;
	materialDiffuse[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse);

	materialSpecular[0] = 0.633f;
	materialSpecular[1] = 0.727811f;
	materialSpecular[2] = 0.633f;
	materialSpecular[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular);

	materialShininess = 0.6f * 128.0f;
	glMaterialf(GL_FRONT, GL_SHININESS, materialShininess);

	//glLoadIdentity();
	glPushMatrix();
	glTranslatef(1.5f, 14.0f, -0.0f);
	gluSphere(quadric, 1.0f, 30, 30);
	glPopMatrix();


	//// 2. Jade Material
	materialAmbient[0] = 0.135f;
	materialAmbient[1] = 0.2225f;
	materialAmbient[2] = 0.1575f;
	materialAmbient[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient);

	materialDiffuse[0] = 0.54f;
	materialDiffuse[1] = 0.89f;
	materialDiffuse[2] = 0.63f;
	materialDiffuse[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse);

	materialSpecular[0] = 0.316228f;
	materialSpecular[1] = 0.316228f;
	materialSpecular[2] = 0.316228f;
	materialSpecular[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular);

	materialShininess = 0.1f * 128.0f;
	glMaterialf(GL_FRONT, GL_SHININESS, materialShininess);

   	//glLoadIdentity();
	glPushMatrix();
	glTranslatef(1.5f, 11.5f, 0.0f);
	gluSphere(quadric, 1.0f, 30, 30);
	glPopMatrix();


	//// 3. Obsidian Material
	materialAmbient[0] = 0.05375f;
	materialAmbient[1] = 0.05f;
	materialAmbient[2] = 0.06625f;
	materialAmbient[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient);

	materialDiffuse[0] = 0.18275f;
	materialDiffuse[1] = 0.17f;
	materialDiffuse[2] = 0.22525f;
	materialDiffuse[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse);

	materialSpecular[0] = 0.332741f;
	materialSpecular[1] = 0.328634f;
	materialSpecular[2] = 0.346435f;
	materialSpecular[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular);

	materialShininess = 0.3f * 128.0f;
	glMaterialf(GL_FRONT, GL_SHININESS, materialShininess);

  	//glLoadIdentity();
	glPushMatrix();
	glTranslatef(1.5f, 9.0f, -0.0f);
	gluSphere(quadric, 1.0f, 30, 30);
	glPopMatrix();

	//// 4. Pearl Material
	materialAmbient[0] = 0.25f;
	materialAmbient[1] = 0.20725f;
	materialAmbient[2] = 0.20725f;
	materialAmbient[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient);

	materialDiffuse[0] = 1.0f;
	materialDiffuse[1] = 0.829f;
	materialDiffuse[2] = 0.829f;
	materialDiffuse[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse);

	materialSpecular[0] = 0.296648f;
	materialSpecular[1] = 0.296648f;
	materialSpecular[2] = 0.296648f;
	materialSpecular[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular);

	materialShininess = 0.088f * 128.0f;
	glMaterialf(GL_FRONT, GL_SHININESS, materialShininess);

  	//glLoadIdentity();
	glPushMatrix();
	glTranslatef(1.5f, 6.5f, -0.0f);
	gluSphere(quadric, 1.0f, 30, 30);
	glPopMatrix();

	//// 5. Ruby Material 
	materialAmbient[0] = 0.1745f;
	materialAmbient[1] = 0.01175f;
	materialAmbient[2] = 0.01175f;
	materialAmbient[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient);

	materialDiffuse[0] = 0.61424f;
	materialDiffuse[1] = 0.04136f;
	materialDiffuse[2] = 0.04136f;
	materialDiffuse[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse);

	materialSpecular[0] = 0.727811f;
	materialSpecular[1] = 0.626959f;
	materialSpecular[2] = 0.626959f;
	materialSpecular[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular);

	materialShininess = 0.6f * 128.0f;
	glMaterialf(GL_FRONT, GL_SHININESS, materialShininess);

 	//glLoadIdentity();
	glPushMatrix();
	glTranslatef(1.5f, 4.0f, -0.0f);
	gluSphere(quadric, 1.0f, 30, 30);
	glPopMatrix();


	//// 6. Turquoise Material
	materialAmbient[0] = 0.1f;
	materialAmbient[1] = 0.18725f;
	materialAmbient[2] = 0.1745f;
	materialAmbient[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient);

	materialDiffuse[0] = 0.396f;
	materialDiffuse[1] = 0.74151f;
	materialDiffuse[2] = 0.69102f;
	materialDiffuse[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse);

	materialSpecular[0] = 0.297254f;
	materialSpecular[1] = 0.30829f;
	materialSpecular[2] = 0.306678f;
	materialSpecular[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular);

	materialShininess = 0.1f * 128.0f;
	glMaterialf(GL_FRONT, GL_SHININESS, materialShininess);

 	//glLoadIdentity();
	glPushMatrix();
	glTranslatef(1.5f, 1.5f, -0.0f);
	gluSphere(quadric, 1.0f, 30, 30);
	glPopMatrix();


	//////// Second Column : Metals

	//// 1. Brass Material
	materialAmbient[0] = 0.329412f;
	materialAmbient[1] = 0.223529f;
	materialAmbient[2] = 0.027451f;
	materialAmbient[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient);

	materialDiffuse[0] = 0.780392f;
	materialDiffuse[1] = 0.568627f;
	materialDiffuse[2] = 0.113725f;
	materialDiffuse[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse);

	materialSpecular[0] = 0.992157f;
	materialSpecular[1] = 0.941176f;
	materialSpecular[2] = 0.807843f;
	materialSpecular[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular);

	materialShininess = 0.21794872f * 128.0f;
	glMaterialf(GL_FRONT, GL_SHININESS, materialShininess);

 	//glLoadIdentity();
	glPushMatrix();
	glTranslatef(7.5f, 14.0f, -0.0f);
	gluSphere(quadric, 1.0f, 30, 30);
	glPopMatrix();

	//// 2. Bronze Material
	materialAmbient[0] = 0.2125f;
	materialAmbient[1] = 0.1275f;
	materialAmbient[2] = 0.054f;
	materialAmbient[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient);

	materialDiffuse[0] = 0.714f;
	materialDiffuse[1] = 0.4284f;
	materialDiffuse[2] = 0.18144f;
	materialDiffuse[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse);

	materialSpecular[0] = 0.393548f;
	materialSpecular[1] = 0.271906f;
	materialSpecular[2] = 0.166721f;
	materialSpecular[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular);

	materialShininess = 0.2f * 128.0f;
	glMaterialf(GL_FRONT, GL_SHININESS, materialShininess);

 	//glLoadIdentity();
	glPushMatrix();
	glTranslatef(7.5f, 11.5f, -0.0f);
	gluSphere(quadric, 1.0f, 30, 30);
	glPopMatrix();

	//// 3. Chrome Material
	materialAmbient[0] = 0.25f;
	materialAmbient[1] = 0.25f;
	materialAmbient[2] = 0.25f;
	materialAmbient[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient);

	materialDiffuse[0] = 0.4f;
	materialDiffuse[1] = 0.4f;
	materialDiffuse[2] = 0.4f;
	materialDiffuse[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse);

	materialSpecular[0] = 0.774597f;
	materialSpecular[1] = 0.774597f;
	materialSpecular[2] = 0.774597f;
	materialSpecular[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular);

	materialShininess = 0.6f * 128.0f;
	glMaterialf(GL_FRONT, GL_SHININESS, materialShininess);

 	//glLoadIdentity();
	glPushMatrix();
	glTranslatef(7.5f, 9.0f, -0.0f);
	gluSphere(quadric, 1.0f, 30, 30);
	glPopMatrix();

	//// 4. Copper Material
	materialAmbient[0] = 0.19125f;
	materialAmbient[1] = 0.0735f;
	materialAmbient[2] = 0.0225f;
	materialAmbient[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient);

	materialDiffuse[0] = 0.7038f;
	materialDiffuse[1] = 0.27048f;
	materialDiffuse[2] = 0.0828f;
	materialDiffuse[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse);

	materialSpecular[0] = 0.256777f;
	materialSpecular[1] = 0.137622f;
	materialSpecular[2] = 0.086014f;
	materialSpecular[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular);

	materialShininess = 0.1f * 128.0f;
	glMaterialf(GL_FRONT, GL_SHININESS, materialShininess);

 	//glLoadIdentity();
	glPushMatrix();
	glTranslatef(7.5f, 6.5f, -0.0f);
	gluSphere(quadric, 1.0f, 30, 30);
	glPopMatrix();

	//// 5. Gold Material 
	materialAmbient[0] = 0.24725f;
	materialAmbient[1] = 0.1995f;
	materialAmbient[2] = 0.0745f;
	materialAmbient[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient);

	materialDiffuse[0] = 0.75164f;
	materialDiffuse[1] = 0.60648f;
	materialDiffuse[2] = 0.22648f;
	materialDiffuse[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse);

	materialSpecular[0] = 0.628281f;
	materialSpecular[1] = 0.555802f;
	materialSpecular[2] = 0.366065f;
	materialSpecular[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular);

	materialShininess = 0.4f * 128.0f;
	glMaterialf(GL_FRONT, GL_SHININESS, materialShininess);

 	//glLoadIdentity();
	glPushMatrix();
	glTranslatef(7.5f, 4.0f, -0.0f);
	gluSphere(quadric, 1.0f, 30, 30);
	glPopMatrix();

	//// 6. Silver Material
	materialAmbient[0] = 0.19225f;
	materialAmbient[1] = 0.19225f;
	materialAmbient[2] = 0.19225f;
	materialAmbient[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient);

	materialDiffuse[0] = 0.50754f;
	materialDiffuse[1] = 0.50754f;
	materialDiffuse[2] = 0.50754f;
	materialDiffuse[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse);

	materialSpecular[0] = 0.508273f;
	materialSpecular[1] = 0.508273f;
	materialSpecular[2] = 0.508273f;
	materialSpecular[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular);

	materialShininess = 0.4f * 128.0f;
	glMaterialf(GL_FRONT, GL_SHININESS, materialShininess);

 	//glLoadIdentity();
	glPushMatrix();
	glTranslatef(7.5f, 1.5f, -0.0f);
	gluSphere(quadric, 1.0f, 30, 30);
	glPopMatrix();



	//////// Third Column : Plastics

	//// 1. Black Material
	materialAmbient[0] = 0.0f;
	materialAmbient[1] = 0.0f;
	materialAmbient[2] = 0.0f;
	materialAmbient[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient);

	materialDiffuse[0] = 0.01f;
	materialDiffuse[1] = 0.01f;
	materialDiffuse[2] = 0.01f;
	materialDiffuse[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse);

	materialSpecular[0] = 0.50f;
	materialSpecular[1] = 0.50f;
	materialSpecular[2] = 0.50f;
	materialSpecular[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular);

	materialShininess = 0.25f * 128.0f;
	glMaterialf(GL_FRONT, GL_SHININESS, materialShininess);

 	//glLoadIdentity();
	glPushMatrix();
	glTranslatef(13.5f, 14.0f, -0.0f);
	gluSphere(quadric, 1.0f, 30, 30);
	glPopMatrix();

	//// 2. Cyan Material
	materialAmbient[0] = 0.0f;
	materialAmbient[1] = 0.1f;
	materialAmbient[2] = 0.06f;
	materialAmbient[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient);

	materialDiffuse[0] = 0.0f;
	materialDiffuse[1] = 0.50980392f;
	materialDiffuse[2] = 0.50980392f;
	materialDiffuse[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse);

	materialSpecular[0] = 0.50196078f;
	materialSpecular[1] = 0.50196078f;
	materialSpecular[2] = 0.50196078f;
	materialSpecular[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular);

	materialShininess = 0.25f * 128.0f;
	glMaterialf(GL_FRONT, GL_SHININESS, materialShininess);

 	//glLoadIdentity();
	glPushMatrix();
	glTranslatef(13.5f, 11.5f, -0.0f);
	gluSphere(quadric, 1.0f, 30, 30);
	glPopMatrix();

	//// 3. Green Material
	materialAmbient[0] = 0.0f;
	materialAmbient[1] = 0.0f;
	materialAmbient[2] = 0.0f;
	materialAmbient[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient);

	materialDiffuse[0] = 0.1f;
	materialDiffuse[1] = 0.35f;
	materialDiffuse[2] = 0.1f;
	materialDiffuse[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse);

	materialSpecular[0] = 0.45f;
	materialSpecular[1] = 0.55f;
	materialSpecular[2] = 0.45f;
	materialSpecular[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular);

	materialShininess = 0.25f * 128.0f;
	glMaterialf(GL_FRONT, GL_SHININESS, materialShininess);

 	//glLoadIdentity();
	glPushMatrix();
	glTranslatef(13.5f, 9.0f, -0.0f);
	gluSphere(quadric, 1.0f, 30, 30);
	glPopMatrix();

	//// 4. Red Material
	materialAmbient[0] = 0.0f;
	materialAmbient[1] = 0.0f;
	materialAmbient[2] = 0.0f;
	materialAmbient[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient);

	materialDiffuse[0] = 0.5f;
	materialDiffuse[1] = 0.0f;
	materialDiffuse[2] = 0.0f;
	materialDiffuse[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse);

	materialSpecular[0] = 0.7f;
	materialSpecular[1] = 0.6f;
	materialSpecular[2] = 0.6f;
	materialSpecular[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular);

	materialShininess = 0.25f * 128.0f;
	glMaterialf(GL_FRONT, GL_SHININESS, materialShininess);

 	//glLoadIdentity();
	glPushMatrix();
	glTranslatef(13.5f, 6.5f, -0.0f);
	gluSphere(quadric, 1.0f, 30, 30);
	glPopMatrix();

	//// 5. White Material 
	materialAmbient[0] = 0.0f;
	materialAmbient[1] = 0.0f;
	materialAmbient[2] = 0.0f;
	materialAmbient[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient);

	materialDiffuse[0] = 0.55f;
	materialDiffuse[1] = 0.55f;
	materialDiffuse[2] = 0.55f;
	materialDiffuse[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse);

	materialSpecular[0] = 0.7f;
	materialSpecular[1] = 0.7f;
	materialSpecular[2] = 0.7f;
	materialSpecular[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular);

	materialShininess = 0.25f * 128.0f;
	glMaterialf(GL_FRONT, GL_SHININESS, materialShininess);

 	//glLoadIdentity();
	glPushMatrix();
	glTranslatef(13.5f, 4.0f, -0.0f);
	gluSphere(quadric, 1.0f, 30, 30);
	glPopMatrix();

	//// 6. Yellow Material
	materialAmbient[0] = 0.0f;
	materialAmbient[1] = 0.0f;
	materialAmbient[2] = 0.0f;
	materialAmbient[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient);

	materialDiffuse[0] = 0.5f;
	materialDiffuse[1] = 0.5f;
	materialDiffuse[2] = 0.5f;
	materialDiffuse[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse);

	materialSpecular[0] = 0.6f;
	materialSpecular[1] = 0.6f;
	materialSpecular[2] = 0.6f;
	materialSpecular[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular);

	materialShininess = 0.25f * 128.0f;
	glMaterialf(GL_FRONT, GL_SHININESS, materialShininess);

 	//glLoadIdentity();
	glPushMatrix();
	glTranslatef(13.5f, 1.5f, -0.0f);
	gluSphere(quadric, 1.0f, 30, 30);
	glPopMatrix();


	//////// Fourth Column : Rubber

	//// 1. Black Material
	materialAmbient[0] = 0.02f;
	materialAmbient[1] = 0.02f;
	materialAmbient[2] = 0.02f;
	materialAmbient[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient);

	materialDiffuse[0] = 0.01f;
	materialDiffuse[1] = 0.01f;
	materialDiffuse[2] = 0.01f;
	materialDiffuse[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse);

	materialSpecular[0] = 0.40f;
	materialSpecular[1] = 0.40f;
	materialSpecular[2] = 0.40f;
	materialSpecular[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular);

	materialShininess = 0.078125f * 128.0f;
	glMaterialf(GL_FRONT, GL_SHININESS, materialShininess);

 	//glLoadIdentity();
	glPushMatrix();
	glTranslatef(19.5f, 14.0f, -0.0f);
	gluSphere(quadric, 1.0f, 30, 30);
	glPopMatrix();

	//// 2. Cyan Material
	materialAmbient[0] = 0.0f;
	materialAmbient[1] = 0.05f;
	materialAmbient[2] = 0.05f;
	materialAmbient[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient);

	materialDiffuse[0] = 0.4f;
	materialDiffuse[1] = 0.5f;
	materialDiffuse[2] = 0.5f;
	materialDiffuse[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse);

	materialSpecular[0] = 0.04f;
	materialSpecular[1] = 0.7f;
	materialSpecular[2] = 0.7f;
	materialSpecular[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular);

	materialShininess = 0.078125f * 128.0f;
	glMaterialf(GL_FRONT, GL_SHININESS, materialShininess);

 	//glLoadIdentity();
	glPushMatrix();
	glTranslatef(19.5f, 11.5f, -0.0f);
	gluSphere(quadric, 1.0f, 30, 30);
	glPopMatrix();

	//// 3. Green Material
	materialAmbient[0] = 0.0f;
	materialAmbient[1] = 0.05f;
	materialAmbient[2] = 0.0f;
	materialAmbient[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient);

	materialDiffuse[0] = 0.4f;
	materialDiffuse[1] = 0.5f;
	materialDiffuse[2] = 0.4f;
	materialDiffuse[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse);

	materialSpecular[0] = 0.04f;
	materialSpecular[1] = 0.7f;
	materialSpecular[2] = 0.04f;
	materialSpecular[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular);

	materialShininess = 0.078125f * 128.0f;
	glMaterialf(GL_FRONT, GL_SHININESS, materialShininess);

 	//glLoadIdentity();
	glPushMatrix();
	glTranslatef(19.5f, 9.0f, -0.0f);
	gluSphere(quadric, 1.0f, 30, 30);
	glPopMatrix();

	//// 4. Red Material
	materialAmbient[0] = 0.05f;
	materialAmbient[1] = 0.0f;
	materialAmbient[2] = 0.0f;
	materialAmbient[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient);

	materialDiffuse[0] = 0.5f;
	materialDiffuse[1] = 0.4f;
	materialDiffuse[2] = 0.4f;
	materialDiffuse[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse);

	materialSpecular[0] = 0.7f;
	materialSpecular[1] = 0.04f;
	materialSpecular[2] = 0.04f;
	materialSpecular[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular);

	materialShininess = 0.078125f * 128.0f;
	glMaterialf(GL_FRONT, GL_SHININESS, materialShininess);

 	//glLoadIdentity();
	glPushMatrix();
	glTranslatef(19.5f, 6.5f, -0.0f);
	gluSphere(quadric, 1.0f, 30, 30);
	glPopMatrix();

	//// 5. White Material 
	materialAmbient[0] = 0.05f;
	materialAmbient[1] = 0.05f;
	materialAmbient[2] = 0.05f;
	materialAmbient[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient);

	materialDiffuse[0] = 0.5f;
	materialDiffuse[1] = 0.5f;
	materialDiffuse[2] = 0.5f;
	materialDiffuse[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse);

	materialSpecular[0] = 0.7f;
	materialSpecular[1] = 0.7f;
	materialSpecular[2] = 0.7f;
	materialSpecular[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular);

	materialShininess = 0.078125f * 128.0f;
	glMaterialf(GL_FRONT, GL_SHININESS, materialShininess);

 	//glLoadIdentity();
	glPushMatrix();
	glTranslatef(19.5f, 4.0f, -0.0f);
	gluSphere(quadric, 1.0f, 30, 30);
	glPopMatrix();


	//// 6. Yellow Material
	materialAmbient[0] = 0.05f;
	materialAmbient[1] = 0.05f;
	materialAmbient[2] = 0.0f;
	materialAmbient[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient);

	materialDiffuse[0] = 0.5f;
	materialDiffuse[1] = 0.5f;
	materialDiffuse[2] = 0.4f;
	materialDiffuse[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse);

	materialSpecular[0] = 0.7f;
	materialSpecular[1] = 0.7f;
	materialSpecular[2] = 0.04f;
	materialSpecular[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular);

	materialShininess = 0.078125f * 128.0f;
	glMaterialf(GL_FRONT, GL_SHININESS, materialShininess);

 	//glLoadIdentity();
	glPushMatrix();
	glTranslatef(19.5f, 1.5f, -0.0f);
	gluSphere(quadric, 1.0f, 30, 30);
	glPopMatrix();

	//////// End Of Materials



    glXSwapBuffers(gpDisplay, window);
}
void update(void)
{
    // code

	if (keyPressed == 1)
	{

		angleForXRotation = angleForXRotation + 1.0f;

		/*if (angleForXRotation >= 360.0f) {

			angleForXRotation = angleForXRotation - 360.0f;
		}*/
	}

	if (keyPressed == 2)
	{

		angleForYRotation = angleForYRotation + 1.0f;

		/*if (angleForYRotation >= 360.0f) {

			angleForYRotation = angleForYRotation - 360.0f;
		}*/
	}

	if (keyPressed == 3)
	{

		angleForZRotation = angleForZRotation + 1.0f;

		/*if (angleForZRotation >= 360.0f) {

			angleForZRotation = angleForZRotation - 360.0f;
		}*/
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



