#include "t.h"
#include "ft_malloc.h"
#include "ft_malloc_internal.h"


int	inital_base_next_point_to_itself(void)
{
	_IS(g_base.next == &g_base);
	_END("inital_base_next_point_to_itself");
}

int	returns_not_null_pointer(void)
{
	void	*ptr;

	ptr = malloc(10);
	_IS(ptr != NULL);
	_END("returns_not_null_pointer");
}

int	main(void)
{
	_SHOULD(inital_base_next_point_to_itself);
	_SHOULD(returns_not_null_pointer);
	return 0;
}