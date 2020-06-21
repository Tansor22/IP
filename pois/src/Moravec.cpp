//
// Created by Sergei on 21.06.2020.
//

#include "pois/headers/Moravec.h"
#include "convolution/headers/ConvolutionBuilder.h"
#include "convolution/headers/KernelsHandler.h"

vector<POI> Moravec::FindPOIs(int windowSize, int pointsCount) {
    int w = _itp._w;
    int h = _itp._h;
    GrayImage smoothed;
    smoothed = _itp;

    auto *convolutionBuilder = new ConvolutionBuilder;
    convolutionBuilder
            ->WithImage(&smoothed)
            ->WithKernel(KernelsHandler::GetGauss(1.3))
            ->WithOperation("SMOOTH_MORAVEC")
            ->Save()
            ->Apply();

    GrayImage moravec = GrayImage(w, h);
    for (int i = windowSize + 1; i < h - windowSize - 1; i++) {
        for (int j = windowSize + 1; j < w - windowSize - 1; j++) {
            auto local = std::numeric_limits<double>::max();
            for (int iy = -1; iy <= 1; iy++) {
                for (int ix = -1; ix <= 1; ix++) {
                    if (ix != 0 && iy != 0) {
                        double sum = 0;
                        for (int u = -windowSize; u <= windowSize; u++) {
                            for (int v = -windowSize; v <= windowSize; v++) {
                                double tmp = smoothed[j * w + i] - smoothed[(j + ix + u) * w + i + iy + v];
                                sum += tmp * tmp;
                            }
                        }
                        local = std::min(sum, local);
                    }
                }
                moravec[j * w + i] = local;
            }
        }
    }
    vector<POI> pois;
    _itp = moravec;
    LocalMaximums(pois, windowSize);
    int maxSize = std::min(w / 2, h / 2);
    Filter(pois, pointsCount, maxSize);

    return pois;
}
