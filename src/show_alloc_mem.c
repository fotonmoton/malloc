/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtertysh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 21:45:17 by gtertysh          #+#    #+#             */
/*   Updated: 2019/05/08 21:45:41 by gtertysh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc_internal.h"
#include "ft_malloc.h"
#include "libft.h"
#include "stdio.h"

static void	print_size(void *addr, size_t size)
{
	printf("%p - %p : size %zu", addr, addr + size, size);
	fflush(stdout);
}

static void	print_arena(t_arena *arena)
{
	if (arena->type == TINY)
		ft_putstr("TINY :  ");
	else if (arena->type == SMALL)
		ft_putstr("SMALL : ");
	else
		ft_putstr("LARGE : ");
	print_size(arena, arena->size);
	ft_putstr("\n");
}

static void	print_chunk(t_chunk *chunk)
{
	ft_putstr("        ");
	print_size(chunk, chunk->size);
	ft_putstr("\n");
}

void		show_alloc_mem(void)
{
	t_arena	*arena_runner;
	t_chunk	*heap_runner;

	arena_runner = g_base.next;
	while (arena_runner != &g_base)
	{
		heap_runner = arena_runner->heap;
		print_arena(arena_runner);
		while (heap_runner)
		{
			print_chunk(heap_runner);
			heap_runner = heap_runner->next;
		}
		arena_runner = arena_runner->next;
	}
}
