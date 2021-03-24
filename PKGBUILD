_realname="msys2-launcher"
pkgname=("${_realname}-git")
pkgver=1.1
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
            '07ef013bddc4241408c14c094311b408627b9ba773716fa64389188a1d38bb5089ca4f36c59d71bef816c8fc3381adff6db455a58a13735239e96972426a48a6'
            'a8f7568ae878481641422a8e9c1d19e84b3d33815f179af179fa9c83ebac9fb5834a939b97b38b5b5c53f9f86753daf06d1e1551019764d3f8305571e6fe32d5'
            'a591e978af84a5deec5dfd28e421ba165d8d3d23b5e58a828346edadbdaecf8f6c847862b318af3e04f3fdf8531b3e7344e7f38e757ca208ec175822be132f51'
            '88940f62af67685894bfe897fe6a1b8bce439708e18d0c0c1d065c44e8a5e3ce414e65c66c5f572f1ffd6f713d1ab8810a5f7e737ecaa0f5b9ff567a86589c33'
            '29a9d80f338eaa6e39e6ed0b8941d579e9483de8db4499ccb4723c1cce4bce03dee07e9fda54a21d39d5de13c979395cfaf43bea91f50fc930dfc30a13dbcae6'
            'f1729c410b8027587c8865afa04113a667214761fd82748e896b7b53dfe93186537898edc87d12add9e4be208bfe45333fcb1824655c5c46b1e71ec048d83739'
            '2a7925862864ad350f334e84ebe0da2160532b08faa1bd9923bb6848ccc6541054d027ffa6ccfd6861170afd06e126c33fcb0d89d4a08d694ef5ead53ff0dc96')

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
