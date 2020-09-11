if wayland_scanner.found()
    prog_wayland_scanner = find_program(wayland_scanner.get_pkgconfig_variable('wayland_scanner'))
else
    prog_wayland_scanner = find_program('wayland-scanner')
endif

protocols = [
    'mir-window-management-unstable-v1.xml'
]

gen_client_header = generator(prog_wayland_scanner,
    output: ['@BASENAME@-client.h'],
    arguments: ['-c', 'client-header', '@INPUT@', '@BUILD_DIR@/@BASENAME@-client.h'])

gen_private_code = generator(prog_wayland_scanner,
    output: ['@BASENAME@.c'],
    arguments: ['-c', 'code', '@INPUT@', '@BUILD_DIR@/@BASENAME@.c'])
# 'code' is deprecated, and can be replaced with 'private-code' when all platforms have a new enough wayland-scanner

protocol_srcs = []

foreach protocol : protocols
    protocol_srcs += gen_client_header.process(protocol)
    protocol_srcs += gen_private_code.process(protocol)
endforeach
