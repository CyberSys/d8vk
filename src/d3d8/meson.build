d3d8_res = wrc_generator.process('version.rc')

d3d8_src = [
  'd3d8_main.cpp',
  'd3d8_interface.cpp',
  'd3d8_device.cpp',
  'd3d8_options.cpp',
  'd3d8_surface.cpp',
  'd3d8_state_block.cpp',
  'd3d8_shader.cpp'
]

d3d8_ld_args      = []
d3d8_link_depends = []

if platform != 'windows'
  lib_d3d9 = d3d9_dep
  d3d8_ld_args      += [ '-Wl,--version-script', join_paths(meson.current_source_dir(), 'd3d8.sym') ]
  d3d8_link_depends += files('d3d8.sym')
endif

d3d8_dll = shared_library('d3d8'+dll_ext, d3d8_src, d3d8_res,
  name_prefix         : dxvk_name_prefix,
  dependencies        : [ lib_d3d9, util_dep, dxso_dep, dxvk_dep ],
  include_directories : dxvk_include_path,
  install             : true,
  objects             : (not dxvk_is_msvc and platform == 'windows') ? 'd3d8'+def_spec_ext : [],
  vs_module_defs      : 'd3d8'+def_spec_ext,
  link_args           : d3d8_ld_args,
  link_depends        : [ d3d8_link_depends ],
)

