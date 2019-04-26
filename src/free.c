#include "ft_malloc.h"

void			free(void *used)
{
	t_header 	*runner;
	t_header	*to_be_freed;

	to_be_freed = (t_header *)used - UINIT;
	runner = free_blocks;
	while(!(to_be_freed > runner && to_be_freed < runner->next))
	{
		if (runner >= runner->next && (to_be_freed > runner || to_be_freed < runner->next))
			break ;
		runner = runner->next;
	}
	if (to_be_freed + to_be_freed->units == runner->next)
	{
		to_be_freed->units += runner->units;
		to_be_freed->next = runner->next->next;
	}
	else if (runner + runner->units == to_be_freed)
	{
		runner->units += to_be_freed->units;
		runner->next = to_be_freed->next;
	}
	else
		runner->next = to_be_freed;
	free_blocks = runner;
}
