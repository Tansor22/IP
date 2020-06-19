//
// Created by Sergei on 19.06.2020.
//

#include "convolution/headers/SequentialConvolutionTool.h"

double *SequentialConvolutionTool::Process(int w, int h, int nCanals, double *toProcess,
                                           int kernelW, int kernelH, double *kernel, double divider) {
    // data required by calculation
    int ku = kernelH / 2;
    int kv = kernelW / 2;

    auto *crossed = new double[w * h * nCanals];

    // initialize auxiliary data
    auto *toReduce = new double[kernelW * kernelH * nCanals];
    auto *reduced = new double[0];

    for (int i = 0; i < h; i++) {
        // cross
        for (int j = 0; j < w; j++) {
            for (int u = -ku; u <= ku; u++)
                for (int v = -kv; v <= kv; v++) {
                    int x = i - u;
                    int y = j - v;
                    // correct out of bound, copies of the image at the edges effect
                    if (x < 0 || y < 0 || x >= h || y >= w) {
                        // x coordinat
                        if (x < 0)
                            x += h;
                        else if (x >= h)
                            x -= h;
                        // y coordinat
                        if (y < 0)
                            y += w;
                        else if (y >= w)
                            y -= w;
                    }
                    // store values to reduce by canals, canal-corrected ->  + w * h * c
                    int reducedPtr = 0;
                    for (int c = 0; c < nCanals; c++)
                        toReduce[reducedPtr++] =
                                kernel[(u + ku) * kernelW + v + kv] * toProcess[x * w + y + w * h * c];
                    delete[] reduced;
                    reduced = _Reduce(nCanals, toReduce, kernelW * kernelH);
                }
            //Helper::printSample(0, nCanals, reduced);

            // correct by divider and fill output array
            for (int c = 0; c < nCanals; c++) {
                reduced[c] *= divider;
                crossed[i * w + j + w * h * c] = reduced[c];
            }
        }
    }
    delete[] toReduce;
    delete[] reduced;
    return crossed;
}
