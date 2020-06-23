//
// Created by Sergei on 22.06.2020.
//

#include <common/headers/RgbImage.h>
#include <common/headers/ImagesHandler.h>
#include <pois/headers/POIsFinder.h>
#include <pois/headers/Harris.h>
#include <descriptors/headers/DescritorBuilder.h>
#include "demos/headers/Lab5.h"
#include "distortions/headers/Distortion.h"
#include "distortions/headers/Rotate.h"
#include <QDebug>
#include <QPainter>

void Lab5::Go() {
    GrayImage itp = GrayImage(_pixmap,
                              ImagesHandler::Instance()->GetImageNameById(_imageId));

    //poisFinder = new Harris(GrayImage::From(reinterpret_cast<ImageToProcess *&>(itp)));
    POIsFinder *poisFinder = new Harris(&itp);
    vector<POI> pois = poisFinder->FindPOIs(_windowSize, _pointsCount);

    DescritorBuilder descritorBuilder1(&itp, pois);

    vector<Descriptor> imageDescriptor1 = descritorBuilder1.Build();

//    for (auto& descriptor : imageDescriptor1) {
//        descriptor.Print();
//    }

    _distortion->Distort(_distorted).save(ImagesHandler::Instance()->GetImagesPath() + "/output/TES.JPG", "JPG");
    GrayImage distorted = GrayImage(_distortion->Distort(_distorted),
                                    ImagesHandler::Instance()->GetImageNameById(_distortedId));

    distorted.SetSecondName(_distortion->GetName());
    //distorted->Save();

    poisFinder = new Harris(&distorted);

    vector<POI> poisDistorted = poisFinder->FindPOIs(_windowSize, _pointsCount);

    DescritorBuilder descritorBuilderDistorted(&distorted,
                                               poisDistorted);

    vector<Descriptor> imageDescriptorDistorted = descritorBuilderDistorted.Build();

//    for (auto& descriptor : imageDescriptorDistorted) {
//        descriptor.Print();
//    }


    QImage joined = descritorBuilder1.Join(&distorted, imageDescriptorDistorted);

    joined.save(ImagesHandler::Instance()->GetImagesPath() + "/output/"
                +
                QString::fromStdString(itp.GetName() + "_JOIN_" + distorted.GetName() + "_" + _distortion->GetName()) +
                ".JPG", "JPG");

}
