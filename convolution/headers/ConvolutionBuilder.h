//
// Created by Sergei on 20.06.2020.
//

#ifndef IP_CONVOLUTIONBUILDER_H
#define IP_CONVOLUTIONBUILDER_H

#include "Convolution.h"

class ConvolutionBuilder {
public:
    ConvolutionBuilder() : _convolution(new Convolution) {};

    ~ConvolutionBuilder() {delete _convolution;};

    ConvolutionBuilder *WithImage(ImageToProcess *itp) {
        _convolution->_itp = itp;
        return this;
    };

    ConvolutionBuilder *WithTool(ConvolutionTool *tool) {
        _convolution->_tool = tool;
        return this;
    };

    ConvolutionBuilder *WithKernel(Kernel *kernel) {
        _convolution->_kernel = kernel;
        return this;
    };

    void Apply() { _convolution->Apply(); };
private:
    Convolution *_convolution;

};


#endif //IP_CONVOLUTIONBUILDER_H
