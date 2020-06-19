//
// Created by Sergei on 18.06.2020.
//

#include "../headers/DataRetriever.h"
// retrieves data from QPixmap, QImage, and canals value from rgb int array
double DataRetriever::_Map(QRgb rgb) {
    return _mapper != nullptr ? _mapper(rgb) : (double) rgb;
}

QRgb* DataRetriever::RetrieveData(const QImage& qi) {
    int w = qi.width();
    int h = qi.height();
    QRgb* data = new QRgb[w * h];
    for (int i = 0; i < h; i++)
        for (int j = 0; j < w; j++)
            data[i * w + j] = qi.pixel(j,i);
    return data;
}

QRgb *DataRetriever::RetrieveData(const QPixmap& qp) {
    return RetrieveData(qp.toImage());
}

double *DataRetriever::RetrieveData(const QRgb *arr, int w, int h) {
    // checks for gray first
    int coef = 1;
    if ((GRAY & _canals ) != GRAY) {
        // gray, coef = 0 will be used
        if ((R & _canals ) == R) coef++;
        if ((G & _canals ) == G) coef++;
        if ((B & _canals ) == B) coef++;
        //if ((A & canals ) == A) coef++;
        // for alpha
        coef++;

    }

    auto* data = new double[w * h * coef];
    for (int i = 0; i < h; i++)
        for (int j = 0; j < w; j++) {
            QRgb rgb = arr[i * w + j];
            if ((GRAY & _canals ) == GRAY) {
                data[i * w + j] = _Map(qGray(rgb));
                continue;
            }
            // the idea
            int canalI = 0;
            if ((R & _canals ) == R)
                data[i * w + j + w * h * canalI++] = _Map(qRed(rgb));
            if ((G & _canals ) == G)
                data[(i * w + j) + w * h * canalI++] = _Map(qGreen(rgb));
            if ((B & _canals ) == B)
                data[(i * w + j) + w * h * canalI++] = _Map(qBlue(rgb));
            if ((A & _canals ) == A)
                data[(i * w + j) + w * h * canalI] = _Map(qAlpha(rgb));
            else data[(i * w + j) + w * h * canalI] = _Map(255);
        }
    return data;
}
