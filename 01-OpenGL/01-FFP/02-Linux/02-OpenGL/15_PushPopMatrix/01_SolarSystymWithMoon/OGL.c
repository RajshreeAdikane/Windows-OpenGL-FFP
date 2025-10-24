#include<stdio.h>
#include<stdlib.h>
#include<memory.h>

#define _USE_MATH_DEFINES 1 
#include <math.h>

//xlib header files
#include<X11/Xlib.h>
#include<X11/Xutil.h>
#include<X11/XKBlib.h>

//OPENGL RELATED HEADER FILES
#include<GL/gl.h>
#include<GL/glx.h>
#include <GL/glu.h>

#include <SOIL/SOIL.h>

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

//Solar System related Variables
int year = 0;
int date = 0;
int moonAngle = 0;
float skyboxAngle = 0.0f;
GLUquadric* quadric = NULL;
GLfloat size = 50.0f;

//Texture related variables
GLuint background;
GLuint sun_texture;
GLuint earth_texture;
GLuint moon_texture;
GLuint mars_texture;
GLuint saturn_ring;
GLuint jupiter_texture;
GLuint saturn_texture;

//rotation varibales
GLfloat marsYear = 0.0f; // Mars revolution around Sun
GLfloat marsDay = 0.0f;  // Mars rotation on axis

GLfloat jupiterYear = 0.0f;
GLfloat saturnYear = 0.0f;
GLfloat jupiterDay = 0.0f;
GLfloat saturnDay = 0.0f;


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
	//function declaration
    void printGLInfo(void);
    void resize(int, int);
	bool loadGLTexture(GLuint* texture, const char* filename);

    glxContext = glXCreateContext(gpDisplay, visualInfo, NULL, True);
    if(glxContext == NULL)
    {
        fprintf(gpFile, "glxcontex failed!!!!\n");
        return -1;
    }
	glXMakeCurrent(gpDisplay, window, glxContext); 

    if (!loadGLTexture(&background, "background.bmp")) 
    {
        fprintf(gpFile, "Failed to load texture: background\n");
        return -6;
    }
    if (!loadGLTexture(&sun_texture, "sun_texture.bmp"))
    {
        fprintf(gpFile, "Failed to load texture: sun\n");
        return -7;
    }
if (!loadGLTexture(&earth_texture, "earth_texture.bmp"))
{
    fprintf(gpFile, "Failed to load texture: earth\n");
    return -8;
}
if (!loadGLTexture(&moon_texture, "moon_texture.bmp"))
{
    fprintf(gpFile, "Failed to load texture: moon\n");
    return -9;
}
if (!loadGLTexture(&mars_texture, "mars_texture.bmp"))
{
    fprintf(gpFile, "Failed to load texture: mars\n");
    return -10;
}
if (!loadGLTexture(&saturn_ring, "saturn_ring.bmp"))
{
    fprintf(gpFile, "Failed to load texture: saturn_ring\n");
    return -11;
}
if (!loadGLTexture(&jupiter_texture, "jupiter_texture.bmp"))
{
    fprintf(gpFile, "Failed to load texture: jupiter\n");
    return -12;
}
if (!loadGLTexture(&saturn_texture, "saturn_texture.bmp"))
{
    fprintf(gpFile, "Failed to load texture: saturn\n");
    return -13;
}

	
	//printGLInfo
	// printGLInfo();

	// From here Onwords OpenGL code starts
	// Tell OpenGL to choose the color to clear the screen
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // state func

	// Depth related code
	glShadeModel(GL_SMOOTH); // for smoothness
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL); // glcleardepth madhlya 1.0 fragment value <=
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	// Initialize Quadricn
	quadric = gluNewQuadric(); 
	gluQuadricTexture(quadric, GL_TRUE);
	gluQuadricOrientation(quadric, GLU_INSIDE);

	//enable texture
	glEnable(GL_TEXTURE_2D); //cause our texture is 2D


    glXMakeCurrent(gpDisplay, window, glxContext);

    //clear color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    return 0;
}


Bool loadGLTexture(GLuint *texture, const char* imageFilePath)
{
    int width, height;
    unsigned char* imageData = NULL;
    imageData = SOIL_load_image(imageFilePath, &width, &height, NULL, SOIL_LOAD_RGB);

    if(imageData == NULL)
    {
        fprintf(gpFile, "image data failed\n");
        return False;
    }

    // genereta opengl texture objcet
    glGenTextures(1, texture);

    //bind to the newly created empty object
    glBindTexture(GL_TEXTURE_2D, *texture);

    //unpack image in memory for faster loading
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, imageData);
    glBindTexture(GL_TEXTURE_2D, 0);
    SOIL_free_image_data(imageData);
    return True;
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

void drawSaturnRings(float innerRadius, float outerRadius) {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, saturn_ring);

	glBegin(GL_QUAD_STRIP);
	for (int i = 0; i <= 360; i += 10) {
		float angle = i * M_PI / 180.0f;
		float x = cos(angle);
		float y = sin(angle);

		glTexCoord2f((float)i / 360.0f, 0.0f);
		glVertex3f(x * innerRadius/4, y * innerRadius/4, 0.0f);

		glTexCoord2f((float)i / 360.0f, 1.0f);
		glVertex3f(x * outerRadius/12, y * outerRadius/12, 0.0f);
	}
	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void drawOrbit(float radius)
{
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 360; i++)
	{
		float angle = i * 3.14159f / 180.0f;

		glVertex3f(radius * cos(angle), 0.0f, radius * sin(angle));
	}
	glEnd();
}


