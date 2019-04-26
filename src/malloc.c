#include "ft_malloc.h"

t_header	*morecore(size_t size)
{
	(void)size;
	return NULL;
}

void	*malloc(size_t size)
{
	t_header	*curr;
	t_header	*prev;
	size_t		nunits;
	void		*space;

	space = NULL;
	nunits = (size + sizeof(t_header) - 1) / (sizeof(t_header) + 1);
	if ((prev = freep) == NULL)
	{
		base.next = freep = prev = &base;
		base.units = 0;
	}
	while(!space)
	{
		curr = prev->next;
		if (curr->units >= nunits)
			prev->next = curr->next;
		prev = curr;
		curr = curr->next;
	}
	return (space);
}