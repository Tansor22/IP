//
// Created by Sergei on 20.06.2020.
//

#ifndef IP_CONVOLUTIONBUILDER_H
#define IP_CONVOLUTIONBUILDER_H

#include "Convolution.h"

class ConvolutionBuilder {
public:
    ConvolutionBuilder() : _convolution(new Convolution) {};

    ~ConvolutionBuilder() { delete _convolution; };

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

    ConvolutionBuilder *WithOperation(string operationName) {
        _convolution->_operation = operationName;
        return this;
    };

    ConvolutionBuilder *WithOutOfBoundPolicy(OutOfBoundPolicy *policy) {
        _convolution->_tool->_policy = policy;
        return this;
    };

    ConvolutionBuilder *WithClipFlag(bool flag) {
        _convolution->_tool->_clipFlag = flag;
        return this;
    };

    ConvolutionBuilder *WithNormalization(void (*normalization)(Canal, double *&, int)) {
        _convolution->_normalization = normalization;
        return this;
    };

    ConvolutionBuilder *NoClip() {
        return WithClipFlag(false);
    };

    void Apply() { _convolution->Apply(); };
protected:
    Convolution *_convolution;

};


#endif //IP_CONVOLUTIONBUILDER_H
