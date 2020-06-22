//
// Created by Sergei on 22.06.2020.
//

#include <common/headers/ImageToProcess.h>
#include <common/headers/RgbImage.h>
#include <common/headers/GrayImage.h>
#include <convolution/headers/ConvolutionBuilder.h>
#include <convolution/headers/KernelsHandler.h>
#include <convolution/headers/BorderPolicy.h>
#include <convolution/headers/FavOperations.h>
#include "demos/headers/Lab1.h"
#include "common/headers/ImagesHandler.h"

void Lab1::Go() {
    ImageToProcess *itp = new RgbImage(_pixmap,
                                       ImagesHandler::Instance()->GetImageNameById(_imageId));
    GrayImage dx, dy;
    dx = dy = *GrayImage::From(itp);
    auto *convolutionBuilder = new ConvolutionBuilder;

    convolutionBuilder
            ->WithImage(&dx)
            ->WithTool(new SequentialConvolutionTool)
            ->WithKernel(KernelsHandler::GetSobelX())
            ->WithOutOfBoundPolicy(new BorderPolicy)
            ->WithOperation("DERIVATIVE_X")
            ->NoNormalize()
            ->NoClip()
            ->Apply();

    convolutionBuilder
            ->WithImage(&dy)
            ->WithOperation("DERIVATIVE_Y")
            ->NoNormalize()
            ->WithKernel(KernelsHandler::GetSobelY())
            ->Apply();

    GrayImage sobel(_pixmap.width(), _pixmap.height());


    for (int i = 0; i < _pixmap.width() * _pixmap.height(); ++i)
        sobel[i] = sqrt(dx[i] * dx[i] + dy[i] * dy[i]);



    sobel.NormalizeMinMax();

    dx.NormalizeMinMax();
    dy.NormalizeMinMax();

    dx.Save(itp->GetName() + "_DERIVATIVE_X");
    dy.Save(itp->GetName() + "_DERIVATIVE_Y");


    sobel.Save(itp->GetName() + "_SOBEL");

    RgbImage gauss;

    gauss = itp;

    double sigma = 1.3;
    convolutionBuilder
            ->WithImage(&gauss)
            ->WithOperation(itp->GetColorPrefix() + "_GAUSS_SIGMA_" + to_string(sigma))
            ->WithClipFlag(false)
            ->Save()
            ->WithNormalizationFlag(false)
            ->WithKernel(KernelsHandler::GetGauss(sigma))
            ->Apply();

    delete convolutionBuilder;

//    GrayImage *sobfav = FavOperations::GetSobel(itp);
//    sobfav->Save("SOBVAF");
//    GrayImage *dirfav = FavOperations::GetGradientDirection(itp);
//    dirfav->Save("dirFAv");
//    GrayImage *dxFav = FavOperations::GetDerivativeX(itp);
//    dxFav->Save("dxFav");
//    GrayImage *dyFav = FavOperations::GetDerivativeY(itp);
//    dyFav->Save("dyFav");
}
