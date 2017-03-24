#include "stdafx.h"
#include "myclass.h"


myclass::myclass(int count)
{
	if(count != this->count)
	printf("count = %d\n", count);
}


myclass::~myclass(void)
{
}
