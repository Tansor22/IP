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

    explicit RgbImage(ImageToProcess *other);

private:
    double *_r;
    double *_g;
    double *_b;
};


#endif //IP_RGBIMAGE_H
