#include "bool_string.h"

std::ostream& operator<<(std::ostream& os, BoolString bs)
{
	for(size_t i = 0; i < bs.size(); ++i)
		os << bs[i];
	return os;
}
