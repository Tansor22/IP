//
// Created by Sergei on 22.06.2020.
//

#include "convolution/headers/FavOperations.h"
#include "convolution/headers/ConvolutionBuilder.h"
#include "convolution/headers/ConvolutionTool.h"
#include "convolution/headers/BorderPolicy.h"
#include "convolution/headers/KernelsHandler.h"
#include "common/headers/GrayImage.h"

GrayImage *FavOperations::GetSobel(ImageToProcess *&input) {
    GrayImage dx, dy;

    dx = dy = *GrayImage::From(input);

    auto *convolutionBuilder = new ConvolutionBuilder;

    convolutionBuilder
            ->WithImage(&dx)
            ->WithTool(new SequentialConvolutionTool)
            ->WithKernel(KernelsHandler::GetSobelX())
            ->WithOutOfBoundPolicy(new BorderPolicy)
            ->NoNormalize()
            ->NoClip()
            ->Apply();

    convolutionBuilder
            ->WithImage(&dy)
            ->WithKernel(KernelsHandler::GetSobelY())
            ->Apply();

    auto *sobel = new GrayImage(input->_w, input->_h);

    for (int i = 0; i < input->_size; ++i)
        (*sobel)[i] = sqrt(dx[i] * dx[i] + dy[i] * dy[i]);

    sobel->NormalizeMinMax();
    delete convolutionBuilder;
    return sobel;
}


GrayImage *FavOperations::GetGradientDirection(ImageToProcess *&input) {
    GrayImage dx, dy;

    dx = dy = *GrayImage::From(input);

    auto *convolutionBuilder = new ConvolutionBuilder;

    convolutionBuilder
            ->WithImage(&dx)
            ->WithTool(new SequentialConvolutionTool)
            ->WithKernel(KernelsHandler::GetSobelX())
            ->WithOutOfBoundPolicy(new BorderPolicy)
            ->NoNormalize()
            ->NoClip()
            ->Apply();

    convolutionBuilder
            ->WithImage(&dy)
            ->WithKernel(KernelsHandler::GetSobelY())
            ->Apply();

    auto *dir = new GrayImage(input->_w, input->_h);

    for (int i = 0; i < input->_size; ++i)
        (*dir)[i] = atan2(dx[i], dy[i]) * 180 / M_PI + 180;

    dir->NormalizeMinMax();
    delete convolutionBuilder;
    return dir;
}

GrayImage *FavOperations::GetDerivativeX(ImageToProcess *&input) {
    GrayImage *dx = GrayImage::From(input);

    auto *convolutionBuilder = new ConvolutionBuilder;

    convolutionBuilder
            ->WithImage(dx)
            ->WithTool(new SequentialConvolutionTool)
            ->WithKernel(KernelsHandler::GetSobelX())
            ->WithOutOfBoundPolicy(new BorderPolicy)
            ->Normalize()
            ->NoClip()
            ->Apply();

    delete convolutionBuilder;
    return dx;
}

GrayImage *FavOperations::GetDerivativeY(ImageToProcess *&input) {
    GrayImage *dy = GrayImage::From(input);

    auto *convolutionBuilder = new ConvolutionBuilder;

    convolutionBuilder
            ->WithImage(dy)
            ->WithTool(new SequentialConvolutionTool)
            ->WithKernel(KernelsHandler::GetSobelY())
            ->WithOutOfBoundPolicy(new BorderPolicy)
            ->Normalize()
            ->NoClip()
            ->Apply();
    delete convolutionBuilder;
    return dy;
}

void FavOperations::GaussSeparable(ImageToProcess *&input, double sigma) {

    double s = sigma * sigma * 2;

    int halfSize = static_cast<int>(sigma) * 3;
    if (halfSize % 2 == 0) {
        ++halfSize;
    }
    int size = 2 * halfSize;
    auto *kernel = new double[size];
    int k = 0;

    for (int i = -halfSize; i <= halfSize; i++, k++)
        kernel[k] = (exp(-i * i / s) / (M_PI * s));

    auto *convolutionBuilder = new ConvolutionBuilder;

    convolutionBuilder
            ->WithImage(input)
                    // as a row
            ->WithKernel(new Kernel(kernel, size, 1))
            ->Apply();

    convolutionBuilder
            ->WithImage(input)
                    // as a column
            ->WithKernel(new Kernel(kernel, 1, size))
            ->Apply();
    delete convolutionBuilder;
}
