project('mir-window-management-gtk3',
    ['c'],
    version: '0.1.0',
    license: 'MIT',
    meson_version: '>=0.45.1',
    default_options: ['c_std=gnu11', 'warning_level=3'])

add_project_arguments(
    ['-Wno-pedantic'],
    language: 'c')

gtk = dependency('gtk+-wayland-3.0', version: '>=3.22.0')
wayland_client = dependency('wayland-client', version: '>=1.10.0')
# wayland_scanner is required, but we can find it without pkg-config
wayland_scanner = dependency('wayland-scanner', version: '>=1.10.0', required: false)
# use system xdg-shell protocol when available
wayland_protocols = dependency('wayland-protocols', version: '>=1.16', required: false)

pkg_config = import('pkgconfig')
gnome = import('gnome')

subdir('include')
subdir('protocol')
subdir('src')
subdir('example')

lib_dep = declare_dependency(
    link_with: lib,
    include_directories: inc_dirs)
