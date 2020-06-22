//
// Created by Sergei on 21.06.2020.
//

#ifndef IP_POISFINDER_H
#define IP_POISFINDER_H

#include <common/headers/GrayImage.h>
#include <common/headers/ImageToProcess.h>
#include "vector"
#include "POI.h"

using namespace std;

class POIsFinder {
public:
    explicit POIsFinder(GrayImage *itp)
            : _itp(GrayImage(itp)){
    };

    ~POIsFinder() = default;

    virtual vector<POI> FindPOIs(int windowSize, int pointsCount) = 0;

    void LocalMaximums(vector<POI> &pois, int windowSize, double thresholdCoeff = 0.005);

    static void Filter(vector<POI> &pois, int pointsCount, int maxSize);

protected:
    GrayImage _itp;
};


#endif //IP_POISFINDER_H
