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
#include<SOIL/SOIL.h>

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

#define MAX_LIMITS_CUBE_TRANSLATE_X 8.0f
#define MIN_LIMITS_CUBE_TRANSLATE_X -8.0f

#define MAX_LIMITS_CUBE_TRANSLATE_Y 4.0f
#define MIN_LIMITS_CUBE_TRANSLATE_Y 0.45f

#define CLOSEST_LIMIT_CUBE_TRANSLATE_Z 5.0f 
#define FARTHEST_LIMIT_CUBE_TRANSLATE_Z -20.0f 

#define INCREMENT 0.1f
#define DECREMENT 0.1f

GLfloat angleCube = 0.0f;


// Lights Variable
GLfloat lightAmbient[] = { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat lightDefuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat lightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat lightPositon[] = { 0.0f, 5.0f, 10.0f, 2.0f }; //x ,y, z, w

GLfloat materialAmbient[] = { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat materialDeffuse[] = { 1.0f, 0.0f, 0.0f, 1.0f };
GLfloat materialSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat materialShininess = 128.0f;

//Texture related variables
GLuint texture_marble;

GLfloat translateCubeX = 0.0f;
GLfloat translateCubeY = 1.0f;
GLfloat translateCubeZ = 0.0f;

GLfloat CubeScale = 0.25f;


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

                    case XK_Right:  // +X axis
            if (translateCubeX < MAX_LIMITS_CUBE_TRANSLATE_X)
                translateCubeX += INCREMENT;
            break;

        case XK_Left:   // -X axis
            if (translateCubeX > MIN_LIMITS_CUBE_TRANSLATE_X)
                translateCubeX -= DECREMENT;
            break;

        case XK_Up:     // +Y axis
            if (translateCubeY < MAX_LIMITS_CUBE_TRANSLATE_Y)
                translateCubeY += INCREMENT;
            break;

        case XK_Down:   // -Y axis
            if (translateCubeY > MIN_LIMITS_CUBE_TRANSLATE_Y)
                translateCubeY -= DECREMENT;
            break;

        case XK_KP_Add:     // Numpad '+', cube moves away from viewer
        case XK_plus:       // Regular '+'
        case XK_equal: 
            if (translateCubeZ < CLOSEST_LIMIT_CUBE_TRANSLATE_Z)
                translateCubeZ += INCREMENT;
            break;

        case XK_KP_Subtract: // Numpad '-'
        case XK_minus:       // Regular '-'
            if (translateCubeZ > FARTHEST_LIMIT_CUBE_TRANSLATE_Z)
                translateCubeZ -= DECREMENT;
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

    // function declarations
    void printGLInfo(void);
    void resize(int, int);
    Bool loadGLTexture(GLuint*, const char*);

    glxContext = glXCreateContext(gpDisplay, visualInfo, NULL, True);
    if(glxContext == NULL)
    {
        fprintf(gpFile, "glxcontex failed!!!!\n");
        return -1;
    }

    glXMakeCurrent(gpDisplay, window, glxContext);

    // print gl info
    printGLInfo();

   glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // state fuc

	// Depth related code
	glShadeModel(GL_SMOOTH); // for smoothness
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL); // glcleardepth madhlya 1.0 fragment value <=
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	//Load Textures
	

	//enable texture
	glEnable(GL_TEXTURE_2D); //cause our texture is 2D

	// Light Configuration
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient); // light type, light property, Value 
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDefuse);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPositon);
	glLightfv(GL_LIGHT0, GL_SPECULAR , lightSpecular);

	glEnable(GL_LIGHT0); //Enable Light
	glEnable(GL_NORMALIZE); // normal scalling enable with norbale when scle up and scale down we are doing
	glEnable(GL_AUTO_NORMAL);

	//matrial confi
	glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDeffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular);
	glMaterialf(GL_FRONT, GL_SHININESS, materialShininess);

	//if we want to add light then Normal  Line is very imp it shows the orientation of the light its the perpendicular 


    return 0;
}
void printGLInfo(void)
{
    // code
    // print opengl information
    fprintf(gpFile,"OpenGL Information\n");
    fprintf(gpFile,"******************\n");
    fprintf(gpFile,"OpenGL Vender : %s\n", glGetString(GL_VENDOR));
    fprintf(gpFile,"OpenGL Renderer : %s\n", glGetString(GL_RENDERER));
    fprintf(gpFile,"OpenGL Version : %s\n", glGetString(GL_VERSION));
    fprintf(gpFile,"******************\n");
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



void display(void)
{
   // function prototypes
	void DrawLitCube(void);
	void DrawFloor(void);

	// Clear the color and depth buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	// Set the matrix mode to model-view
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//set up camera
	gluLookAt(0.0f, 5.0f, 10.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f);

	//render actual cube
	glPushMatrix(); // set camera matrix cody we need to push for the cube camera push 
	// Translate the scene backward
	glTranslatef(translateCubeX, translateCubeY, translateCubeZ);

	glScalef(CubeScale, CubeScale, CubeScale);
	// Apply rotation
	glRotatef(angleCube, 1.0f, 1.0f, 1.0f);

	DrawLitCube();
	glPopMatrix();


	//define your floor as a stencil Stencil means chapa rangolicha chap
	//we are defining floor as a stencil so that we dont need a depth testing to improve performance
	glDisable(GL_DEPTH_TEST);
	//as now we not rendering anything for sometime so mask out all the colour component 
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);

	//now enable stencil test
	glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_ALWAYS, 1, 1); // always pass the stencil test where where its 1 pass 1 

	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE); // what should be done when stencil operation firt para keep all the values same 2 if depth test fails keep sme if both values pass replace glstencilfunc cha 2nd bharun trak replace ker 

	DrawFloor(); // this call will not render the floor this is only for stencil so that stencil is for the floor only define the floor as the stencil, its define the stencil limits

	glEnable(GL_DEPTH_TEST); //reanable the depth test

	//now we want start rendering so unmask the colour let the colours comes
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);

	//draw only when there is only 1 stored in stencil buffer
	glStencilFunc(GL_EQUAL, 1, 1);

	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

	//render the reflected cube
	glPushMatrix(); // set camera matrix cody we need to push for the cube camera push 

	glScalef(1.0f, -1.0f, 1.0f);
	// Translate the scene backward
	glTranslatef(translateCubeX, translateCubeY, translateCubeZ);

	glScalef(CubeScale, CubeScale, CubeScale);
	// Apply rotation
	glRotatef(angleCube, 1.0f, 1.0f, 1.0f);

	DrawLitCube();
	glPopMatrix();
	glDisable(GL_STENCIL_TEST);

	//render the floor
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(1.0f, 1.0f, 1.0f, 0.7f);
	DrawFloor();
	glDisable(GL_BLEND);




    glXSwapBuffers(gpDisplay, window);
}

