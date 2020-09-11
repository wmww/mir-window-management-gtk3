srcs = files(
    'mir-window-management-gtk3.c')

lib = library('mir-window-management-gtk3',
    srcs, protocol_srcs,
    include_directories: inc_dirs,
    dependencies: [gtk, wayland_client],
    version: meson.project_version(),
    install: true)

pkg_config_name = 'mir-window-management-gtk3-0'

gir = gnome.generate_gir(
    lib,
    sources: srcs + [ '../include/mir-window-management-gtk3.h' ],
    namespace: 'MirWm',
    nsversion: '0.1',
    identifier_prefix: 'MirWm',
    symbol_prefix: 'mir_wm',
    export_packages: pkg_config_name,
    includes: [ 'Gtk-3.0' ],
    header: 'mir-window-management-gtk3/mir-window-management-gtk3.h',
    install: true)

pkg_config.generate(
    name: 'mir-window-management-gtk3',
    version: meson.project_version(),
    libraries: [lib],
    filebase: pkg_config_name,
    subdirs: 'mir-window-management-gtk3',
    description: 'Use Mir-specific window management hints in GTK',
    url: 'https://github.com/wmww/mir-window-management-gtk3')
