cl.exe /c /EHsc /I. Triangle1.c
rc.exe Triangle.rc
link.exe Triangle1.obj triangle.res user32.lib gdi32.lib kernel32.lib /SUBSYSTEM:WINDOWS








