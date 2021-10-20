all: ../msys2.ico ../mingw32.ico ../mingw64.ico ../ucrt64.ico ../clang64.ico ../clang32.ico ../clangarm64.ico

sources=icon-large.svg icon-medium.svg icon-small.svg

../msys2.ico: $(sources)
	./build.sh '#894c84' $@

../mingw32.ico: $(sources)
	./build.sh '#748787' $@

../mingw64.ico: $(sources)
	./build.sh '#276597' $@

../ucrt64.ico: $(sources)
	./build.sh '#8b7b16' $@

../clang64.ico: $(sources)
	./build.sh '#be643e' $@

../clang32.ico: $(sources)
	./build.sh '#d49b63' $@

../clangarm64.ico: $(sources)
	./build.sh '#238423' $@
