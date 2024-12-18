_realname="msys2-launcher"
pkgname=("${_realname}-git")
pkgver=1.5
pkgrel=1
pkgdesc="Helper for launching MSYS2 shells"
arch=('x86_64' 'i686')
license=('MIT')
backup=({msys2,mingw32,mingw64,ucrt64,clang64}.ini)
provides=("${_realname}")
conflicts=("${_realname}")
depends=("mintty>=2.2.1")
makedepends=('mingw-w64-cross-gcc')
source=(launcher.{c,ini,rc} {macros,version}.h Makefile {msys2,mingw32,mingw64,ucrt64,clang64,clangarm64}.ico)
sha256sums=('8e3912d38ba631a525caec2be982b462181125c8767b0b5d7271d13df8ad85be'
            '232eaa3de03c5c2cde8106a229b4df768d26f2343ea5df88e22e0e8c088f017e'
            '0b118e093f514fdabfabf69dd6148d56a3a282b77add1d53ef31f50635c21d7a'
            'ca88f2e77322c0d2a7930b84a981723897eb720131026356f4e14d2be8a35291'
            '30b6807a39d8bf0857767daa0dfe0227fd3583c1ee099a496c35a7f9e75dbdac'
            'd1e1298433ee116b0a61bfe738aa736422742acd6208f7999fb2ca3dad818578'
            '793b9450a1a59a6c294e51fd0c2a47090d68c68ff2f33a25a11b45f6408c3917'
            'f8f1b5943d385e8a7e3b5a4a2c7d64004108c94c17b2f936016e2ae50bdb65af'
            '91b4a790aad38a102565f0cfcba6c0e6d274f6cda0b37b128d9cc43c5ad6b24d'
            '733e97cbb823773e1a08a91a41035a7692bc0ff270d3c894224911b4b091db44'
            '56d4080c15dff89a6263f3d5f9aa68849b2062179cabd6d78edfe0e3af6bf64a'
            '3b7af99516768485383b34d606749e6f98a250372a8191bc8d3a962d66bdfe35')

pkgver() {
  local _major=$(cat version.h | grep -F 'VER_MAJOR' | head -1 | sed -e 's/.* //')
  local _minor=$(cat version.h | grep -F 'VER_MINOR' | head -1 | sed -e 's/.* //')
  printf "%s.%s.%s.%s" "${_major}" "${_minor}"  "$(git rev-list --count HEAD)" "$(git rev-parse --short HEAD)"
}

build() {
  make PREFIX=/opt/bin/${CARCH}-w64-mingw32-
}

package() {
  cp {msys2,mingw32,mingw64,ucrt64,clang64,clangarm64}.{exe,ini} "${pkgdir}"
}
