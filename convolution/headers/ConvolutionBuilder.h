//
// Created by Sergei on 20.06.2020.
//

#ifndef IP_CONVOLUTIONBUILDER_H
#define IP_CONVOLUTIONBUILDER_H

#include "Convolution.h"
#include "string"
#include "common/headers/ItpPrinter.h"
#include "ConvolutionTool.h"


using namespace std;

class ConvolutionBuilder {
public:
    ConvolutionBuilder() : _save(false), _operation("UNNAMED_OPERATION"), _convolution(new Convolution) {};

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

    ConvolutionBuilder *WithOperation(const string &operationName) {
        _operation = operationName;
        return this;
    };

    ConvolutionBuilder *WithSaveFlag(bool saveFlag) {
        _save = saveFlag;
        return this;
    };

    ConvolutionBuilder *Save() {
        return WithSaveFlag(true);
    };

    ConvolutionBuilder *WithOutOfBoundPolicy(OutOfBoundPolicy *policy) {
        _convolution->_tool->_policy = policy;
        return this;
    };

    ConvolutionBuilder *WithClipFlag(bool flag) {
        _convolution->_tool->_clipFlag = flag;
        return this;
    };

    ConvolutionBuilder *WithNormalizationFlag(bool normalizationFlag) {
        _convolution->_normalization = normalizationFlag;
        return this;
    };

    ConvolutionBuilder *Normalize() {
        return WithNormalizationFlag(true);
    };

    ConvolutionBuilder *NoClip() {
        return WithClipFlag(false);
    };

    void Apply() {
        string message = "Before" + _operation + ": ";
        ItpPrinter().Print(message, *_convolution->_itp);


        _convolution->Apply();

        message = "After" + _operation + ": ";
        ItpPrinter().Print(message, *_convolution->_itp);
        if (_save)
            _convolution->_itp->Save(_convolution->_itp->_name + " " + _operation);
    };
protected:
    Convolution *_convolution;
    string _operation;
    bool _save;
};


#endif //IP_CONVOLUTIONBUILDER_H
