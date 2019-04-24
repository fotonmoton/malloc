/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_search.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtertysh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 16:28:30 by gtertysh          #+#    #+#             */
/*   Updated: 2018/06/21 19:44:24 by gtertysh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list				*ft_lst_search
(
	t_list *l,
	void *to_find,
	int (*cmp)(void *to_find, void *l_content)
)
{
	while (l && cmp)
	{
		if (cmp(to_find, l->content))
			return (l);
		l = l->next;
	}
	return (NULL);
}
