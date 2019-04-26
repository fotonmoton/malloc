#include "ft_malloc.h"

t_header	*morecore(size_t size)
{
	(void)size;
	return NULL;
}

void	*malloc(size_t size)
{
	t_header	*p;
	t_header	*prevp;
	size_t		nunits;

	nunits = (size + sizeof(t_header) - 1) / (sizeof(t_header) + 1);
	if ((prevp = freep) == NULL)
	{
		base.next = freep = prevp = &base;
		base.size = 0;
	}
}