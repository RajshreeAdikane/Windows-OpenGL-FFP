cl.exe /c /EHsc /I. windows.c
rc.exe window.rc
link.exe windows.obj window.res user32.lib gdi32.lib kernel32.lib /SUBSYSTEM:WINDOWS














