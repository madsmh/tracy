//
// Created by mads on 14/02/2020.
//

#ifndef TRACY_KAHAN_H
#define TRACY_KAHAN_H

#include <vector>

/* Copyright (c) 2020 By the Authors
 *
 * This file is part of Tracy.

 MMRenderer is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 MMRenderer is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with MMRender.  If not, see <http://www.gnu.org/licenses/>.
 *
 * */


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
