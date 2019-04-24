/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtertysh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/31 10:27:11 by gtertysh          #+#    #+#             */
/*   Updated: 2018/06/21 19:46:28 by gtertysh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double		ft_atof(const char *str)
{
	double	fraction;
	double	number;
	int		sign;
	char	ch;

	fraction = 1;
	number = 0.0;
	sign = 1;
	ch = 0;
	while (str && *str && (ch = GETCH(str)) && ft_isspace(ch))
		;
	if (ch == '-' && (ch = GETCH(str)))
		sign = -1;
	if (ch == '+' && (ch = GETCH(str)))
		sign = 1;
	while (ch && ft_isdigit(ch))
	{
		number = number * 10.0 + (ch - '0');
		ch = GETCH(str);
	}
	if ('.' == ch)
		while ((ch = GETCH(str)) && ft_isdigit(ch) && (fraction *= 0.1))
			number += (ch - '0') * fraction;
	return (number * sign);
}
