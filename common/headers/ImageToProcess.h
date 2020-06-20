//
// Created by Sergei on 19.06.2020.
//

#ifndef IP_IMAGETOPROCESS_H
#define IP_IMAGETOPROCESS_H

#include "iostream"
#include <algorithm>
#include <QPixmap>
#include <QDebug>
#include "ProjectConstants.h"
#include "ProjectHelper.h"

// forward declaration
#include "ItpPrinter.fwd.h"
#include "ImageToProcess.fwd.h"

using namespace std;

class ImageToProcess {
    // friends
    friend class ItpPrinter;
    friend class Convolution;

public:
    ImageToProcess()
            : _name("Unnamed"), _type(0), _w(0), _h(0), _size(0), _data(new double) {
        ReportOperation("Creating", this);
    };

    // copy construct
    ImageToProcess(const ImageToProcess& other);
    // assignment operator
    ImageToProcess &operator=(const ImageToProcess& other);

    double &operator[](int i) {
        return _data[i];
    };

    ~ImageToProcess() {
        ReportOperation("Disposing", this);
        delete _data;
    }

    ImageToProcess(Canal type, double *data, int w, int h, string name = "Unnamed")
            : _name(name), _type(type), _w(w), _h(h), _size(w * h), _canalsCount(ProjectHelper::GetCanalsCount(_type)),
            _data(new double[_size * _canalsCount]) {
        ReportOperation("Creating", this);
        // ???
        std::copy(data, data + _size * _canalsCount, _data);
    };

    // savers
    void Save(string fileName = string(), const string &format = "JPG");

    void Save(ImageId imageId, const string &format = "JPG");

    // mappers
    QRgb *ToIntRGB();

    QImage ToQImage();


private:
    static void ReportOperation(QString operation, ImageToProcess *itp) {
        qDebug() << operation  << QString::fromStdString(itp->_name) << '\n';
    };
    Canal _type;
    int _canalsCount, _w, _h, _size;
    string _name;
    double *_data;
};


#endif //IP_IMAGETOPROCESS_H
