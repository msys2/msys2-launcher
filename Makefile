all: msys2.exe mingw32.exe mingw64.exe

.PHONY: all

msys2.res: launcher.rc msys2.ico
	windres -O COFF -o $@ $< -DMSYSTEM=MSYS -DICONFILE=msys2.ico
msys2.exe: launcher.c msys2.res
	gcc -Wall -Wextra -Werror -static -municode -mwindows -o $@ $^ -DMSYSTEM=MSYS
	strip $@

mingw32.res: launcher.rc mingw32.ico
	windres -O COFF -o $@ $< -DMSYSTEM=MINGW32 -DICONFILE=mingw32.ico
mingw32.exe: launcher.c mingw32.res
	gcc -Wall -Wextra -Werror -static -municode -mwindows -o $@ $^ -DMSYSTEM=MINGW32
	strip $@

mingw64.res: launcher.rc mingw64.ico
	windres -O COFF -o $@ $< -DMSYSTEM=MINGW64 -DICONFILE=mingw64.ico
mingw64.exe: launcher.c mingw64.res
	gcc -Wall -Wextra -Werror -static -municode -mwindows -o $@ $^ -DMSYSTEM=MINGW64
	strip $@
