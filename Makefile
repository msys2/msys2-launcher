PREFIX=

msys2: msys2.exe msys2.ini mingw32.exe mingw32.ini mingw64.exe mingw64.ini
cygwin: cygwin.exe cygwin.ini
all: msys2 cygwin

.PHONY: all msys2 cygwin

msys2.ini: launcher.ini
	cp -f $^ $@
	echo MSYSTEM=MSYS>> $@
msys2.res: launcher.rc msys2.ico
	$(PREFIX)windres -O COFF -o $@ $< -DPRODUCT=MSYS2 -DMSYSTEM=MSYS -DICONFILE=msys2.ico
msys2.exe: launcher.c msys2.res
	$(PREFIX)gcc -std=c11 -Wall -Wextra -Werror -static -municode -mwindows -o $@ $^ -DPRODUCT=MSYS2 -DSHELLPATH='usr\\bin\\mintty.exe'

mingw32.ini: launcher.ini
	cp -f $^ $@
	echo MSYSTEM=MINGW32>> $@
mingw32.res: launcher.rc mingw32.ico
	$(PREFIX)windres -O COFF -o $@ $< -DPRODUCT=MSYS2 -DMSYSTEM=MINGW32 -DICONFILE=mingw32.ico
mingw32.exe: launcher.c mingw32.res
	$(PREFIX)gcc -std=c11 -Wall -Wextra -Werror -static -municode -mwindows -o $@ $^ -DPRODUCT=MSYS2 -DSHELLPATH='usr\\bin\\mintty.exe'

mingw64.ini: launcher.ini
	cp -f $^ $@
	echo MSYSTEM=MINGW64>> $@
mingw64.res: launcher.rc mingw64.ico
	$(PREFIX)windres -O COFF -o $@ $< -DPRODUCT=MSYS2 -DMSYSTEM=MINGW64 -DICONFILE=mingw64.ico
mingw64.exe: launcher.c mingw64.res
	$(PREFIX)gcc -std=c11 -Wall -Wextra -Werror -static -municode -mwindows -o $@ $^ -DPRODUCT=MSYS2 -DSHELLPATH='usr\\bin\\mintty.exe'

cygwin.ini: launcher.ini
	cp -f $^ $@
	echo MSYSTEM=CYGWIN>> $@
cygwin.res: launcher.rc cygwin.ico
	$(PREFIX)windres -O COFF -o $@ $< -DPRODUCT=Cygwin -DMSYSTEM=CYGWIN -DICONFILE=cygwin.ico
cygwin.exe: launcher.c cygwin.res
	$(PREFIX)gcc -std=c11 -Wall -Wextra -Werror -static -municode -mwindows -o $@ $^ -DPRODUCT=Cygwin -DSHELLPATH='bin\\mintty.exe'
