cl.exe /c /EHsc /I. windows_icon.c
rc.exe window.rc
link.exe windows_icon.obj window.res user32.lib gdi32.lib kernel32.lib /SUBSYSTEM:WINDOWS






