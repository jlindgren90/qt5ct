# Maintainer: Antonio Rojas <arojas@archlinux.org>
# Contributor: FadeMind <fademind@gmail.com>
# Contributor: Zatherz <zatherz at linux dot pl>

pkgname=qt5ct
pkgver=1.7
pkgrel=1
pkgdesc='Qt5 Configuration Utility'
arch=(x86_64)
url='https://qt5ct.sourceforge.io/'
license=(BSD)
depends=(qt5-svg)
makedepends=(cmake qt5-tools)

build() {
  cd ..
  cmake -B build -DCMAKE_INSTALL_PREFIX=/usr
  cmake --build build
}

package() {
  cd ..
  DESTDIR="$pkgdir" cmake --install build
  install -Dm644 COPYING "$pkgdir"/usr/share/licenses/$pkgname/LICENSE
} 
