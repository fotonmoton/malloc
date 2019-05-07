/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtertysh <gtertysh@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 22:35:53 by foton             #+#    #+#             */
/*   Updated: 2019/05/06 22:40:09 by gtertysh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"
#include "ft_malloc_internal.h"

void			free(void *used)
{
	t_chunk *chunk;

	if (!used)
		return ;
	chunk = (t_chunk *)used - 1;
	if (chunk->magic != MAGIC)
		return ;
	chunk->is_free = 1;
	if (chunk->prev && chunk->prev->is_free)
	{
		chunk->prev->size += chunk->size;
		chunk->prev->next = chunk->next;
		if (chunk->next)
			chunk->next->prev = chunk->prev;
		chunk = chunk->prev;
	}
	if (chunk->next && chunk->next->is_free)
	{
		chunk->size += chunk->next->size;
		chunk->next = chunk->next->next;
		if (chunk->next)
			chunk->next->prev = chunk;
	}
}
