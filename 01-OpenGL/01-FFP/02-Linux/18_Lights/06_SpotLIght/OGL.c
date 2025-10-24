#include<stdio.h>
#include<stdlib.h>
#include<memory.h>
#include<math.h>

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

GLfloat angle = 0.0f;
GLfloat spotCutoff = 30.0f; // Initial 30 degree cone
// Spotlight Variables
GLfloat lightAmbient[] = { 0.3f, 0.3f, 0.1f, 1.0f };  // Dark yellow ambient
GLfloat lightDiffuse[] = { 0.8f, 0.8f, 0.2f, 1.0f };  // Dark yellow diffuse
GLfloat lightSpecular[] = { 0.9f, 0.9f, 0.3f, 1.0f }; // Dark yellow specular
GLfloat lightPosition[] = { 0.0f, 5.0f, 0.0f, 1.0f }; // Light above the plane
GLfloat spotExponent = 2.0f; // Focus of the spotlight

Bool blight = False;

int main(void)
{
    //function declarations
    void toggleFullScreen(void);
    int initialize(void);
    void resize(int, int);
    void display(void);
    void update(void);
    void uninitialize(void);

    // variable declarations
    int defaultScreen;
    int defaultDepth;
    XSetWindowAttributes windowAttributes;
    Atom windowManagerDeleteAtom;
    XEvent event;
    Screen *screen = NULL;
    int screenWidth, screenHeight;
    KeySym keySym;
    char keys[26];
    int frameBufferAttributes[] = {
        GLX_DOUBLEBUFFER, True,
        GLX_RGBA, True,
        GLX_RED_SIZE, 8,
        GLX_GREEN_SIZE, 8, 
        GLX_BLUE_SIZE, 8, 
        GLX_ALPHA_SIZE, 8,
        GLX_DEPTH_SIZE, 24,
        None
    };
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
        fflush(gpFile);
    }

    //code
    gpDisplay = XOpenDisplay(NULL);
    if(gpDisplay == NULL)
    {
        printf("XOpenDisplay failed !!\n");
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
        printf("glXChooseVisual failed\n");
        uninitialize();
        exit(EXIT_FAILURE);
    }

    //set window attributes
    memset((void*)&windowAttributes, 0, sizeof(XSetWindowAttributes));

    windowAttributes.border_pixel = 0;
    windowAttributes.background_pixmap = 0;
    windowAttributes.background_pixel = XBlackPixel(gpDisplay, visualInfo->screen);
    windowAttributes.colormap = XCreateColormap(gpDisplay,
                                                XRootWindow(gpDisplay, visualInfo->screen),
                                                visualInfo->visual,
                                                AllocNone
                                                );
    colormap = windowAttributes.colormap;
    windowAttributes.event_mask = KeyPressMask | ButtonPressMask | FocusChangeMask | StructureNotifyMask | ExposureMask;

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
                            &windowAttributes
    );

    if(!window)
    {
        printf("WINDOW creation failed\n");
        uninitialize();
        exit(EXIT_FAILURE);
    }

    //create atom for window manager to destroy window
    windowManagerDeleteAtom = XInternAtom(gpDisplay, "WM_DELETE_WINDOW", True);
    XSetWMProtocols(gpDisplay, window, &windowManagerDeleteAtom, 1);

    //set window title
    XStoreName(gpDisplay, window, "RAJASHREE ADIKANE: Dark Yellow Spotlight");

    //map window to show it
    XMapWindow(gpDisplay, window);

    //centering of window
    screen = XScreenOfDisplay(gpDisplay, visualInfo->screen);
    screenWidth = XWidthOfScreen(screen);
    screenHeight = XHeightOfScreen(screen);
    XMoveWindow(gpDisplay, window, (screenWidth - WIN_WIDTH)/2, (screenHeight - WIN_HEIGHT)/2);

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
                //for alphabetic keypress
                XLookupString(&event.xkey, keys, sizeof(keys), NULL, NULL);
                switch (keys[0])
                {
                    case 'f':
                    case 'F':
                    if(bFullScreen == False)
                    {
                        toggleFullScreen();
                        bFullScreen = True;
                    }
                    else
                    {
                        toggleFullScreen();
                        bFullScreen = False;
                    }
                    break;

                    case 'L':
case 'l':
    blight = !blight;
    if (blight) {
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);

        // Set the spotlight position above the center
        lightPosition[0] = 0.0f;
        lightPosition[1] = 5.0f;  // height above the plane
        lightPosition[2] = 0.0f;

        // Spotlight direction towards center of plane
        GLfloat spotDirection[] = { 0.0f - lightPosition[0],
                                    0.0f - lightPosition[1],
                                    0.0f - lightPosition[2] };
        glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
        glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotDirection);
        glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, spotCutoff);

        fprintf(gpFile, "Spotlight Enabled and Focused on Center\n");
        fflush(gpFile);
    } else {
        glDisable(GL_LIGHT0);
        glDisable(GL_LIGHTING);
        fprintf(gpFile, "Lighting Disabled\n");
        fflush(gpFile);
    }
    break;

                    case '+': // Increase spotlight angle
                    case '=':
                    if (spotCutoff < 90.0f) {
                        spotCutoff += 5.0f;
                        fprintf(gpFile, "Spotlight angle increased to: %.1f degrees\n", spotCutoff);
                        fflush(gpFile);
                    }
                    break;

                    case '-': // Decrease spotlight angle
                    case '_':
                    if (spotCutoff > 1.0f) {
                        spotCutoff -= 5.0f;
                        fprintf(gpFile, "Spotlight angle decreased to: %.1f degrees\n", spotCutoff);
                        fflush(gpFile);
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

                case ClientMessage:
                if(event.xclient.data.l[0] == windowManagerDeleteAtom)
                {
                    bDone = True;
                }
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

void toggleFullScreen(void)
{
    Atom windowManagerStateAtom = XInternAtom(gpDisplay, "_NET_WM_STATE", False);
    Atom windowManagerFullScreenStateAtom = XInternAtom(gpDisplay, "_NET_WM_STATE_FULLSCREEN", False);
    XEvent event;
    memset((void*)&event, 0, sizeof(XEvent));
    event.type = ClientMessage;
    event.xclient.window = window;
    event.xclient.message_type = windowManagerStateAtom;
    event.xclient.format = 32;
    event.xclient.data.l[0] = bFullScreen ? 0 : 1;
    event.xclient.data.l[1] = windowManagerFullScreenStateAtom;
    event.xclient.data.l[2] = 0;

    XSendEvent(gpDisplay, XRootWindow(gpDisplay, visualInfo->screen), False, 
               SubstructureNotifyMask | SubstructureRedirectMask, &event);
    XFlush(gpDisplay);
}

int initialize(void)
{
    glxContext = glXCreateContext(gpDisplay, visualInfo, NULL, True);
    if(glxContext == NULL)
    {
        fprintf(gpFile, "glXCreateContext failed!!!!\n");
        fflush(gpFile);
        return -1;
    }

    if(glXMakeCurrent(gpDisplay, window, glxContext) == False)
    {
        fprintf(gpFile, "glXMakeCurrent failed!!!!\n");
        fflush(gpFile);
        return -1;
    }

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // Depth related code
    glShadeModel(GL_SMOOTH);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    // DARK YELLOW SPOTLIGHT Configuration
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    
    // Spotlight specific properties
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, spotCutoff);        // Initial cutoff
    glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, spotExponent);    // Focus of spotlight
    
    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.0f);
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.05f);
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.01f);

    // Material properties for the plane - make it respond well to yellow light
    GLfloat matAmbient[] = { 0.8f, 0.8f, 0.6f, 1.0f };     // Warm ambient
    GLfloat matDiffuse[] = { 0.9f, 0.9f, 0.7f, 1.0f };     // Warm diffuse
    GLfloat matSpecular[] = { 1.0f, 1.0f, 0.8f, 1.0f };    // Warm specular
    GLfloat matShininess[] = { 30.0f };
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);

    // Enable color material
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    // Warm up resize
    // resize(WIN_WIDTH, WIN_HEIGHT);


    return 0;
}

