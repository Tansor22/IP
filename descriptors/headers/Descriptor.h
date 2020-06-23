//
// Created by Sergei on 22.06.2020.
//

#ifndef IP_DESCRIPTOR_H
#define IP_DESCRIPTOR_H

#include "vector"
#include <QDebug>
#include <cmath>

using namespace std;

class Descriptor {
    friend class DescritorBuilder;

public:
    Descriptor(int basketsCount, int histSize, int descriptorSize, int x, int y)
            : _basketsCount(basketsCount), _histSize(histSize), _descriptorSize(descriptorSize),
              _x(x), _y(y) {
        // init points descriptors
        vector<double> hist;
        hist.reserve(_basketsCount);
        for (int i = 0; i < _basketsCount; ++i) {
            hist.push_back(0);
        }
        _hists.reserve(_descriptorSize * _descriptorSize);
        for (int j = 0; j < _descriptorSize * _descriptorSize; ++j) {
            _hists.push_back(hist);
        }
    };

    void Print() {
        qDebug() << _hists;
    };

    double Distance(Descriptor const &other) {
        double result = 0;
        for (int i = 0; i < _histSize; i++) {
            for (int j = 0; j < _basketsCount; j++) {
                result += pow((_hists[i][j] - other._hists[i][j]), 2);
            }
        }
        return sqrt(result);
    }

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
