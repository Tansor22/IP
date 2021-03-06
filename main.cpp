#include <QApplication>
#include <QDebug>
#include "common/headers/ProjectHelper.h"
#include "common/headers/ItpPrinter.h"
#include <common/headers/DataRetriever.h>
#include <QtWidgets/QFileDialog>
#include "common/headers/ImagesHandler.h"
#include "pois/headers/POIsFinder.h"
#include "pois/headers/Moravec.h"
#include "pois/headers/Harris.h"
#include "common/headers/ImageToProcess.fwd.h"
#include "common/headers/RgbImage.h"
#include "convolution/headers/ConvolutionBuilder.h"
#include "convolution/headers/BorderPolicy.h"
#include "descriptors/headers/DescritorBuilder.h"
#include "convolution/headers/SequentialConvolutionTool.h"
#include "convolution/headers/KernelsHandler.h"
#include "convolution/headers/FavOperations.h"
#include "convolution/headers/MirrorPolicy.h"
#include <cmath>
#include <demos/headers/Lab.h>
#include <demos/headers/Lab1.h>
#include <distortions/headers/Distortion.h>
#include <distortions/headers/Contrast.h>
#include <distortions/headers/Shift.h>
#include <distortions/headers/Scale.h>
#include <demos/headers/Lab2.h>
#include <demos/headers/Lab3.h>
#include <demos/headers/Lab4.h>
#include <demos/headers/Lab5.h>
#include <distortions/headers/Rotate.h>


int main(int argc, char *argv[]) {
    // init Qt context
    QApplication a(argc, argv);
    // env settings
    ImagesHandler *imagesHandler = ImagesHandler::Instance();
    imagesHandler->SetImagesPath(R"(C:\Users\Sergei\Documents\CLionProjects\IP\images)");
    // experiment settings
    ImageId imageId1 = CAPPED_GIRL;
    ImageId imageId2 = BUTTERFLY;
    ImageId imageId3 = GIRL_N_BICYCLE;
    ImageId imageId4 = LENA_ZOOMED;
    ImageId images[] = {imageId1, imageId2, imageId3, imageId4};
    int degrees[] = {45, 90, 180, 35};
    // QPixmap pixmap = imagesHandler->GetImageByImageId(imageId);

    ImageId distortedImageId = CAT_DOG;
    QPixmap distortedPixmap = imagesHandler->GetImageByImageId(distortedImageId);
    // g.Save("fdf");
    // lab
    for (int i = 0; i < 4; ++i) {
        QPixmap pixmap = imagesHandler->GetImageByImageId(images[i]);
        Lab *lab = new Lab2(pixmap, images[i], 5, 2, 0, 1, 7.13);
        //Lab *lab = new Lab1(pixmap, imageId);


        //Lab *lab = new Lab3(pixmap, imageId);
        //Lab *lab = new Lab4(pixmap, distortedPixmap, imageId, distortedImageId, new Shift(-30, 0), 3, 100, 8, 16, 4);
        //Lab *lab = new Lab5(pixmap, distortedPixmap, imageId, distortedImageId, new Rotate(27), 3, 200, 8, 16, 4);
        lab->Go();
    }
    // DISTORTIONS TEST
//    for (int i = 0; i < 4; ++i) {
//        for (int j = 0; j < 4; ++j) {
//            Distortion *c = new Rotate(degrees[j]);
//            c->Distort(imagesHandler->GetImageByImageId(images[i])).toImage().save(
//                    ImagesHandler::Instance()->GetImagesPath() + "/output/"
//                    +
//                    "GRAY_" + QString::fromStdString(imagesHandler->GetImageNameById(images[i]))
//                    + "_"
//                    + QString::fromStdString(c->GetName()) +
//                    ".JPG", "JPG");
//        }
//    }


    // initialize required objects
//
//
//    ImageId imageId = LENA_ZOOMED;
//    QPixmap pixmap = imagesHandler->GetImageByImageId(imageId);
//    //QPixmap pixmap = imagesHandler->GetImageViaFileDialog();
//
//
//    ImageToProcess *itp = new RgbImage(pixmap, imagesHandler->GetImageNameById(imageId));
//
//    auto *convolutionBuilder = new ConvolutionBuilder();
//
//    POIsFinder *poisFinder = new Harris(GrayImage::From(itp));
//    vector<POI> pois = poisFinder->FindPOIs(1, 1000);
//
//    ImageToProcess *marked = new RgbImage(itp);
//
//    //marked->Save("BEFORE_MARKED");
//
//    marked->Mark(pois, 1);
//
//    marked->Save("HARRIS_MARKED_1_1000");
//
//    DescritorBuilder descritorBuilder(GrayImage::From(itp), pois);
//
//    descritorBuilder.Build();

//
//    GrayImage dx, dy;
//    dx = dy = *GrayImage::From(itp);
//
//    convolutionBuilder
//            ->WithImage(&dx)
//            ->WithTool(new SequentialConvolutionTool)
//            ->WithKernel(KernelsHandler::GetSobelX())
//            ->WithOutOfBoundPolicy(new MirrorPolicy)
//                    ->WithOperation("DXXXXX")
//                    ->Normalize()
//                    ->Save()
//                    ->NoClip()
//            ->Apply();
//
//    convolutionBuilder
//            ->WithImage(&dy)
//            ->WithOperation("DYYYYY")
//            ->WithKernel(KernelsHandler::GetSobelY())
//            ->Apply();
//
//    GrayImage sobel = *GrayImage::From(itp);
//
//    sobel.Save("SOBEL_AFTER");
//
//    for (int i = 0; i < pixmap.width() * pixmap.height(); ++i)
//        sobel[i] =  sqrt(dx[i] * dx[i] + dy[i] * dy[i]);
//
//    sobel.Save("SOBEL");
//
//    delete convolutionBuilder;
    return 0;
}

