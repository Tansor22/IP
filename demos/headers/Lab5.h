//
// Created by Sergei on 22.06.2020.
//

#ifndef IP_LAB5_H
#define IP_LAB5_H


#include <QtGui/QPixmap>
#include <common/headers/ProjectConstants.h>

#include <distortions/headers/Distortion.h>
#include "Lab.h"

class Lab5 : public Lab {
public:
    explicit Lab5(QPixmap &pixmap, QPixmap &distorted, ImageId imageId, ImageId distortedId,
                  Distortion *distortion, int windowSize,
                  int pointsCount,
                  int basketsCount, int histSize, int descriptorSize)
            : Lab(), _pixmap(pixmap), _distorted(distorted), _imageId(imageId), _distortedId(distortedId),
              _distortion(distortion),
              _windowSize(windowSize),
              _pointsCount(pointsCount),
              _basketsCount(basketsCount),
              _histSize(histSize), _descriptorSize(descriptorSize) {};

    void Go() override;

    ~Lab5() override = default;

private:
    Distortion *_distortion;
    QPixmap _pixmap, _distorted;
    ImageId _imageId, _distortedId;
    int _windowSize, _pointsCount, _basketsCount, _histSize, _descriptorSize;
};


#endif //IP_LAB5_H
