//
// Created by Sergei on 23.06.2020.
//

#include "demos/headers/Lab4.h"
#include <common/headers/RgbImage.h>
#include <common/headers/ImagesHandler.h>
#include <pois/headers/POIsFinder.h>
#include <pois/headers/Harris.h>
#include <descriptors/headers/DescritorBuilder.h>
#include "distortions/headers/Distortion.h"
#include "distortions/headers/Shift.h"
#include "distortions/headers/Contrast.h"
#include <QDebug>
#include <QPainter>

void Lab4::Go() {
    auto *itp = new GrayImage(_pixmap,
                              ImagesHandler::Instance()->GetImageNameById(_imageId));

    //POIsFinder *poisFinder = new Harris(GrayImage::From(reinterpret_cast<ImageToProcess *&>(itp)));
    POIsFinder *poisFinder = new Harris(itp);
    vector<POI> pois = poisFinder->FindPOIs(_windowSize, _pointsCount);

    DescritorBuilder descritorBuilder1(GrayImage::From(reinterpret_cast<ImageToProcess *&>(itp)), pois);

    vector<Descriptor> imageDescriptor1 = descritorBuilder1.Build();

//    for (auto& descriptor : imageDescriptor) {
//        descriptor.Print();
//    }
    // Distortion *distortion = new Shift(40, 0);
    // factor 0.1 .. 2.00
    //Distortion *distortion = new Contrast(0.6);

    auto *distorted = new GrayImage(_distortion->Distort(_distorted),
                                    ImagesHandler::Instance()->GetImageNameById(_distortedId));

    poisFinder = new Harris(distorted);

    vector<POI> poisDistorted = poisFinder->FindPOIs(_windowSize, _pointsCount);

    DescritorBuilder descritorBuilderDistorted(GrayImage::From(reinterpret_cast<ImageToProcess *&>(distorted)),
                                               poisDistorted);

    vector<Descriptor> imageDescriptorDistorted = descritorBuilderDistorted.Build();

//    for (auto& descriptor : imageDescriptorDistorted) {
//        descriptor.Print();
//    }


    QImage joined = descritorBuilder1.Join(distorted, imageDescriptorDistorted);

    joined.save(ImagesHandler::Instance()->GetImagesPath() + "/output/"
                +
                QString::fromStdString(itp->GetName() + "_JOIN_" + distorted->GetName() + "_" + _distortion->GetName()) +
                ".JPG", "JPG");

}
