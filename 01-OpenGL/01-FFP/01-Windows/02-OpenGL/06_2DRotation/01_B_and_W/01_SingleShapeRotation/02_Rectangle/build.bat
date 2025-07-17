cl.exe /c /EHsc /I. OGL.c
rc.exe Triangle.rc
link.exe OGL.obj triangle.res user32.lib gdi32.lib kernel32.lib /SUBSYSTEM:WINDOWS










