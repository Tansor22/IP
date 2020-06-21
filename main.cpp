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
#include "convolution/headers/MirrorPolicy.h"
#include <cmath>


int main(int argc, char *argv[]) {
    // init Qt context
    QApplication a(argc, argv);

    // initialize required objects
    ImagesHandler *imagesHandler = ImagesHandler::Instance();
    imagesHandler->SetImagesPath(R"(C:\Users\Sergei\Documents\CLionProjects\IP\images)");

    ImageId imageId = LENA_ZOOMED;
    QPixmap pixmap = imagesHandler->GetImageByImageId(imageId);
    //QPixmap pixmap = imagesHandler->GetImageViaFileDialog();


    ImageToProcess *itp = new RgbImage(pixmap, imagesHandler->GetImageNameById(imageId));

    auto *convolutionBuilder = new ConvolutionBuilder();

    POIsFinder *poisFinder = new Harris(GrayImage::From(itp));
    vector<POI> pois = poisFinder->FindPOIs(1, 1000);

    ImageToProcess *marked = new RgbImage(itp);

    //marked->Save("BEFORE_MARKED");

    marked->Mark(pois, 1);

    marked->Save("HARRIS_MARKED_1_1000");

    DescritorBuilder descritorBuilder(GrayImage::From(itp), pois);

    descritorBuilder.Build();

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

