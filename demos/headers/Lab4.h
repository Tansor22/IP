//
// Created by Sergei on 23.06.2020.
//

#ifndef IP_LAB4_H
#define IP_LAB4_H


#include <common/headers/ProjectConstants.h>
#include "Lab.h"
#include "QPixmap"

class Lab4 : public Lab {
public:
    explicit Lab4(QPixmap &pixmap, QPixmap &distorted, ImageId imageId, ImageId distortedId, int windowSize,
                  int pointsCount,
                  int basketsCount, int histSize, int descriptorSize)
            : Lab(), _pixmap(pixmap), _distorted(distorted), _imageId(imageId), _distortedId(distortedId),
              _windowSize(windowSize),
              _pointsCount(pointsCount),
              _basketsCount(basketsCount),
              _histSize(histSize), _descriptorSize(descriptorSize) {};

    void Go() override;

    ~Lab4() override = default;

private:
    QPixmap _pixmap, _distorted;
    ImageId _imageId, _distortedId;
    int _windowSize, _pointsCount, _basketsCount, _histSize, _descriptorSize;

};


#endif //IP_LAB4_H
