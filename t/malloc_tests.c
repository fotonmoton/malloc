#include "t.h"
#include "ft_malloc.h"
#include "ft_malloc_internal.h"


int	inital_base_next_point_to_itself(void)
{
	_IS(g_base.next == &g_base);
	_END("inital_base_next_point_to_itself");
}

int	returns_not_null_pointer(void)
{
	t_chunk	*ptr;

	g_base.next = &g_base;
	ptr = malloc(10);
	_IS(ptr != NULL);

	ptr = ptr - 1;
	_IS(ptr->is_free == 0);
	_IS(ptr->size ==  10 + sizeof(t_chunk));
	_IS(ptr->magic == MAGIC);
	_IS(ptr->next == NULL);
	_IS(ptr->prev != NULL);
	_IS(ptr->prev->size > TINY * NALLOC && ptr->prev->size < SMALL * NALLOC);
	_END("returns_not_null_pointer");
}

int	free_concatenates_andjustent_blocks(void)
{
	t_chunk	*ptr;
	t_chunk	*next_malloc;
	t_chunk	*heap;

	g_base.next = &g_base;
	ptr = malloc(10);
	next_malloc = malloc(10);

	ptr -= 1;
	next_malloc -= 1;

	free(ptr + 1);

	_IS(ptr->is_free == 1);
	_IS(ptr->prev == next_malloc);
	_IS(next_malloc->is_free == 0);
	_IS(next_malloc->next == ptr);
	_IS(next_malloc->prev->prev == NULL);

	heap = next_malloc->prev;
	free(next_malloc + 1);

	_IS(heap->is_free == 1);
	_IS(heap->prev == NULL);
	_IS(heap->next == NULL);

	_END("free_concatenates_andjustent_blocks");
}

int	main(void)
{
	_SHOULD(inital_base_next_point_to_itself);
	_SHOULD(returns_not_null_pointer);
	_SHOULD(free_concatenates_andjustent_blocks);
	return 0;
}