all: msys2.exe mingw32.exe mingw64.exe

pathtools.o: pathtools.c
	g++ -Wall -Wextra -o $@ -c $^
launcher.res: launcher.rc
	windres -o $@ $^ -O COFF

msys2.exe: launcher.cpp pathtools.o launcher.res
	g++ -Wall -Wextra -static-libstdc++ -static -mwindows -o $@ $^ -luuid -lshlwapi -lpsapi -DMSYSTEM=MSYS -DEXENAME=$@
mingw32.exe: launcher.cpp pathtools.o launcher.res
	g++ -Wall -Wextra -static-libstdc++ -static -mwindows -o $@ $^ -luuid -lshlwapi -lpsapi -DMSYSTEM=MINGW32 -DEXENAME=$@
mingw64.exe: launcher.cpp pathtools.o launcher.res
	g++ -Wall -Wextra -static-libstdc++ -static -mwindows -o $@ $^ -luuid -lshlwapi -lpsapi -DMSYSTEM=MINGW64 -DEXENAME=$@
