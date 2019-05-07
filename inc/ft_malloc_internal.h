/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc_internal.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtertysh <gtertysh@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 22:37:07 by foton             #+#    #+#             */
/*   Updated: 2019/05/06 22:40:18 by gtertysh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_INTERNAL_H
# define FT_MALLOC_INTERNAL_H

# include <stddef.h>
# include <stdint.h>

# define TINY 512
# define SMALL 4096
# define LARGE 4097
# define START -1
# define MAGIC 0xDEADBEEF
# define NALLOC 100

typedef struct		s_chunk
{
	uint8_t			is_free;
	size_t			size;
	struct s_chunk	*next;
	struct s_chunk	*prev;
	uint32_t		magic;
}					t_chunk;

# define CHUNK_SIZE(size) ((size) + sizeof(t_chunk))

typedef struct		s_arena
{
	int				type;
	size_t			size;
	struct s_arena	*next;
	t_chunk			*heap;
}					t_arena;

# define HEAP_SIZE(size) ((size) - sizeof(t_arena))
# define ARENA_SIZE(size) ((size) + sizeof(t_arena))

extern t_arena		g_base;

#endif