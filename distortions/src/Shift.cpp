//
// Created by Sergei on 23.06.2020.
//

#include "distortions/headers/Shift.h"

QPixmap Shift::Distort(QPixmap pixmap) {
    QRect r = pixmap.rect();
    r.moveTo(_x, _y);
    return pixmap.copy(r);
}
