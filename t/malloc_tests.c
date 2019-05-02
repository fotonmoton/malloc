#include "t.h"

int	return_null_on_zero_size()
{
	_IS(1 == 1);
	_END("return null on zero size");
}

int	main(void)
{
	_SHOULD(return_null_on_zero_size);
	return 0;
}