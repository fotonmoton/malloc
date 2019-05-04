project(
	'malloc',
	'c',
	default_options: [
		'buildtype=plain',
	],
)

add_global_arguments(
	'-Wall',
	'-Wextra',
	'-Werror',
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

install_headers('inc/ft_malloc.h')

sources = [
	'src/malloc.c',
	'src/free.c',
	'src/realloc.c',
]

libft = subproject('libft')

libft_dep = libft.get_variable('libft_dep')

ft_malloc = shared_library(
	'ft_malloc',
	sources,
	include_directories: inc,
	dependencies: libft_dep,
	install: true,
)

subdir('t')