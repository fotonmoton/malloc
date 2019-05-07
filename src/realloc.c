/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtertysh <gtertysh@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 22:35:48 by foton             #+#    #+#             */
/*   Updated: 2019/05/07 00:25:13 by gtertysh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"
#include "ft_malloc_internal.h"
#include "libft.h"

void		*realloc(void *ptr, size_t size)
{
	t_chunk	*chunk;
	t_chunk	*new_chunk;

	if (!ptr)
		return (malloc(size));
	chunk = (t_chunk *)ptr - 1;
	if (chunk->magic != MAGIC)
		return (NULL);
	if (chunk->size >= CHUNK_SIZE(size))
		return (ptr);
	new_chunk = malloc(size);
	ft_memmove(new_chunk, ptr, chunk->size - CHUNK_SIZE(0));
	free(ptr);
	return (new_chunk);
}