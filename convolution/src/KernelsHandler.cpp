//
// Created by Sergei on 18.06.2020.
//

#include <cmath>
#include "convolution/headers/KernelsHandler.h"

Kernel *KernelsHandler::GetSobelX() {
    return new Kernel(new double[9]{
            1.0, 0, -1.0,
            2.0, 0, -2.0,
            1.0, 0, -1.0
    }, 3, 3);
}

Kernel *KernelsHandler::GetSobelY() {
    return new Kernel(new double[9]{
            1.0, 2.0, 1.0,
            0.0, 0.0, 0.0,
            -1.0, -2.0, -1.0
    }, 3, 3);
}

Kernel *KernelsHandler::GetIncreaseSharpness() {
    return new Kernel(new double[9]{
            -1.0, -1.0, -1.0,
            -1.0, 9.0, -1.0,
            -1.0, -1.0, -1.0
    }, 3, 3);
}

Kernel *KernelsHandler::GetGauss(double sigma) {
    int size = floor(3 * sigma);
    auto *matrix_gauss = new double[size * size];
    int halfSize = size / 2;
    double ss2 = 2 * sigma * sigma;
    double firstDrob = 1.0 / (M_PI * ss2);
    double test_sum = 0.0;
    int rowI = 0;
    for (int x = -halfSize; x <= halfSize; x++) {
        int columnI = 0;
        for (int y = -halfSize; y <= halfSize; y++) {
            double gauss = firstDrob * exp(-(x * x + y * y) / ss2);
            matrix_gauss[rowI * size + columnI++] = gauss;
            test_sum += gauss;
        }
        rowI++;
    }
    for (int x = -halfSize; x <= halfSize; x++)
        for (int y = -halfSize; y <= halfSize; y++)
            matrix_gauss[(x + halfSize) * size + y + halfSize] /= test_sum;
    return new Kernel(matrix_gauss, size, size);
}

Kernel *KernelsHandler::GetGauss(double sigma, int radius, bool normalize) {
    double coeff = 1 / (2 * M_PI * sigma * sigma);
    double divider = 2 * sigma * sigma;
    double sum = 1;
    // -radius .. 0 .. radius
    // 2 radius + point at 0, so + 1
    int w = (2 * radius) + 1;
    int h = (2 * radius) + 1;
    auto *matrix_gauss = new double[w * h];
    int k = 0;
    for (int u = -radius; u <= radius; u++) {
        //qDebug() << "U :" << u << ' ';
        for (int v = -radius; v <= radius; v++) {
            double gaussValue = coeff * exp(-(u * u + v * v) / divider);
            matrix_gauss[k++] = gaussValue;
            sum += gaussValue;

        }
        //qDebug() << "Size gauss::" << k << endl;
        //qDebug() << "radius gauss::" << radius << endl;
    }
    if (normalize)
        for (int i = 0; i < w * h; ++i)
            matrix_gauss[i] /= sum;
    return new Kernel(matrix_gauss, w, h);
}
