//
// Created by Sergei on 22.06.2020.
//

#include <common/headers/ImageToProcess.h>
#include <common/headers/ImagesHandler.h>
#include <common/headers/RgbImage.h>
#include <common/headers/GrayImage.h>
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
    FavOperations::GaussSeparable(itp, sigmaB, false);


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
            FavOperations::GaussSeparable(reinterpret_cast<ImageToProcess *&>(itp), sigma[j - 1], false);
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
            layer->GetItp()->NormalizeMinMax();
            layer->GetItp()->Save(path);
        }
    }
    // L(x,y,sigma)
    RgbImage *imgL = L(pyramid, _sigma0);
    //imgL->Save("L");
}

inline string Lab2::WithPrecision(double value, int precision) {
    return to_string(value).substr(0, to_string(value).find('.') + precision + 1);
}

RgbImage *Lab2::L(vector<Octave *> pyramid, double sigma) {
    Pyramid *targetLayer = pyramid[0]->_layers[0][0];

    int octaveLevel = 0;
    int octaveCount = 0;
    for (auto &octave : pyramid) {
        for (auto &layer : *octave->_layers) {
            if (fabs(layer->_sigmaEffective - sigma) < fabs(targetLayer->_sigmaEffective - sigma)) {
                targetLayer = layer;
                octaveLevel = octaveCount;
            }
        }
        octaveCount++;
    }
    targetLayer->_itp->Save("TARGET");

    int trans_coeff = pow(2., octaveLevel);
    RgbImage *output = new RgbImage(_pixmap.width(), _pixmap.height());
    for (int i = 0; i < _pixmap.height(); i++)
        for (int j = 0; j < _pixmap.width(); j++) {
            //преобразование координат
            int i_n = static_cast<int>(i / trans_coeff);
            int j_n = static_cast<int>(j / trans_coeff);
            if (j_n >= targetLayer->_itp->_w) j_n = targetLayer->_itp->_w - 1;
            if (i_n >= targetLayer->_itp->_h) i_n = targetLayer->_itp->_h - 1;

            output->_r[i * output->_w + j] = targetLayer->_itp->_r[i_n * output->_w + j_n];
            output->_g[i * output->_w + j] = targetLayer->_itp->_g[i_n * output->_w + j_n];
            output->_b[i * output->_w + j] = targetLayer->_itp->_b[i_n * output->_w + j_n];
        }
    output->Save("L");
    return output;
}
