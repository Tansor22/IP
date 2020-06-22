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
                                     kernel->_w, kernel->_h, kernel->_data);
    auto *processedG = tool->Process(_w, _h, _g,
                                     kernel->_w, kernel->_h, kernel->_data);
    auto *processedB = tool->Process(_w, _h, _b,
                                     kernel->_w, kernel->_h, kernel->_data);

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
        _policy->SetValue(_r, _w, _h, poi.x, poi.y, ProjectHelper::NormalizeStraight(qRed(color)));
        _policy->SetValue(_g, _w, _h, poi.x, poi.y, ProjectHelper::NormalizeStraight(qGreen(color)));
        _policy->SetValue(_b, _w, _h, poi.x, poi.y, ProjectHelper::NormalizeStraight(qBlue(color)));

        for (int i = 1; i <= crossSize; i++) {

            _policy->SetValue(_r, _w, _h, poi.x - i, poi.y, ProjectHelper::NormalizeStraight((qRed(color))));
            _policy->SetValue(_g, _w, _h, poi.x - i, poi.y, ProjectHelper::NormalizeStraight((qGreen(color))));
            _policy->SetValue(_b, _w, _h, poi.x - i, poi.y, ProjectHelper::NormalizeStraight(qBlue(color)));


            _policy->SetValue(_r, _w, _h, poi.x + i, poi.y, ProjectHelper::NormalizeStraight(qRed(color)));
            _policy->SetValue(_g, _w, _h, poi.x + i, poi.y, ProjectHelper::NormalizeStraight(qGreen(color)));
            _policy->SetValue(_b, _w, _h, poi.x + i, poi.y, ProjectHelper::NormalizeStraight(qBlue(color)));

            _policy->SetValue(_r, _w, _h, poi.x, poi.y - i, ProjectHelper::NormalizeStraight(qRed(color)));
            _policy->SetValue(_g, _w, _h, poi.x, poi.y - i, ProjectHelper::NormalizeStraight(qGreen(color)));
            _policy->SetValue(_b, _w, _h, poi.x, poi.y - i, ProjectHelper::NormalizeStraight(qBlue(color)));

            _policy->SetValue(_r, _w, _h, poi.x, poi.y + i,ProjectHelper::NormalizeStraight( qRed(color)));
            _policy->SetValue(_g, _w, _h, poi.x, poi.y + i, ProjectHelper::NormalizeStraight(qGreen(color)));
            _policy->SetValue(_b, _w, _h, poi.x, poi.y + i, ProjectHelper::NormalizeStraight(qBlue(color)));
        }
    }
}

RgbImage::RgbImage(ImageToProcess *other) : ImageToProcess(*other) {
    if (other->GetColorPrefix().rfind("RGB", 0) == 0) {
        // rgb
        _r = new double[_size],
        _g = new double[_size],
        _b = new double[_size];

        auto *otherRgb = dynamic_cast<RgbImage *>(other);
        std::copy(otherRgb->_r, otherRgb->_r + otherRgb->_size, _r);
        std::copy(otherRgb->_g, otherRgb->_g + otherRgb->_size, _g);
        std::copy(otherRgb->_b, otherRgb->_b + otherRgb->_size, _b);

    } else {
        qDebug() << "Couldn't convert GrayImage to RgbImage!" << endl;
        exit(EXIT_FAILURE);
    }
}

void RgbImage::DownSample() {
    int w = _w;
    int h = _h;
    _w  /= 2;
    _h /= 2;
    _size = _w * _h;

    double *rOld = _r;
    double *gOld = _g;
    double *bOld = _b;

    _r = new double [_size];
    _g = new double [_size];
    _b = new double [_size];

    for (int j = 0; j < _h; j++)
        for (int i = 0; i < _w; i++){
            _r[j * _w + i] = rOld[j * 2 * w + i * 2];
            _g[j * _w + i] = gOld[j * 2 * w + i * 2];
            _b[j * _w + i] = bOld[j * 2 * w + i * 2];
        }

    delete [] rOld;
    delete [] gOld;
    delete [] bOld;

}
