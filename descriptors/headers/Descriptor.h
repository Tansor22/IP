//
// Created by Sergei on 22.06.2020.
//

#ifndef IP_DESCRIPTOR_H
#define IP_DESCRIPTOR_H

#include "vector"

using namespace std;

class Descriptor {
public:
    Descriptor(int basketsCount, int histSize, int descriptorSize, int x, int y)
            : _basketsCount(basketsCount), _histSize(histSize), _descriptorSize(descriptorSize),
              _x(x), _y(y) {};

    vector<double> &operator[](int histNum) { return _hists[histNum]; };

    void Normalize();

private:
    int _x, _y;
    int _basketsCount;
    int _descriptorSize;
    int _histSize;
    vector<vector<double>> _hists;
};


#endif //IP_DESCRIPTOR_H
