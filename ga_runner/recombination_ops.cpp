#include "recombination_ops.h"
#include <algorithm>
#include <random>
#include <cmath>

static std::random_device dev_urandom;
static std::mt19937 point_rng(dev_urandom());
std::vector<BoolString> multi_point_crossingover(GARunner<BoolString>& gar, BoolString bs1, BoolString bs2)
{
	std::vector<size_t> points;
	// Генерируем ceil(ln(N)) уникальных точек разреза
	std::uniform_int_distribution<size_t> point_dist(0, bs1.size() - 1);
	for(size_t i = 0; i < ceil(log(bs1.size())); ++i){
		while(1){
			size_t pt = point_dist(point_rng);
			int repeat = 0;
			for(size_t j = 0; j < i; ++j)
				if(points[j] == pt)
				{ repeat = 1; break; }
			if(!repeat){
				points.push_back(pt);
				break;
			}
		}
	}
	std::sort(points.begin(), points.end());
	// Генерируем первого потомка: берём первую булеву строку и вставляем в неё фрагменты из второй согласно точкам разреза
	BoolString ch1 = bs1;
	for(size_t i = 0; i < points.size(); i += 2){
		if(i != points.size() - 1){
			std::copy(bs2.begin() + points[i], bs2.begin() + points[i + 1], ch1.begin() + points[i]);
		}
		else{ // обмен генами с закольцовыванием от конца в начало
			std::copy(bs2.begin() + points[i], bs2.end(), ch1.begin() + points[i]);
			std::copy(bs2.begin(), bs2.begin() + points[0], ch1.begin());
		}
	}
	// Генерируем второго потомка: берём вторую булеву строку и вставляем в неё фрагменты из первой согласно точкам разреза
	BoolString ch2 = bs2;
	for(size_t i = 0; i < points.size(); i += 2){
		if(i != points.size() - 1){
			std::copy(bs1.begin() + points[i], bs1.begin() + points[i + 1], ch2.begin() + points[i]);
		}
		else{ // обмен генами с закольцовыванием от конца в начало
			std::copy(bs1.begin() + points[i], bs1.end(), ch2.begin() + points[i]);
			std::copy(bs1.begin(), bs1.begin() + points[0], ch2.begin());
		}
	}
	return {ch1, ch2};
}
