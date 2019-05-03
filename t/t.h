/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t.h                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtertysh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 19:36:58 by gtertysh          #+#    #+#             */
/*   Updated: 2018/10/23 19:40:12 by gtertysh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_H
# define T_H
# include <stdio.h>

# define FAIL() printf("\nfail in %s() %s:%d\n\n", __func__, __FILE__, __LINE__)
# define _IS(t) do { if (!(t)) { FAIL(); return 1; } } while(0)
# define _SHOULD(t) do { int r = t(); if(r) return r; } while(0)
# define _P_START(m) do { printf("%s\n", m); } while(0)
# define _VERIFY(m, t) do { _P_START(m); int r = t(); if(r) return r; } while(0)
# define _END(m) do { printf("  %s - OK\n", m); return 0; } while(0)

#endif