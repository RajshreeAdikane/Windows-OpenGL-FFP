cl.exe /c /EHsc /I. windows_filelogin.c
rc.exe window.rc
link.exe windows_filelogin.obj window.res user32.lib gdi32.lib kernel32.lib /SUBSYSTEM:WINDOWS











