/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arena_type.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtertysh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 21:08:05 by gtertysh          #+#    #+#             */
/*   Updated: 2019/05/08 21:08:06 by gtertysh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc_internal.h"

int		get_arena_type(size_t size)
{
	if (size <= CHUNK_SIZE(TINY))
		return (TINY);
	if (size <= CHUNK_SIZE(SMALL))
		return (SMALL);
	return (LARGE);
}
