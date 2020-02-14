//
// Created by mads on 14/02/2020.
//

#ifndef TRACY_KAHAN_H
#define TRACY_KAHAN_H

#include <vector>

// implements the Kahan summation algorithm as described at
// https://en.wikipedia.org/wiki/Kahan_summation_algorithm

double kahanSum(const std::vector<double>& input){
    double sum = 0.0;
    double c = 0.0;

    for (double i : input) {
        double y = i - c;
        double t = sum + y;

        c = (t-sum)-y;
        sum = t;
    }

    return sum;
}

#endif //TRACY_KAHAN_H
