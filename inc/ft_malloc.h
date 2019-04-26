#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include <stddef.h>
# include <stdint.h>

typedef struct 		s_header
{
	struct s_header	*next;
	size_t			units;
} 					t_header;

static t_header		base;
static t_header		*freep = NULL;

void				free(void *ptr);
void				*malloc(size_t size);
void				*realloc(void *ptr, size_t size);

#endif
