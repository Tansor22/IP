//
// Created by Sergei on 22.06.2020.
//

#include "descriptors/headers/Descriptor.h"
#include "cmath"

void Descriptor::Normalize() {
    double length = 0;

    for (int i = 0; i < _hists.size(); i++)
        for (int j = 0; j < _hists[i].size(); j++)
            length += _hists[i][j];

    for (int i = 0; i < _hists.size(); i++)
        for (int j = 0; j < _hists[i].size(); j++)
            _hists[i][j] /= length;

}
