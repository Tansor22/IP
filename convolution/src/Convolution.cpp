//
// Created by Sergei on 20.06.2020.
//

#include "convolution/headers/Convolution.h"
#include "common/headers/ItpPrinter.h"
#include "common/headers/ImagesHandler.h"
using namespace std;
void Convolution::Apply() {
    string message = "Before" + _operation + ": ";
    ItpPrinter().Print(message, *_itp);
    if (ProjectHelper::IsGray(_itp->_type)) {
        auto *processedData = _tool->Process(_itp->_w, _itp->_h, _itp->_data,
                                             _kernel->_w, _kernel->_h, _kernel->_data, 0);
        ProjectHelper::NormalizeMinMax(GRAY, processedData, _itp->_size);
        delete _itp->_data;
        _itp->_data = processedData;
    } else {
        // rgb
        auto *newData = new double[_itp->_size * _itp->_canalsCount];

        auto *r = new double[_itp->_size],
                *g = new double[_itp->_size],
                *b = new double[_itp->_size];

        std::copy(_itp->_data, _itp->_data + _itp->_size, r);
        std::copy(_itp->_data + _itp->_size, _itp->_data + _itp->_size * 2, g);
        std::copy(_itp->_data + _itp->_size * 2, _itp->_data + _itp->_size * 3, b);

        auto *processedR = _tool->Process(_itp->_w, _itp->_h, r,
                                          _kernel->_w, _kernel->_h, _kernel->_data, 0);
        auto *processedG = _tool->Process(_itp->_w, _itp->_h, g,
                                          _kernel->_w, _kernel->_h, _kernel->_data, 0);
        auto *processedB = _tool->Process(_itp->_w, _itp->_h, b,
                                          _kernel->_w, _kernel->_h, _kernel->_data, 0);


        // ??? replace on custom copier
        std::copy(processedR, processedR + _itp->_size, newData);
        std::copy(processedG, processedG + _itp->_size, newData + _itp->_size - 1);
        std::copy(processedB, processedB + _itp->_size, newData + _itp->_size * 2 - 1);

        delete _itp->_data;
        delete processedR;
        delete processedG;
        delete processedB;
        _itp->_data = newData;
    }
    if (_normalization != nullptr)
        _normalization(_itp->_type, _itp->_data, _itp->_size);

    message = "After" + _operation + ": ";
    ItpPrinter().Print(message, *_itp);
    _itp->Save(_itp->_name + " " + _operation);
}
