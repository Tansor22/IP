//
// Created by Sergei on 23.06.2020.
//

#ifndef IP_SCALE_H
#define IP_SCALE_H

#include <distortions/headers/Distortion.h>

using namespace std;

class Scale : public Distortion {
public:
    explicit Scale(double coeff) : _coeff(coeff){};

    virtual QPixmap Distort(QPixmap pixmap) override ;

    inline virtual std::string GetName() { return "SCALED_COEFF" + to_string(_coeff); }

private:
    double _coeff;
};


#endif //IP_SCALE_H
