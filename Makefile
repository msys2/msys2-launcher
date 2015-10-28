PREFIX=

all: msys2.exe msys2.ini mingw32.exe mingw32.ini mingw64.exe mingw64.ini

.PHONY: all

msys2.ini: launcher.ini
	cp -f $^ $@
	echo MSYSTEM=MSYS>> $@
msys2.res: launcher.rc msys2.ico
	$(PREFIX)windres -O COFF -o $@ $< -DMSYSTEM=MSYS -DICONFILE=msys2.ico
msys2.exe: launcher.c msys2.res
	$(PREFIX)gcc -std=c11 -Wall -Wextra -Werror -static -municode -mwindows -o $@ $^
	$(PREFIX)strip $@

mingw32.ini: launcher.ini
	cp -f $^ $@
	echo MSYSTEM=MINGW32>> $@
mingw32.res: launcher.rc mingw32.ico
	$(PREFIX)windres -O COFF -o $@ $< -DMSYSTEM=MINGW32 -DICONFILE=mingw32.ico
mingw32.exe: launcher.c mingw32.res
	$(PREFIX)gcc -std=c11 -Wall -Wextra -Werror -static -municode -mwindows -o $@ $^
	$(PREFIX)strip $@

mingw64.ini: launcher.ini
	cp -f $^ $@
	echo MSYSTEM=MINGW64>> $@
mingw64.res: launcher.rc mingw64.ico
	$(PREFIX)windres -O COFF -o $@ $< -DMSYSTEM=MINGW64 -DICONFILE=mingw64.ico
mingw64.exe: launcher.c mingw64.res
	$(PREFIX)gcc -std=c11 -Wall -Wextra -Werror -static -municode -mwindows -o $@ $^
	$(PREFIX)strip $@
