//
// Created by Sergei on 19.06.2020.
//

#include "../headers/ImagesHandler.h"
#include "convolution/headers/KernelsHandler.h"
#include "../headers/ImageToProcess.h"
#include "../headers/ItpPrinter.h"

QRgb *ImageToProcess::ToIntRGB() {
    QRgb *output = new QRgb[_size];
    for (int i = 0; i < _size; i++)
        output[i] =
                ProjectHelper::IsGray(_type)
                ? qRgb(ProjectHelper::NormalizeReverse(_data[i]),
                       ProjectHelper::NormalizeReverse(_data[i]),
                       ProjectHelper::NormalizeReverse(_data[i]))
                : qRgba(
                        ProjectHelper::NormalizeReverse(_data[i]), // RED
                        ProjectHelper::NormalizeReverse(_data[i + _size]), // GREEN
                        ProjectHelper::NormalizeReverse(_data[i + _size * 2]), // BLUE
                        ProjectHelper::IsNoAlpha(_type)
                        ? 255 : ProjectHelper::NormalizeReverse(_data[i + _size * 3])); // ALPHA
    return output;
}

QImage ImageToProcess::ToQImage() {
    QRgb *rgb = ToIntRGB();
    QImage image = QImage(_w, _h, QImage::Format_RGB32);
    for (int y = 0; y < _h; y++)
        for (int x = 0; x < _w; x++)
            image.setPixelColor(x, y, rgb[y * _w + x]);
    // SF
    delete rgb;
    return image;
}

void ImageToProcess::Save(string fileName, const string &format) {
    if (fileName.empty()) {
        fileName = "IMAGE_";
        fileName += _name;
    }
    fileName += ".";
    fileName += format;

    ToQImage().save(ImagesHandler::Instance()->GetImagesPath()
                    + "/output/" + QString::fromStdString(fileName), format.c_str());
}

void ImageToProcess::Save(ImageId imageId, const string &format) {
    Save(ImagesHandler::Instance()->GetImageNameById(imageId), format);
}
