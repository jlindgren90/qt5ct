# Maintainer: Antonio Rojas <arojas@archlinux.org>
# Contributor: FadeMind <fademind@gmail.com>
# Contributor: Zatherz <zatherz at linux dot pl>

pkgname=qt5ct
pkgver=1.9
pkgrel=1
pkgdesc='Qt5 Configuration Utility'
arch=(x86_64)
url='https://qt5ct.sourceforge.io/'
license=(BSD-3-Clause)
depends=(gcc-libs
         glibc
         qt5-base
         qt5-svg)
makedepends=(cmake
             qt5-tools)
source=(https://downloads.sourceforge.net/project/$pkgname/$pkgname-$pkgver.tar.bz2)
sha256sums=('dc10e6939d423b925981ce67febb1a015b6f61c022a9cc7e6c8b5efea4588bff')

build() {
  cmake -B build -S $pkgname-$pkgver \
    -DCMAKE_INSTALL_PREFIX=/usr
  cmake --build build
}

package() {
  DESTDIR="$pkgdir" cmake --install build

  install -Dm644 $pkgname-$pkgver/COPYING "$pkgdir"/usr/share/licenses/$pkgname/LICENSE
} 
