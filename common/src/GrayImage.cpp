//
// Created by Sergei on 21.06.2020.
//

#include <common/headers/RgbImage.h>
#include "common/headers/GrayImage.h"

QRgb *GrayImage::ToIntRGB() {
    QRgb *output = new QRgb[_size];
    for (int i = 0; i < _size; i++)
        output[i] = qRgb(ProjectHelper::NormalizeReverse(_data[i]),
                         ProjectHelper::NormalizeReverse(_data[i]),
                         ProjectHelper::NormalizeReverse(_data[i]));
    return output;
}

GrayImage *GrayImage::From(ImageToProcess *&other) {
    auto *output = new GrayImage;
    output->_w = other->_w;
    output->_h = other->_h;
    output->_size = other->_size;
    output->_policy = other->_policy;
    output->_name = other->_name;
    output->_data = new double[other->_size];
    if (other->GetColorPrefix().rfind("RGB", 0) == 0) {
        auto *otherRgb = dynamic_cast<RgbImage *>(other);
        output->_data =
                ProjectHelper::toGray(otherRgb->_r, otherRgb->_g, otherRgb->_b, otherRgb->_size);
    } else {
        auto *otherGray = dynamic_cast<GrayImage *>(other);

        std::copy(otherGray->_data, otherGray->_data + otherGray->_size, output->_data);
    }
    return output;
};

void GrayImage::Convolution(ConvolutionTool *tool, Kernel *kernel) {
    auto *processedData = tool->Process(_w, _h, _data,
                                        kernel->_w, kernel->_h, kernel->_data);
    delete _data;
    _data = processedData;
}

double &GrayImage::operator[](int i) {
    return _policy->GetValue(_data, _w, _h, i / _w, i % _w);
}

void GrayImage::Mark(vector<POI> &pois, int crossSize, QRgb color) {
    for (auto &poi : pois) {
        operator[]((poi.x * _w + poi.y)) = ProjectHelper::NormalizeStraight(qGray(color));
        for (int i = 1; i <= crossSize; i++) {
            operator[](((poi.x - i) * _w + poi.y)) = ProjectHelper::NormalizeStraight(qGray(color));
            operator[](((poi.x + i) * _w + poi.y)) = ProjectHelper::NormalizeStraight(qGray(color));
            operator[]((poi.x * _w + poi.y - i)) = ProjectHelper::NormalizeStraight(qGray(color));
            operator[]((poi.x * _w + poi.y + i)) = ProjectHelper::NormalizeStraight(qGray(color));
        }
    }
}

GrayImage *GrayImage::Join(GrayImage *one, GrayImage *other) {
    auto *output
            = new GrayImage(one->_w + other->_w, max(one->_h, other->_h), "JOINED_" + one->_name + "_" + other->_name);

    for (int i = 0; i < one->_h; ++i)
        for (int j = 0; j < one->_w; ++j)
            (*output)[i * output->_w + j] = (*one)[i * one->_w + j];

    for (int i = 0; i < other->_h; ++i)
        for (int j = 0; j < other->_w; ++j)
            // first x calculating, then shifting
            (*output)[i * output->_w + j + one->_w] = (*other)[i * other->_w + j];
    return output;
}