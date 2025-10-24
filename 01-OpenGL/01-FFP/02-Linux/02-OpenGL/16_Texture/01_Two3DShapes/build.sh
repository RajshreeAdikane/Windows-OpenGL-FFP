clear
gcc -c -o OGL.o -I /usr/include OGL.c
gcc -o OGL OGL.o -lX11 -lGL -lGLU -lSOIL
./OGL

