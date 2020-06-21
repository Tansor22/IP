//
// Created by Sergei on 21.06.2020.
//

#ifndef IP_MORAVEC_H
#define IP_MORAVEC_H


#include "POIsFinder.h"

class Moravec : public POIsFinder {
public:
    explicit Moravec(GrayImage *itp) : POIsFinder(itp) {
    }

    vector<POI> FindPOIs(int windowSize, int pointsCount) override;

};


#endif //IP_MORAVEC_H
