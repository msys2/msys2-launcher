_realname="msys2-launcher"
pkgname=("${_realname}-git")
pkgver=0.3.15.551bb17
pkgrel=1
pkgdesc="Helper for launching MSYS2 shells"
arch=('x86_64' 'i686')
license=('MIT')
provides=("${_realname}")
conflicts=("${_realname}")
depends=("mintty>=2.2.1")
makedepends=('mingw-w64-cross-gcc')
source=(launcher.{c,ini,rc} {macros,version}.h Makefile {mingw32,mingw64,msys2}.ico)
md5sums=('052ba00d62b07adca186d57615b43834'
         'b7fb06d6faaf530c187b817088228ce6'
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
