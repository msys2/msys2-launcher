_realname="msys2-launcher"
pkgname=("${_realname}-git")
pkgver=0
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
sha512sums=('7038aa9d1e913110f1dd79ccf56c3455eae69f4e3de7080ef5366bc809af71000605fe6628c1acd2b003067df73ed8c1c757524e465523d9dc1f8fa0e664791f'
            '4508fc564c6c926a149e21a3bc528641b756b8fa90d672497b2e524c163c34d540241a6cb22604eac9f7967c8022061cf777d77f688cc69a71281ee5f8013584'
            'cf257f1f5b7fc69a32c63fe5bf5299db078621850b1e12358654d71da7777a94a0668d657c1834be308db099cad9d48a42fa7877ad58dfdbd576248150913a12'
            '6019ca0d67375c1261dda0d54d45fc411b02244c51b71d5c57d2613e9edfb4e8f9000754e5c7d632ed0101005c01cd0a98c3961d5b5f51c94d83eceba4296d35'
            '328c62f85e4f6e017ecadb0cf17a04802dde8dfc664a8e8c4b66713bbbdef6402b1ead63803bdf2ece8f83defc928f5b2ce0bb89904e10b586cec9433e2ab1d7'
            '270db9d92b944754cc71523053532473d8a477241725e7aded02dc34d35895a33cf135be7a87692c0f9d2204731e345b8ae82d33f15a1a197e73357552c564e0'
            '27b9591fa286a15b0eb76a381191f025184d545359285215b9958632a5bce99484de0130296ff4b285e38cec9d88299c09b2ce1fe4b4957b4ef295d31a620817'
            'b1ecd3def00a023a9e88806ff9bbb1bbd73086fbf7554799eb5fe8adb16bf96ed1a7da375bb2b9f9268fcf08e25dab4414bb4888e1ee6eff4587ee0973374f6f'
            '7f369b102391eba9ab56e1fb2157f820ecce41434b7232137da32b924b2d53840731e18ef80916703effc6770e862d1fee2986e66c1d03a8c8bb3feef4f08d58')

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
