/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstreduce.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtertysh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/31 10:27:11 by gtertysh          #+#    #+#             */
/*   Updated: 2018/06/21 19:42:58 by gtertysh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_lstreduce
(
		t_list *l,
		void *(*iterator)(t_list *, void *, int index),
		void *acc
)
{
	int	i;

	i = 0;
	while (l && iterator && acc)
	{
		acc = iterator(l, acc, i++);
		l = l->next;
	}
	return (acc);
}
