#include "ft_malloc.h"

void			free(void *used)
{
	t_header 	*pivot;
	t_header	*to_be_freed;

	to_be_freed = (t_header *)used - UINIT;
	pivot = free_blocks;
	while(!(to_be_freed > pivot && to_be_freed < pivot->next))
	{
		if (pivot >= pivot->next && (to_be_freed > pivot || to_be_freed < pivot->next))
			break ;
		pivot = pivot->next;
	}
	if (to_be_freed + to_be_freed->units == pivot->next)
	{
		to_be_freed->units += pivot->units;
		to_be_freed->next = pivot->next->next;
	}
	else if (pivot + pivot->units == to_be_freed)
	{
		pivot->units += to_be_freed->units;
		pivot->next = to_be_freed->next;
	}
	else
		pivot->next = to_be_freed;
	free_blocks = pivot;
}
