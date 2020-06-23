//
// Created by Sergei on 23.06.2020.
//

#include "distortions/headers/Rotate.h"

inline QPixmap Rotate::Distort(QPixmap pixmap) {
    return pixmap.transformed(QMatrix().rotate(_degrees));
}
