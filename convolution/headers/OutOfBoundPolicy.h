//
// Created by Sergei on 20.06.2020.
//

#ifndef IP_OUTOFBOUNDPOLICY_H
#define IP_OUTOFBOUNDPOLICY_H


class OutOfBoundPolicy {
public:
    virtual ~OutOfBoundPolicy() = default;

    virtual double &GetValue(double *&data, int w, int h,
                             int x, int y) = 0;

    void SetValue(double *&data, const int &w, const int &h,
                  const int &x, const int &y, double value) {
        if (y >= 0 && x >= 0 && y < w && x < h)
            data[x * w + y] = value;
    };
};


#endif //IP_OUTOFBOUNDPOLICY_H