void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   	// Set matrix mode before anything
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Setup camera
	gluLookAt(0.0, 4.0, 8.0,   // Eye
		0.0, 0.0, 0.0,   // Center
		0.0, 5.0, 0.0);  // Up

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, background);
	glTranslatef(0.0f, 0.0f, 0.0f);
	glRotatef((GLfloat)skyboxAngle, 0.0f, 1.0f, 0.0f);

	glPushMatrix();
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f); // Correct pole 
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINES);
	gluSphere(quadric, 8.0f,50, 50);   
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);

	//Sun
	glPushMatrix();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, sun_texture);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	gluSphere(quadric, 0.5f, 30, 30);

	glPopMatrix();

	// Earth
	glPushMatrix();
	// Earth orbit around Sun

	//orbit
	glDisable(GL_TEXTURE_2D);
	glColor3f(1.0f, 1.0f, 1.0f);
	glLineWidth(0.7f);
	drawOrbit(1.5f);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, earth_texture);
	// around the sun
	glRotatef((GLfloat)year, 0.0f, 1.0f, 0.0f);
	glTranslatef(1.5f, 0.0f, 0.0f);
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, moon_texture);
	glRotatef((GLfloat)moonAngle, 0.0f, 1.0f, 0.0f);
	glTranslatef(0.4f, 0.1f, 0.0f);
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	gluSphere(quadric, 0.1f, 20, 20);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	//adjust polls of the earth
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, earth_texture);
	// earth spin / rotatate around its own axis 
	glRotatef((GLfloat)date, 0.0f, 0.0f, 1.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	gluSphere(quadric, 0.2f, 20, 20);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	glPopMatrix();
	

	// Mars
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	glLineWidth(0.7f);
	drawOrbit(2.5f);
	// Mars revolves around Sun
	glRotatef((GLfloat)marsYear, 0.0f, 1.0f, 0.0f);
	glTranslatef(2.5f, 0.0f, 0.0f); 
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f); 
	glRotatef((GLfloat)marsDay, 0.0f, 0.0f, 1.0f);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, mars_texture); 
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	gluSphere(quadric, 0.17f, 20, 20);

	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	// jupiter
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	glLineWidth(0.7f);
	drawOrbit(3.2f);
	glRotatef((GLfloat)jupiterYear, 0.0f, 1.0f, 0.0f);
	glTranslatef(3.2f, 0.0f, 0.0f);
	glRotatef(-90.0f, 1.0f, 0.0f, 1.0f); 
	glRotatef(3.1f, 0.0f, 0.0f, 1.0f);
	glRotatef((GLfloat)jupiterDay, 0.0f, 0.0f, 1.0f);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, jupiter_texture);
	gluSphere(quadric, 0.12f, 50, 50);  
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	// saturn
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	glLineWidth(0.7f);
	drawOrbit(4.2f);
	glRotatef((GLfloat)saturnYear, 0.0f, 1.0f, 0.0f);
	glTranslatef(4.2f, 0.0f, 0.0f);
	glRotatef(-80.7f, 1.0f, 0.0f, 1.0f); 
	glRotatef((GLfloat)saturnDay, 0.0f, 0.0f, 1.0f);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, saturn_texture);
	gluQuadricTexture(quadric, GL_TRUE);
	gluSphere(quadric, 0.15f, 50, 50);  
	glDisable(GL_TEXTURE_2D);

	// Saturn rings
	glPushMatrix();
	drawSaturnRings(1.2f, 2.2f); 
	glPopMatrix();

	glPopMatrix();

    glXSwapBuffers(gpDisplay, window);
}

void update(void)
{
	// code
	// earth rotate around its oen axis
	if (date < 360) {
		date += 0.1; 
		if (date >= 360) date = 0; 
	}

	// Earth revolution around sun
	if (year < 360) {
		year += 1.0; 
		if (year >= 360) year = 0; 
	}

	// Moon's revolution 
	if (moonAngle < 360) {
		moonAngle += 2; 
		if (moonAngle >= 360) moonAngle = 0; 
	}

	//mars revolution around sun
	marsYear += 1.0f;
	if (marsYear >= 360.0f) marsYear = 0.0f;

	//mars rotate around its oen axis
	marsDay += 0.5f;
	if (marsDay >= 360.0f) marsDay = 0.0f;

	//jupiter revolution around sun
	jupiterYear += 1.2f;
	if (jupiterYear >= 360.0f) jupiterYear = 0.0f;

	//jupiter rotate around its oen axis
	jupiterDay  += 0.5f;
	if (jupiterDay >= 360.0f) jupiterDay = 0.0f;

	//saturn revolution around sun
	saturnYear += 0.8f;
	if (saturnYear >= 360.0f) saturnYear = 0.0f;

	// saturn rotate around its oen axis
	saturnDay += 1.0f;
	if (saturnDay >= 360.0f) saturnDay = 0.0f;

	//galexy starts rotating
	skyboxAngle += 0.05f;
	if (skyboxAngle >= 360.0f) skyboxAngle -= 360.0f;

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



