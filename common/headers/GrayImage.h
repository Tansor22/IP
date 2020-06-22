//
// Created by Sergei on 21.06.2020.
//

#ifndef IP_GRAYIMAGE_H
#define IP_GRAYIMAGE_H

#include <convolution/headers/Kernel.h>
#include "convolution/headers/OutOfBoundPolicy.h"
#include "convolution/headers/MirrorPolicy.h"
#include "ImageToProcess.h"
#include "DataRetriever.h"

class GrayImage : public ImageToProcess {

    friend class ItpPrinter;

    friend class Convolution;

    friend class ConvolutionBuilder;

    friend class POIsFinder;

    friend class Moravec;

    friend class DescritorBuilder;

public:
    QRgb *ToIntRGB() override;

    void Convolution(ConvolutionTool *tool, Kernel *kernel) override;

    void NormalizeMinMax() override { ProjectHelper::NormalizeMinMax(_data, _size); };

    string GetColorPrefix() override { return "GRAY_"; };

    double &operator[](int i) override;

    void Mark(vector<POI> &pois, int crossSize, QRgb color) override;

    static GrayImage *From(ImageToProcess *&other);

    // assignment operator
    GrayImage &operator=(const GrayImage &other) {
//        _name = "ASSIGNED_" + string(other._name);
        _name = "_" + string(other._name);
        _w = other._w;
        _h = other._h;
        _size = other._size;
        _policy = other._policy;

        auto newData = new double[_size];
        std::copy(other._data, other._data + other._size, newData);
        delete _data;
        _data = newData;
        ReportOperation("ASSIGNING", this);
        return *this;
    };

    GrayImage()
            : ImageToProcess(), _data(new double) { };

    GrayImage(int w, int h, const string &name = "Unnamed", OutOfBoundPolicy *policy = new MirrorPolicy)
            : ImageToProcess(w, h, name, policy), _data(new double[_size]) {};

    explicit GrayImage(GrayImage *&other)
            : ImageToProcess(other->_w, other->_h, "COPY_" + other->_name, other->_policy) {
        _size = _w * _h;
        _data = new double[_size];
        std::copy(other->_data, other->_data + other->_size, _data);
    };

    explicit GrayImage(const QPixmap &pixmap, const string &name = "Unnamed",
                       OutOfBoundPolicy *policy = new MirrorPolicy)
            : ImageToProcess(pixmap, name, policy) {
        // data binding
        DataRetriever dr;
        // maybe save?
        QRgb *rgb = dr.RetrieveData(pixmap);
        dr = DataRetriever(GRAY, ProjectHelper::NormalizeStraight);

        _data = dr.RetrieveData(rgb, _w, _h);
    }


private:
    double *_data;
};


#endif //IP_GRAYIMAGE_H
