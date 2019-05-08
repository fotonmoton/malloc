/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_tests.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtertysh <gtertysh@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 22:35:37 by foton             #+#    #+#             */
/*   Updated: 2019/05/08 19:47:45 by gtertysh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
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
	_IS(ptr->size == 10 + sizeof(t_chunk));
	_IS(ptr->magic == MAGIC);
	_IS(ptr->next == NULL);
	_IS(ptr->prev != NULL);
	_IS(ptr->prev->size > TINY * NALLOC && ptr->prev->size < SMALL * NALLOC);
	// show_alloc_mem();
	_END("returns_not_null_pointer");
}

int	free_concatenates_adjacent_blocks(void)
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
	_END("free_concatenates_adjacent_blocks");
}

int	malloc_creates_new_arena(void)
{
	t_chunk	*second_arena_chunk;
	int		chunks_count;
	int		i;
	int		page;

	g_base.next = &g_base;
	page = getpagesize();
	// minimum 100 chunks aligned to page size
	chunks_count = (ARENA_SIZE(CHUNK_SIZE(TINY) * NALLOC) + page - 1)
		/ page * page / CHUNK_SIZE(TINY);
	i = 0;
	while (i < chunks_count)
	{
		second_arena_chunk = malloc(TINY);
		i++;
	}
	_IS(g_base.next->next == &g_base);
	_IS(g_base.next->type == TINY);
	second_arena_chunk = malloc(TINY);
	_IS(g_base.next->next != &g_base);
	_IS(g_base.next->type == TINY);
	_IS(g_base.next->heap->next == second_arena_chunk - 1);
	// show_alloc_mem();
	_END("malloc_creates_new_arena");
}

int	realloc_return_same_pointer(void)
{
	t_chunk *ptr;
	t_chunk *new_ptr;

	g_base.next = &g_base;
	ptr = malloc(20);
	new_ptr = realloc(ptr, 10);
	_IS(ptr == new_ptr);
	_END("realloc_return_same_pointer");
}

int	main(void)
{
	_SHOULD(inital_base_next_point_to_itself);
	_SHOULD(returns_not_null_pointer);
	_SHOULD(free_concatenates_adjacent_blocks);
	_SHOULD(malloc_creates_new_arena);
	_SHOULD(realloc_return_same_pointer);
	return (0);
}
