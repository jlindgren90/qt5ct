# Maintainer: Antonio Rojas <arojas@archlinux.org>
# Contributor: FadeMind <fademind@gmail.com>
# Contributor: Zatherz <zatherz at linux dot pl>

pkgname=qt5ct
pkgver=1.8
pkgrel=1
pkgdesc='Qt5 Configuration Utility'
arch=(x86_64)
url='https://qt5ct.sourceforge.io/'
license=(BSD)
depends=(gcc-libs
         glibc
         qt5-base
         qt5-svg)
makedepends=(cmake
             qt5-tools)
source=(https://downloads.sourceforge.net/project/$pkgname/$pkgname-$pkgver.tar.bz2)
sha256sums=('23b74054415ea4124328772ef9a6f95083a9b86569e128034a3ff75dfad808e9')

build() {
  cmake -B build -S $pkgname-$pkgver \
    -DCMAKE_INSTALL_PREFIX=/usr
  cmake --build build
}

package() {
  DESTDIR="$pkgdir" cmake --install build

  install -Dm644 $pkgname-$pkgver/COPYING "$pkgdir"/usr/share/licenses/$pkgname/LICENSE
} 
