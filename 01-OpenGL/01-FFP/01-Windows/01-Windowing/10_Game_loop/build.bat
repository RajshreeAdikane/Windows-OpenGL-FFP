cl.exe /c /EHsc /I. window_gameLoop.c
rc.exe window.rc
link.exe window_gameLoop.obj window.res user32.lib gdi32.lib kernel32.lib /SUBSYSTEM:WINDOWS












