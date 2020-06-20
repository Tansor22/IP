//
// Created by Sergei on 19.06.2020.
//

#ifndef IP_SEQUENTIALCONVOLUTIONTOOL_H
#define IP_SEQUENTIALCONVOLUTIONTOOL_H

#include "ConvolutionTool.h"

class SequentialConvolutionTool : public ConvolutionTool {
public:
    SequentialConvolutionTool() : ConvolutionTool() {};

    double *Process(int w, int h, double *toProcess, int kernelW, int kernelH, double *kernel, double divider) override;

};


#endif //IP_SEQUENTIALCONVOLUTIONTOOL_H
