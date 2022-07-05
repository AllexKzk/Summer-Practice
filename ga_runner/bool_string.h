#ifndef BOOL_STRING_H
#define BOOL_STRING_H

#include <ostream>
#include <vector>

class BoolString : public std::vector<bool>
{
};

std::ostream& operator<<(std::ostream& os, BoolString bs);

#endif
