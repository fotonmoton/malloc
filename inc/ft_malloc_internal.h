#ifndef FT_MALLOC_INTERNAL_H
# define FT_MALLOC_INTERNAL_H

# include <stddef.h>
# include <stdint.h>

# define TINY 512
# define SMALL 1024
# define LARGE 1025
# define START -1
# define MAGIC 0xDEADBEEF
# define NALLOC 100

typedef struct		s_chunk
{
	uint8_t			is_free;
	size_t			size;
	struct s_chunk	*next;
	struct s_chunk	*prev;
	uint32_t		magic;
}					t_chunk;

# define CHUNK_SIZE(size) ((size) + sizeof(t_chunk))

typedef struct		s_arena
{
	int				type;
	size_t			size;
	struct s_arena	*next;
	t_chunk			*heap;
}					t_arena;

# define HEAP_SIZE(size) ((size) - sizeof(t_arena))

extern t_arena		g_base;

#endif