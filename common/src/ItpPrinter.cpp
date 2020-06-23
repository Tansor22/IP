//
// Created by Sergei on 19.06.2020.
//



#include <common/headers/ItpPrinter.h>
#include <common/headers/ImageToProcess.h>

void ItpPrinter::Print(const ImageToProcess &itp) {
    //ProjectHelper::PrintAsMatrix(itp._w, itp._h, itp._data);
}

void ItpPrinter::Print(const string& message, const ImageToProcess &itp) {
    if (itp._name.rfind("SAMPLE", 0) == 0) {
        qDebug() << QString::fromStdString(message) << endl;
        // bug
        //ProjectHelper::PrintAsMatrix(itp._w, itp._h, ((GrayImage *&) itp)->_data);
    }
}
