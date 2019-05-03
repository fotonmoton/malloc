project(
	'malloc',
	'c',
	default_options: [
		'buildtype=release',
	],
)

add_global_arguments(
	'-Wall',
	'-Wextra',
	'-Werror',
	'-Wpointer-arith',
	'-Wcast-align',
	'-Wwrite-strings',
	'-Wunreachable-code',
	'-Winit-self',
	'-Wmissing-field-initializers',
	'-Wno-unknown-pragmas',
	'-Wstrict-prototypes',
	'-Wundef',
	'-Wold-style-definition',
	language: 'c',
)

inc = include_directories('inc')
subdir('inc')
subdir('src')
subdir('t')