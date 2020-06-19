//
// Created by Sergei on 18.06.2020.
//

#ifndef IP_DATARETRIEVER_H
#define IP_DATARETRIEVER_H


#include <QtGui/QRgb>
#include <QtGui/QImage>
#include <QtGui/QPixmap>
#include "ProjectConstants.h"

class DataRetriever {
private:
    double (*_mapper)(QRgb);

    // canals retriever works with
    Canal _canals;

    double _Map(QRgb rgb);

public:
    explicit DataRetriever(Canal canals = 0, double (*mapper)(QRgb) = nullptr)
            : _mapper(mapper), _canals(canals) { };

    // splits into canals
    double* RetrieveData(const QRgb *arr, int w, int h);

    // retrieving ints from Qt objects
    QRgb* RetrieveData(const QImage& qi);

    QRgb* RetrieveData(const QPixmap& qp);

};


#endif //IP_DATARETRIEVER_H
