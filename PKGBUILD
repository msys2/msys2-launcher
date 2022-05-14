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
source=(launcher.{c,ini,rc} {macros,version}.h Makefile {msys2,mingw32,mingw64,ucrt64,clang64,clang32,clangarm64}.ico)
sha512sums=('ed2937084cc7d176bb9f06af96121dbf4433a05cfc8fa260918a5f96ed5e8c4201fa2b45aa196a858ece0c8a86f7ffc617a8330b57b7231a4ea4ab23d75920b0'
            '5ed8a2e9997d9d2c1e17940292d68542f897e2716b274741d8a3ba7c8f46235c175b7e0a1252a879ba3c79b571504d25de2a8d6b004aedd117d263195bc2b185'
            'cf257f1f5b7fc69a32c63fe5bf5299db078621850b1e12358654d71da7777a94a0668d657c1834be308db099cad9d48a42fa7877ad58dfdbd576248150913a12'
            '6019ca0d67375c1261dda0d54d45fc411b02244c51b71d5c57d2613e9edfb4e8f9000754e5c7d632ed0101005c01cd0a98c3961d5b5f51c94d83eceba4296d35'
            '972d366b7e4bffeafbd624cea89c2f5d7cf7ee6f14b3534c39e42711b9257b76054578b23c41d6fe1d10d0d848fbc2c32b86ea611f98ffa22f60be7067a44edc'
            '76fc9b0fc5931d748f02d8b726f2e461e04c8e31aaac309c8ed349f303f3c976cb2972c89913b0192ebfcfe13bf5b1c1ffd1ea11439e2a2c6d819207eead89ad'
            'b0eb5a71d4611fd79a681e89ce1c915a12858c7be4d64740b9d127576d39cba352696a594cfb8392aaf00dad0f12c40c78e8fd2019b15c88507286efa0171e0d'
            '24e05f79df6aa51ca85fee43f1d10eeace85739d60ab5b2bfc82b2b6edd3040e6ae0355fdd3f4455eb7adb83e3c6269457b2462552fd3b5d5a5e14c0771c3437'
            '7749d962dd19b4e93bf74ca339fd1c06fd457dd92ea501d4a19b34973ce2b0ddd9c9ed09921c26bea3adc7dfbbd821042b467ffc6d4050b6301c025d4f0c844d'
            'e77d67d33fb364d84416a727d24a5fabdedc4b42ddccffd296ac6c2049cbdc8b7df700a492f386a812867924c8dc2a34b0c858bc1a252957db06e9f1869d7ff2'
            'a1fcffd0b7fe7f3e2c18d03206909aba830e983925a85ef69dc165606e543e53eb17164a089d84a40cc53d6a626cce2302071aec8519b7e44f001b2d4602d5e2'
            '13118938dc6a084a005d723f329fffa3364284254d9167fe04e93c0ca870b7b3bef1e9a5f0b5b2a7df14f3f1af9a589fc2709d1593231fa3615174b062e62d70'
            '29f607099a6f1aab35bec2e4a78701ba2b7c4adf2385e5a2da4167b89b1f46cde2070a01182271a8fbde03c4bb8c7e29a6cb4c4d8308c3be9c503ad84f986ba3')

pkgver() {
  local _major=$(cat version.h | grep -F 'VER_MAJOR' | head -1 | sed -e 's/.* //')
  local _minor=$(cat version.h | grep -F 'VER_MINOR' | head -1 | sed -e 's/.* //')
  printf "%s.%s.%s.%s" "${_major}" "${_minor}"  "$(git rev-list --count HEAD)" "$(git rev-parse --short HEAD)"
}

build() {
  make PREFIX=/opt/bin/${CARCH}-w64-mingw32-
}

package() {
  cp {msys2,mingw32,mingw64,ucrt64,clang64,clang32,clangarm64}.{exe,ini} "${pkgdir}"
}
