#include "perm_ga.h"
#include <random>

static std::random_device dev_r;
static std::mt19937 rnd(dev_r());

std::vector<BoolString> generate_rand_perms(size_t matrix_size, size_t pop_size){
    std::vector<BoolString> vbs;
    for(size_t j = 0; j < pop_size; j++){
        Permutation perm;
        std::vector<unsigned> indexes;
        for(size_t i = 0; i < matrix_size; i++){
            indexes.push_back(i);
        }

        for(size_t i = 0; i < matrix_size; i++){
            std::uniform_int_distribution<unsigned> d(0, indexes.size()-1);
            unsigned temp = d(rnd);
            perm.push_back(indexes[temp]);
            indexes.erase(indexes.begin() + temp);
        }
        vbs.push_back(perm_to_bool_string(perm));
    }
    return vbs;
}

double perm_fitness_func(GARunner<BoolString> &gar,BoolString bs){
    std::vector<std::vector<double>> mat = std::any_cast<std::vector<std::vector<double>>>(gar.get_parameter("cost_matrix", {}));
    Permutation p = bool_string_to_perm(bs, mat.size());
    if (p.size() != mat.size()){
        return -INFINITY;
    }
    double summ = 0;
    for(size_t i = 0; i < p.size(); i++){
        summ -= mat[i][p[i]];
    }
    return summ;
}