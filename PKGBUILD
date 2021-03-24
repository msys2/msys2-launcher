_realname="msys2-launcher"
pkgname=("${_realname}-git")
pkgver=1.0
pkgrel=1
pkgdesc="Helper for launching MSYS2 shells"
arch=('x86_64' 'i686')
license=('MIT')
backup=({mingw32,mingw64,msys2}.ini)
provides=("${_realname}")
conflicts=("${_realname}")
depends=("mintty>=2.2.1")
makedepends=('mingw-w64-cross-gcc')
source=(launcher.{c,ini,rc} {macros,version}.h Makefile {mingw32,mingw64,msys2,ucrt64,clang64}.ico)
sha512sums=('eac22e62609e06a49931f70b12abaf0f1a412a98bcf349a2b6a0738b511d05ed7ce7731d2e30f9510926c3175d3521d0164e25cd70e9b18ba33aeb887deef11e'
            '5ed8a2e9997d9d2c1e17940292d68542f897e2716b274741d8a3ba7c8f46235c175b7e0a1252a879ba3c79b571504d25de2a8d6b004aedd117d263195bc2b185'
            'cf257f1f5b7fc69a32c63fe5bf5299db078621850b1e12358654d71da7777a94a0668d657c1834be308db099cad9d48a42fa7877ad58dfdbd576248150913a12'
            '6019ca0d67375c1261dda0d54d45fc411b02244c51b71d5c57d2613e9edfb4e8f9000754e5c7d632ed0101005c01cd0a98c3961d5b5f51c94d83eceba4296d35'
            '2e2669db2e8ef54ff6859f4e9a2657f867aef89094f29386da6df6a39931b55927bd16f92a5058fb4aecc5705a2bf3a867172740bc53bca560b98820790ad3c9'
            'a8f7568ae878481641422a8e9c1d19e84b3d33815f179af179fa9c83ebac9fb5834a939b97b38b5b5c53f9f86753daf06d1e1551019764d3f8305571e6fe32d5'
            '27b9591fa286a15b0eb76a381191f025184d545359285215b9958632a5bce99484de0130296ff4b285e38cec9d88299c09b2ce1fe4b4957b4ef295d31a620817'
            'b1ecd3def00a023a9e88806ff9bbb1bbd73086fbf7554799eb5fe8adb16bf96ed1a7da375bb2b9f9268fcf08e25dab4414bb4888e1ee6eff4587ee0973374f6f'
            '7f369b102391eba9ab56e1fb2157f820ecce41434b7232137da32b924b2d53840731e18ef80916703effc6770e862d1fee2986e66c1d03a8c8bb3feef4f08d58'
            '371cdec15691b5cf9e2ceba5811a9ee984a390d5f294220593a65f64b46c9e10758fa66e9fba5149a10f3f9bcf2cb413ef58e08c225473293d24ed7ba534d8e6'
            'f26ae15c0a2284d8ebb5928843849ae53ea43dfbf9ab6526e0a7991aee58ba7e3843152ecb11777efcf9ce32efb5f1fcf65bbd056d6334191053bb564418d557')

pkgver() {
  local _major=$(cat version.h | grep -F 'VER_MAJOR' | head -1 | sed -e 's/.* //')
  local _minor=$(cat version.h | grep -F 'VER_MINOR' | head -1 | sed -e 's/.* //')
  printf "%s.%s.%s.%s" "${_major}" "${_minor}"  "$(git rev-list --count HEAD)" "$(git rev-parse --short HEAD)"
}

build() {
  make PREFIX=/opt/bin/${CARCH}-w64-mingw32-
}

package() {
  cp {mingw32,mingw64,ucrt64,clang64,msys2}.{exe,ini} "${pkgdir}"
}
