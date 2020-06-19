//
// Created by Sergei on 18.06.2020.
//

#ifndef IP_IMAGESHANDLER_H
#define IP_IMAGESHANDLER_H


#include <QtCore/QString>
#include <QtGui/QPixmap>
#include <QtGui/QImage>
#include "ProjectConstants.h"

class ImagesHandler {
public:
    static ImagesHandler *Instance();

    QPixmap GetImageViaFileName(const QString &fn);

    QPixmap GetImageByImageId(const ImageId id);


    QPixmap GetImageViaFileDialog();

    void SetImagesPath(const char *imagesPath);

    QString GetImagesPath();

    std::string GetImageNameById(const ImageId id);

private:
    QString _imagesPath;
    static ImagesHandler *_instance;
};


#endif //IP_IMAGESHANDLER_H
