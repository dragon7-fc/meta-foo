project('example-sdbusplus', 'cpp', 'c',
    default_options: [
      'buildtype=debugoptimized',
      'cpp_std=c++17',
      'werror=true',
    ],
    version: '1.0.0',
)

subdir('tools')

sdbusplus_dep = dependency('sdbusplus')

buildroot = meson.current_build_dir()
yaml_files = files(
    run_command(
        sdbusgen_prog,
        '--tool', sdbusplusplus_prog,
        '--output', buildroot,
        'xyz',
        check: true
    ).stdout().strip().split('\n')
)

executable(
    'method-server',
    'method-server.cpp',
    yaml_files,
    dependencies: sdbusplus_dep,
)

executable(
    'method-client',
    'method-client.cpp',
    yaml_files,
    dependencies: sdbusplus_dep,
)

executable(
    'property-server',
    'property-server.cpp',
    yaml_files,
    dependencies: sdbusplus_dep,
)

executable(
    'property-client',
    'property-client.cpp',
    yaml_files,
    dependencies: sdbusplus_dep,
)

executable(
    'signal-server',
    'signal-server.cpp',
    yaml_files,
    dependencies: sdbusplus_dep,
)

executable(
    'signal-client',
    'signal-client.cpp',
    yaml_files,
    dependencies: sdbusplus_dep,
)
