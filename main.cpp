#include <QApplication>
#include <QDebug>
#include "common/headers/ProjectHelper.h"
#include "common/headers/ItpPrinter.h"
#include <common/headers/DataRetriever.h>
#include <QtWidgets/QFileDialog>
#include "common/headers/ImagesHandler.h"
#include "common/headers/ImageToProcess.fwd.h"
#include "convolution/headers/ConvolutionBuilder.h"
#include "convolution/headers/SequentialConvolutionTool.h"
#include "convolution/headers/KernelsHandler.h"
#include "convolution/headers/MirrorPolicy.h"
#include <math.h>


int main(int argc, char *argv[]) {
    // init Qt context
    QApplication a(argc, argv);

    // initialize required objects
    DataRetriever dr;
    ImagesHandler *imagesHandler = ImagesHandler::Instance();
    imagesHandler->SetImagesPath(R"(C:\Users\Sergei\Documents\CLionProjects\IP\images)");

    ImageId imageId = GIRL_N_BICYCLE;
    QPixmap pixmap = imagesHandler->GetImageByImageId(imageId);
    //QPixmap pixmap = imagesHandler->GetImageViaFileDialog();

    int w = pixmap.width();
    int h = pixmap.height();
    QRgb *rgb = dr.RetrieveData(pixmap);

    // main logic
    Canal type = GRAY;
    dr = DataRetriever(type, ProjectHelper::NormalizeStraight);
    double *data = dr.RetrieveData(rgb, w, h);
    ImageToProcess itp = ImageToProcess(type, data, w, h, imagesHandler->GetImageNameById(imageId));
    ImageToProcess dx, dy;
    dx = dy = itp;
    itp.Save();
    auto *convolutionBuilder = new ConvolutionBuilder();

    convolutionBuilder
            ->WithImage(&dx)
            ->WithTool(new SequentialConvolutionTool)
            ->WithKernel(KernelsHandler::GetSobelX())
            ->WithOutOfBoundPolicy(new MirrorPolicy)
                    //->WithOperation("GAUSS_SIGMA_2,4")
                    //->WithNormalization(ProjectHelper::NormalizeMinMax)
                    //->NoClip()
            ->Apply();

    convolutionBuilder
            ->WithImage(&dy)
            ->WithKernel(KernelsHandler::GetSobelY())
            ->Apply();

    ImageToProcess gradientDirection = itp;
    for (int i = 0; i < w * h; ++i)
        gradientDirection[i] = atan2(dy[i], dx[i]) * 180 / M_PI + 180;

    gradientDirection.Save("GRADIENT_DIRECTION");

    delete convolutionBuilder;
    return 0;
}

