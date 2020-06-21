//
// Created by Sergei on 22.06.2020.
//

#include "descriptors/headers/DescritorBuilder.h"
#include "descriptors/headers/Descriptor.h"
#include "convolution/headers/KernelsHandler.h"
#include "convolution/headers/ConvolutionBuilder.h"
#include "convolution/headers/BorderPolicy.h"
#include "QtMath"

void DescritorBuilder::Build() {
    int w = _itp._w;
    int h = _itp._h;
    auto *convolutionBuilder = new ConvolutionBuilder;
    GrayImage dx;
    GrayImage dy;
    dx = _itp;
    dy = _itp;

    convolutionBuilder
            ->WithImage(&dx)
            ->WithKernel(KernelsHandler::GetSobelX())
            ->WithOperation("DERIVATIVE_X_DESCRIPTORS")
            ->WithOutOfBoundPolicy(new BorderPolicy)
            ->Normalize()
                    //->Save()
            ->NoClip()
            ->Apply();


    convolutionBuilder
            ->WithImage(&dy)
            ->WithKernel(KernelsHandler::GetSobelY())
            ->WithOperation("DERIVATIVE_Y_DESCRIPTORS")
            ->Normalize()
                    //->Save()
            ->NoClip()
            ->Apply();
    delete convolutionBuilder;

    GrayImage gradientDirection(w, h);
    GrayImage gradientMagnitude(w, h);
    gradientDirection = _itp;


    //TODO
    //direction
    for (int i = 0; i < w * h; i++)
        gradientDirection._data[i] = atan2(dx._data[i], dy._data[i]) * 180 / M_PI + 180;

    gradientDirection.Save("GRADIENT_DIRECTION");

    // sobel
    for (int i = 0; i < w * h; i++)
        gradientMagnitude[i] = sqrt(dx[i] * dx[i] + dy[i] * dy[i]);

    gradientMagnitude.Save("GRADIENT_MAGNITUDE");

    // descriptors start
    double basketSize = 360. / _basketsCount;
    int descriptorRadius = _descriptorSize / 2 * _histGridSize;
    int histogramRadius = _histGridSize / 2;

    double sigma = static_cast<double>(_histGridSize) / 6;
    QVector<QVector<double>> gaussKernel;

    double coeff = 1 / (2 * M_PI * sigma * sigma);
    double divider = 2 * sigma * sigma;

    for (int u = -histogramRadius; u <= histogramRadius; u++) {
        QVector<double> gaussRow;
        for (int v = -histogramRadius; v <= histogramRadius; v++) {
            gaussRow.append(coeff * exp(-(u * u + v * v) / divider));
        }
        gaussKernel.append(gaussRow);
    }
    int pointCount = 0;
    vector<Descriptor> imageDescriptor;


    for (auto &poi : _pois) {
        pointCount++;
        int x = poi.x, y = poi.y;
        Descriptor pointDescriptor(_basketsCount, _histGridSize, _descriptorSize, x, y);
        for (int ih = -descriptorRadius; ih < descriptorRadius; ih++) {
            for (int jh = -descriptorRadius; jh < descriptorRadius; jh++) {
                int currX = x + jh, currY = y + ih;

                double currDirection = gradientDirection[currX * w + currY];
                currDirection = (currDirection < 0) ? currDirection + 360 : currDirection;
                currDirection = (currDirection >= 360) ? currDirection - 360 : currDirection;
                double currMagnitude = gradientMagnitude[currX * w + currY];

                double basketBetw = currDirection / basketSize;

                int basket1 = floor(basketBetw);
                double b1Weight = 1;

                int basket2 = ceil(basketBetw);
                double b2Weight = 0;

                //если на границе с 0 или 360 градусов
                if (basketBetw < basket1 + 0.5) {
                    basket2 = basket1 - 1;
                    if (basket2 < 0) basket2 = _basketsCount - 1;

                    b1Weight = abs(basketBetw - floor(basketBetw) + 0.5);
                } else {
                    basket2 = basket1 + 1;
                    if (basket2 > _basketsCount - 1) basket2 = 0;

                    b1Weight = abs(basketBetw - floor(basketBetw) - 0.5);

                }
                b2Weight = 1. - b1Weight;

                int histRowNum = (ih + descriptorRadius) / _descriptorSize / histogramRadius;
                int histColNum = (jh + descriptorRadius) / _descriptorSize / histogramRadius;
                int currHist = _descriptorSize * histRowNum + histColNum;

                pointDescriptor[currHist][basket1] += currMagnitude * b1Weight *
                                                      gaussKernel[(ih + descriptorRadius) / (_descriptorSize)]
                                                      [(jh + descriptorRadius) / (_descriptorSize)];

                pointDescriptor[currHist][basket2] += currMagnitude * b2Weight *
                                                      gaussKernel[(ih + descriptorRadius) / (_descriptorSize)]
                                                      [(jh + descriptorRadius) / (_descriptorSize)];

            }
        }
        pointDescriptor.Normalize();
        imageDescriptor.push_back(pointDescriptor);
    }
    _imageDescriptor = imageDescriptor;
}
