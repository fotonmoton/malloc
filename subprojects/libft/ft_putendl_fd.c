/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtertysh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/04 15:17:18 by gtertysh          #+#    #+#             */
/*   Updated: 2016/12/04 15:24:55 by gtertysh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char const *s, int fd)
{
	if (s)
		while (*s)
			if(write(fd, s++, 1) == -1)
				return ;
	if(write(fd, "\n", 1) == -1)
		return ;
}
