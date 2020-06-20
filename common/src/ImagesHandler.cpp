//
// Created by Sergei on 18.06.2020.
//

#include "../headers/ImagesHandler.h"
#include <QDebug>
#include <QtWidgets/QFileDialog>

ImagesHandler *ImagesHandler::_instance = nullptr;

ImagesHandler *ImagesHandler::Instance() {
    if (_instance == nullptr) {
        _instance = new ImagesHandler;
    }
    return _instance;
}

QPixmap ImagesHandler::GetImageViaFileName(const QString &fn) {
    QPixmap pixmap;
    pixmap.load(fn);
    return pixmap;
}

QPixmap ImagesHandler::GetImageViaFileDialog() {
    QPixmap pixmap;
    QString fileName = QFileDialog::getOpenFileName(nullptr,
                                                    "Open Image", _imagesPath, "Image Files (*.png *.jpg *.bmp)");
    pixmap.load(fileName);
    return pixmap;
}

void ImagesHandler::SetImagesPath(const char *imagesPath) {
    _imagesPath = QString::fromUtf8(imagesPath);
}

QString ImagesHandler::GetImagesPath() {
    return QString(_imagesPath);
}

QPixmap ImagesHandler::GetImageByImageId(ImageId id) {
    switch (id) {
        case HOCKEY:
            return GetImageViaFileName(_imagesPath + "/input/hockey.jpg");
        case BUTTERFLY:
            return GetImageViaFileName(_imagesPath + "/input/butterfly.jpg");
        case SAMPLE_COLOR:
            return GetImageViaFileName(_imagesPath + "/input/sample_color.jpg");
        case SAMPLE_WHITE:
            return GetImageViaFileName(_imagesPath + "/input/sample_white.jpg");
        case SAMPLE_BLACK:
            return GetImageViaFileName(_imagesPath + "/input/sample_black.jpg");
        case LENA:
            return GetImageViaFileName(_imagesPath + "/input/lena.jpg");
        case LENA_ZOOMED:
            return GetImageViaFileName(_imagesPath + "/input/lena_zoomed.jpg");
        case GIRL_N_BICYCLE:
            return GetImageViaFileName(_imagesPath + "/input/girl_n_bicycle.jpg");
        default:
            qDebug() << "Unknown ImageId: " << id << '\n';
            exit(EXIT_FAILURE);
    }
}

std::string ImagesHandler::GetImageNameById(ImageId id) {
    switch (id) {
        case HOCKEY:
            return "HOCKEY";
        case BUTTERFLY:
            return "BUTTERFLY";
        case SAMPLE_COLOR:
            return "SAMPLE_COLOR";
        case SAMPLE_WHITE:
            return "SAMPLE_WHITE";
        case SAMPLE_BLACK:
            return "SAMPLE_BLACK";
        case LENA:
            return "LENA";
        case LENA_ZOOMED:
            return "LENA_ZOOMED";
        case GIRL_N_BICYCLE:
            return "GIRL_N_BICYCLE";
        default:
            qDebug() << "Unknown ImageId: " << id << '\n';
            return "UNKNOWN";
    }
}
