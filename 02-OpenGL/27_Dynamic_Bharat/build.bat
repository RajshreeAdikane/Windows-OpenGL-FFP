cl.exe /c /EHsc /I. OGL3.c
rc.exe Triangle.rc
link.exe OGL3.obj triangle.res user32.lib gdi32.lib kernel32.lib /SUBSYSTEM:WINDOWS














