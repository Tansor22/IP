//
// Created by Sergei on 21.06.2020.
//

#ifndef IP_POI_H
#define IP_POI_H

#include <cmath>

struct POI {
public:
    POI(int x, int y, double c) : x(x), y(y), c(c) {};

    POI(POI const &other) = default;

    bool operator<(POI poi) const { return c < poi.c; }

    bool operator>(POI poi) const { return c > poi.c; }

    double Distance(POI poi) {
        double xd = x - poi.x;
        double yd = y - poi.y;
        return sqrt(xd * xd + yd * yd);
    }

    int x, y;
    double c;
};


#endif //IP_POI_H
