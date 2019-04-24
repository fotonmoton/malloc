/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtertysh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 19:32:43 by gtertysh          #+#    #+#             */
/*   Updated: 2018/06/21 20:21:38 by gtertysh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	get_sign_and_base(const char **s, char *ch, int *sign, int *base)
{
	if (*ch == '-' && (*ch = GETCH(*s)))
		*sign = -1;
	else if (*ch == '+' && (*ch = GETCH(*s)))
		*sign = 1;
	if (*base == 0)
	{
		if (*ch == '0' && (*ch = GETCH(*s)))
		{
			if (ft_tolower(*ch) == 'x' && (*ch = GETCH(*s)))
				*base = 16;
			else
				*base = 8;
		}
		else
			*base = 10;
	}
}

long int	ft_strtol(const char *s, char **endptr, int base)
{
	long int	result;
	int			sign;
	char		ch;

	sign = 1;
	result = 0;
	ch = 0;
	while (s && *s && (ch = GETCH(s)) && ft_isspace(ch))
		;
	get_sign_and_base(&s, &ch, &sign, &base);
	if (base == 16 && ch == '0' && ft_tolower(ch = GETCH(s)) == 'x')
		ch = GETCH(s);
	while (ch && (ft_isdigit(ch) || ft_isalpha(ch)))
	{
		ft_isdigit(ch) ? (ch -= '0') : (ch = (char)(ft_tolower(ch) - 'a' + 10));
		if (ch < base)
			result = result * base + ch;
		else
			break ;
		ch = GETCH(s);
	}
	if (endptr)
		*endptr = (char *)s;
	return (result * sign);
}
