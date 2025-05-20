cl.exe /c /EHsc /I. Line.c
rc.exe Triangle.rc
link.exe Line.obj triangle.res user32.lib gdi32.lib kernel32.lib /SUBSYSTEM:WINDOWS









