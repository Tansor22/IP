//
// Created by Sergei on 22.06.2020.
//

#ifndef IP_LAB1_H
#define IP_LAB1_H


#include <QtGui/QPixmap>
#include "Lab.h"

class Lab1 : public Lab {
public:
    explicit Lab1(QPixmap &pixmap, ImageId imageId)
    : Lab(), _pixmap(pixmap), _imageId(imageId) {};

    void Go() override;

    ~Lab1() override = default;

private:
    QPixmap _pixmap;
    ImageId _imageId;
};


#endif //IP_LAB1_H
