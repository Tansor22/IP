//
// Created by Sergei on 22.06.2020.
//

#include <common/headers/ImageToProcess.h>
#include <common/headers/ImagesHandler.h>
#include <common/headers/RgbImage.h>
#include <pyramids/headers/Pyramid.h>
#include <pyramids/headers/Octave.h>
#include <convolution/headers/ConvolutionBuilder.h>
#include <convolution/headers/FavOperations.h>
#include "demos/headers/Lab2.h"
#include "cmath"

void Lab2::Go() {
    vector<Octave *> pyramid;

    double k = pow(2.0, 1.0 / (_nLevels - 1)); // interval
    double sigmaB = sqrt(_sigma0 * _sigma0 - _sigmaA * _sigmaA);

    auto *itp = new RgbImage(_pixmap, ImagesHandler::Instance()->GetImageNameById(_imageId));

    // blur it a bit
    FavOperations::GaussSeparable(reinterpret_cast<ImageToProcess *&>(itp), sigmaB);


    double sigma[_nLevels - 1];
    double sigmaOld = _sigma0;
    for (int i = 0; i < _nLevels - 1; i++) {
        double sigmaNew = sigmaOld * k;
        sigma[i] = sqrt(sigmaNew * sigmaNew - sigmaOld * sigmaOld);
        sigmaOld = sigmaNew;
    }

    double sigmaEff = _sigma0;
    vector<Pyramid *> *oneOctave;  // single octave
    Pyramid *currentLayer;

    for (int i = 0; i < _nOctaves; i++) {
        oneOctave = new vector<Pyramid *>();
        double sigmaLocal = _sigma0;

        currentLayer = new Pyramid(itp, i, 0);
        currentLayer->SetSigmaLocal(sigmaLocal);
        currentLayer->SetSigmaEffective(sigmaEff);
        oneOctave->push_back(currentLayer);

        for (int j = 1; j < _nLevels; j++) {
            FavOperations::GaussSeparable(reinterpret_cast<ImageToProcess *&>(itp), sigma[j - 1]);
            sigmaLocal *= k;
            sigmaEff *= k;
            currentLayer = new Pyramid(itp, i, j);
            currentLayer->SetSigmaLocal(sigmaLocal);
            currentLayer->SetSigmaEffective(sigmaEff);
            oneOctave->push_back(currentLayer);
        }

        pyramid.push_back(new Octave(oneOctave, i));

        if (i < _nOctaves - 1)
            itp->DownSample(); // shrinking image
    }

    // writing to hard disk

    for (auto *octave : pyramid) {
        for (Pyramid *layer : *octave->GetLayers()) {
            string path = itp->GetName() + "_octave " + WithPrecision(layer->GetOctaves() + 1, 3) +
                          +"-sigma_local" + WithPrecision(layer->GetSigmaLocal(), 3) + "-sigma_global" +
                    WithPrecision(layer->GetSigmaEffective(), 3) +
                          "_image" + WithPrecision(layer->GetLayers() + 1, 3);
            layer->GetItp()->Save(path);
        }
    }
}

inline string Lab2::WithPrecision(double value, int precision) {
    return to_string(value).substr(0, to_string(value).find('.') + precision + 1);
}