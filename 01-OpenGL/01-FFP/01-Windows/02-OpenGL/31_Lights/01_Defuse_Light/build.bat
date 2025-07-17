cl.exe /c /EHsc /I. Triangle.c
rc.exe Triangle.rc
link.exe Triangle.obj triangle.res user32.lib gdi32.lib kernel32.lib /SUBSYSTEM:WINDOWS









