//
// Created by Sergei on 20.06.2020.
//

#ifndef IP_CONVOLUTION_H
#define IP_CONVOLUTION_H


#include <convolution/headers/Kernel.h>
#include <common/headers/ImageToProcess.h>
#include "ConvolutionTool.h"
#include "SequentialConvolutionTool.h"
#include "OutOfBoundPolicy.h"

class Convolution {
    friend class ConvolutionBuilder;

public:
    Convolution() : _normalization(false), _itp(nullptr),
                    _tool(new SequentialConvolutionTool), _kernel(nullptr) {};

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

    bool _normalization;
};

#endif //IP_CONVOLUTION_H
