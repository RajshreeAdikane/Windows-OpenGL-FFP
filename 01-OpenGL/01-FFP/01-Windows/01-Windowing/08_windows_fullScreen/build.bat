cl.exe /c /EHsc /I. windows_fullScreen.c
rc.exe window.rc
link.exe windows_fullScreen.obj window.res user32.lib gdi32.lib kernel32.lib /SUBSYSTEM:WINDOWS









