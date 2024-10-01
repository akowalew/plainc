@echo off
set WFLAGS=/W4 /WX /wd4100 /wd4189
set CFLAGS=/nologo /MT /Zi /Gm- /GR- /EHa- /Oi /EHc- /EHs- /GA /GF /GR- /GS- /guard:cf- /guard:ehcont- /Gw /Gy- /Gs9999999 /Fm:test.map
set LFLAGS=/DEBUG:FULL /OPT:REF /INCREMENTAL:NO /SUBSYSTEM:WINDOWS /WX /SAFESEH:NO /NODEFAULTLIB user32.lib kernel32.lib /LTCG:OFF /STACK:0x100000,0x100000
cl win32_test.c /Fe:test.exe %CFLAGS% %WFLAGS% /link %LFLAGS%
dir test.exe