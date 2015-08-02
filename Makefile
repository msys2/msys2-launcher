all: msys2.exe mingw32.exe mingw64.exe

pathtools.o: pathtools.c pathtools.h
	g++ -Wall -Wextra -o $@ -c $^

msys2.res: launcher.rc msys2.ico
	windres -O COFF -o $@ $< -DMSYSTEM=MSYS -DICONFILE=msys2.ico
msys2.exe: launcher.cpp pathtools.o msys2.res
	g++ -Wall -Wextra -static-libstdc++ -static -mwindows -o $@ $^ -luuid -lshlwapi -lpsapi -DMSYSTEM=MSYS -DEXENAME=$@

mingw32.res: launcher.rc mingw32.ico
	windres -O COFF -o $@ $< -DMSYSTEM=MINGW32 -DICONFILE=mingw32.ico
mingw32.exe: launcher.cpp pathtools.o mingw32.res
	g++ -Wall -Wextra -static-libstdc++ -static -mwindows -o $@ $^ -luuid -lshlwapi -lpsapi -DMSYSTEM=MINGW32 -DEXENAME=$@

mingw64.res: launcher.rc mingw64.ico
	windres -O COFF -o $@ $< -DMSYSTEM=MINGW64 -DICONFILE=mingw64.ico
mingw64.exe: launcher.cpp pathtools.o mingw64.res
	g++ -Wall -Wextra -static-libstdc++ -static -mwindows -o $@ $^ -luuid -lshlwapi -lpsapi -DMSYSTEM=MINGW64 -DEXENAME=$@
