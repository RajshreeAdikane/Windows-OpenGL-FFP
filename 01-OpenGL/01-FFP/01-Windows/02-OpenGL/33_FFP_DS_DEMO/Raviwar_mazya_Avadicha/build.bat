cl.exe /c /EHsc /I. triangle.c
rc.exe Triangle.rc
link.exe Triangle.obj Triangle.res user32.lib gdi32.lib kernel32.lib /SUBSYSTEM:WINDOWS














