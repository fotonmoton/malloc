malloc_tests = executable(
	'malloc_tests',
	'malloc_tests.c',
	include_directories: inc,
	link_with: ft_malloc,
)


malloc_fuzzy = executable(
	'malloc_fuzzy',
	'fuzzy.c',
	include_directories: inc,
	link_with: ft_malloc,
)

zlib_dep = dependency('zlib')

malloc_fuzzy_fast = executable(
	'malloc_fuzzy_fast',
	'fuzzy_fast.c',
	include_directories: inc,
	link_with: ft_malloc,
	dependencies: zlib_dep
)


test('basic', malloc_tests)

test('fuzzy', malloc_fuzzy, args: ['10', '1000', '0', '10000'])
test('fuzzy_fast', malloc_fuzzy_fast, args: ['10', '1000', '0', '10000'])