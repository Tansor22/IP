//
// Created by Sergei on 21.06.2020.
//

#include "common/headers/RgbImage.h"

QRgb *RgbImage::ToIntRGB() {
    QRgb *output = new QRgb[_size];
    for (int i = 0; i < _size; i++)
        output[i] = qRgb(ProjectHelper::NormalizeReverse(_r[i]),
                         ProjectHelper::NormalizeReverse(_g[i]),
                         ProjectHelper::NormalizeReverse(_b[i]));
    return output;
}

void RgbImage::Convolution(ConvolutionTool *tool, Kernel *kernel) {
    auto *processedR = tool->Process(_w, _h, _r,
                                     kernel->_w, kernel->_h, kernel->_data, 0);
    auto *processedG = tool->Process(_w, _h, _g,
                                     kernel->_w, kernel->_h, kernel->_data, 0);
    auto *processedB = tool->Process(_w, _h, _b,
                                     kernel->_w, kernel->_h, kernel->_data, 0);

    delete _r;
    delete _g;
    delete _b;
    _r = processedR;
    _g = processedG;
    _b = processedB;
}

void RgbImage::NormalizeMinMax() {
    ProjectHelper::NormalizeMinMax(_r, _size);
    ProjectHelper::NormalizeMinMax(_g, _size);
    ProjectHelper::NormalizeMinMax(_b, _size);
}

double &RgbImage::operator[](int i) {
    qDebug() << "Warn: RGB pixel getting!" << endl;
    exit(EXIT_FAILURE);
}

void RgbImage::Mark(vector<POI> &pois, int crossSize, QRgb color) {
    for (auto &poi : pois) {
        _policy->SetValue(_r, _w, _h, poi.x, poi.y, qRed(color));
        _policy->SetValue(_g, _w, _h, poi.x, poi.y, qGreen(color));
        _policy->SetValue(_b, _w, _h, poi.x, poi.y, qBlue(color));

        for (int i = 1; i <= crossSize; i++) {

            _policy->SetValue(_r, _w, _h, poi.x - i, poi.y, qRed(color));
            _policy->SetValue(_g, _w, _h, poi.x - i, poi.y, qGreen(color));
            _policy->SetValue(_b, _w, _h, poi.x - i, poi.y, qBlue(color));


            _policy->SetValue(_r, _w, _h, poi.x + i, poi.y, qRed(color));
            _policy->SetValue(_g, _w, _h, poi.x + i, poi.y, qGreen(color));
            _policy->SetValue(_b, _w, _h, poi.x + i, poi.y, qBlue(color));

            _policy->SetValue(_r, _w, _h, poi.x, poi.y - i, qRed(color));
            _policy->SetValue(_g, _w, _h, poi.x, poi.y - i, qGreen(color));
            _policy->SetValue(_b, _w, _h, poi.x, poi.y - i, qBlue(color));

            _policy->SetValue(_r, _w, _h, poi.x, poi.y + i, qRed(color));
            _policy->SetValue(_g, _w, _h, poi.x, poi.y + i, qGreen(color));
            _policy->SetValue(_b, _w, _h, poi.x, poi.y + i, qBlue(color));
        }
    }
}
