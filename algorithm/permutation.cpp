#include "permutation.h"

std::ostream& operator<<(std::ostream& os, Permutation bs)
{
	for(size_t i = 0; i < bs.size(); ++i)
		os << bs[i] << " ";
	return os;
}