all: ../msys2.ico ../mingw32.ico ../mingw64.ico ../clang64.ico ../ucrt64.ico

sources=icon-large.svg icon-medium.svg icon-small.svg

../msys2.ico: $(sources)
	./build.sh '#894c84' $@

../mingw32.ico: $(sources)
	./build.sh '#748787' $@

../mingw64.ico: $(sources)
	./build.sh '#276597' $@

../clang64.ico: $(sources)
	./build.sh '#be643e' $@

../ucrt64.ico: $(sources)
	./build.sh '#8b7b16' $@