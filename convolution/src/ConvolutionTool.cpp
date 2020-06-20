//
// Created by Sergei on 19.06.2020.
//

#include "convolution/headers/ConvolutionTool.h"
#include "cmath"

double ConvolutionTool::Reduce(const double *toReduce, int length) {
    double sum = 0.0;
    for (int i = 0; i < length; i++) sum += toReduce[i];
    return sum;
}

double ConvolutionTool::Clip(double num, double max, double min) {
    return num < min ? min : fmin(num, max);
}
