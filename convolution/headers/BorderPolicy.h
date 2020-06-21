//
// Created by Sergei on 22.06.2020.
//

#ifndef IP_BORDERPOLICY_H
#define IP_BORDERPOLICY_H

#include "OutOfBoundPolicy.h"

class BorderPolicy : public OutOfBoundPolicy {
public:
    double &GetValue(double *&data, int w, int h,
                     int x, int y) override {
        if (x < 0 || y < 0 || x >= h || y >= w) {
            if (x < 0)
                x = 0;
            else if (x >= h)
                x = h - 1;
            if (y < 0)
                y = 0;
            else if (y >= w)
                y = w - 1;
        }
        return data[x * w + y];
    };
};


#endif //IP_BORDERPOLICY_H
