cl.exe /c /EHsc /I. Single_Point.c
rc.exe Triangle.rc
link.exe Single_Point.obj triangle.res user32.lib gdi32.lib kernel32.lib /SUBSYSTEM:WINDOWS








