//
// Created by Sergei on 23.06.2020.
//

#ifndef IP_CONTRAST_H
#define IP_CONTRAST_H


#include "Distortion.h"
#include "common/headers/ProjectHelper.h"
#include "cmath"
using namespace std;

class Contrast : public Distortion {
public:
    explicit Contrast(double factor) : _factor(factor) {};

    QPixmap Distort(QPixmap pixmap) override;


    inline virtual string GetName() override { return "CONTRAST " + ProjectHelper::WithPrecision(_factor, 2); }

private:
    double _factor;

};


#endif //IP_CONTRAST_H
