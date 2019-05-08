/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtertysh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 21:07:09 by gtertysh          #+#    #+#             */
/*   Updated: 2019/05/08 21:07:34 by gtertysh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc_internal.h"
#include "libft.h"

static void	*calloc_core(size_t count, size_t size)
{
	void	*ptr;

	ptr = malloc(count * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, count * size);
	return (ptr);
}

void		*calloc(size_t count, size_t size)
{
	void	*ptr;

	pthread_mutex_lock(&g_malloc_mutex);
	ptr = calloc_core(count, size);
	pthread_mutex_unlock(&g_malloc_mutex);
	return (ptr);
}
