//
// Created by Sergei on 19.06.2020.
//

#include "convolution/headers/SequentialConvolutionTool.h"

double *SequentialConvolutionTool::Process(int w, int h, double *toProcess, int kernelW, int kernelH, double *kernel,
                                           double factor, double bias) {
    int ku = kernelH / 2;
    int kv = kernelW / 2;

    int kernelSize = kernelW * kernelH;

    auto *crossed = new double[w * h];
    auto *toReduce = new double[kernelH * kernelW];

    for (int x = 0; x < h; x++) {
        for (int y = 0; y < w; y++) {
            int k = 0;

            for (int u = -ku; u <= ku; u++)
                for (int v = -kv; v <= kv; v++)
                    toReduce[k++] =
                            _policy->GetValue(toProcess, w, h, x - u, y - v) * kernel[(u + ku) * kernelW + v + kv];


            double reduced = Reduce(toReduce, kernelSize);
            double clipped = _clipFlag ? Clip(reduced, 1.0, 0.0) : reduced;

            _policy->SetValue(crossed, w, h, x, y, clipped);
        }
    }
    delete[] toReduce;
    return crossed;
}
