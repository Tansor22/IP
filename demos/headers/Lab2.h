//
// Created by Sergei on 22.06.2020.
//

#ifndef IP_LAB2_H
#define IP_LAB2_H


#include <QtGui/QPixmap>
#include <common/headers/ProjectConstants.h>
#include <pyramids/headers/Octave.h>
#include "Lab.h"

class Lab2 : public Lab {
public:
    explicit Lab2(QPixmap &pixmap, ImageId imageId,
                  int nOctaves, int nLevels, double sigmaA, double sigma0)
            : Lab(), _pixmap(pixmap), _imageId(imageId), _nOctaves(nOctaves), _nLevels(nLevels),
              _sigmaA(sigmaA), _sigma0(sigma0) {};

    void Go() override;

    ~Lab2() override = default;
    RgbImage* L(vector<Octave*> pyramid, double sigma);
    static string WithPrecision(double value, int precision);

private:

    QPixmap _pixmap;
    ImageId _imageId;
    int _nOctaves, _nLevels;
    double _sigmaA, _sigma0;
};


#endif //IP_LAB2_H
