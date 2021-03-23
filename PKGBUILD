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
            'c38f98f7a8018eb166b96d7cc9e1d4c205a1162ff22ca73d6353a26a9ec418cfb7c3d74af03412a2fd639ca8eafb12f80f5976b336c690f95ed31c4031242d58'
            'ed7c164668489b0be125f04d122da0150dbf2050cf80559ca1fe4569c5ea93d1874005ebdc5f1d8431d565422f750b6d4c7d54e792cbe138ccb14ac1db1b27d2'
            '7b3ec55a9468158184b9258e272558ca41bc667ced2bfa6d4e19a0a9d7f2f8cff5c7d65d70d0214f75566ef5ca8dfbcc7e72e2b10ad7983b00c5d11b8b4d1b77'
            'f7f9cb6c0dc031236297b2259a710a69959b5b80148c8e1522588fcb3feb796046c42acf6b7df54acf332348b9e85e76424da32aa8b8fac8a3faa128854b9c5a'
            'f806ae8a14bdd6dd8a68e2b01386b0da0985ca5fe49ff838102463387442cacac6edb28738dfc47659afb1b2540f631a9549db88290b34846121c84b5bfa1db3')

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
