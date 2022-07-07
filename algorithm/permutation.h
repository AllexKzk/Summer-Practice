#ifndef PERMUTATION_H
#define PERMUTATION_H

#include <ostream>
#include <vector>

class Permutation : public std::vector<unsigned>
{
};

std::ostream& operator<<(std::ostream& os, Permutation bs);

#endif