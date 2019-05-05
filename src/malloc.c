#include <sys/mman.h>
#include "ft_malloc.h"
#include "ft_malloc_internal.h"
#include "libft.h"

t_arena	g_base = { .type = START, .size = 0, .next = &g_base, .heap = NULL};

static size_t	get_actual_size(size_t size, int type)
{
	size_t	minimum;
	int		page;

	page = getpagesize();
	if (type == LARGE)
		minimum = size;
	else
		minimum = (type * NALLOC);
	return ((minimum + sizeof(t_arena) + page - 1) / page * page);
}

static int		get_arena_type(size_t size)
{
	if (size <= TINY)
		return (TINY);
	if (size <= SMALL)
		return (SMALL);
	return (LARGE);
}

static t_arena	*get_more_arena(size_t size, int type)
{
	t_arena	*arena;
	int		prot;
	int		flags;

	size = get_actual_size(size, type);
	prot = PROT_WRITE | PROT_READ;
	flags = MAP_ANON | MAP_PRIVATE;
	if ((arena = mmap(NULL, size, prot, flags, -1, 0)) == MAP_FAILED)
		return (NULL);
	arena->size = size;
	arena->type = type;
	arena->heap = (t_chunk *)(arena + 1);
	arena->heap->is_free = 1;
	arena->heap->magic = MAGIC;
	arena->heap->size = HEAP_SIZE(size);
	arena->heap->next = NULL;
	arena->heap->prev = NULL;
	arena->next = g_base.next;
	g_base.next = arena;
	return (arena);
}

static t_chunk	*chunk_heap(t_chunk *chunk, size_t size)
{
	t_chunk		*new_chunk;

	if (chunk->size == size)
	{
		chunk->is_free = 0;
		return (chunk);
	}
	chunk->size -= size;
	new_chunk = (t_chunk *)((uint8_t *)chunk + chunk->size);
	new_chunk->is_free = 0;
	new_chunk->magic = MAGIC;
	new_chunk->size = size;
	new_chunk->next = chunk->next;
	new_chunk->prev = chunk;
	new_chunk->prev->next = new_chunk;
	if (new_chunk->next)
		new_chunk->next->prev = new_chunk;
	return (new_chunk);
}

void			*malloc(size_t size)
{
	t_arena	*arena;
	t_chunk	*heap;
	t_chunk	*space;
	int		arena_type;

	space = NULL;
	size = CHUNK_SIZE(size);
	arena = g_base.next;
	arena_type = get_arena_type(size);
	while(!space)
	{
		if(arena->type == arena_type && (heap = arena->heap))
			while(!space && heap)
			{
				if (heap->size >= size && heap->is_free)
					space = chunk_heap(heap, size);
				heap = heap->next;
			}
		arena = arena->next;
		if (!space && arena == &g_base)
			if ((arena = get_more_arena(size, arena_type)) == NULL)
				return (NULL);
	}
	return (space + 1);
}