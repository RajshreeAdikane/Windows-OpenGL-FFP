# Compile the source file into an object file
gcc -c XWindow.c -o XWindow.o

# Link the object file into an executable
gcc XWindow.o -o XWindow -lX11
./XWindow


