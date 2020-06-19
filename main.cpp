#include <QApplication>
#include <QDebug>
#include "common/headers/ProjectHelper.h"
#include "common/headers/ItpPrinter.h"
#include <common/headers/DataRetriever.h>
#include <QtWidgets/QFileDialog>
#include "common/headers/ImagesHandler.h"
#include "common/headers/ImageToProcess.h"
#include "convolution/headers/ConvolutionBuilder.h"
#include "convolution/headers/SequentialConvolutionTool.h"
#include "convolution/headers/KernelsHandler.h"


int main(int argc, char *argv[]) {
    // init Qt context
    QApplication a(argc, argv);

    // initialize required objects
    DataRetriever dr;
    ImagesHandler *imagesHandler = ImagesHandler::Instance();
    imagesHandler->SetImagesPath(R"(C:\Users\Sergei\Documents\CLionProjects\IP\images)");

    ImageId imageId = SAMPLE_COLOR;
    QPixmap pixmap = imagesHandler->GetImageByImageId(imageId);
    //QPixmap pixmap = imagesHandler->GetImageViaFileDialog();

    int w = pixmap.width();
    int h = pixmap.height();
    QRgb *rgb = dr.RetrieveData(pixmap);

    // main logic
    dr = DataRetriever(GRAY, ProjectHelper::NormalizeStraight);
    double *data = dr.RetrieveData(rgb, w, h);
    ImageToProcess itp = ImageToProcess(GRAY, data, w, h, imagesHandler->GetImageNameById(imageId));
    itp.Save();
    auto *convolutionBuilder = new ConvolutionBuilder();
    convolutionBuilder
            ->WithImage(&itp)
            ->WithTool(new SequentialConvolutionTool)
            ->WithKernel(KernelsHandler::GetSobelX())
            ->Apply();
    delete convolutionBuilder;
    itp.Save(imagesHandler->GetImageNameById(imageId) + "_DERIVATIVE_X");
    return 0;
}

