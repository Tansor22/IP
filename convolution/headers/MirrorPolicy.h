//
// Created by Sergei on 20.06.2020.
//

#ifndef IP_MIRRORPOLICY_H
#define IP_MIRRORPOLICY_H


#include "OutOfBoundPolicy.h"

class MirrorPolicy : public OutOfBoundPolicy {
    double &GetValue(double *&data, int w, int h,
                     int x, int y) override {
        if (x < 0 || y < 0 || x >= h || y >= w) {
            if (x < 0)
                x += h;
            else if (x >= h)
                x -= h;
            if (y < 0)
                y += w;
            else if (y >= w)
                y -= w;
        }
        return data[x * w + y];
    };
};


#endif //IP_MIRRORPOLICY_H
