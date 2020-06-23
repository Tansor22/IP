//
// Created by Sergei on 22.06.2020.
//

#ifndef IP_DESCRITORBUILDER_H
#define IP_DESCRITORBUILDER_H

#include "pois/headers/POI.h"
#include "common/headers/GrayImage.h"
#include "vector"
#include "Descriptor.h"

using namespace std;

class DescritorBuilder {
public:
    DescritorBuilder(ImageToProcess *itp, vector<POI> &pois, int basketsCount = 8,
                     int histGridSize = 16, int descriptorSize = 4)
            : _pois(pois), _itp(itp), _basketsCount(basketsCount),
              _histGridSize(histGridSize), _descriptorSize(descriptorSize) {}

    vector<Descriptor> Build();

    vector<POI> GetOrientedPOIs(GrayImage *direction, GrayImage *magnitude);

    QImage Join(GrayImage *itp, const vector<Descriptor> &otherDescriptor);

private:
    vector<POI> _pois;
    ImageToProcess *_itp;
    int _basketsCount, _histGridSize, _descriptorSize;
    vector<Descriptor> _imageDescriptor;
};


#endif //IP_DESCRITORBUILDER_H