void resize(int width, int height)
{
    if (height <= 0)
    {
        height = 1;
    }
    glViewport(0, 0, (GLsizei)width, (GLsizei)height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);
}

void display()
{
    // Clear color and depth buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Set model-view matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Camera setup
    gluLookAt(0.0f, 5.0f, 8.0f,   // Eye position
              0.0f, 0.0f, 0.0f,   // Look at center
              0.0f, 1.0f, 0.0f);  // Up vector

    // Update spotlight if enabled
    if (blight) {
        // Spotlight position above center
        lightPosition[0] = 0.0f;
        lightPosition[1] = 5.0f;
        lightPosition[2] = 0.0f;

        // Direction towards center
        GLfloat spotDirection[] = {
            0.0f - lightPosition[0],
            0.0f - lightPosition[1],
            0.0f - lightPosition[2]
        };

        glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
        glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotDirection);
        glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, spotCutoff);
        glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, spotExponent);
    }

    // Draw plane (XZ plane)
    glBegin(GL_QUADS);
        glColor3f(0.4f, 0.4f, 0.3f); // Neutral color to reflect yellow light
        glNormal3f(0.0f, 1.0f, 0.0f);

        glVertex3f(-10.0f, 0.0f, -10.0f);
        glVertex3f(-10.0f, 0.0f, 10.0f);
        glVertex3f(10.0f, 0.0f, 10.0f);
        glVertex3f(10.0f, 0.0f, -10.0f);
    glEnd();

    // Draw spotlight source as small cube
    if (blight) {
        glPushMatrix();
        glTranslatef(lightPosition[0], lightPosition[1], lightPosition[2]);
        glColor3f(0.8f, 0.8f, 0.2f); // Dark yellow

        float size = 0.1f;
        glBegin(GL_QUADS);
            // Front
            glVertex3f(-size, -size, size);
            glVertex3f(size, -size, size);
            glVertex3f(size, size, size);
            glVertex3f(-size, size, size);

            // Back
            glVertex3f(-size, -size, -size);
            glVertex3f(-size, size, -size);
            glVertex3f(size, size, -size);
            glVertex3f(size, -size, -size);

            // Top
            glVertex3f(-size, size, -size);
            glVertex3f(-size, size, size);
            glVertex3f(size, size, size);
            glVertex3f(size, size, -size);

            // Bottom
            glVertex3f(-size, -size, -size);
            glVertex3f(size, -size, -size);
            glVertex3f(size, -size, size);
            glVertex3f(-size, -size, size);

            // Right
            glVertex3f(size, -size, -size);
            glVertex3f(size, size, -size);
            glVertex3f(size, size, size);
            glVertex3f(size, -size, size);

            // Left
            glVertex3f(-size, -size, -size);
            glVertex3f(-size, -size, size);
            glVertex3f(-size, size, size);
            glVertex3f(-size, size, -size);
        glEnd();
        glPopMatrix();
    }

    // Draw soft spotlight cone on floor
    if (blight) {
        float coneRadius = tanf(spotCutoff * 3.14159f / 180.0f) * lightPosition[1];

        glDisable(GL_LIGHTING);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glColor4f(1.0f, 1.0f, 0.6f, 0.3f); // Soft yellow glow

        glBegin(GL_TRIANGLE_FAN);
            glVertex3f(0.0f, 0.01f, 0.0f); // center
            for(int i = 0; i <= 50; i++) {
                float theta = 2.0f * 3.14159f * i / 50;
                float x = coneRadius * cosf(theta);
                float z = coneRadius * sinf(theta);
                glVertex3f(x, 0.01f, z);
            }
        glEnd();

        glDisable(GL_BLEND);
        glEnable(GL_LIGHTING);
    }

    // Swap buffers
    glXSwapBuffers(gpDisplay, window);
}

void update(void)
{
    angle = angle + 0.5f; 
    if (angle >= 360.0f)
    {
        angle = angle - 360.0f;
    }
}

void uninitialize(void)
{
    GLXContext currentContext = glXGetCurrentContext();
    if(currentContext && currentContext == glxContext)
    {
        glXMakeCurrent(gpDisplay, 0, 0);
    }
    if(glxContext)
    {
        glXDestroyContext(gpDisplay, glxContext);
        glxContext = NULL;
    }
    
    if(window)
    {
        XDestroyWindow(gpDisplay, window);
        window = 0;
    }
    if(colormap)
    {
        XFreeColormap(gpDisplay, colormap);
        colormap = 0;
    }
    if(visualInfo)
    {
        XFree(visualInfo);
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

// no i want after clicking the l th sport light come and and focu on center