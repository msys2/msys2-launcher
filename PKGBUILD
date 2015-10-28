pkgname=("msys2-launcher")
pkgver=0.2
pkgrel=1
pkgdesc="Helper for launching MSYS2 shells"
arch=('x86_64' 'i686')
license=('MIT')
makedepends=('mingw-w64-cross-gcc')
source=(launcher.c launcher.ini launcher.rc macros.h Makefile {mingw32,mingw64,msys2}.ico)
md5sums=('8c08150729060c402f492451786749ec'
         'b7fb06d6faaf530c187b817088228ce6'
         '7ebf52f48d7184bb33e6db327bc091dc'
         '6cec0c5886d59f8ac929a4955108d679'
         'dc25fea701fa71381b364ed9c5ae5399'
         '797a8ea3012b22705caadcb17b1291c2'
         '0237b204a9d09dcadc955b435cefd311'
         '292ad5cdd78abac9d694cc06819a96fc')

build() {
    make PREFIX=/opt/bin/${CARCH}-w64-mingw32-
}

package() {
    cp "${srcdir}"/{mingw32,mingw64,msys2}.{exe,ini} "${pkgdir}"
}
