/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtertysh <gtertysh@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 21:45:17 by gtertysh          #+#    #+#             */
/*   Updated: 2019/05/09 23:46:34 by gtertysh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc_internal.h"
#include "ft_malloc.h"
#include "libft.h"
#include "stdio.h"

static void	print_addr(void *addr)
{
	size_t	i;
	size_t	bit_4;
	size_t	count;

	count = sizeof(addr) * 2;
	i = 0;
	while (i < count)
	{
		bit_4 = ((size_t)addr >> ((count - i - 1) * 4)) & 0xf;
		if (bit_4 < 10)
			ft_putnbr(bit_4);
		else
			ft_putchar('A' + bit_4 - 10);
		i++;
	}
}

static void	print_size(void *addr, size_t size)
{
	print_addr(addr + size);
	ft_putstr(" - ");
	print_addr(addr);
	ft_putstr(" : size ");
	ft_putnbr(size);
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
	ft_putstr(" of ARENA\n");
}

static void	print_chunk(t_chunk *chunk)
{
	ft_putstr("        ");
	print_size(chunk, chunk->size);
	if (chunk->is_free)
		ft_putstr(" of free block\n");
	else
		ft_putstr(" of not free block\n");
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
