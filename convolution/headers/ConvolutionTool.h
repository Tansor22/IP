//
// Created by Sergei on 19.06.2020.
//

#ifndef IP_CONVOLUTIONTOOL_H
#define IP_CONVOLUTIONTOOL_H

#include "OutOfBoundPolicy.h"
#include "MirrorPolicy.h"

class ConvolutionTool {
    friend class ConvolutionBuilder;

public:
    ConvolutionTool() : _policy(new MirrorPolicy()), _clipFlag(true) {};

    virtual double *
    Process(int w, int h, double *toProcess, int kernelW, int kernelH, double *kernel, double divider) = 0;

    virtual ~ConvolutionTool() { delete _policy; };

protected:

    double Reduce(const double *toReduce, int length);

    double Clip(double num, double max, double min);

protected:
    OutOfBoundPolicy *_policy;
    bool _clipFlag;
};


#endif //IP_CONVOLUTIONTOOL_H
