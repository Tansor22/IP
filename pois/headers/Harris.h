//
// Created by Sergei on 21.06.2020.
//

#ifndef IP_HARRIS_H
#define IP_HARRIS_H

#include "POIsFinder.h"

class Harris : public POIsFinder{
public:
    explicit Harris(GrayImage *itp) : POIsFinder(itp) {}

    vector<POI> FindPOIs(int windowSize, int pointsCount) override;

};


#endif //IP_HARRIS_H
