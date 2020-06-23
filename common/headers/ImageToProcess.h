//
// Created by Sergei on 19.06.2020.
//

#ifndef IP_IMAGETOPROCESS_H
#define IP_IMAGETOPROCESS_H

#include "iostream"
#include <algorithm>
#include <QPixmap>
#include <QDebug>
#include <pois/headers/POI.h>
#include "ProjectConstants.h"
#include "ProjectHelper.h"

// forward declaration
#include "ItpPrinter.fwd.h"
#include "convolution/headers/OutOfBoundPolicy.h"
#include "convolution/headers/ConvolutionTool.h"
#include "convolution/headers/MirrorPolicy.h"
#include "ImageToProcess.fwd.h"
#include "convolution/headers/Kernel.h"
#include "GrayImage.fwd.h"

using namespace std;

class ImageToProcess {
    // friends
    friend class ItpPrinter;

    friend class GrayImage;

    friend class RgbImage;

    friend class Convolution;

    friend class ConvolutionBuilder;

    friend class POIsFinder;

    friend class Moravec;

    friend class Harris;

    friend class DescriptorBuilder;

    friend class FavOperations;

    friend class DescritorBuilder;


public:
    ImageToProcess()
            : _name("Unnamed"), _w(0), _h(0), _size(0), _policy(new MirrorPolicy) {
    };

    ImageToProcess(ImageToProcess const &other)
            : _name(other._name), _w(other._w), _h(other._h), _size(other._size), _policy(other._policy) {
    };

    ImageToProcess(const QPixmap &pixmap, const string &name = "Unnamed", OutOfBoundPolicy *policy = new MirrorPolicy) :
            _name(name), _w(pixmap.width()), _h(pixmap.height()), _size(_w * _h), _policy(policy) {};

    ImageToProcess(int w, int h, const string &name = "Unnamed", OutOfBoundPolicy *policy = new MirrorPolicy) :
            _name(name), _w(w), _h(h), _size(_w * _h), _policy(policy) {};

    virtual string GetColorPrefix() = 0;

    virtual double &operator[](int i) = 0;

    // savers
    void Save(string fileName = string(), const string &format = "JPG");

    void Save(ImageId imageId, const string &format = "JPG");

    QImage Join(ImageToProcess &other);

    // mappers
    virtual QRgb *ToIntRGB() = 0;

    virtual void Convolution(ConvolutionTool *tool, Kernel *kernel) = 0;

    virtual void NormalizeMinMax() = 0;

    virtual void Mark(vector<POI> &pois, int crossSize = 3, QRgb color = qRgb(255, 255, 255)) = 0;

    QImage ToQImage();

    string GetName() { return _name; };


protected:
    static void ReportOperation(QString operation, ImageToProcess *itp) {
        qDebug() << operation << QString::fromStdString(itp->_name) << '\n';
    };
    int _w, _h, _size;
    OutOfBoundPolicy *_policy;
    string _name;
};


#endif //IP_IMAGETOPROCESS_H
