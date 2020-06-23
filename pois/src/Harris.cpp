//
// Created by Sergei on 21.06.2020.
//

#include "pois/headers/Harris.h"
#include "convolution/headers/ConvolutionBuilder.h"
#include "convolution/headers/KernelsHandler.h"
#include "convolution/headers/FavOperations.h"

vector<POI> Harris::FindPOIs(int windowSize, int pointsCount) {
    int w = _itp._w;
    int h = _itp._h;
    GrayImage smoothed, dx, dy;
    smoothed = _itp;

    FavOperations::GaussSeparable(&smoothed, 1.3, false);

   // smoothed.Save("HARRIS_GAUSS_SEP");
    dx = *FavOperations::GetDerivativeX(&_itp);
    dy = *FavOperations::GetDerivativeY(&_itp);


    QVector<QVector<double>> a,b,c;


    double sigma = static_cast<double>(windowSize * 2) / 6;
    QVector<QVector<double>> gaussKernel;

    double coeff = 1 / (2 * M_PI * sigma * sigma);
    double delitel = 2 * sigma * sigma;

    for (int u = -windowSize; u <= windowSize; u++) {
        QVector<double> gaussRow;
        for (int v = -windowSize; v <= windowSize; v++) {
            gaussRow.append(coeff * exp(-(u * u + v * v) / delitel));
        }
        gaussKernel.append(gaussRow);
    }
    for (int i = 0; i < h; i++) {
        QVector<double> aRow, bRow, cRow;
        for (int j = 0; j < w; j++) {
            double sumA = 0, sumB = 0, sumC = 0;

            for (int u = -windowSize; u <= windowSize; u++) {
                for (int v = -windowSize; v <= windowSize; v++) {
                    double i_x = dx[(j + v) * w + i + u];
                    double i_y = dy[(j + v) * w + i + u];
                    sumA += i_x * i_x * gaussKernel[windowSize + u][windowSize + v];
                    sumB += i_x * i_y * gaussKernel[windowSize + u][windowSize + v];
                    sumC += i_y * i_y * gaussKernel[windowSize + u][windowSize + v];
                }
            }
            aRow.append(sumA);
            bRow.append(sumB);
            cRow.append(sumC);
        }
        a.append(aRow);
        b.append(bRow);
        c.append(cRow);
    }
    GrayImage harris = GrayImage(w, h);

    for (int i =0; i < h; i++) {
        for (int j =0; j < w; j++) {
            double sc = a[i][j] + c[i][j];
            double d = a[i][j] * c[i][j] - b[i][j] * b[i][j];
            double det = sc * sc - 4 * d;
            double L1 = (sc + sqrt(det)) / 2;
            double L2 = (sc - sqrt(det)) / 2;
            double cHarris = std::min (L1, L2);
            harris[j * w + i] = cHarris;
        }
    }
    vector<POI> pois;
    _itp = harris;
    LocalMaximums(pois, windowSize, 0.004);
    Filter(pois, pointsCount,  std::min(w/2,h/2));


    return pois;
}
