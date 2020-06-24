//
// Created by Sergei on 23.06.2020.
//

#ifndef IP_ROTATE_H
#define IP_ROTATE_H


#include <distortions/headers/Distortion.h>
#include <common/headers/ProjectHelper.h>
using namespace std;
class Rotate : public Distortion {
public:
    explicit Rotate(double degrees) : _degrees(degrees) {};

    virtual QPixmap Distort(QPixmap pixmap);

    inline virtual std::string GetName() { return "ROTATED_" + ProjectHelper::WithPrecision(_degrees, 0); }

private:
    double _degrees;
};


#endif //IP_ROTATE_H