void DrawLitCube(void) 
{
	// code 
	glEnable(GL_LIGHTING);

	// Draw the cube
	// Front face
	glBegin(GL_QUADS);
	//glColor3f(1.0f, 0.0f, 0.0f); // Red
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glEnd();

	// Back face
	glBegin(GL_QUADS);
	//glColor3f(0.0f, 1.0f, 0.0f); // Green
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glEnd();

	// Right face
	glBegin(GL_QUADS);
	//glColor3f(0.0f, 0.0f, 1.0f); // Blue
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glEnd();

	// Left face
	glBegin(GL_QUADS);
	//glColor3f(1.0f, 1.0f, 0.0f); // Yellow
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glEnd();

	// Top face
	glBegin(GL_QUADS);
	//glColor3f(1.0f, 0.0f, 1.0f); // Magenta
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);
	glEnd();

	// Bottom face
	glBegin(GL_QUADS);
	//glColor3f(0.0f, 1.0f, 1.0f); // Cyan
	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glEnd();
	glDisable(GL_LIGHTING);
}

void DrawFloor(void)
{
	//code
	// translate triangle backwords by z
	glPushMatrix(); // pushing the camera matrix set in display
	glTranslatef(0.0f, -1.0f, -2.0f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f); // angle, x, y, z

	glScalef(10.0f, 10.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, texture_marble);
	glBegin(GL_QUADS);

	// Top-right
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.5f, 0.5f, 0.0f);

	// Top-left
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.5f, 0.5f, 0.0f);

	// Bottom-left
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.5f, -0.5f, 0.0f);

	// Bottom-right
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.5f, -0.5f, 0.0f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, 0);

	glPopMatrix();

}


void update(void)
{
    // code
    angleCube = angleCube + 2.0f;

	if (angleCube >= 360.0f)
	{
		angleCube = angleCube - 360.0f;
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



