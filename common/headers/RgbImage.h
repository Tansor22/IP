//
// Created by Sergei on 21.06.2020.
//

#ifndef IP_RGBIMAGE_H
#define IP_RGBIMAGE_H

// forward declaration
#include <utility>

#include "convolution/headers/OutOfBoundPolicy.h"
#include "convolution/headers/MirrorPolicy.h"
#include "convolution/headers/Kernel.h"
#include "ImageToProcess.h"
#include "DataRetriever.h"

class RgbImage : public ImageToProcess {
    friend class GrayImage;

public:
    QRgb *ToIntRGB() override;

    void Convolution(ConvolutionTool *tool, Kernel *kernel) override;

    void NormalizeMinMax() override;

    void Mark(vector<POI> &pois, int crossSize, QRgb color) override;

    double &operator[](int i) override;

    string GetColorPrefix() override { return "RGB_"; };

    explicit RgbImage(ImageToProcess *other);

    RgbImage()
            : ImageToProcess(), _r(new double), _g(new double), _b(new double) {};

    RgbImage(int w, int h, const string &name = "Unnamed", OutOfBoundPolicy *policy = new MirrorPolicy)
            : ImageToProcess(w, h, name, policy), _r(new double), _g(new double), _b(new double) {};

    explicit RgbImage(const QPixmap &pixmap, const string &name = "Unnamed",
                      OutOfBoundPolicy *policy = new MirrorPolicy)
            : ImageToProcess(pixmap, name, policy) {
        // data binding
        DataRetriever dr;
        // maybe save?
        QRgb *rgb = dr.RetrieveData(pixmap);


        dr = DataRetriever(R | G | B, ProjectHelper::NormalizeStraight);

        double *data = dr.RetrieveData(rgb, _w, _h);

        _r = new double[_size],
        _g = new double[_size],
        _b = new double[_size];

        std::copy(data, data + _size, _r);
        std::copy(data + _size, data + _size * 2, _g);
        std::copy(data + _size * 2, data + _size * 3, _b);

        delete[] data;

        ReportOperation("Creating", this);
    };


    // assignment operator
    RgbImage &operator=(ImageToProcess *other) {
//        _name = "ASSIGNED_" + string(other._name);
        _w = (*other)._w;
        _h = (*other)._h;
        _size = (*other)._size;
        _policy = (*other)._policy;
        _name = (*other)._name;
        _r = new double[_size];
        _g = new double[_size];
        _b = new double[_size];
        if ((*other).GetColorPrefix().rfind("RGB", 0) == 0) {
            auto *otherRgb = dynamic_cast<RgbImage *>(other);
            std::copy(otherRgb->_r, otherRgb->_r + otherRgb->_size, _r);
            std::copy(otherRgb->_g, otherRgb->_g + otherRgb->_size, _g);
            std::copy(otherRgb->_b, otherRgb->_b + otherRgb->_size, _b);
            // delete ??
        } else {
            qDebug() << "Couldn't convert GrayImage to RgbImage!" << endl;
            exit(EXIT_FAILURE);
        }
        return *this;
    };

private:
    double *_r;
    double *_g;
    double *_b;
};


#endif //IP_RGBIMAGE_H
