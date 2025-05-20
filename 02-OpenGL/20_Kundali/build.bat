cl.exe /c /EHsc /I. kundali.c
rc.exe Triangle.rc
link.exe kundali.obj triangle.res user32.lib gdi32.lib kernel32.lib /SUBSYSTEM:WINDOWS











