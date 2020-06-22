//
// Created by Sergei on 22.06.2020.
//

#ifndef IP_LAB3_H
#define IP_LAB3_H


#include <QtGui/QPixmap>
#include <common/headers/ProjectConstants.h>
#include "Lab.h"

class Lab3 : public Lab {
public:
    Lab3(QPixmap &pixmap, ImageId imageId) :

            _pixmap(pixmap), _imageId(imageId) {};

    void Go() override;

private:
    QPixmap _pixmap;
    ImageId _imageId;
};


#endif //IP_LAB3_H
