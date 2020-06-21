//
// Created by Sergei on 20.06.2020.
//

#include "convolution/headers/Convolution.h"
#include "common/headers/ItpPrinter.h"

using namespace std;

void Convolution::Apply() {
    _itp->Convolution(_tool, _kernel);
    if (_normalization)
        _itp->NormalizeMinMax();
}
