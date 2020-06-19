//
// Created by Sergei on 20.06.2020.
//

#include "convolution/headers/Convolution.h"
#include "common/headers/ItpPrinter.h"

void Convolution::Apply() {
    ItpPrinter().Print("Before: ", *_itp);

    auto *processedData = _tool->Process(_itp->_w, _itp->_h,
                                         ProjectHelper::GetCanalsCount(_itp->_type), _itp->_data,
                                         _kernel->_w, _kernel->_h, _kernel->_data);
    delete _itp->_data;
    _itp->_data = processedData;
    ItpPrinter().Print("After: ", *_itp);
}
