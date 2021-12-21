#include <cstdio>

#include "map.h"

int main()
{
	#define CALL(x) putchar x;
	MAP(CALL, ('a'), ('b'), ('c'))
}
