//
// Created by Sergei on 19.06.2020.
//

#ifndef IP_KERNEL_H
#define IP_KERNEL_H

#include <algorithm>
#include <common/headers/ProjectHelper.h>
#include <QDebug>

using namespace std;

class Kernel {
    friend class Convolution;

    // todo inheritance and friend class
    friend class GrayImage;

    friend class RgbImage;

    friend class DescritorBuilder;

public:
    Kernel(double *data, int w, int h) : _data(data), _w(w), _h(h) {
//        _data = new double [_w * _h];
//        std::copy(data, data + _w * _h, _data);
    }

    Kernel() : _data(nullptr), _w(0), _h(0) {}

    ~Kernel() { delete _data; }

    double &operator[](int i) {
        if (i < 0 || i >= _w * _h) {
            qDebug() << "Kernel out of bound index " << i << endl;
            exit(EXIT_FAILURE);
        }
        return _data[i];
    };

    void Print(int precision = 4) {
        ProjectHelper::PrintAsMatrix(_w, _h, _data, precision);
    }

private:
    double *_data;
    int _w, _h;
};


#endif //IP_KERNEL_H
