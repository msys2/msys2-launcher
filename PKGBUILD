_realname="msys2-launcher"
pkgname=("${_realname}-git")
pkgver=0.3.17.1a1c586
pkgrel=1
pkgdesc="Helper for launching MSYS2 shells"
arch=('x86_64' 'i686')
license=('MIT')
backup=({mingw32,mingw64,msys2}.ini)
provides=("${_realname}")
conflicts=("${_realname}")
depends=("mintty>=2.2.1")
makedepends=('mingw-w64-cross-gcc')
source=(launcher.{c,ini,rc} {macros,version}.h Makefile {mingw32,mingw64,msys2}.ico)
md5sums=('e21db11d21f95aab30966a8c528efd9b'
         '7ab96cb34fef046e4839e270f9397a32'
         '3a3c9fd8d083716e5efd759641eb4f31'
         '57a40ae9972dac94df0830a1ab480895'
         'fef245f65b6826502b953b81fb397d97'
         '8d3fa1f8eb06343a13b72299c164f6cd'
         '797a8ea3012b22705caadcb17b1291c2'
         '0237b204a9d09dcadc955b435cefd311'
         '292ad5cdd78abac9d694cc06819a96fc')

pkgver() {
  local _major=$(cat version.h | grep -F 'VER_MAJOR' | head -1 | sed -e 's/.* //')
  local _minor=$(cat version.h | grep -F 'VER_MINOR' | head -1 | sed -e 's/.* //')
  printf "%s.%s.%s.%s" "${_major}" "${_minor}"  "$(git rev-list --count HEAD)" "$(git rev-parse --short HEAD)"
}

build() {
  make PREFIX=/opt/bin/${CARCH}-w64-mingw32-
}

package() {
  cp {mingw32,mingw64,msys2}.{exe,ini} "${pkgdir}"
}
