//
// Created by Sergei on 23.06.2020.
//

#include "distortions/headers/Scale.h"

QPixmap Scale::Distort(QPixmap pixmap) {
    return pixmap.scaled((int) (pixmap.width() * _coeff),(int) (pixmap.height() * _coeff));
}
