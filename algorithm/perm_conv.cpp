#include "perm_conv.h"
#include <gmpxx.h>
#include <string>
#include <iostream>
#include <cmath>

static double bilog(mpz_t x) {
    signed long int ex;
    const double di = mpz_get_d_2exp(&ex, x);
    return log(di) + log(2) * (double) ex;
}

BoolString perm_to_bool_string(Permutation p){
    for(size_t i = 0; i < p.size(); i++){
        for(size_t j = i+1; j < p.size(); j++){
            if(p[j] > p[i]) --p[j];
        }
    }

    unsigned fact_mod = 1;
    mpz_class fact = 1, num = 0;
    for(size_t i = p.size()-1; ; i--){
        num += fact*p[i];
        fact *= fact_mod;
        fact_mod++;
        if(i == 0) break;
    }

    std::string s = num.get_str(2);
    BoolString bs;
    size_t i = 0;
    for(; i < s.length(); i++) bs.push_back(s[i] - '0');
    for(; i <= ceil(bilog(fact.get_mpz_t())); i++) bs.insert(bs.begin(), 0);
    return bs;
}

Permutation bool_string_to_perm(BoolString bs, size_t matrix_size){
    std::string s;
    for(size_t i = 0; i < bs.size(); i++) s.push_back(bs[i] + '0');
    
    Permutation p;
    mpz_class num;
    num.set_str(s, 2);
    size_t div = 1;
    size_t k = 0;
    for(; num != 0; num /= div, div++, k++){
        mpz_class dig = num % div;
        p.insert(p.begin(), dig.get_ui());
    }
    
    for(; k < matrix_size; k++) p.insert(p.begin(), 0);

    for(size_t i = p.size()-1;;i--){
        for(size_t j = i+1; j < p.size(); j++)if(p[j] >= p[i]) p[j]++;
        if(i == 0) break;
    }
    return p;
}