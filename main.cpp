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
#include "convolution/headers/SequentialConvolutionTool.h"
#include "convolution/headers/KernelsHandler.h"
#include "convolution/headers/MirrorPolicy.h"
#include <cmath>


int main(int argc, char *argv[]) {
    // init Qt context
    QApplication a(argc, argv);

    // initialize required objects
    DataRetriever dr;
    ImagesHandler *imagesHandler = ImagesHandler::Instance();
    imagesHandler->SetImagesPath(R"(C:\Users\Sergei\Documents\CLionProjects\IP\images)");

    ImageId imageId = LENA_ZOOMED;
    QPixmap pixmap = imagesHandler->GetImageByImageId(imageId);
    //QPixmap pixmap = imagesHandler->GetImageViaFileDialog();


    ImageToProcess *itp = new RgbImage(pixmap, imagesHandler->GetImageNameById(imageId));

    POIsFinder *poisFinder = new Moravec(GrayImage::From(itp));
    vector<POI> pois = poisFinder->FindPOIs(1, 1000);
    auto *convolutionBuilder = new ConvolutionBuilder();

    itp->Save("BEFORE_MARKED");

    itp->Mark(pois, 1);

    itp->Save("MORAVEC_MARKED_1_1000");
//    ImageToProcess dx, dy;
//    dx = dy = itp;
//
//    convolutionBuilder
//            ->WithImage(&dx)
//            ->WithTool(new SequentialConvolutionTool)
//            ->WithKernel(KernelsHandler::GetSobelX())
//            ->WithOutOfBoundPolicy(new MirrorPolicy)
//                    ->WithOperation("GAUSS_SIGMA_2,4")
//                    ->WithNormalization(ProjectHelper::NormalizeMinMax)
//                    ->NoClip()
//            ->Apply();
//    dx.Save();
//
//    convolutionBuilder
//            ->WithImage(&dy)
//            ->WithKernel(KernelsHandler::GetSobelY())
//            ->Apply();
//
//    ImageToProcess gradientDirection = itp;
//    for (int i = 0; i < w * h; ++i)
//        gradientDirection[i] = atan2(dy[i], dx[i]) * 180 / M_PI + 180;
//
//    gradientDirection.Save("GRADIENT_DIRECTION");

    delete convolutionBuilder;
    return 0;
}

