cl.exe /c /EHsc /I. 03_TwoShapes.c
rc.exe Triangle.rc
link.exe 03_TwoShapes.obj triangle.res user32.lib gdi32.lib kernel32.lib /SUBSYSTEM:WINDOWS










