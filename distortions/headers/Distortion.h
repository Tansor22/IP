//
// Created by Sergei on 23.06.2020.
//

#ifndef IP_DISTORTION_H
#define IP_DISTORTION_H


#include <QtGui/QPixmap>

class Distortion {
public:
    Distortion() = default;

    virtual QPixmap Distort(QPixmap pixmap) = 0;

    virtual std::string GetName() = 0;

    virtual ~Distortion() = default;
};


#endif //IP_DISTORTION_H
