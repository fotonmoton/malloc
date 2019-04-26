#include "ft_malloc.h"
#include <sys/mman.h>

t_header	*morecore(size_t nuints)
{
	t_header	*block;
	if (nuints < MIN_ALLOC_UNITS)
		nuints = MIN_ALLOC_UNITS;
	block = mmap(NULL, nuints * UINIT, PROT_READ | PROT_WRITE, MAP_ANON, -1, 0);
	if (block == MAP_FAILED)
		return (NULL);
	block->units = nuints;
	free((void *)(block + UINIT));
	return free_blocks;
}

void	*malloc(size_t size)
{
	t_header	*curr;
	t_header	*prev;
	size_t		nunits;
	void		*space;

	space = NULL;
	nunits = (size + UINIT - 1) / (UINIT + 1);
	if ((prev = free_blocks) == NULL)
	{
		base.next = free_blocks = prev = &base;
		base.units = 0;
	}
	while(!space)
	{
		curr = prev->next;
		if (curr->units >= nunits)
		{
			if (curr->units == nunits)
				prev->next = curr->next;
			else
			{
				curr->units -= nunits;
				curr += curr->units;
				curr->units = nunits;
			}
		}
		free_blocks = prev;
		space = (void *)(curr + UINIT);
		if (curr == free_blocks)
			if ((curr = morecore(nunits)) == NULL)
				return (NULL);
		prev = curr;
		curr = curr->next;
	}
	return (space);
}