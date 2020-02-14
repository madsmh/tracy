//
// Created by mads on 14/02/2020.
//

#ifndef TRACY_KAHAN_H
#define TRACY_KAHAN_H

#include <vector>

// implements the Kahan summation algorithm as described at
// https://en.wikipedia.org/wiki/Kahan_summation_algorithm

double kahanSum(std::vector<double> input){
    double sum = 0.0;
    double c = 0.0;

    for (int i = 0; i <input.size() ; ++i) {
        double y = input[i] - c;
        double t = sum + y;

        c = (t-sum)-y;
        sum = t;
    }

    return sum;
}

#endif //TRACY_KAHAN_H
