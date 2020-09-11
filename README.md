# Mir Window Management for GTK3
This library is experimental. The protocol it uses is not yet implemented in Mir master, and is subject to change.

## Building from source
1. Clone this repo
2. Install build dependencies (see below)
3. `$ meson build`
4. `$ ninja -C build`
5. `$ sudo ninja -C build install`
6. `$ sudo ldconfig`

### Build dependencies
* [Meson](https://mesonbuild.com/) (>=0.45.1)
* [libwayland](https://gitlab.freedesktop.org/wayland/wayland) (>=1.10.0)
* [GTK3](https://www.gtk.org/) (>=3.22.0)

To install these dependencies on Ubuntu 18.04 and later:
```
sudo apt install meson libwayland-dev libgtk-3-dev libgirepository1.0-dev gtk-doc-tools
```

### Meson options
* `-Dexample`: If to build the example app (default: true)

## Licensing
This project is licensed under MIT
