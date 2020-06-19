//
// Created by Sergei on 20.06.2020.
//

#ifndef IP_CONVOLUTION_H
#define IP_CONVOLUTION_H


#include <convolution/headers/Kernel.h>
#include <common/headers/ImageToProcess.h>
#include "ConvolutionTool.h"

class Convolution {
    friend class ConvolutionBuilder;

public:
    Convolution() = default;

    ~Convolution() {
        // do not delete image
        delete _kernel;
        delete _tool;
    };

    void Apply();

private:
    ImageToProcess *_itp;
    Kernel *_kernel;
    ConvolutionTool *_tool;
};


#endif //IP_CONVOLUTION_H
