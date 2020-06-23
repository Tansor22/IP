//
// Created by Sergei on 23.06.2020.
//

#ifndef IP_SHIFT_H
#define IP_SHIFT_H


#include "Distortion.h"

using namespace std;

class Shift : public Distortion {
public:
    Shift(int x, int y) : _x(x), _y(y) {};

    QPixmap Distort(QPixmap pixmap) override;

    inline virtual std::string GetName() override { return "SHIFTED X_" + to_string(_x) + "_Y_" + to_string(_y); }

private:
    int _x;
    int _y;
};


#endif //IP_SHIFT_H
