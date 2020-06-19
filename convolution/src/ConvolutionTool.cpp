//
// Created by Sergei on 19.06.2020.
//

#include "convolution/headers/ConvolutionTool.h"
#include "cmath"

double *ConvolutionTool::_Reduce(int nCanals, const double *toReduce, int length) {
    auto* reducedValues = new double[nCanals];
    for (int c = 0; c < nCanals; c++) {
        int canalPtr = c * length;
        reducedValues[c] = 0.0;
        for (int i = 0; i < length; i++) reducedValues[c] += toReduce[i + canalPtr];
    }
    return reducedValues;
}

double ConvolutionTool::_Clip(double num, double max, double min) {
    return num < min ? min : fmin(num, max);
}
