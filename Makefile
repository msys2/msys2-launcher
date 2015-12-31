PREFIX=

msys: msys.exe msys.ini mingw.exe mingw.ini
all: msys

.PHONY: all msys

msys.ini: launcher.ini
	cp -f $^ $@
	echo MSYSTEM=MSYS>> $@
msys.res: launcher.rc msys.ico
	$(PREFIX)windres -O COFF -o $@ $< -DMSYSTEM=MSYS -DICONFILE=msys.ico
msys.exe: launcher.c msys.res
	$(PREFIX)gcc -std=c11 -Wall -Wextra -Werror -municode -mwindows -o $@ $^ -luuid -lshlwapi -lpsapi

mingw.ini: launcher.ini
	cp -f $^ $@
	echo MSYSTEM=MINGW32>> $@
mingw.res: launcher.rc mingw.ico
	$(PREFIX)windres -O COFF -o $@ $< -DMSYSTEM=MINGW32 -DICONFILE=mingw.ico
mingw.exe: launcher.c mingw.res
	$(PREFIX)gcc -std=c11 -Wall -Wextra -Werror -municode -mwindows -o $@ $^ -luuid -lshlwapi -lpsapi
