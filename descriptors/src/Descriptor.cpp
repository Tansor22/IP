//
// Created by Sergei on 22.06.2020.
//

#include "descriptors/headers/Descriptor.h"
#include "cmath"

void Descriptor::Normalize() {
    for (int k = 0; k < 2; k++) {
        double length = 0;

        for (int i = 0; i < _hists.size(); i++)
            for (int j = 0; j < _hists[i].size(); j++)
                length += _hists[i][j] * _hists[i][j];

        length = sqrt(length);

        for (int i = 0; i < _hists.size(); i++)
            for (int j = 0; j < _hists[i].size(); j++) {
                _hists[i][j] /= length;

                if (_hists[i][j] > 0.2 && k == 0)
                    _hists[i][j] = 0.2;
            }
    }
}
