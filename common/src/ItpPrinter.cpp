//
// Created by Sergei on 19.06.2020.
//



#include <common/headers/ItpPrinter.h>
#include <common/headers/ImageToProcess.h>

void ItpPrinter::Print(const ImageToProcess &itp) {
    ProjectHelper::PrintAsMatrix(itp._w, itp._h, itp._data);
}

void ItpPrinter::Print(const char *message, const ImageToProcess &itp) {
    qDebug() << message << endl;
    ProjectHelper::PrintAsMatrix(itp._w, itp._h, itp._data);
}
