PREFIX=

all: msys2.exe msys2.ini mingw32.exe mingw32.ini mingw64.exe mingw64.ini ucrt64.exe ucrt64.ini clang64.exe clang64.ini clang32.exe clang32.ini clangarm64.exe clangarm64.ini

.PHONY: all

msys2.ini: launcher.ini
	cp -f $^ $@
	echo MSYSTEM=MSYS>> $@
msys2.res: launcher.rc msys2.ico
	$(PREFIX)windres -O COFF -o $@ $< -DMSYSTEM=MSYS -DICONFILE=msys2.ico
msys2.exe: launcher.c msys2.res
	$(PREFIX)gcc -std=c11 -Wall -Wextra -Werror -static -municode -mwindows -o $@ $^

mingw32.ini: launcher.ini
	cp -f $^ $@
	echo MSYSTEM=MINGW32>> $@
mingw32.res: launcher.rc mingw32.ico
	$(PREFIX)windres -O COFF -o $@ $< -DMSYSTEM=MINGW32 -DICONFILE=mingw32.ico
mingw32.exe: launcher.c mingw32.res
	$(PREFIX)gcc -std=c11 -Wall -Wextra -Werror -static -municode -mwindows -o $@ $^

mingw64.ini: launcher.ini
	cp -f $^ $@
	echo MSYSTEM=MINGW64>> $@
mingw64.res: launcher.rc mingw64.ico
	$(PREFIX)windres -O COFF -o $@ $< -DMSYSTEM=MINGW64 -DICONFILE=mingw64.ico
mingw64.exe: launcher.c mingw64.res
	$(PREFIX)gcc -std=c11 -Wall -Wextra -Werror -static -municode -mwindows -o $@ $^

ucrt64.ini: launcher.ini
	cp -f $^ $@
	echo MSYSTEM=UCRT64>> $@
ucrt64.res: launcher.rc ucrt64.ico
	$(PREFIX)windres -O COFF -o $@ $< -DMSYSTEM=UCRT64 -DICONFILE=ucrt64.ico
ucrt64.exe: launcher.c ucrt64.res
	$(PREFIX)gcc -std=c11 -Wall -Wextra -Werror -static -municode -mwindows -o $@ $^

clang64.ini: launcher.ini
	cp -f $^ $@
	echo MSYSTEM=CLANG64>> $@
clang64.res: launcher.rc clang64.ico
	$(PREFIX)windres -O COFF -o $@ $< -DMSYSTEM=CLANG64 -DICONFILE=clang64.ico
clang64.exe: launcher.c clang64.res
	$(PREFIX)gcc -std=c11 -Wall -Wextra -Werror -static -municode -mwindows -o $@ $^

clang32.ini: launcher.ini
	cp -f $^ $@
	echo MSYSTEM=CLANG32>> $@
clang32.res: launcher.rc clang32.ico
	$(PREFIX)windres -O COFF -o $@ $< -DMSYSTEM=CLANG32 -DICONFILE=clang32.ico
clang32.exe: launcher.c clang32.res
	$(PREFIX)gcc -std=c11 -Wall -Wextra -Werror -static -municode -mwindows -o $@ $^

clangarm64.ini: launcher.ini
	cp -f $^ $@
	echo MSYSTEM=CLANGARM64>> $@
clangarm64.res: launcher.rc clangarm64.ico
	$(PREFIX)windres -O COFF -o $@ $< -DMSYSTEM=CLANGARM64 -DICONFILE=clangarm64.ico
clangarm64.exe: launcher.c clangarm64.res
	$(PREFIX)gcc -std=c11 -Wall -Wextra -Werror -static -municode -mwindows -o $@ $^
