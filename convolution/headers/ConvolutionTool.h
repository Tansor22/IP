//
// Created by Sergei on 19.06.2020.
//

#ifndef IP_CONVOLUTIONTOOL_H
#define IP_CONVOLUTIONTOOL_H


class ConvolutionTool {
public:
    virtual double *Process(int w, int h, int nCanals, double *toProcess,
                            int kernelW, int kernelH, double *kernel, double divider = 1.0) = 0;
    virtual ~ConvolutionTool() = default;
protected:

    // todo добавить
//double *Process(ImageToProcess ??? itp,
//        int kernelW, int kernelH, double *kernel, double divider = 1.0);
    double *_Reduce(int nCanals, const double *toReduce, int length);

    double _Clip(double num, double max, double min);

};


#endif //IP_CONVOLUTIONTOOL_H
